# LeanSTL - Sample 4 - How Deque works

Try to figure out how Deque works

This is what the deque looks like, when

* The map size is 6, which means it has 6 buffers

* Each buffer can contain 6 elements at most, the buffer pointer by end iterator has 3 vacancies, which means this deque's size is 21, and its capcity is 36.

* The first buffer and the last buffer are all vacant, it makes Deque more efficient when either pushing back or pushing front, cause in many case, Deque don't need to allocate another two buffer(both back and front) dynamically.


![](https://raw.githubusercontent.com/Jameeeees/LeanSTL/master/Sample3-How_Deque_works/deque.png)

