#ifndef KFMDenseBlockSparseMatrix_HH__
#define KFMDenseBlockSparseMatrix_HH__

#include "KSquareMatrix.hh"
#include "KEMChunkedFileInterface.hh"
#include "KEMSparseMatrixFileInterface.hh"
#include "KFMDenseBlockSparseMatrixStructure.hh"
#include "KFMMessaging.hh"

#include "KFMLinearAlgebraDefinitions.hh"
#include "KFMMatrixOperations.hh"
#include "KFMVectorOperations.hh"

namespace KEMField
{

/*
*
*@file KFMDenseBlockSparseMatrix.hh
*@class KFMDenseBlockSparseMatrix
*@brief responsible for evaluating the sparse 'near-field' component of the BEM matrix
*@details
*
*<b>Revision History:<b>
*Date Name Brief Description
*Wed Jan 29 14:53:59 EST 2014 J. Barrett (barrettj@mit.edu) First Version
*
*/

template< typename ValueType>
class KFMDenseBlockSparseMatrix: public KSquareMatrix< ValueType >
{
    public:

        KFMDenseBlockSparseMatrix(std::string unique_id, unsigned int verbosity = 0):
            fUniqueID(unique_id),
            fVerbosity(verbosity)
        {
            fZero = 0.0;
            fRowFileInterface = NULL;
            fColumnFileInterface = NULL;
            fElementFileInterface = NULL;
        };

        virtual ~KFMDenseBlockSparseMatrix()
        {
            delete fRowFileInterface;
            delete fColumnFileInterface;
            delete fElementFileInterface;
        };

        virtual unsigned int Dimension() const {return (unsigned int)fDimension;};

        static size_t GetSuggestedMatrixElementBufferSize()
        {
            size_t buff = KEMFIELD_SPARSE_MATRIX_BUFFER_SIZE_MB;
            buff *= 1024*1024/sizeof(ValueType);
            return buff;
        };

        size_t GetSuggestedIndexBufferSize() const
        {
            size_t buff = KEMFIELD_SPARSE_MATRIX_BUFFER_SIZE_MB;
            buff *= 1024*1024/sizeof(size_t);
            return buff;
        };

        static size_t GetSuggestedMaximumRowWidth() { return 1024;};

        virtual void Multiply(const KVector<ValueType>& x, KVector<ValueType>& y) const
        {
            //initialize y to zero
            for(size_t i=0; i<fDimension; i++)
            {
                y[i] = 0.0;
            }

            //must buffer rows, columns, and matrix elements from the disk
            size_t start_block_id;
            size_t n_blocks;
            size_t block_id;

            double mx_element;
            size_t row;
            size_t col;
            size_t row_size;
            size_t col_size;
            size_t row_offset;
            size_t col_offset;
            size_t element_offset;


            if(fIsSingleBuffer)
            {
                //add row, column, and matrix elements are in RAM
                start_block_id = fMatrixStructure.GetBufferStartBlockID(0);
                n_blocks = fMatrixStructure.GetBufferNumberOfBlocks(0);

                for(size_t n = 0; n < n_blocks; n++)
                {
                    //retrieve block information
                    block_id = n;
                    row_size = (*fRowSizes)[block_id];
                    col_size = (*fColumnSizes)[block_id];
                    row_offset = (*fRowOffsets)[block_id];
                    col_offset = (*fColumnOffsets)[block_id];
                    element_offset = (*fElementOffsets)[block_id];

                    //apply multiplication
                    for(size_t i=0; i<row_size; i++)
                    {
                        double temp = 0.0;
                        row = fRowIndices[row_offset+i];
                        for(size_t j=0; j<col_size; j++)
                        {
                            col = fColumnIndices[col_offset+j];
                            mx_element = fMatrixElements[element_offset + i*col_size + j];
                            temp += x(col)*mx_element;
                        }
                        y[row] += temp;
                    }
                }
            }
            else
            {
                fRowFileInterface->OpenFileForReading(fRowFileName);
                fColumnFileInterface->OpenFileForReading(fColumnFileName);
                fElementFileInterface->OpenFileForReading(fElementFileName);

                for(size_t buffer_id=0; buffer_id < fMatrixStructure.GetNBuffers(); buffer_id++)
                {
                    start_block_id = fMatrixStructure.GetBufferStartBlockID(buffer_id);
                    n_blocks = fMatrixStructure.GetBufferNumberOfBlocks(buffer_id);

                    fRowFileInterface->Read(fMatrixStructure.GetBufferRowIndexSize(buffer_id), &(fRowIndices[0]) );
                    fColumnFileInterface->Read(fMatrixStructure.GetBufferColumnIndexSize(buffer_id), &(fColumnIndices[0]) );
                    fElementFileInterface->Read(fMatrixStructure.GetBufferMatrixElementSize(buffer_id), &(fMatrixElements[0]) );

                    for(size_t n = 0; n < n_blocks; n++)
                    {
                        //retrieve block information
                        block_id = start_block_id + n;
                        row_size = (*fRowSizes)[block_id];
                        col_size = (*fColumnSizes)[block_id];
                        row_offset = (*fRowOffsets)[block_id];
                        col_offset = (*fColumnOffsets)[block_id];
                        element_offset = (*fElementOffsets)[block_id];

                        //apply multiplication
                        for(size_t i=0; i<row_size; i++)
                        {
                            double temp = 0.0;
                            row = fRowIndices[row_offset+i];
                            for(size_t j=0; j<col_size; j++)
                            {
                                col = fColumnIndices[col_offset+j];
                                mx_element = fMatrixElements[element_offset + i*col_size + j];
                                temp += x(col)*mx_element;
                            }
                            y[row] += temp;
                        }
                    }
                }

                fRowFileInterface->CloseFile();
                fColumnFileInterface->CloseFile();
                fElementFileInterface->CloseFile();
            }
        }


