# **Module: Exception**
### ***Java similar exception***  
<br>
This module provides you some exception which could be useful in order to give more information about errors encourented during the life of your program. 
<br>All exception extends the same parent class i.e. AbstractException, although there is a defined hierarchy as you can see below through packaging 
<br><br>
Keep in mind that, altough JPL provide <a href="https://github.com/Gabriele-P03/Libraries/tree/main/logger">Logger</a>, it is not used in this
module to print messages of occurred exception, it will be your responsablity to do it.
<br><br>
The message of thrown exception can be retrieved via <span style="color:green">what()</span> function. Some of these exception override it in order to take out a template message composed by different argumentd passed to constructors. These overriding-ones will be marked as red and there will be a list of <em>special</em>  parameter(s) to pass to constructors

<br><br>

## **Exception**

> ### AbstractException
>- It is the parent class of every exception thrown
<br><br>
---
> ### RuntimeException
> - Thrown due to an event occurred in runtime
<br>
>> 1. ### RuntimeException
>> - Thrown when the exception is occurred in runtime but its cause could not be evaluated 
<br><br>
>> 2. ### <span style="color:red">IllegalArgumentException</span>
>> - Thrown when an invalid parameter is passed to a function
>> - <span style="color:pink">List of *special* parameter(s):</span>
>>> 1. *object* is the invalid argument passed
<br><br>
>> 3. ### IllegalStateException
>> 4. ### IndexOutOfBoundsException
>> 5. ### NotFoundException
>> 6. ### NullPointerException
>> 1. ### ArithmeticException
>> 1. ### IllegalCastException





