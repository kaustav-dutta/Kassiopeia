#ifndef KGeoBag_KGCylinderMesher_hh_
#define KGeoBag_KGCylinderMesher_hh_

#include "KGCylinder.hh"

#include "KGComplexMesher.hh"

namespace KGeoBag
{
    class KGCylinderMesher :
        virtual public KGComplexMesher,
        public KGCylinder::Visitor
    {
        public:
            using KGMesherBase::VisitExtendedSurface;
            using KGMesherBase::VisitExtendedSpace;

        public:
            KGCylinderMesher()
            {
            }
            ~KGCylinderMesher() override
            {
            }

        protected:
            void VisitCylinder( KGCylinder* cylinder ) override;
    };

}

#endif
