/*
 * KMagnetostaticConstantField.hh
 *
 *  Created on: 23 Mar 2016
 *      Author: wolfgang
 */

#ifndef KMAGNETOSTATICCONSTANTFIELD_HH_
#define KMAGNETOSTATICCONSTANTFIELD_HH_

#include "KMagnetostaticField.hh"

namespace KEMField {

class KMagnetostaticConstantField: public KEMField::KMagnetostaticField
{
public:
    KMagnetostaticConstantField() :
        KMagnetostaticField(),
        fFieldVector() {}

    KMagnetostaticConstantField( const KThreeVector& aField ) :
        KMagnetostaticField(),
        fFieldVector(aField) {}

    ~KMagnetostaticConstantField() override {}

private:
    /** We choose A(r) = 1/2 * B x r as the magnetic potential.
     * This is a viable choice for Coulomb gauge.*/
    KThreeVector MagneticPotentialCore(const KPosition& P) const override {
        return 0.5 * fFieldVector.Cross(P);
    }
    KThreeVector MagneticFieldCore(const KPosition& /*P*/) const override {
        return fFieldVector;
    }
    KGradient MagneticGradientCore(const KPosition& /*P*/) const override {
        return KThreeMatrix::sZero;
    }

public:
    void SetField( const KThreeVector& aFieldVector ) {
        fFieldVector = aFieldVector;
    }

    KThreeVector GetField() const {
        return fFieldVector;
    }

private:
    KThreeVector fFieldVector;
};

} /* namespace KEMFIELD */

#endif /* KMAGNETOSTATICCONSTANTFIELD_HH_ */
