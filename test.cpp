#include "vector.h"


using namespace std;

int main(){
	//Vector<int*> v1;
	Vector<int> v2;
	//cout<<"sizeof(v1): "<<v1.capacity()<<endl;
	cout<<"sizeof(v2): "<<v2.capacity()<<endl;
	v2.push_back(1);
	cout<<"v2.begin(): "<<v2.begin()<<endl;
	cout<<"v2[0]: "<<v2.begin()<<endl;
	cout<<"v2[0]: "<<*(v2.begin())<<endl;
	return 0;
}
