#ifndef Kassiopeia_KSRootSpaceNavigator_h_
#define Kassiopeia_KSRootSpaceNavigator_h_

#include "KSSpaceNavigator.h"
#include "KSList.h"

#include "KSStep.h"
#include "KSTrajectory.h"

#include "KMathBracketingSolver.h"
using katrin::KMathBracketingSolver;

namespace Kassiopeia
{

    class KSRootSpaceNavigator :
        public KSComponentTemplate< KSRootSpaceNavigator, KSSpaceNavigator >
    {
        public:
            KSRootSpaceNavigator();
            KSRootSpaceNavigator( const KSRootSpaceNavigator& aCopy );
            KSRootSpaceNavigator* Clone() const override;
            ~KSRootSpaceNavigator() override;

            //*****************
            //space interaction
            //*****************

        public:
            void CalculateNavigation( const KSTrajectory& aTrajectory, const KSParticle& aTrajectoryInitialParticle, const KSParticle& aTrajectoryFinalParticle, const KThreeVector& aTrajectoryCenter, const double& aTrajectoryRadius, const double& aTrajectoryStep, KSParticle& aNavigationParticle, double& aNavigationStep, bool& aNavigationFlag ) override;
            void ExecuteNavigation( const KSParticle& anNavigationParticle, KSParticle& aFinalParticle, KSParticleQueue& aSecondaries ) const override;
            void FinalizeNavigation( KSParticle& aFinalParticle ) const override;
            void StartNavigation( KSParticle& aParticle, KSSpace* aRoot ) override;
            void StopNavigation( KSParticle& aParticle, KSSpace* aRoot ) override;

            //***********
            //composition
            //***********

        public:
            void SetSpaceNavigator( KSSpaceNavigator* anNavigation );
            void ClearSpaceNavigator( KSSpaceNavigator* anNavigation );

        private:
            KSSpaceNavigator* fSpaceNavigator;

            //******
            //action
            //******

        public:
            void SetStep( KSStep* anStep );
            void SetTrajectory( KSTrajectory* aTrajectory );

            void CalculateNavigation();
            void ExecuteNavigation();
            void FinalizeNavigation();


        private:
            KSStep* fStep;
            const KSParticle* fTerminatorParticle;
            const KSParticle* fTrajectoryParticle;
            KSParticle* fNavigationParticle;
            KSParticle* fFinalParticle;
            KSParticleQueue* fParticleQueue;
            KSTrajectory* fTrajectory;
    };

}

#endif
