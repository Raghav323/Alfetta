# Implementing Semaphore using Queues 

1. Semaphore : Semaphore is simply a variable that is non-negative and shared between threads.
This variable is used to solve the critical section problem and to achieve process synchronization in the multiprocessing environment.
 
2. Binary Semaphore :  A semaphore which can take either 1 or 0 . Also called as mutex lock . Differs from the mutex in the fact that it can be signaled
by any thread unlike the mutex which can be released only by the thread that acquired it .

3. Queues : A queue is a simple FIFO system with atomic reads and writes . Queue may be used to start another task to start doing its work while the primary task continues doing its own work independently.


# Output After Implementing functionality of Semaphore using Queue

![Screenshot from 2022-08-31 13-05-39](https://user-images.githubusercontent.com/111511248/187620268-d1b70ea9-f18c-44fd-b862-b122836aa859.png)

A semaphore is implemented using functions xQueueSend and xQueueReceive . The shared resource is being accessed and modified by two different tasks with
the help of the semaphore created . Every task takes the semaphore , then works on the shared resource and gives back the semaphore signaling that it does not need the semaphore right now . 
