# Homework Assignment 3: Ring Queue
## Class Details:
The ring queue, similar to the container `std::queue` stores objects, adding them using `push,back()` and removing them using `pop_front()`. The ring queue is has a storage capacity, "forgetting" the oldest objects in order to "remember" the new ones. It works like a ring because of it's iterators. Due to the way it forgets and remembers, the "beginning" and "ending" indexes of the queue do not remain static, but move. Therefore in order to keep track of the iterator's place in the queue, it uses an offset, which keeps track of the number of indexes it is away from the beginning index. 

A better description of how the class `RingQueue` and its `iterators`/`const_iterators` work can be found here: http://pic.ucla.edu/%7Ersalazar/pic10c/assignments/hw3/index.html.
## Programming Details:
Writing the code was a bit challenging, however once I had figured out the offset worked, it became easier. I made a few infinite loops when writing the prefix `operator++()`. Eventually I got it right. The test code that was give runs successfully. I did not test it out for other data types, but I have faith that it works.
### `ring_queue.cpp`
This file contains the entire program, including the both the RingQueue and iterator classes as well as `int.main(){ ... }` (located at the bottom).
