/*
 * KGGenericSurfaceRandom.hh
 *
 *  Created on: 21.05.2014
 *      Author: Jan Oertlin
 */

#ifndef KGGENERICSURFACERANDOM_HH_
#define KGGENERICSURFACERANDOM_HH_

#include "KGShapeRandom.hh"
#include "KGArea.hh"
#include "KGRandomMessage.hh"

namespace KGeoBag
{
  /**
   * \brief Class for implementation of a generic code
   * for dicing a point on an arbitrary surface.
   */
  class KGGenericSurfaceRandom : virtual public KGShapeRandom,
				 public KGArea::Visitor
  {
  public:
	  KGGenericSurfaceRandom() : KGShapeRandom() {}
    ~KGGenericSurfaceRandom() override {}

    /**
	 * \brief Visitor function to dice the point on
	 * an arbitrary surface.
	 *
	 * \brief aArea
	 */
    void VisitArea(KGArea* aArea) override;
  };
}

#endif /* KGGENERICSURFACERANDOM_HH_ */
