#ifndef Kassiopeia_KSIntCalculator_h_
#define Kassiopeia_KSIntCalculator_h_

#include "KSComponentTemplate.h"

#include "KSParticle.h"

#include "KField.h"

namespace Kassiopeia
{

    class KSIntCalculator :
        public KSComponentTemplate< KSIntCalculator >
    {
        public:
            KSIntCalculator();
            ~KSIntCalculator() override;
            KSIntCalculator* Clone() const override = 0;

        public:
            virtual void CalculateCrossSection( const KSParticle& aParticle, double& aCrossSection ) = 0;
            virtual void ExecuteInteraction( const KSParticle& anInitialParticle, KSParticle& aFinalParticle, KSParticleQueue& aSecondaries ) = 0;

        protected:
            void PullDeupdateComponent() override;
            void PushDeupdateComponent() override;

            //variables for output
            K_REFS( int, StepNInteractions )
            K_REFS( double, StepEnergyLoss )
    };

}

#endif
