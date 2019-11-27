#ifndef KELECTROSTATICCONSTANTFIELD_DEF
#define KELECTROSTATICCONSTANTFIELD_DEF

#include "KElectrostaticField.hh"

namespace KEMField
{
  class KElectrostaticConstantField : public KElectrostaticField
  {
  public:
    KElectrostaticConstantField() :
      KElectrostaticField(),
      fField() {}

    KElectrostaticConstantField(const KThreeVector& field) :
      KElectrostaticField(),
      fField(field) {}

    ~KElectrostaticConstantField() override {}

    void SetField(KThreeVector field) { fField = field; }
    KThreeVector GetField() {return fField;}

    static std::string Name() { return "ElectrostaticConstantFieldSolver"; }

private:
    double PotentialCore(const KPosition& P) const override {
    	return fField.Dot(P);
    }

    KThreeVector ElectricFieldCore(const KPosition&) const override {
    	return fField;
    }

  protected:

    KThreeVector fField;
  };

}

#endif /* KELECTROSTATICCONSTANTFIELD_DEF */
