#include "path.h"

//prints path
void Path::print() {
	std::cout<<"distance :"<<length<<endl;
	std::cout<<"route :";
	for (vector<string>::iterator it = route.begin(); it != route.end(); it++) {
		std::cout<<*it<<" ";
	}
	std::cout<<endl;
}
