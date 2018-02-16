/*
 * KFMVTKElectrostaticTreeViewerBuilder.hh
 *
 *  Created on:
 *      Author:
 */

#ifndef KEMFIELD_SOURCE_2_0_PLUGINS_BINDINGS_FIELDSOLVERS_ELECTRIC_INCLUDE_KFMVTKELECTROSTATICTREEVIEWERBUILDER_HH_
#define KEMFIELD_SOURCE_2_0_PLUGINS_BINDINGS_FIELDSOLVERS_ELECTRIC_INCLUDE_KFMVTKELECTROSTATICTREEVIEWERBUILDER_HH_

#include "KFMVTKElectrostaticTreeViewer.hh"
#include "KComplexElement.hh"

namespace KEMField {

class KFMVTKElectrostaticTreeViewerData
{
    public:
        std::string fFileName;
        //bool fViewGeometry;
        bool fSaveGeometry;
};

}

namespace katrin {

typedef KComplexElement<KEMField::KFMVTKElectrostaticTreeViewerData>
KFMVTKElectrostaticTreeViewerBuilder;

template< >
inline bool KFMVTKElectrostaticTreeViewerBuilder::Begin()
{
    fObject = new KEMField::KFMVTKElectrostaticTreeViewerData;
    return true;
}

template< >
inline bool KFMVTKElectrostaticTreeViewerBuilder::AddAttribute( KContainer* aContainer )
{
    if( aContainer->GetName() == "file" )
    {
        aContainer->CopyTo( fObject->fFileName );
        return true;
    }
    if( aContainer->GetName() == "save" )
    {
        aContainer->CopyTo( fObject->fSaveGeometry );
        return true;
    }
    return false;
}

template< >
inline bool KFMVTKElectrostaticTreeViewerBuilder::End()
{
    KEMField::KFMElectrostaticTree *tTree = dynamic_cast<KEMField::KFMElectrostaticTree*>(fParentElement);

    KEMField::KFMVTKElectrostaticTreeViewer *tViewer = new KEMField::KFMVTKElectrostaticTreeViewer(*tTree);

    if (fObject->fSaveGeometry)
    {
        tViewer->GenerateGeometryFile(fObject->fFileName);
    }

    delete tViewer;
    return true;
}

} /* namespace katrin */

#endif /* KEMFIELD_SOURCE_2_0_PLUGINS_BINDINGS_FIELDSOLVERS_ELECTRIC_INCLUDE_KFMVTKELECTROSTATICTREEVIEWERBUILDER_HH_ */
