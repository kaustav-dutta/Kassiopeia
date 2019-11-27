#ifndef KGeoBag_KGRotatedPolyLineSpaceAxialMesher_hh_
#define KGeoBag_KGRotatedPolyLineSpaceAxialMesher_hh_

#include "KGRotatedPolyLineSpace.hh"

#include "KGSimpleAxialMesher.hh"

namespace KGeoBag
{
    class KGRotatedPolyLineSpaceAxialMesher :
        virtual public KGSimpleAxialMesher,
        public KGRotatedPolyLineSpace::Visitor
    {
        public:
            using KGAxialMesherBase::VisitExtendedSurface;
            using KGAxialMesherBase::VisitExtendedSpace;

        public:
            KGRotatedPolyLineSpaceAxialMesher();
            ~KGRotatedPolyLineSpaceAxialMesher() override;

        protected:
            void VisitRotatedOpenPathSpace( KGRotatedPolyLineSpace* aRotatedPolyLineSpace ) override;
    };

}

#endif
