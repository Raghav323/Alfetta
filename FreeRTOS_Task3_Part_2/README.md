# Solving Problem of DeadLock by Using Mutex instead of Semaphore 


**DeadLock** : A deadlock consists of a set of blocked processes, each holding a resource and waiting to acquire a resource held by another process in the set.

**Mutex** : A mutex is similar to binary semaphore but it differs in the fact that a mutex will only allow ONE task to get past xSemaphoreTake() operation and other tasks will be put to sleep if they reach this function at the same time.

This is the reason **why** , on changing semaphores to mutexes , the problem of deadlock is solved that is mutex provides **mutual exclusion** with **priority inversion** mechanism.


# OUTPUT 

![Screenshot from 2022-09-05 18-41-44](https://user-images.githubusercontent.com/111511248/188457714-ed6ffdd7-4e0d-4d10-94ac-bf77f7fd582c.png)
