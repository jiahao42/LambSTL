#include "vector.h"
#include <iostream>

using namespace std;

int main(){
	Vector<int*> v1;
	Vector<int> v2;
	cout<<"sizeof(v1): "<<v1.capacity()<<endl;
	cout<<"sizeof(v2): "<<v2.capacity()<<endl;
	v1.push_back(1);
	cout<<"v1.begin(): "<<v1.begin()<<endl;
	cout<<"v1[0]: "<<v1[0]<<endl;
	return 0;
}