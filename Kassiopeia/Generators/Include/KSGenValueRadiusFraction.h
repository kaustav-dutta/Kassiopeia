#ifndef Kassiopeia_KSGenValueRadiusFraction_h_
#define Kassiopeia_KSGenValueRadiusFraction_h_

#include "KSGenValue.h"

#include "KField.h"

namespace Kassiopeia
{
    class KSGenValueRadiusFraction :
        public KSComponentTemplate< KSGenValueRadiusFraction, KSGenValue >
    {
        public:
            KSGenValueRadiusFraction();
            KSGenValueRadiusFraction( const KSGenValueRadiusFraction& aCopy );
            KSGenValueRadiusFraction* Clone() const override;
            ~KSGenValueRadiusFraction() override;

        public:
            void DiceValue( std::vector< double >& aDicedValues ) override;

    };

}

#endif
