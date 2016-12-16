# LeanSTL - Sample 1
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