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

### Steps 
