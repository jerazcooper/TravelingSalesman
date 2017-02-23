#include "city.h"
#include "path.h"
using std::string;

//constructor
City::City(string name, int x, int y) {
	this->name = name;
	xPos = x;
	yPos = y;
}

//used to store precomputed distances
void City::setDistance(City *city) {
	float squareDistance = ((xPos - city->xPos) * (xPos - city->xPos)) + 
							((yPos - city->yPos) * (yPos - city->yPos));  
	this->distance[city->name] = sqrt(squareDistance);
}

float City::getDistance(string city) {
	return distance[city];
}

//build heuristic using brute force distance from start using 
//	topmost, lowest, rightmost and leftmost points
float City::getHueristic(map<string, City *> cities, City *end) {
	//remove this fom cities list	
	if (cities.find(this->name) != cities.end()){
		cities.erase(this->name);
	}
	City *top = NULL;
	City *right = NULL;
	City *bottom = NULL;
	City *left = NULL;
	map<string, City *>::iterator it;

	//find top/bottom/right/left city
	for (it = cities.begin(); it != cities.end(); it++) {
		if (top == NULL) {
			top = it->second;
			right = it->second;
			bottom = it->second;
			left = it->second;
		} else {
			if (it->second->yPos > top->yPos) {
				top = it->second;					
			}
			if (it->second->xPos > right->xPos) {
				right = it->second;	
			}
			if (it->second->yPos < bottom->yPos) {
				bottom = it->second;					
			}
			if (it->second->xPos < left->xPos) {
				left = it->second;	
			}
		}
	}
		
	//edges of the square
	map<string, City*> edges;
	edges[top->name] = top;
	edges[right->name] = right;
	edges[bottom->name] = bottom;
	edges[left->name] = left;
	Path *path = this->bruteForce(edges, end);
	return path->length;
}

//find the shortest path between 2 points passing thru all the cities
vector<Path *> City::bruteForceInternal(map<string, City *> cities, City *end) {
//remove start if it is in the cities
	map<string, City *>::iterator it = cities.find(this->name);
	if (it != cities.end()) {
		cities.erase(it);
	}
	if (cities.size() == 0) {
		Path *path = new Path;
		path->length = this->getDistance(end->name);
		path->route.push_back(end->name);
		path->route.push_back(this->name);
		vector<Path *> paths;
		paths.push_back(path);
		return paths;
	} else {
		vector<Path *> paths;
		for (map<string, City *>::iterator it = cities.begin(); it != cities.end(); it++) {
			City *startCity = it->second;			
			vector<Path *> localPaths = startCity->bruteForceInternal(cities, end);			
			float distance = this->getDistance(startCity->name);
			//add start to each path
			for (vector<Path *>::iterator it = localPaths.begin(); it != localPaths.end(); it++) {
				(*it)->length += distance;
				(*it)->route.push_back(this->name);
			}
			//add local paths to paths
			paths.insert(paths.end(), localPaths.begin(), localPaths.end());
		}
		return paths;
	}
}

//wrap bruteForce to remove extra paths and return the shortest path
Path * City::bruteForce(map<string, City *> cities, City *end) {
	vector<Path *> paths = this->bruteForceInternal(cities, end);
	Path *minPath = NULL;	
	for(vector<Path *>::iterator it = paths.begin(); it != paths.end(); it++) {
		if (minPath == NULL) {
			minPath = *it;
		} else if (((*it)->length < minPath->length)) {
			minPath = *it;
		}		
	}

	for (unsigned i = 0; i < paths.size(); i++) {
		if (paths[i] != minPath) delete paths[i]; //remove unused paths
	}
	return minPath;
}

string City::getName() {
	return name;
}

