#ifndef Kassiopeia_KSGenSpinComposite_h_
#define Kassiopeia_KSGenSpinComposite_h_

#include "KSGenCreator.h"
#include "KSGenValue.h"

namespace Kassiopeia
{

    class KSGenSpinComposite :
        public KSComponentTemplate< KSGenSpinComposite, KSGenCreator >
    {
        public:
            KSGenSpinComposite();
            KSGenSpinComposite( const KSGenSpinComposite& aCopy );
            KSGenSpinComposite* Clone() const override;
            ~KSGenSpinComposite() override;

        public:
            void Dice( KSParticleQueue* aParticleList ) override;

        public:
            void SetXAxis( const KThreeVector& anXAxis );
            void SetYAxis( const KThreeVector& anYAxis );
            void SetZAxis( const KThreeVector& anZAxis );

            void SetThetaValue( KSGenValue* anThetaValue );
            void ClearThetaValue( KSGenValue* anThetaValue );

            void SetPhiValue( KSGenValue* aPhiValue );
            void ClearPhiValue( KSGenValue* aPhiValue );

        private:
            KSGenValue* fThetaValue;
            KSGenValue* fPhiValue;

            KThreeVector fXAxis;
            KThreeVector fYAxis;
            KThreeVector fZAxis;

        protected:
            void InitializeComponent() override;
            void DeinitializeComponent() override;
    };

}

#endif
