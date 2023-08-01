#pragma once
#ifndef AMAINSTANCE_H
#define AMAINSTANCE_H

#include "../../indicator/Indicator.h"
#include "../../Block.h"

namespace stradex {

Indicator stradex_API AmaSpecial(const Block& block, KQuery query, Indicator ind);

} /* namespace stradex*/

#endif /* AMAINSTANCE_H */
