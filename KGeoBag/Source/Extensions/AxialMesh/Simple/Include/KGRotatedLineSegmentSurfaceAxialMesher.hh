#ifndef KGeoBag_KGRotatedLineSegmentSurfaceAxialMesher_hh_
#define KGeoBag_KGRotatedLineSegmentSurfaceAxialMesher_hh_

#include "KGRotatedLineSegmentSurface.hh"

#include "KGSimpleAxialMesher.hh"

namespace KGeoBag
{
    class KGRotatedLineSegmentSurfaceAxialMesher :
        virtual public KGSimpleAxialMesher,
        public KGRotatedLineSegmentSurface::Visitor
    {
        public:
            using KGAxialMesherBase::VisitExtendedSurface;
            using KGAxialMesherBase::VisitExtendedSpace;

        public:
            KGRotatedLineSegmentSurfaceAxialMesher();
            ~KGRotatedLineSegmentSurfaceAxialMesher() override;

        protected:
            void VisitRotatedPathSurface( KGRotatedLineSegmentSurface* aRotatedLineSegmentSurface ) override;
    };

}

#endif
