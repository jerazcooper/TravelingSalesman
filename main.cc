#include "main.h"
#include "city.h"
#include "path.h"
#include "tracker.h"
#include "state.h"

using namespace std;	

int main (int argc, char **args) {
	int numCities;
	map<string, City *> cities;
	cin>>numCities;
	
	//scan in all the cities
	for (int i = 0; i < numCities; i++) {
		string name;
		int x;
		int y;
		cin>>name>>x>>y;
		cities[name] = new City(name, x, y);
	}

	//precompute distance between cities
	for (map<string, City *>::iterator it = cities.begin(); it != cities.end(); it++) {
		for (map<string, City *>::iterator it2 = cities.begin(); it2 != cities.end(); it2++) {
			it->second->setDistance(it2->second);			
		}
	}
	City *A = cities["A"];
	cities.erase("A");

	//bruteforce for testing
	if (argc == 2 && string(args[1]) == "-b") {
		A->bruteForce(cities, A)->print();
	} else {
		if (numCities <= 6) {
			int expantions = 1;
			for (int x = 1; x < numCities; x++) {
				expantions *= x;
				expantions++;
			}
			A->bruteForce(cities, A)->print();
			cout<<"Expanded nodes: "<<expantions<<endl;
		} else {
			//setup tracker			
			Tracker tracking;
			tracking.expandedNodes = 0;
			tracking.minFound = false;
			//create start state
			
			Path p;
			p.length = 0;
			p.route.push_back(A->getName());
			
			State startState = State((float)0, A, cities, p);
			
			//track time
			int start = clock();
			//expand the first state
			startState.expand(tracking, A);			
			for (;tracking.queue.size() != 0;) {
				//expand the best state				
				State best = tracking.queue.top();
				//if the best state has an f value more than the found min we're done
				if (tracking.minFound && best.getFval() > tracking.minPath.length) break;
				tracking.queue.pop();
				best.expand(tracking, A);
			}
			int stop = clock();

			//print data
			cout << "time: " << (stop - start)/double(CLOCKS_PER_SEC)*1000 << endl;
			tracking.minPath.print();
			//nodes seen = nodes expanded + nodes seen and not expanded
			cout<<"Nodes seen: "<<tracking.expandedNodes + tracking.queue.size() <<endl;
		}	
	}
}
