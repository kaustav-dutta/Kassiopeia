#ifndef Kassiopeia_KESSSurfaceInteraction_h_
#define Kassiopeia_KESSSurfaceInteraction_h_

#include "KSSurfaceInteraction.h"
#include "KSParticle.h"
#include "KField.h"

namespace Kassiopeia
{

    class KESSSurfaceInteraction :
        public KSComponentTemplate< KESSSurfaceInteraction, KSSurfaceInteraction >
    {
        public:
            KESSSurfaceInteraction();
            KESSSurfaceInteraction( const KESSSurfaceInteraction& aCopy );
            KESSSurfaceInteraction* Clone() const override;
            ~KESSSurfaceInteraction() override;



            void ExecuteInteraction( const KSParticle& anInitialParticle,
                                                   KSParticle& aFinalParticle,
                                                   KSParticleQueue& aQueue) override;



            void ExecuteTransmission( const KSParticle& anInitialParticle,
                                            KSParticle& aFinalParticle );

            void ExecuteReflection(const KSParticle& anInitialParticle,
                                         KSParticle& aFinalParticle );

            double CalculateTransmissionProbability( const double aKineticEnergy,
                                                     const double aCosIncidentAngle );



            typedef enum
            {
                eEnteringSilicon, eExitingSilicon
            } ElectronDirection;
            ElectronDirection fElectronDirection;

            typedef enum
            {
                eNormalPointingSilicon, eNormalPointingAway
            } SurfaceOrientation;

            K_SET_GET( double, ElectronAffinity )

            K_SET_GET( SurfaceOrientation, SurfaceOrientation)


    };
}

#endif //Kassiopeia_KESSSurfaceInteraction_h_
