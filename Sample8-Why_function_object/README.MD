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


Without local state, function pointer can cause more problems. Let's say we expect 



















