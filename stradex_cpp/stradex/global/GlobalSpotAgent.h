#include "agent/SpotAgent.h"

namespace stradex {


void stradex_API startSpotAgent(bool print = true);

void stradex_API stopSpotAgent();

SpotAgent* getGlobalSpotAgent();

void releaseGlobalSpotAgent();

} 