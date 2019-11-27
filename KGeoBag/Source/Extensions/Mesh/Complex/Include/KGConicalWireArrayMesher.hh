#ifndef KGeoBag_KGConicalWireArrayMesher_hh_
#define KGeoBag_KGConicalWireArrayMesher_hh_

#include "KGConicalWireArraySurface.hh"

#include "KGComplexMesher.hh"

namespace KGeoBag
{
  class KGConicalWireArrayMesher :
    virtual public KGComplexMesher,
    public KGWrappedSurface<KGConicalWireArray>::Visitor
  {
  public:
    using KGMesherBase::VisitExtendedSurface;
    using KGMesherBase::VisitExtendedSpace;

  public:
    KGConicalWireArrayMesher()
    {
    }
    ~KGConicalWireArrayMesher() override
    {
    }

  protected:
    void VisitWrappedSurface(KGWrappedSurface< KGConicalWireArray >* conicalWireArraySurface) override;
  };

}

#endif
