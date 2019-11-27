#ifndef KGeoBag_KGRotatedPolyLoopSurfaceMesher_hh_
#define KGeoBag_KGRotatedPolyLoopSurfaceMesher_hh_

#include "KGRotatedPolyLoopSurface.hh"

#include "KGSimpleMesher.hh"

namespace KGeoBag
{
    class KGRotatedPolyLoopSurfaceMesher :
        virtual public KGSimpleMesher,
        public KGRotatedPolyLoopSurface::Visitor
    {
        public:
            using KGMesherBase::VisitExtendedSurface;
            using KGMesherBase::VisitExtendedSpace;

        public:
            KGRotatedPolyLoopSurfaceMesher();
            ~KGRotatedPolyLoopSurfaceMesher() override;

        protected:
            void VisitRotatedPathSurface( KGRotatedPolyLoopSurface* aRotatedPolyLoopSurface ) override;
    };

}

#endif
