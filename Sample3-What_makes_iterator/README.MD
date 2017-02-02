# LeanSTL - Sample 3 - What makes iterator

#### Figure out what makes iterator using List, iterator is not just a pointer!

---

![](https://raw.githubusercontent.com/Jameeeees/LeanSTL/master/Sample3-What_makes_iterator/structure%20of%20iterator.png)

**We must aware of these:**
* List is a data structure which is made of a series of nodes which can both move forward or move backward.
* The node contains two void pointers and a value, which is the very basic part of the List.
* The iterator must have the ability to traverse the List, which means it can represent any node in the List and move as a real node.
* List is the same as other containers such as Vector, the range of the container should be like ```[start, finish)```, as a result, there comes a solution which is to set a node as a special node, represents the node after the last node which has a value. So that if the user invokes the ```end()``` function, just return the special node, and if the user invokes the ```begin()``` function, just return the next node of the special node.

---

If you are carefully enough, you may find some questions when figuring out the source files as I did, and here is my answers.


* **Q1: Why begin() and end() returns link_type instead of iterator?**

```
iterator begin(){		
	return (link_type)((*node).next);
}
iterator end(){
	return node;
}
```
As we can see in the source file, the ```begin()``` and ```end()``` functions return ```link_type``` instead of iterator. However, the ```link_type``` is a typedef of ```__list_node<T>*```, and iterator is a typedef of ```__list_iterator<T, T&, T*>```, which is different at all.

The key to the answer is the constructor of the iterator, we can find a constructor like this:
```
__list_iterator(link_type x) : node(x) {}
```
This function receives a link_type(```__list_node<T>*```), and when the ```begin() or end()```returns a value, it will invoke the constructor of the iterator automatically and create a temporary iterator to return.

* **Q2: Why ```__list_iterator``` has a typedef named iterator and another typedef named self**
```
template<class T, class Ref, class Ptr>
struct __list_iterator {
	typedef __list_iterator<T, T&, T*> iterator;
	typedef __list_iterator<T, const T&, const T*> const_iterator;
	typedef __list_iterator<T, Ref, Ptr> self;
	typedef T value_type;
	typedef Ptr pointer;
	...
};
```
