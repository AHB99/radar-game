#include "UtilityFunctions.h"
#include <random>
#include <ctime>

int generateUniformIntegerRandomNumberInRange(int start, int end) {
	 static std::default_random_engine rawEngine( time(0) );
	 std::uniform_int_distribution<int> uniIntDist{ start,end };
	 return uniIntDist(rawEngine);
}

bool generateRandomBool() {
	static std::default_random_engine rawEngine(time(0));
	std::bernoulli_distribution bernDist{};
	return bernDist(rawEngine);
}