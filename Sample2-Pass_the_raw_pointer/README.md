# STL-Tutorial - Sample 2 - Pass the raw pointer

自定义Vector容器，利用模板偏特化技术(partial template specialization)，将原生指针作为参数传给模板

```
Vector<int*> v;
int* array = new int[10];
v.push_back(array);

```


