#ifndef KGeoBag_KGRotatedCircleSurfaceMesher_hh_
#define KGeoBag_KGRotatedCircleSurfaceMesher_hh_

#include "KGRotatedCircleSurface.hh"

#include "KGSimpleMesher.hh"

namespace KGeoBag
{
    class KGRotatedCircleSurfaceMesher :
        virtual public KGSimpleMesher,
        public KGRotatedCircleSurface::Visitor
    {
        public:
            using KGMesherBase::VisitExtendedSurface;
            using KGMesherBase::VisitExtendedSpace;

        public:
            KGRotatedCircleSurfaceMesher();
            ~KGRotatedCircleSurfaceMesher() override;

        protected:
            void VisitRotatedPathSurface( KGRotatedCircleSurface* aRotatedCircleSurface ) override;
    };

}

#endif
