#ifndef Kassiopeia_KSGenValueRadiusCylindrical_h_
#define Kassiopeia_KSGenValueRadiusCylindrical_h_

#include "KSGenValue.h"

#include "KField.h"

namespace Kassiopeia
{
    class KSGenValueRadiusCylindrical :
        public KSComponentTemplate< KSGenValueRadiusCylindrical, KSGenValue >
    {
        public:
            KSGenValueRadiusCylindrical();
            KSGenValueRadiusCylindrical( const KSGenValueRadiusCylindrical& aCopy );
            KSGenValueRadiusCylindrical* Clone() const override;
            ~KSGenValueRadiusCylindrical() override;

        public:
            void DiceValue( std::vector< double >& aDicedValues ) override;

        public:
            K_SET_GET( double, RadiusMin )
            K_SET_GET( double, RadiusMax )

    };

}

#endif
