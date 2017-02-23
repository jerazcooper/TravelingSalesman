#ifndef CITY_H
#define CITY_H

#include <map>
#include <vector> 
#include <cmath>

struct Path;

using namespace std;
//city structure

class City {
	string name;
	int xPos;
	int yPos;
	map<string, float> distance;
	
	vector<Path *> bruteForceInternal (map<string, City *> cities, City *end);
	
public:
	
	City(string name, int x, int y);

	void setDistance(City *city);

	float getDistance(string city);

	float getHueristic(map<string, City *> cities, City *end);
	
	Path *bruteForce(map<string, City *> cities, City *end);
	
	string getName();
};

#endif
