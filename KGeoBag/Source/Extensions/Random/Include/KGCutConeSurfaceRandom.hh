/*
 * KGCutConeSurfaceRandom.hh
 *
 *  Created on: 20.05.2014
 *      Author: Jan Oertlin
 */

#ifndef KGCUTCONESURFACERANDOM_HH_
#define KGCUTCONESURFACERANDOM_HH_

#include "KGShapeRandom.hh"
#include "KGCutConeSpace.hh"

namespace KGeoBag
{
  /**
   * \brief Class for dicing a point on a
   * KGCutConeSurface.
   */
  class KGCutConeSurfaceRandom : virtual public KGShapeRandom,
				 public KGCutConeSurface::Visitor
  {
  public:
	  KGCutConeSurfaceRandom() : KGShapeRandom() {}
    ~KGCutConeSurfaceRandom() override {}

    /**
     * \brief Visitor function to dice a point
     * on a KGCutConeSurface.
     *
     * \param aCutConeSurface
     */
    void VisitCutConeSurface(KGCutConeSurface* aCutConeSurface) override;
  };
}

#endif /* KGCUTCONESURFACERANDOM_HH_ */
