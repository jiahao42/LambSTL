# LambSTL
## STL Tutorial, Following SGI STL, I call it LambSTL

### \_\_Sample1 - Trace the memory\_\_

Print how memory allocates and deallocates when using vector.

You should be aware that the LambSTL is using a **memory pool** to avoid the possible memory fragment.

### \_\_Sample2 - Pass the raw pointer\_\_

Passing raw pointer such as int* to the template with **partial template specialization**

### \_\_Sample3 - What makes iterator\_\_

Figure out what makes iterator using list, **iterator is not just a pointer!**

Also, why list can grow unlimitedly(only if the memory is enough) and the iterator will not broken-down just like vector?

### \_\_Sample4 - How Deque works\_\_

Try to figure out the data structure of deque, how it is structured, what makes it more convinent than vector and faster than list? 

### \_\_Sample5 - Other Containers\_\_

Now we have some basic containers, and we can try to use them.

We can build a stack using deque, vector or list, or build a queue using list or deque.

Also, there is heap(implicit repressentation), priority_Queue and slist.

### \_\_Sample6 - Custom your own container\_\_

Not figured out yet.

### \_\_Sample7 - Red-Black Tree\_\_

Do you know that set and map can be based on Red-Black Tree, let's see it

### \_\_Sample8 - Why function object\_\_

Why use function object instead of function pointer? 

In C programming, we use function pointer a lot, but it has some drawbacks comparing to function object in C++, what's these?