        //following function must be defined but it is not implemented
        virtual const ValueType& operator()(unsigned int,unsigned int) const
        {
            return fZero;
        }


        void Initialize()
        {
            //construct file names from unique id

            //DBSMSF = dense block sparse matrix structure file
            fStructureFileName = KFMDenseBlockSparseMatrixStructure::StructureFilePrefix;
            fStructureFileName += fUniqueID;
            fStructureFileName += KFMDenseBlockSparseMatrixStructure::StructureFilePostfix;

            //DBSMRF = dense block sparse matrix row file
            fRowFileName = KFMDenseBlockSparseMatrixStructure::RowFilePrefix;
            fRowFileName += fUniqueID;
            fRowFileName += KFMDenseBlockSparseMatrixStructure::RowFilePostfix;

            //DBSMCF = dense block sparse matrix column file
            fColumnFileName = KFMDenseBlockSparseMatrixStructure::ColumnFilePrefix;
            fColumnFileName += fUniqueID;
            fColumnFileName += KFMDenseBlockSparseMatrixStructure::ColumnFilePostfix;

            //DBSMEF = dense block sparse matrix element file
            fElementFileName = KFMDenseBlockSparseMatrixStructure::ElementFilePrefix;
            fElementFileName += fUniqueID;
            fElementFileName += KFMDenseBlockSparseMatrixStructure::ElementFilePostfix;

            //read the structure file from disk
            bool result = false;
            KSAObjectInputNode< KFMDenseBlockSparseMatrixStructure >* structure_node;
            structure_node = new KSAObjectInputNode<KFMDenseBlockSparseMatrixStructure>( KSAClassName<KFMDenseBlockSparseMatrixStructure>::name() );
            KEMFileInterface::GetInstance()->ReadKSAFileFromActiveDirectory(structure_node, fStructureFileName, result);

            if(result)
            {
                fMatrixStructure = *( structure_node->GetObject() );
                delete structure_node;
            }
            else
            {
                //error, abort
                delete structure_node;
                kfmout<<"KFMDenseBlockSparseMatrix::Initialize(): Error, structure file"<<fStructureFileName<<" corrupt or not present."<<kfmendl;
                kfmexit(1);
            }

            if(fVerbosity > 2)
            {
                kfmout<<"Sparse matrix component has "<<fMatrixStructure.GetNBlocks()<<" blocks. "<<kfmendl;
                kfmout<<"Sparse matrix has "<<fMatrixStructure.GetNTotalNonZeroElements()<<" non-zero elements."<<kfmendl;

                double fraction = fMatrixStructure.GetNTotalNonZeroElements();
                fraction /= ((double)fMatrixStructure.GetDimension())*((double)fMatrixStructure.GetDimension());

                kfmout<<"Sparse matrix percentage of full system is: "<<fraction*100<<"%."<<kfmendl;
                kfmout<<"Sparse matrix component is divided across "<<fMatrixStructure.GetNBuffers()<<" buffers. "<<kfmendl;
            }


            fDimension = fMatrixStructure.GetDimension();

            fRowSizes = fMatrixStructure.GetRowSizes();
            fColumnSizes = fMatrixStructure.GetColumnSizes();
            fNElements = fMatrixStructure.GetNElements();
            fRowOffsets = fMatrixStructure.GetRowOffsets();
            fColumnOffsets = fMatrixStructure.GetColumnOffsets();
            fElementOffsets = fMatrixStructure.GetMatrixElementOffsets();

            //prepare file interfaces
            fRowFileInterface = new KEMChunkedFileInterface();
            fColumnFileInterface = new KEMChunkedFileInterface();
            fElementFileInterface = new KEMChunkedFileInterface();

            //check that the row, column, and matrix element files exits
            bool row_exists = fRowFileInterface->DoesFileExist(fRowFileName);
            bool col_exists = fColumnFileInterface->DoesFileExist(fColumnFileName);
            bool elem_exists = fElementFileInterface->DoesFileExist(fElementFileName);

            if(!row_exists)
            {
                //abort, error
                delete fRowFileInterface;
                delete fColumnFileInterface;
                delete fElementFileInterface;
                kfmout<<"KFMDenseBlockSparseMatrix::Initialize(): Error, row file corrupt or not present."<<kfmendl;
                kfmout<<"Row file name = "<<fRowFileName<<kfmendl;
                kfmexit(1);
            }

            if(!col_exists)
            {
                //abort, error
                delete fRowFileInterface;
                delete fColumnFileInterface;
                delete fElementFileInterface;
                kfmout<<"KFMDenseBlockSparseMatrix::Initialize(): Error, column file corrupt or not present."<<kfmendl;
                kfmout<<"Column file name = "<<fColumnFileName<<kfmendl;
                kfmexit(1);
            }

            if(!elem_exists)
            {
                //abort, error
                delete fRowFileInterface;
                delete fColumnFileInterface;
                delete fElementFileInterface;
                kfmout<<"KFMDenseBlockSparseMatrix::Initialize(): Error, matrix element file corrupt or not present."<<kfmendl;
                kfmout<<"Element file name = "<<fElementFileName<<kfmendl;
                kfmexit(1);
            }

            //create the buffers needed to read the row, column and matrix elements
            if(fMatrixStructure.GetTotalNumberOfRowIndices() < fMatrixStructure.GetMaxIndexBufferSize() )
            {
                fRowIndices.resize(fMatrixStructure.GetTotalNumberOfRowIndices() + 1);
            }
            else
            {
                fRowIndices.resize(fMatrixStructure.GetMaxIndexBufferSize());
            }

            if(fMatrixStructure.GetTotalNumberOfColumnIndices() < fMatrixStructure.GetMaxIndexBufferSize() )
            {
                fColumnIndices.resize(fMatrixStructure.GetTotalNumberOfColumnIndices() + 1);
            }
            else
            {
                fColumnIndices.resize(fMatrixStructure.GetMaxIndexBufferSize());
            }

            if(fMatrixStructure.GetNTotalNonZeroElements() < fMatrixStructure.GetMaxMatrixElementBufferSize() )
            {
                fMatrixElements.resize(fMatrixStructure.GetNTotalNonZeroElements() + 1);
            }
            else
            {
                fMatrixElements.resize(fMatrixStructure.GetMaxMatrixElementBufferSize());
            }


            fIsSingleBuffer = false;
            if(fMatrixStructure.GetNBuffers() == 1)
            {
                //only need a single buffer read
                //so we load the rows, columns, and matrix elements into memory
                //otherwise these will be buffered/read when a matrix-vector product is performed
                fIsSingleBuffer = true;

                fRowFileInterface->OpenFileForReading(fRowFileName);
                fRowFileInterface->Read(fMatrixStructure.GetBufferRowIndexSize(0), &(fRowIndices[0]) );
                fRowFileInterface->CloseFile();

                fColumnFileInterface->OpenFileForReading(fColumnFileName);
                fColumnFileInterface->Read(fMatrixStructure.GetBufferColumnIndexSize(0), &(fColumnIndices[0]) );
                fColumnFileInterface->CloseFile();

                fElementFileInterface->OpenFileForReading(fElementFileName);
                fElementFileInterface->Read(fMatrixStructure.GetBufferMatrixElementSize(0), &(fMatrixElements[0]) );
                fElementFileInterface->CloseFile();
            }
        }

    protected:

        //data
        std::string fUniqueID;
        std::string fStructureFileName;
        std::string fRowFileName;
        std::string fColumnFileName;
        std::string fElementFileName;

        size_t fDimension;
        unsigned int fVerbosity;

        bool fIsSingleBuffer;

        KFMDenseBlockSparseMatrixStructure fMatrixStructure;

        KEMChunkedFileInterface* fRowFileInterface;
        KEMChunkedFileInterface* fColumnFileInterface;
        KEMChunkedFileInterface* fElementFileInterface;

        const std::vector<size_t>* fRowSizes;
        const std::vector<size_t>* fColumnSizes;
        const std::vector<size_t>* fNElements;
        const std::vector<size_t>* fRowOffsets;
        const std::vector<size_t>* fColumnOffsets;
        const std::vector<size_t>* fElementOffsets;

        mutable std::vector<size_t> fRowIndices;
        mutable std::vector<size_t> fColumnIndices;
        mutable std::vector<double> fMatrixElements;

        ValueType fZero;
};








}//end of KEMField namespace

#endif /* KFMDenseBlockSparseMatrix_H__ */
