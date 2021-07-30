# parallel_linked_list

CS4532 Concurrent Programming
Take Home Lab 1

### Learning Outcomes

In this lab we will learn how to develop parallel programs using the Pthread library. We will also
compare the performance of different implementations. At the end of the lab you will be able to: <br>

• develop a simple program to solve a concurrent problem using threads <br>
• collect performance data and use them to compare the performance of different implementations
used to solve a problem <br>

### Problem

Implement a linked list as a: <br>
a) Serial program <br>
b) Parallel program (based on Pthreads) with one mutex for the entire linked list <br>
c) Parallel program (based on Pthreads) with read-write locks for the entire linked list <br>

Your implementation should support Member( ), Insert( ), and Delete( ) functions. Populate the
linked list with n random, but unique values. Make sure to set a different random seed for each execution.
Each value should be between 0 and 2^16 – 1. Then perform m random Member, Insert, and Delete operations
(simultaneously) on the link list. Let mMember, mInsert, and mDelete be the fractions of operations of each type.
You may use any values within 0 and 2^16 – 1 while performing these three operations. However, to
simplify the implementation, a new value inserted into the list cannot be a value already in the list (it could
be a value that was initially added to the list, but later removed).

### How To Run

1. Complile linked_list.c, linked_list_mutex.c and linked_list_read_write_lock.c source files using gcc <br>
  ```gcc -g -Wall <file_name.c> -o <file_name> -pthread```

2. Install pip statistics library <br>
  ``` pip install statistics ```

3. Run the python script <br>
  ```python run.py <n_threads>```


### Steps 

The following procedure was used to design the solution, <br>
1. Use a C struct to implement the linked list data structure<br>
2. Implement the member, insert, and delete operations in C<br>
3. Implement the sequential program to perform the operations in the linked list<br>
4. Use the mutex lock in pthread library to implement the threaded linked list using mutex lock to synchronize the threads<br>
5. Use the read/write lock in pthread library to implement a threaded linked list using read/write lock to synchronize the threads
Furthermore implement global variables to avoid any losses in operations<br>
6. Implement a python script and invoke subprocesses according to the calculated sample size to calculate the average execution time
and standard deviation for all the instances<br>


### Sample Test Case

n = 1,000 and m = 10,000, mMember = 0.99, mInsert = 0.005, mDelete = 0.005


