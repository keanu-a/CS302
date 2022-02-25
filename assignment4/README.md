# Assignment 4 - Multithreading

## Description
For this assignment, you will need to write a function that is assigned to each thread that computes part
of the product of two matrices, and when all the threads are done, the product of two matrices has been
computed. You may use a 2D std::vector< std::vector<int> > object to maintain the matrices, and
they can be global vectors since they will be shared memory among the threads.

Thus in main, it will be your responsibility to not spawn more than the amount of threads that can be run
concurrently, and assign each thread to the appropriate part of the matrices to allow the computation to be
done in parallel. A warning, passing by reference into a thread function causes issues. Luckily you can have
your matrices declared globally, and you can pass value parameters into the thread function that tells the
thread which parts of the matrices the thread will access. You would need a std::vector< std::thread > >
object to maintain the list of threads.
