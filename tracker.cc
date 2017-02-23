#include "tracker.h"
#include "state.h"
//compartor class for states
bool CompareState::operator()(State const &s1, State const &s2) {
	return s1.getFval() > s2.getFval();
}

