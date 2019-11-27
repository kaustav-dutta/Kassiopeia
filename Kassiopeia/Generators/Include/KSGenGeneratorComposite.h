#ifndef Kassiopeia_KSGenGeneratorComposite_h_
#define Kassiopeia_KSGenGeneratorComposite_h_

#include "KSGenerator.h"
#include "KSGenValue.h"
#include "KSGenStringValue.h"
#include "KSGenCreator.h"
#include "KSList.h"

#include "KSGenSpecial.h"

namespace Kassiopeia
{

    class KSGenGeneratorComposite :
        public KSComponentTemplate< KSGenGeneratorComposite, KSGenerator >
    {
        public:
            KSGenGeneratorComposite();
            KSGenGeneratorComposite( const KSGenGeneratorComposite& aCopy );
            KSGenGeneratorComposite* Clone() const override;
            ~KSGenGeneratorComposite() override;

            //******
            //action
            //******

        public:
            void ExecuteGeneration( KSParticleQueue& aPrimaries ) override;

            //***********
            //composition
            //***********

        public:            
            void SetPid( KSGenValue* aPidValue );
            KSGenValue* GetPid();

	    void SetStringId( KSGenStringValue* aStringIdValue );
            KSGenStringValue* GetStringId();

            void AddCreator( KSGenCreator* aCreator );
            void RemoveCreator( KSGenCreator* aCreator );

            void AddSpecial( KSGenSpecial* a );
            void RemoveSpecial( KSGenSpecial* a );

        private:
            void InitializeComponent() override;
            void DeinitializeComponent() override;

        protected:
            KSGenValue* fPidValue;
	    KSGenStringValue* fStringIdValue;
            KSList< KSGenSpecial > fSpecials;
            KSList< KSGenCreator > fCreators;
    };

}

#endif
