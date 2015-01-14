#ifndef Kassiopeia_KSIntSurfaceDiffuse_h_
#define Kassiopeia_KSIntSurfaceDiffuse_h_

#include "KSSurfaceInteraction.h"

#include "KField.h"

namespace Kassiopeia
{

    class KSStep;

    class KSIntSurfaceDiffuse :
        public KSComponentTemplate< KSIntSurfaceDiffuse, KSSurfaceInteraction >
    {
        public:
            KSIntSurfaceDiffuse();
            KSIntSurfaceDiffuse( const KSIntSurfaceDiffuse& aCopy );
            KSIntSurfaceDiffuse* Clone() const;
            virtual ~KSIntSurfaceDiffuse();

        public:
            void ExecuteInteraction( const KSParticle& anInitialParticle, KSParticle& aFinalParticle, KSParticleQueue& aSecondaries );
            void ExecuteReflection( const KSParticle& anInitialParticle, KSParticle& aFinalParticle, KSParticleQueue& aSecondaries );
            void ExecuteTransmission( const KSParticle& anInitialParticle, KSParticle& aFinalParticle, KSParticleQueue& aSecondaries );

        public:
            ;K_SET_GET( double, Probability )
            ;K_SET_GET( double, ReflectionLoss )
            ;K_SET_GET( double, TransmissionLoss )
    };

}

#endif