#include "vector"
#include <cstdlib>
#include <cstdio>

using namespace std;

int main(){
	Vector<int> v;
	v.push_back(0);
	v.pop_back();
	v.clear();
    return 0;
}

