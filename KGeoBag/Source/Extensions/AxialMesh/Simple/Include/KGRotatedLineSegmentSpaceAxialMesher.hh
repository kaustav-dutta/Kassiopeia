#ifndef KGeoBag_KGRotatedLineSegmentSpaceAxialMesher_hh_
#define KGeoBag_KGRotatedLineSegmentSpaceAxialMesher_hh_

#include "KGRotatedLineSegmentSpace.hh"

#include "KGSimpleAxialMesher.hh"

namespace KGeoBag
{
    class KGRotatedLineSegmentSpaceAxialMesher :
        virtual public KGSimpleAxialMesher,
        public KGRotatedLineSegmentSpace::Visitor
    {
        public:
            using KGAxialMesherBase::VisitExtendedSurface;
            using KGAxialMesherBase::VisitExtendedSpace;

        public:
            KGRotatedLineSegmentSpaceAxialMesher();
            ~KGRotatedLineSegmentSpaceAxialMesher() override;

        protected:
            void VisitRotatedOpenPathSpace( KGRotatedLineSegmentSpace* aRotatedLineSegmentSpace ) override;
    };

}

#endif
