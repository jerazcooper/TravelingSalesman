#ifndef TRACKER_H
#define TRACKER_H

#include <queue>
#include "path.h"

using namespace std;

class State;

//comparator class for usising states in a priority queue
struct CompareState {
	bool operator()(State const &s1, State const &s2);
};


//tracks number of expanded states, current min found and unexpanded states
struct Tracker {
	long expandedNodes;
	priority_queue<State, vector<State>, CompareState> queue;
	bool minFound;
	Path minPath;
};

#endif
