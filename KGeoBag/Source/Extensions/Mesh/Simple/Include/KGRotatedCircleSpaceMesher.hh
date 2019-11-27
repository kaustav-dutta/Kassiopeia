#ifndef KGeoBag_KGRotatedCircleSpaceMesher_hh_
#define KGeoBag_KGRotatedCircleSpaceMesher_hh_

#include "KGRotatedCircleSpace.hh"

#include "KGSimpleMesher.hh"

namespace KGeoBag
{
    class KGRotatedCircleSpaceMesher :
        virtual public KGSimpleMesher,
        public KGRotatedCircleSpace::Visitor
    {
        public:
            using KGMesherBase::VisitExtendedSurface;
            using KGMesherBase::VisitExtendedSpace;

        public:
            KGRotatedCircleSpaceMesher();
            ~KGRotatedCircleSpaceMesher() override;

        protected:
            void VisitRotatedClosedPathSpace( KGRotatedCircleSpace* aRotatedCircleSpace ) override;
    };

}

#endif
