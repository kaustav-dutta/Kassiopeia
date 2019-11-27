#ifndef KGeoBag_KGExtrudedCircleSurfaceMesher_hh_
#define KGeoBag_KGExtrudedCircleSurfaceMesher_hh_

#include "KGExtrudedCircleSurface.hh"

#include "KGSimpleMesher.hh"

namespace KGeoBag
{
    class KGExtrudedCircleSurfaceMesher :
        virtual public KGSimpleMesher,
        public KGExtrudedCircleSurface::Visitor
    {
        public:
            using KGMesherBase::VisitExtendedSurface;
            using KGMesherBase::VisitExtendedSpace;

        public:
            KGExtrudedCircleSurfaceMesher();
            ~KGExtrudedCircleSurfaceMesher() override;

        protected:
            void VisitExtrudedPathSurface( KGExtrudedCircleSurface* aExtrudedCircleSurface ) override;
    };

}

#endif
