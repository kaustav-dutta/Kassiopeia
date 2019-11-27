#ifndef KGeoBag_KGRotatedArcSegmentSurfaceAxialMesher_hh_
#define KGeoBag_KGRotatedArcSegmentSurfaceAxialMesher_hh_

#include "KGRotatedArcSegmentSurface.hh"

#include "KGSimpleAxialMesher.hh"

namespace KGeoBag
{
    class KGRotatedArcSegmentSurfaceAxialMesher :
        virtual public KGSimpleAxialMesher,
        public KGRotatedArcSegmentSurface::Visitor
    {
        public:
            using KGAxialMesherBase::VisitExtendedSurface;
            using KGAxialMesherBase::VisitExtendedSpace;

        public:
            KGRotatedArcSegmentSurfaceAxialMesher();
            ~KGRotatedArcSegmentSurfaceAxialMesher() override;

        protected:
            void VisitRotatedPathSurface( KGRotatedArcSegmentSurface* aRotatedArcSegmentSurface ) override;
    };

}

#endif
