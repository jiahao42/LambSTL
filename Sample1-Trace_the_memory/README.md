# LeanSTL - Sample 1 - Trace the memory
观察Vector使用时，内存的分配过程。

See what does the memory look like when using Vector

For example, the test code:

```
int main(){
	Vector<int> v;
	v.push_back(0);
	v.pop_back();
	v.clear();
    return 0;
}
```

Run it, and you can see things below:

![](https://raw.githubusercontent.com/Jameeeees/LeanSTL/master/Sample1-Trace_the_memory/screenshot0.png)