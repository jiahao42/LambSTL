#include "vector.h"
#include <iostream>

using namespace std;

int main(){
	//Vector<int*> v1;
	Vector<int> v2;
	//cout<<"v1: "<<v1.add(1,2)<<endl;
	cout<<"sizeof(v2): "<<v2.size()<<endl;
	cout<<"v2: "<<v2.add(2,2)<<endl;
	return 0;
}