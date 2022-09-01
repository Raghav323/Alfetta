# Implementing Semaphore using Task Notifications 

1. **Semaphore** : Semaphore is simply a variable that is non-negative and shared between threads.
This variable is used to solve the critical section problem and to achieve process synchronization in the multiprocessing environment.
 
2. **Binary Semaphore** :  A semaphore which can take either 1 or 0 . Also called as mutex lock . Differs from the mutex in the fact that it can be signaled
by any thread unlike the mutex which can be released only by the thread that acquired it .

3. **Task Notifications** : Each RTOS task has an array of task notifications. Each task notification has a notification state that can be either 'pending' or 'not pending', and a 32-bit notification value.

## Functions Used 

1. **xTaskNotifyGiveIndexed(TaskHandle,Index)** :Takes in the handle of the task to notify as well as the index of the task notification in the array of task notifications 
of that task which is to be changed . 

2. **xTaskNotifyTakeIndexed(Index,Clear_on_exit,Waiting time)** :Used when a task notification is to be used like a light weight binary semaphore . Takes in the index of the task notification to wait for , the second parameter specifies if the function should either reset the value of the task notification on exit 
or decrement it by 1 . The third parameter specifies the time for which it should wait to receive the task notification . It returns the task notification value . 

3. **xTaskNotifyGive()** : Equivalent to xTaskNotifyGiveIndexed(TaskHandle,0)

4. **xTaskNotifyTake()** : Equivalent to xTaskNotifyTakeIndexed(0,Clear_on_exit,Waiting time)

 
## LOGIC 

We increment the task notification of the task to which we want to give the semaphore by using xTaskNotifyGive() . And in both tasks we check
if their task notifications are incremented from 0 to 1 using xTaskNotifyTake(1,waiting time) which will also set the task notification value to 0 if 
it is set to 1 on exiting therefore "freeing up the semaphore " and then giving it to again to the other function using xTaskNotifyGive() . Also we use a task start_transmission() to give the first task notification to a task .

## Output After Implementing functionality of Semaphore using Task Notifications

![Screenshot from 2022-09-01 17-43-15](https://user-images.githubusercontent.com/111511248/187911534-48ea1e6a-d51c-4066-a88b-1db80124e550.png)



The functionality of semaphore is implemented using functions xTaskNotifyGive and xTaskNotifyTake . The shared resource is being accessed and modified by two different tasks with the help of the semaphore created . Every task takes the semaphore , then works on the shared resource and gives back the semaphore signaling that it does not need the semaphore now.

