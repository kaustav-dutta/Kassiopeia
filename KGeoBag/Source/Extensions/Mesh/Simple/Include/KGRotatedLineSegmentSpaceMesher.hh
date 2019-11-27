#ifndef KGeoBag_KGRotatedLineSegmentSpaceMesher_hh_
#define KGeoBag_KGRotatedLineSegmentSpaceMesher_hh_

#include "KGRotatedLineSegmentSpace.hh"

#include "KGSimpleMesher.hh"

namespace KGeoBag
{
    class KGRotatedLineSegmentSpaceMesher :
        virtual public KGSimpleMesher,
        public KGRotatedLineSegmentSpace::Visitor
    {
        public:
            using KGMesherBase::VisitExtendedSurface;
            using KGMesherBase::VisitExtendedSpace;

        public:
            KGRotatedLineSegmentSpaceMesher();
            ~KGRotatedLineSegmentSpaceMesher() override;

        protected:
            void VisitRotatedOpenPathSpace( KGRotatedLineSegmentSpace* aRotatedLineSegmentSpace ) override;
    };

}

#endif
