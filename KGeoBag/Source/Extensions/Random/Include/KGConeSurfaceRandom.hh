/*
 * KGConeSurfaceRandom.hh
 *
 *  Created on: 20.05.2014
 *      Author: Jan Oertlin
 */

#ifndef KGCONESURFACERANDOM_HH_
#define KGCONESURFACERANDOM_HH_

#include "KGShapeRandom.hh"
#include "KGConeSurface.hh"

namespace KGeoBag
{
  /**
   * \brief Class for dicing a point on a KGConeSurface.
   */
  class KGConeSurfaceRandom : virtual public KGShapeRandom,
				 public KGConeSurface::Visitor
  {
  public:
	  KGConeSurfaceRandom() : KGShapeRandom() {}
    ~KGConeSurfaceRandom() override {}

    /**
     * \brief Visitor function for dicing a point on
     * a KGConeSurface.
     *
     * \param aConeSpace
     */
    void VisitConeSurface(KGConeSurface* aConeSpace) override;
  };
}

#endif /* KGCONESURFACERANDOM_HH_ */
