# LambSTL - Sample 8 - Why_function_object

**Why use function object instead of function pointer?**
[Reference](https://www.experts-exchange.com/articles/849/Function-pointers-vs-Functors.html)

### 1. function object can have different instances while function pointer cannot, which means function object can have local state.

For example:

```
bool callback() {
	return true;
}
```

There does have one way which can store local state : add a static data member, like this:

```
bool callback() {
	static bool result = true;
	return result;
}
```

However, this way is not safe in multiple threads without the additional overhead of thread synchronisation to ensure access to the local static data has mutual exclusion semantics.

So, here comes function object, like this:

```
struct callback {
	bool result;
	callback(bool _result) : result(_result) {}
	bool operator() () { return result; }
}

int main() {
	struct callback c1(true);
	struct callback c2(false);
}
```

With the help of function object, we can easily create different instances of function with different local state.



