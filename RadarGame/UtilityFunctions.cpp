#include "UtilityFunctions.h"

int generateUniformIntegerRandomNumberInRange(int start, int end) {
 static std::default_random_engine rawEngine( time(0) );
 std::uniform_int_distribution<int> uniIntDist{ start,end };
 return uniIntDist(rawEngine);
}