/*
 * KSElectricKEMField.h
 *
 *  Created on: 19.05.2015
 *      Author: gosda
 */

#ifndef KSELECTRICKEMFIELD_H_
#define KSELECTRICKEMFIELD_H_

#include "KSElectricField.h"

namespace KEMField {			// forward declaration has to be in namespace
	class KElectricField;
} // KEMField

namespace Kassiopeia {

class KSElectricKEMField : public KSElectricField {

public:
	KSElectricKEMField();
	KSElectricKEMField(const KSElectricKEMField& aCopy);
    KSElectricKEMField(KEMField::KElectricField* field);
	KSElectricKEMField* Clone() const override;
	~KSElectricKEMField() override;

	void SetElectricField(KEMField::KElectricField* field);
	const KEMField::KElectricField* getElectricField();

	void CalculatePotential( const KGeoBag::KThreeVector& aSamplePoint, const double& aSampleTime, double& aPotential ) override;
	void CalculateField( const KGeoBag::KThreeVector& aSamplePoint, const double& aSampleTime, KGeoBag::KThreeVector& aField ) override;
    void CalculateFieldAndPotential( const KGeoBag::KThreeVector& aSamplePoint, const double& aSampleTime, KGeoBag::KThreeVector& aField, double& aPotential) override;

private:
    void InitializeComponent() override;
    void DeinitializeComponent() override;


	KEMField::KElectricField* fField;
};

} // Kassiopeia

#endif /* KSELECTRICKEMFIELD_H_ */
