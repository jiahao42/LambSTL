# LambSTL
STL Tutorial, Following SGI STL

* **Sample1 - Trace the memory**

Print how memory allocates and deallocates when using vector.

You should be aware that the LambSTL is using a memory pool to avoid the possible memory fragment.

* **Sample2 - Pass the raw pointer**

Passing raw pointer such as int* to the template with **partial template specialization**

* **Sample3 - What makes iterator**

Figure out what makes iterator using list, **iterator is not just a pointer!**

Also, why list can grow unlimitedly(only if the memory is enough) and the iterator will not broken-down just like vector?

* **Sample4 - How Deque works**

Try to figure out the data structure of deque, how it is structured, what makes it more convinent than vector and faster than list? 

* **Sample5 - Other Containers**

Now we have some basic containers, and we can try to use them.

We can make a stack using deque, vector or list, or make a queue using list or deque.

Also, there is heap(implicit repressentation), priority_Queue and slist.

* **Sample6 - Custom your own container**

Not figured out yet.

* **Sample7 - Red-Black Tree**

Do you know that set and map can be based on Red-Black Tree, let's discuss it

* **Sample8 - Why function object**

Why use function object instead of function pointer? 

In C programming, we use function pointer a lot, but it has some drawbacks comparing to function object in C++