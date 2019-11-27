#ifndef KGAFFINEDEFORMATION_HH_
#define KGAFFINEDEFORMATION_HH_

#include "KThreeMatrix.hh"

#include "KGDeformation.hh"

namespace KGeoBag
{

  class KGAffineDeformation : public KGDeformation
  {
  public:
    KGAffineDeformation();
    KGAffineDeformation(const KGAffineDeformation& affine);

    ~KGAffineDeformation() override {}

    void SetLinearMap(const KThreeMatrix& map) { fLinearMap = map; }
    void SetTranslation(const KThreeVector& t) { fTranslation = t; }

    void Apply(KThreeVector& point) const override;

  private:
    KThreeMatrix fLinearMap;
    KThreeVector fTranslation;
  };
}

#endif
