# Solving Problem of DeadLock by Changing Wait Time 


**DeadLock** : A deadlock consists of a set of blocked processes, each holding a resource and waiting to acquire a resource held by another process in the set.


In function XsemaphoreTake(semaphore handle , wait_time) , we can change the wait time from portMAX_Delay to some lower value so that 
the task does not wait indefinitely for the semaphore and after some time moves onto the next bit of code .

# OUTPUT 

![Screenshot from 2022-09-05 08-40-50](https://user-images.githubusercontent.com/111511248/188353502-2f3fd591-a83c-4862-8e8b-896ab6ce3139.png)
