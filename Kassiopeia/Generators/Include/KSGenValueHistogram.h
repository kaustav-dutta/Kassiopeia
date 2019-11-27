#ifndef Kassiopeia_KSGenValueHistogram_h_
#define Kassiopeia_KSGenValueHistogram_h_

#include "KSGenValue.h"

#include "KField.h"

#include "KFile.h"
using katrin::KFile;

#include "KRootFile.h"
using katrin::KRootFile;

#include "TH1.h"
#include "TF1.h"

namespace Kassiopeia
{
    class KSGenValueHistogram :
        public KSComponentTemplate< KSGenValueHistogram, KSGenValue >
    {
        public:
            KSGenValueHistogram();
            KSGenValueHistogram( const KSGenValueHistogram& aCopy );
            KSGenValueHistogram* Clone() const override;
            ~KSGenValueHistogram() override;

        public:
            void DiceValue( std::vector< double >& aDicedValues ) override;

        public:
            ;K_SET_GET( std::string, Base );
            ;K_SET_GET( std::string, Path );
            ;K_SET_GET( std::string, Histogram );
            ;K_SET_GET( std::string, Formula );

        public:
            void InitializeComponent() override;
            void DeinitializeComponent() override;

        private:
            KRootFile* fRootFile;
            TH1* fValueHistogram;
            TF1* fValueFunction;
    };

}

#endif
