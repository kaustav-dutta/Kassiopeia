#include "KGCoreMessage.hh"
#include "KGInterfaceBuilder.hh"
#include "KGAxialMesher.hh"
#include "KGVTKAxialMeshPainter.hh"

#include "KMessage.h"
#include "KTextFile.h"
#include "KCommandLineTokenizer.hh"
#include "KXMLTokenizer.hh"
#include "KVariableProcessor.hh"
#include "KIncludeProcessor.hh"
#include "KLoopProcessor.hh"
#include "KConditionProcessor.hh"
#include "KPrintProcessor.hh"
#include "KElementProcessor.hh"
#include "KTagProcessor.hh"
#include "KVTKWindow.h"

#ifdef KGeoBag_USE_ROOT
#include "KFormulaProcessor.hh"
#endif

using namespace KGeoBag;
using namespace katrin;
using namespace std;

int main( int argc, char** argv )
{
    if( argc < 3 )
    {
        cout << "usage: ./AxialMeshViewer <config_file_name.xml> <geometry_path> [...]" << endl;
        return -1;
    }

    string tFileName( argv[ 1 ] );
    vector<string> tPathList;
    for (int i = 2; i < argc; i++ )
        tPathList.push_back( argv[ i ] );

    KCommandLineTokenizer tCommandLine;
    tCommandLine.ProcessCommandLine( argc, argv );

    KXMLTokenizer tTokenizer;
    KVariableProcessor tVariableProcessor( tCommandLine.GetVariables() );
    KIncludeProcessor tIncludeProcessor;
    KLoopProcessor tLoopProcessor;
    KConditionProcessor tConditionProcessor;
    KPrintProcessor tPrintProcessor;
    KTagProcessor tTagProcessor;
    KElementProcessor tElementProcessor;

    tVariableProcessor.InsertAfter( &tTokenizer );
    tIncludeProcessor.InsertAfter( &tVariableProcessor );

  #ifdef KGeoBag_USE_ROOT
  	KFormulaProcessor tFormulaProcessor;
  	tFormulaProcessor.InsertAfter( &tVariableProcessor );
  	tIncludeProcessor.InsertAfter( &tFormulaProcessor );
  #endif

    tLoopProcessor.InsertAfter( &tIncludeProcessor );
    tConditionProcessor.InsertAfter( &tLoopProcessor );
    tPrintProcessor.InsertAfter( &tConditionProcessor );
    tTagProcessor.InsertAfter( &tPrintProcessor );
    tElementProcessor.InsertAfter( &tTagProcessor );

    coremsg( eNormal ) << "starting initialization..." << eom;

    KTextFile tFile;
    tFile.SetDefaultPath( CONFIG_DEFAULT_DIR );
    tFile.AddToNames( tFileName );
    tTokenizer.ProcessFile( &tFile );

    coremsg( eNormal ) << "...initialization finished" << eom;

    KVTKWindow tWindow;
    tWindow.SetName( "KGeoBag Axial Mesh Viewer" );
    tWindow.SetFrameColorRed( 0. );
    tWindow.SetFrameColorGreen( 0. );
    tWindow.SetFrameColorBlue( 0. );
    tWindow.SetDisplayMode( true );
    tWindow.SetWriteMode( true );

    KGAxialMesher tMesher;

    KGVTKAxialMeshPainter tPainter;
    tPainter.SetName( "AxialMeshPainter" );
    tPainter.SetDisplayMode( true );
    tPainter.SetWriteMode( true );
    tPainter.SetColorMode( KGVTKAxialMeshPainter::sArea );

    for (auto & tPath : tPathList) {
        for (auto & tSurface : KGInterface::GetInstance()->RetrieveSurfaces( tPath ) ) {
            tSurface->MakeExtension< KGAxialMesh >();
            tSurface->AcceptNode( &tMesher );
            tSurface->AcceptNode( &tPainter );
        }
        for (auto & tSpace : KGInterface::GetInstance()->RetrieveSpaces( tPath ) ) {
            tSpace->MakeExtension< KGAxialMesh >();
            tSpace->AcceptNode( &tMesher );
            tSpace->AcceptNode( &tPainter );
        }
    }

    tWindow.AddPainter( &tPainter );
    tWindow.Render();
    tWindow.Write();
    tWindow.Display();
    tWindow.RemovePainter( &tPainter );

    return 0;
}
