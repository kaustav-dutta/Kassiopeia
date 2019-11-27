#ifndef Kassiopeia_KSRootRunModifier_h_
#define Kassiopeia_KSRootRunModifier_h_

#include "KSRunModifier.h"
#include "KSParticle.h"
#include "KSStep.h"
#include "KSTrack.h"
#include "KSEvent.h"
#include "KSRun.h"
#include "KSList.h"

namespace Kassiopeia
{

    class KSRootRunModifier :
            public KSComponentTemplate< KSRootRunModifier, KSRunModifier >
    {
    public:
        KSRootRunModifier();
        KSRootRunModifier( const KSRootRunModifier& aCopy );
        KSRootRunModifier* Clone() const override;
        ~KSRootRunModifier() override;

        //**********
        // modifier
        //**********

    public:
        bool ExecutePreRunModification( KSRun& aRun ) override;
        bool ExecutePostRunModification( KSRun& aRun ) override;

        //***********
        //composition
        //***********

    public:
        void AddModifier( KSRunModifier* aModifier );
        void RemoveModifier( KSRunModifier* aModifier );

    private:
        KSList< KSRunModifier > fModifiers;
        KSRunModifier* fModifier;

        //******
        //action
        //******

    public:
        void SetRun( KSRun* aRun );

        bool ExecutePreRunModification();
        bool ExecutePostRunModification();

        void PushUpdateComponent() override;
        void PushDeupdateComponent() override;

    private:

        KSRun* fRun;
    };


}

#endif
