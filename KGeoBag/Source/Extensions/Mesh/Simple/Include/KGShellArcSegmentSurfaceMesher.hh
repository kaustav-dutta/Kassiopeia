#ifndef KGeoBag_KGShellArcSegmentSurfaceMesher_hh_
#define KGeoBag_KGShellArcSegmentSurfaceMesher_hh_

#include "KGShellArcSegmentSurface.hh"

#include "KGSimpleMesher.hh"

namespace KGeoBag
{
    class KGShellArcSegmentSurfaceMesher :
        virtual public KGSimpleMesher,
        public KGShellArcSegmentSurface::Visitor
    {
        public:
            using KGMesherBase::VisitExtendedSurface;
            using KGMesherBase::VisitExtendedSpace;

        public:
            KGShellArcSegmentSurfaceMesher();
            ~KGShellArcSegmentSurfaceMesher() override;

        protected:
            void VisitShellPathSurface( KGShellArcSegmentSurface* aShellArcSegmentSurface ) override;
    };

}

#endif
