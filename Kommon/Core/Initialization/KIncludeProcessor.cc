#include "KIncludeProcessor.hh"
#include "KInitializationMessage.hh"

#include "KFile.h"
using katrin::KFile;

#include "KTextFile.h"
using katrin::KTextFile;

#include "KXMLTokenizer.hh"

#include <cstdlib>
#include <algorithm>

using namespace std;

namespace katrin
{

    KIncludeProcessor::KIncludeProcessor() :
        KProcessor(),
        fElementState( eElementInactive ),
        fAttributeState( eAttributeInactive ),
        fOptionalFlag(false),
        fNames(),
        fPaths(),
        fBases(),
        fIncludedPaths()
    {
    }

    KIncludeProcessor::~KIncludeProcessor()
    {
    }

    void KIncludeProcessor::SetPath(const string& path)
    {
        fDefaultPath = path;
    }

    void KIncludeProcessor::AddDefaultPath(const string& path)
    {
        if ( find(fAdditionalDefaultPaths.begin(), fAdditionalDefaultPaths.end(), path) == fAdditionalDefaultPaths.end() )
            fAdditionalDefaultPaths.push_back( path );
    }

    void KIncludeProcessor::ProcessToken( KBeginElementToken* aToken )
    {
        if( fElementState == eElementInactive )
        {
            if( aToken->GetValue() == "include" )
            {
                fElementState = eActive;
                return;
            }
            KProcessor::ProcessToken( aToken );
            return;
        }

        if( fElementState == eActive )
        {
            initmsg( eError ) << "got unknown element <" << aToken->GetValue() << ">" << ret;
            initmsg( eError ) << "in path <" << aToken->GetPath() << "in file <" << aToken->GetFile() << "> at line <" << aToken->GetLine() << ">, column <" << aToken->GetColumn() << ">" << eom;
            return;
        }

        return;
    }

    void KIncludeProcessor::ProcessToken( KBeginAttributeToken* aToken )
    {

        if( fElementState == eElementInactive )
        {
            KProcessor::ProcessToken( aToken );
            return;
        }

        if( fElementState == eActive )
        {
            if( aToken->GetValue() == "name" )
            {
                fAttributeState = eName;
                return;
            }
            if( aToken->GetValue() == "path" )
            {
                fAttributeState = ePath;
                return;
            }
            if( aToken->GetValue() == "base" )
            {
                fAttributeState = eBase;
                return;
            }
            if( aToken->GetValue() == "optional" )
            {
                fAttributeState = eOptionalFlag;
                return;
            }

            initmsg( eError ) << "got unknown attribute <" << aToken->GetValue() << ">" << ret;
            initmsg( eError ) << "in path <" << aToken->GetPath() << "in file <" << aToken->GetFile() << "> at line <" << aToken->GetLine() << ">, column <" << aToken->GetColumn() << ">" << eom;
            return;
        }

        return;
    }

    void KIncludeProcessor::ProcessToken( KAttributeDataToken* aToken )
    {
        if( fElementState == eElementInactive )
        {
            KProcessor::ProcessToken( aToken );
            return;
        }

        if( fElementState == eActive )
        {

            if( fAttributeState == eName )
            {
                fNames.push_back( aToken->GetValue() );
                fAttributeState = eAttributeComplete;
                return;
            }

            if( fAttributeState == ePath )
            {
                fPaths.push_back( aToken->GetValue() );
                fAttributeState = eAttributeComplete;
                return;
            }

            if( fAttributeState == eBase )
            {
                fBases.push_back( aToken->GetValue() );
                fAttributeState = eAttributeComplete;
                return;
            }

            if( fAttributeState == eOptionalFlag )
            {
                fOptionalFlag = aToken->GetValue<bool>();
                fAttributeState = eAttributeComplete;
                return;
            }
        }

        return;
    }

    void KIncludeProcessor::ProcessToken( KEndAttributeToken* aToken )
    {
        if( fElementState == eElementInactive )
        {
            KProcessor::ProcessToken( aToken );
            return;
        }

        if( fElementState == eActive )
        {
            if( fAttributeState == eAttributeComplete )
            {
                fAttributeState = eAttributeInactive;
                return;
            }
        }

        return;
    }

    void KIncludeProcessor::ProcessToken( KMidElementToken* aToken )
    {
        if( fElementState == eElementInactive )
        {
            KProcessor::ProcessToken( aToken );
            return;
        }

        if( fElementState == eActive )
        {
            fElementState = eElementComplete;
            return;
        }

        return;
    }

    void KIncludeProcessor::ProcessToken( KElementDataToken* aToken )
    {
        if( fElementState == eElementInactive )
        {
            KProcessor::ProcessToken( aToken );
            return;
        }

        if( fElementState == eElementComplete )
        {
            initmsg( eError ) << "got unknown element data <" << aToken->GetValue() << ">" << ret;
            initmsg( eError ) << "in path <" << aToken->GetPath() << "in file <" << aToken->GetFile() << "> at line <" << aToken->GetLine() << ">, column <" << aToken->GetColumn() << ">" << eom;
            return;
        }

        return;
    }

    void KIncludeProcessor::ProcessToken( KEndElementToken* aToken )
    {
        if( fElementState == eElementInactive )
        {
            KProcessor::ProcessToken( aToken );
            return;
        }

        if( fElementState == eElementComplete )
        {
            auto* aFile = new KTextFile();
            aFile->SetDefaultPath( CONFIG_DEFAULT_DIR );

            for( const string& name : fNames )
                aFile->AddToNames( name );

            for( const string& path : fPaths )
                aFile->AddToPaths( path );

            aFile->AddToPaths( fDefaultPath );
            for( const string& defaultPath : fAdditionalDefaultPaths )
                aFile->AddToPaths( defaultPath );

            for( const string& base : fBases )
                aFile->AddToBases( base );

            bool HasFile = aFile->Open( KFile::eRead );
            if( HasFile == false )
            {
                delete aFile;

                if (fOptionalFlag == false)
                {
                    initmsg( eError ) << "unable to open include file <" << fBases.front() << ">" << eom;
                }
            }

            fElementState = eElementInactive;
            fOptionalFlag = false;
            fNames.clear();
            fPaths.clear();
            fBases.clear();

            if( HasFile == true )
            {
                std::string tFileName = aFile->GetName();
                if ( std::find( fIncludedPaths.begin(), fIncludedPaths.end(), tFileName ) != fIncludedPaths.end() )
                {
                    initmsg( eWarning ) << "skipping file <" << tFileName << "> since it was already included" << eom;
                }
                else
                {
                    bool usingDefaultPath = (std::find(fAdditionalDefaultPaths.begin(), fAdditionalDefaultPaths.end(), aFile->GetPath()) != fAdditionalDefaultPaths.end());
                    if (usingDefaultPath) {
                        initmsg( eWarning ) << "using default include file <" << tFileName << ">" << eom;
                    }

                    initmsg( eInfo ) << "including file <" << tFileName << ">" << eom;
                    fIncludedPaths.push_back( tFileName );

                    auto* aNewTokenizer = new KXMLTokenizer();
                    aNewTokenizer->InsertBefore( GetFirstParent() );
                    aNewTokenizer->ProcessFile( aFile );
                    aNewTokenizer->Remove();

                    delete aNewTokenizer;
                }

                delete aFile;
            }
        }

        return;
    }
}
