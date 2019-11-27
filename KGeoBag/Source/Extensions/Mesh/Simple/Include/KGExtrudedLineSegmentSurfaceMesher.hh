#ifndef KGeoBag_KGExtrudedLineSegmentSurfaceMesher_hh_
#define KGeoBag_KGExtrudedLineSegmentSurfaceMesher_hh_

#include "KGExtrudedLineSegmentSurface.hh"

#include "KGSimpleMesher.hh"

namespace KGeoBag
{
    class KGExtrudedLineSegmentSurfaceMesher :
        virtual public KGSimpleMesher,
        public KGExtrudedLineSegmentSurface::Visitor
    {
        public:
            using KGMesherBase::VisitExtendedSurface;
            using KGMesherBase::VisitExtendedSpace;

        public:
            KGExtrudedLineSegmentSurfaceMesher();
            ~KGExtrudedLineSegmentSurfaceMesher() override;

        protected:
            void VisitExtrudedPathSurface( KGExtrudedLineSegmentSurface* aExtrudedLineSegmentSurface ) override;
    };

}

#endif
