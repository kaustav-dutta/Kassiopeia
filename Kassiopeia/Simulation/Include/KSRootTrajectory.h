#ifndef Kassiopeia_KSRootTrajectory_h_
#define Kassiopeia_KSRootTrajectory_h_

#include "KSTrajectory.h"
#include "KSStep.h"

namespace Kassiopeia
{

    class KSStep;

    class KSRootTrajectory :
        public KSComponentTemplate< KSRootTrajectory, KSTrajectory >
    {
        public:
            KSRootTrajectory();
            KSRootTrajectory( const KSRootTrajectory& aCopy );
            KSRootTrajectory* Clone() const override;
            ~KSRootTrajectory() override;

            //**********
            //trajectory
            //**********

        public:

            void Reset() override
            {
                if(fTrajectory != nullptr){ fTrajectory->Reset(); }
                fFailureFlag = false;
            };
            void CalculateTrajectory( const KSParticle& anInitialParticle, KSParticle& aFinalParticle, KThreeVector& aCenter, double& aRadius, double& aTimeStep ) override;

            bool Check() const {return fFailureFlag;};

            void ExecuteTrajectory( const double& aTimeStep, KSParticle& anIntermediateParticle ) const override;
            void GetPiecewiseLinearApproximation(const KSParticle& anInitialParticle, const KSParticle& aFinalParticle, std::vector< KSParticle >* intermediateParticleStates ) const override;
            //***********
            //composition
            //***********

        public:
            void SetTrajectory( KSTrajectory* aTrajectory );
            void ClearTrajectory( KSTrajectory* aTrajectory );

        private:
            KSTrajectory* fTrajectory;

            //******
            //action
            //******

        public:
            void SetStep( KSStep* anStep );

            void CalculateTrajectory();
            void ExecuteTrajectory();

        private:
            KSStep* fStep;
            const KSParticle* fTerminatorParticle;
            KSParticle* fTrajectoryParticle;
            KSParticle* fFinalParticle;
            bool fFailureFlag;
    };

}

#endif
