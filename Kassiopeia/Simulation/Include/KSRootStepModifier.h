#ifndef Kassiopeia_KSRootStepModifier_h_
#define Kassiopeia_KSRootStepModifier_h_

#include "KSStepModifier.h"
#include "KSStep.h"
#include "KSList.h"
#include "KSParticle.h"

namespace Kassiopeia
{

    class KSTrack;

    class KSRootStepModifier :
            public KSComponentTemplate< KSRootStepModifier, KSStepModifier >
    {
    public:
        KSRootStepModifier();
        KSRootStepModifier( const KSRootStepModifier& aCopy );
        KSRootStepModifier* Clone() const override;
        ~KSRootStepModifier() override;

        //**********
        // modifier
        //**********

    public:
        bool ExecutePreStepModification( KSParticle& anInitialParticle, KSParticleQueue& aQueue ) override;
        bool ExecutePostStepModification( KSParticle& anInitialParticle, KSParticle& aFinalParticle, KSParticleQueue& aQueue ) override;

        //***********
        //composition
        //***********

    public:
        void AddModifier( KSStepModifier* aModifier );
        void RemoveModifier( KSStepModifier* aModifier );

    private:
        KSList< KSStepModifier > fModifiers;
        KSStepModifier* fModifier;

        //******
        //action
        //******

    public:
        void SetStep( KSStep* aStep );

        bool ExecutePreStepModification();
        bool ExecutePostStepModification();

        void PushUpdateComponent() override;
        void PushDeupdateComponent() override;

    private:
        KSStep* fStep;
        const KSParticle* fInitialParticle;
        KSParticle* fModifierParticle;
        KSParticle* fFinalParticle;
        KSParticleQueue* fParticleQueue;
    };


}

#endif
