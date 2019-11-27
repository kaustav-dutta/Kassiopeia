#ifndef KELECTROSTATICLINESEGMENTINTEGRATOR_DEF
#define KELECTROSTATICLINESEGMENTINTEGRATOR_DEF

#include "KSurface.hh"
#include "KEMConstants.hh"

#include "KElectrostaticElementIntegrator.hh"

namespace KEMField
{
  class KElectrostaticAnalyticLineSegmentIntegrator :
          public KElectrostaticElementIntegrator<KLineSegment>
  {
  public:
    typedef KLineSegment Shape;
    typedef KElectrostaticBasis::ValueType ValueType;

    KElectrostaticAnalyticLineSegmentIntegrator() {}
    ~KElectrostaticAnalyticLineSegmentIntegrator() override {}

    double Potential( const KLineSegment* source, const KPosition& P ) const override;
    KThreeVector ElectricField( const KLineSegment* source, const KPosition& P ) const override;
    using KElectrostaticElementIntegrator<KLineSegment>::Potential;
    using KElectrostaticElementIntegrator<KLineSegment>::ElectricField;

  };

}

#endif /* KELECTROSTATICLINESEGMENTINTEGRATOR_DEF */
