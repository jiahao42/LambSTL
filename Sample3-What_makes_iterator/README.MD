# LeanSTL - Sample 3 - What makes iterator

Figure out what makes iterator using list, iterator is not just a pointer!

![]()

We must aware of this: List is a data structure which is made of a series of nodes which can both move forward or move backward.

The node contains two void pointers and a value, which is the very basic part of the List.

The iterator must have the ability to traverse the List, which means it can represent any node in the List and move as a real node.

List is the same as other containers such as Vector, the range of the container should be like [start, finish), as a result, there comes a solution which is to set a node as a special node, represents the node after the last node which has a value. So that if the user invokes the end() function, just return the special node, and if the user invokes the begin() function, just return the next node of the special node.

---

If you are carefully enough, you may find some questions as I did, and here is my answers.


* #####Q1 

















