#ifndef KGROTATEDSURFACEINTERSECTOR_DEF
#define KGROTATEDSURFACEINTERSECTOR_DEF

#include "KGRotatedSurface.hh"

#include "KGIntersectorInitializer.hh"

namespace KGeoBag
{
  class KGRotatedSurfaceIntersectorInitializer :
    public KGRotatedSurface::Visitor,
    virtual public KGIntersectorInitializer
  {
  public:
    KGRotatedSurfaceIntersectorInitializer() {}
    ~KGRotatedSurfaceIntersectorInitializer() override {}

  protected:
    void VisitRotatedSurface(const KGRotatedSurface* rotatedSurface);

  };

  class KGRotatedSurfaceIntersector : virtual public KGAnalyticIntersector
  {
  public:
    KGRotatedSurfaceIntersector(const KGRotatedSurface& rotatedSurface);
    ~KGRotatedSurfaceIntersector() override {}

    bool Intersection(KThreeVector& aStart,
			      KThreeVector& anEnd,
			      KThreeVector& aResult) const override;

  protected:
    const KGRotatedSurface& fRotatedSurface;
  };
}

#endif /* KGROTATEDSURFACEINTERSECTOR_DEF */
