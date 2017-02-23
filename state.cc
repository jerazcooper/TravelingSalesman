#include "state.h"
#include "city.h"
#include "tracker.h"

State::State (float fval, City *start, map<string, City *> cities, Path path) {
	this->fVal = fval;
	this->start = start;
	this->cities = cities;
	this->path = path;
}

void State::expand (Tracker &track, City *end) {
	//remove the city from the list of cities
	if (this->cities.find(this->start->getName()) != this->cities.end()) {
		this->cities.erase(this->start->getName());
	}
	
	if (this->cities.size() == 5) { //goes to goal state
		//bruteForce since heruistic requires 6 to be effective	
		Path *shortest = this->start->bruteForce(this->cities, end);
		track.expandedNodes += 326; //the total nodes expanded when there are 5 untouched cities
		if (track.minFound && shortest->length + this->path.length < track.minPath.length) { //path is new min
			Path p;
			p.length = shortest->length + this->path.length;
			p.route = vector<string> (this->path.route);
			p.route.insert(p.route.end(), shortest->route.rbegin() + 1, shortest->route.rend());
			track.minPath = p;
		} else if (!track.minFound) { //path is first to reach goal state
			Path p;
			p.length = shortest->length + this->path.length;
			p.route = vector<string> (this->path.route);
			p.route.insert(p.route.end(), shortest->route.rbegin() + 1, shortest->route.rend());
			track.minPath = p;
			track.minFound = true;
		}
	} else {
		//create fvals and states for all possbile opeators and place into priority queue
		for (map<string, City *>::iterator it = this->cities.begin(); it != this->cities.end(); it++) {
			
			float f = it->second->getHueristic(this->cities, end) + this->start->getDistance(it->second->getName()) + this->path.length;
			Path p;
			p.length = this->path.length + this->start->getDistance(it->second->getName());
			p.route = vector<string> (this->path.route);
			p.route.push_back(it->second->getName());
			track.queue.push(State(f, it->second, this->cities, p));			
		}
		track.expandedNodes++;
	}	
}

float State::getFval() const{
	return fVal;
}
