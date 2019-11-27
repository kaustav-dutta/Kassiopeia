#ifndef KGeoBag_KGRotatedCircleSurfaceAxialMesher_hh_
#define KGeoBag_KGRotatedCircleSurfaceAxialMesher_hh_

#include "KGRotatedCircleSurface.hh"

#include "KGSimpleAxialMesher.hh"

namespace KGeoBag
{
    class KGRotatedCircleSurfaceAxialMesher :
        virtual public KGSimpleAxialMesher,
        public KGRotatedCircleSurface::Visitor
    {
        public:
            using KGAxialMesherBase::VisitExtendedSurface;
            using KGAxialMesherBase::VisitExtendedSpace;

        public:
            KGRotatedCircleSurfaceAxialMesher();
            ~KGRotatedCircleSurfaceAxialMesher() override;

        protected:
            void VisitRotatedPathSurface( KGRotatedCircleSurface* aRotatedCircleSurface ) override;
    };

}

#endif
