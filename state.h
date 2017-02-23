#ifndef STATE_H
#define STATE_H

#include <map>
#include "path.h"
#include <queue>

using namespace std;

struct Tracker;
class City;


//state structure
class State {
	float fVal;
	City *start;
	map<string, City *> cities;
	Path path;

public:
	
	State(float fval, City *start, map<string, City *> cities, Path path);
	
	void expand (Tracker &track, City *end);
	
	float getFval() const;
};

#endif
