#ifndef Kassiopeia_KSGenStringValueFix_h_
#define Kassiopeia_KSGenStringValueFix_h_

#include "KSGenStringValue.h"

#include "KField.h"

namespace Kassiopeia
{

    class KSGenStringValueFix :
        public KSComponentTemplate< KSGenStringValueFix, KSGenStringValue >
    {
        public:
            KSGenStringValueFix();
            KSGenStringValueFix( const KSGenStringValueFix& aCopy );
            KSGenStringValueFix* Clone() const override;
            ~KSGenStringValueFix() override;

        public:
            void DiceValue( std::vector< std::string >& aDicedValues ) override;

        public:
	    K_SET_GET( std::string, Value )
    };

}

#endif
