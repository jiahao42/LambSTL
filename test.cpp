#include "__malloc_alloc_template.h"
#include "__default_alloc_template.h"
#include "vector.h"
#include <iostream>


using namespace std;

int main(){
	Vector<int*> v;
	cout<<v.add(1,2)<<endl;
}