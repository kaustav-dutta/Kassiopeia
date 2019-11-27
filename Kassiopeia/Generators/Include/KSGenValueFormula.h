#ifndef Kassiopeia_KSGenValueFormula_h_
#define Kassiopeia_KSGenValueFormula_h_

#include "KSGenValue.h"

#include "KField.h"

#include "TF1.h"

namespace Kassiopeia
{
    class KSGenValueFormula :
        public KSComponentTemplate< KSGenValueFormula, KSGenValue >
    {
        public:
            KSGenValueFormula();
            KSGenValueFormula( const KSGenValueFormula& aCopy );
            KSGenValueFormula* Clone() const override;
            ~KSGenValueFormula() override;

        public:
            void DiceValue( std::vector< double >& aDicedValues ) override;

        public:
            ;K_SET_GET( double, ValueMin );
            ;K_SET_GET( double, ValueMax );
            ;K_SET_GET( std::string, ValueFormula );

        public:
            void InitializeComponent() override;
            void DeinitializeComponent() override;

        protected:
            TF1* fValueFunction;
    };

}

#endif
