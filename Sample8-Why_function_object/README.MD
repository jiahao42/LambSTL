# LambSTL - Sample 8 - Why_function_object

**Why use function object instead of function pointer?**
[Reference](https://www.experts-exchange.com/articles/849/Function-pointers-vs-Functors.html)

### 1. function object can have different instances while function pointer cannot, which means function object can have local state.

For example:

```
typedef bool (*func)();
bool callback() {
	return true;
}
void invoker(func f) {
	f();
}
int main() {
	invoker(callback);
}
```

There does have one way which can store local state : add a static data member, like this:

```
typedef bool (*func)();
bool callback() {//what if multiple threads fighting for the static member?
	static bool result = true;
	return true;
}
void invoker(func f) {
	f();
}
int main() {
	invoker(callback);
}
```

However, this way is not safe in multiple threads without the additional overhead of thread synchronisation to ensure access to the local static data has mutual exclusion semantics.

So, here comes function object, like this:

```
class callback {
public:
	callback(bool _result) : result(_result) {}
	bool operator() () { return result; }
private:
	bool result;
};

void invoker(callback f) {
	f();
}

int main() {
	callback c1(true);
	callback c2(false);
	invoker(c1);
	invoker(c2);
}
```

With the help of function object, we can easily create different instances of function with different local state.


Without local state, function pointer can cause more problems. Let's say we expect only one parameter but use a 3rd party function as the callback. There is a solution to create an adaptor to wrap the functions, but what if the situations are too many, then you have write an adaptor for each and every permutation, not to mention this way is not flexible at all.

For example:

```
typedef void (*func)(int n);

void callback(int, int, int) { printf("I'm here!\n"); }

void adaptor1(int n) {
	callback(n, 1, 1);
}

void adaptor2(int n) {//what if there are more situations than [1, 1] and [1, 2]?
	callback(n, 1, 2);
}

void invoker(func f) {
	f(int());
}

int main() {
	invoker(adaptor1);
	invoker(adaptor2);
}
```

As the code above, the function pointer cannot have different instances, so we have to hard code those adaptors in the compiling phase, which is very bad choice. At this time, we should choose function object.

```
class callback {
public:
	callback(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}
	callback(int _a) : a(_a), b(0), c(0) {}
	void operator() (int n) { printf("I'm here!\n"); }
private:
	int a,b,c;
};

void invoker(callback f) {
	f(int());
}

int main() {
	callback c1(1);
	callback c2(1,2,3);
	//... 
	//Create as many as you like...
	invoker(c1);
	invoker(c2);
}
```

With function object, we can create as many as we need **in the runtime**.


