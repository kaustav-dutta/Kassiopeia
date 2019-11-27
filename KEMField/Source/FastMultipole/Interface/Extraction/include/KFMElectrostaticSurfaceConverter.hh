#ifndef KFMElectrostaticSurfaceConverter_HH__
#define KFMElectrostaticSurfaceConverter_HH__


#include "KSurfaceContainer.hh"
#include "KSortedSurfaceContainer.hh"

#include "KFMBasisData.hh"
#include "KFMPointCloud.hh"
#include "KFMIdentityPair.hh"
#include "KFMObjectContainer.hh"
#include "KFMElectrostaticElement.hh"
#include "KFMElectrostaticElementContainerBase.hh"

#include "KFMSurfaceToPointCloudConverter.hh"
#include "KFMPointCloudToBoundingBallConverter.hh"
#include "KFMElectrostaticBasisDataExtractor.hh"
#include "KFMElementAspectRatioExtractor.hh"

#include "KVector.hh"

#include <iostream>

namespace KEMField
{

/*
*
*@file KFMElectrostaticSurfaceConverter.hh
*@class KFMElectrostaticSurfaceConverter
*@brief
*@details
*
*<b>Revision History:<b>
*Date Name Brief Description
*Mon Aug 26 13:31:39 CEST 2013 J. Barrett (barrettj@mit.edu) First Version
*
*/


class KFMElectrostaticSurfaceConverter
{
    public:

        KFMElectrostaticSurfaceConverter()
        {
            fSurfaceContainer = nullptr;
            fSortedSurfaceContainer = nullptr;
            fContainerIsSorted = false;
            fElectrostaticElementContainer = nullptr;
        };

        virtual ~KFMElectrostaticSurfaceConverter(){};

        void SetSurfaceContainer(const KSurfaceContainer* container);
        void SetSortedSurfaceContainer( const KSortedSurfaceContainer* container);

        void SetElectrostaticElementContainer(KFMElectrostaticElementContainerBase<3,1>* container);

        void Extract();

        void UpdateBasisData();

        void UpdateBasisData(const KVector<double>& x);

    private:

        const KSurfaceContainer* fSurfaceContainer;
        const KSortedSurfaceContainer* fSortedSurfaceContainer;
        bool fContainerIsSorted;

        KFMSurfaceToPointCloudConverter fPointCloudGenerator;
        KFMPointCloudToBoundingBallConverter<3> fBoundingBallGenerator;
        KFMElectrostaticBasisDataExtractor fBasisExtractor;
        KFMElementAspectRatioExtractor fAspectRatioExtractor;

        KFMPointCloud<3> fTempPointCloud;
        KFMPoint<3> fCentroid;
        KFMElectrostaticElement<3,1> fTempElement;
        KFMElectrostaticElementContainerBase<3,1>* fElectrostaticElementContainer;

};




}//end of KEMField

#endif /* KFMElectrostaticSurfaceConverter_H__ */
