/*
 * KGCutConeSpaceRandom.hh
 *
 *  Created on: 20.05.2014
 *      Author: Jan Oertlin
 */

#ifndef KGCUTCONESPACERANDOM_HH_
#define KGCUTCONESPACERANDOM_HH_

#include "KGShapeRandom.hh"
#include "KGCutConeSpace.hh"

namespace KGeoBag
{
  /**
   * \brief Class for dicing a point
   * inside a KGCutConeSpace.
   */
  class KGCutConeSpaceRandom : virtual public KGShapeRandom,
				 public KGCutConeSpace::Visitor
  {
  public:
	  KGCutConeSpaceRandom() : KGShapeRandom() {}
    ~KGCutConeSpaceRandom() override {}

    /**
     * \brief Visitor function for dicing the point
     * inside the KGCutConeSpace.
     *
     * \param aCutConeSpace
     */
    void VisitCutConeSpace(KGCutConeSpace* aCutConeSpace) override;
  };
}

#endif /* KGCUTCONESPACERANDOM_HH_ */
