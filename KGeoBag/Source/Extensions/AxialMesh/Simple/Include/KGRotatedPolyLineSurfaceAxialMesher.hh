#ifndef KGeoBag_KGRotatedPolyLineSurfaceAxialMesher_hh_
#define KGeoBag_KGRotatedPolyLineSurfaceAxialMesher_hh_

#include "KGRotatedPolyLineSurface.hh"

#include "KGSimpleAxialMesher.hh"

namespace KGeoBag
{
    class KGRotatedPolyLineSurfaceAxialMesher :
        virtual public KGSimpleAxialMesher,
        public KGRotatedPolyLineSurface::Visitor
    {
        public:
            using KGAxialMesherBase::VisitExtendedSurface;
            using KGAxialMesherBase::VisitExtendedSpace;

        public:
            KGRotatedPolyLineSurfaceAxialMesher();
            ~KGRotatedPolyLineSurfaceAxialMesher() override;

        protected:
            void VisitRotatedPathSurface( KGRotatedPolyLineSurface* aRotatedPolyLineSurface ) override;
    };

}

#endif
