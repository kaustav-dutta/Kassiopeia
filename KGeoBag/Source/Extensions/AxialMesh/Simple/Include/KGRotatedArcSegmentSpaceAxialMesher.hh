#ifndef KGeoBag_KGRotatedArcSegmentSpaceAxialMesher_hh_
#define KGeoBag_KGRotatedArcSegmentSpaceAxialMesher_hh_

#include "KGRotatedArcSegmentSpace.hh"

#include "KGSimpleAxialMesher.hh"

namespace KGeoBag
{
    class KGRotatedArcSegmentSpaceAxialMesher :
        virtual public KGSimpleAxialMesher,
        public KGRotatedArcSegmentSpace::Visitor
    {
        public:
            using KGAxialMesherBase::VisitExtendedSurface;
            using KGAxialMesherBase::VisitExtendedSpace;

        public:
            KGRotatedArcSegmentSpaceAxialMesher();
            ~KGRotatedArcSegmentSpaceAxialMesher() override;

        protected:
            void VisitRotatedOpenPathSpace( KGRotatedArcSegmentSpace* aRotatedArcSegmentSpace ) override;
    };

}

#endif
