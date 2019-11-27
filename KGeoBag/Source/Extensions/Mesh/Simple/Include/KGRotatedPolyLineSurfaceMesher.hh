#ifndef KGeoBag_KGRotatedPolyLineSurfaceMesher_hh_
#define KGeoBag_KGRotatedPolyLineSurfaceMesher_hh_

#include "KGRotatedPolyLineSurface.hh"

#include "KGSimpleMesher.hh"

namespace KGeoBag
{
    class KGRotatedPolyLineSurfaceMesher :
        virtual public KGSimpleMesher,
        public KGRotatedPolyLineSurface::Visitor
    {
        public:
            using KGMesherBase::VisitExtendedSurface;
            using KGMesherBase::VisitExtendedSpace;

        public:
            KGRotatedPolyLineSurfaceMesher();
            ~KGRotatedPolyLineSurfaceMesher() override;

        protected:
            void VisitRotatedPathSurface( KGRotatedPolyLineSurface* aRotatedPolyLineSurface ) override;
    };

}

#endif
