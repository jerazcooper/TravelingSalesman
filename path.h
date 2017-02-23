#ifndef PATH_H
#define PATH_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;


//path structure
struct Path {
	float length;
	vector<std::string> route;
	void print();
};

#endif
