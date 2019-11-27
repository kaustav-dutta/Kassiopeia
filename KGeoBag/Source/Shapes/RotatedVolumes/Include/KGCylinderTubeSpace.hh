#ifndef KGCYLINDERTUBESPACE_HH_
#define KGCYLINDERTUBESPACE_HH_

#include "KGRotatedPolyLoopSpace.hh"

namespace KGeoBag
{

    class KGCylinderTubeSpace :
        public KGRotatedPolyLoopSpace
    {
        public:
            KGCylinderTubeSpace();
            ~KGCylinderTubeSpace() override;

        public:
            void Z1( const double& aZ1 );
            void Z2( const double& aZ2 );
            void R1( const double& anR1 );
            void R2( const double& anR2 );
            void LongitudinalMeshCount( const unsigned int& aLongitudinalMeshCount );
            void LongitudinalMeshPower( const double& aLongitudinalMeshPower );
            void RadialMeshCount( const unsigned int& aRadialMeshCount );
            void RadialMeshPower( const double& aRadialMeshPower );
            void AxialMeshCount( const unsigned int& anAxialMeshCount );

            const double& Z1() const;
            const double& Z2() const;
            const double& R1() const;
            const double& R2() const;
            const unsigned int& LongitudinalMeshCount() const;
            const double& LongitudinalMeshPower() const;
            const unsigned int& RadialMeshCount() const;
            const double& RadialMeshPower() const;
            const unsigned int& AxialMeshCount() const;

        private:
            double fZ1;
            double fZ2;
            double fR1;
            double fR2;
            unsigned int fLongitudinalMeshCount;
            double fLongitudinalMeshPower;
            unsigned int fRadialMeshCount;
            double fRadialMeshPower;
            unsigned int fAxialMeshCount;

        public:
            class Visitor
            {
                public:
                    Visitor();
                    virtual ~Visitor();

                    virtual void VisitCylinderTubeSpace( KGCylinderTubeSpace* aCylinderTubeSpace ) = 0;
            };

        public:
            void VolumeInitialize( BoundaryContainer& aBoundaryContainer ) const override;
            void VolumeAccept( KGVisitor* aVisitor ) override;
    };

}

#endif
