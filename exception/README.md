# **Module: <span style="color:aqua">Exception</span>**
### ***Java similar exception***  
<br>
This module provides you some exception which could be useful in order to give more information about errors encourented during the life of your program. 
<br>All exception extends the same parent class, i.e. <span style="color:yellow">AbstractException</span>, although there is a defined hierarchy - packaging - as you can see below.  
<br><br>
Keep in mind that, although JPL provide <a href="https://github.com/Gabriele-P03/Libraries/tree/main/logger" style="color:aqua">Logger</a>, it is not used in this
module to print messages of occurred exception, it will be your responsablity to perform it.
<br><br>
The message of thrown exception can be retrieved via <span style="color:orange">what()</span> function. Some of these exception override it in order to take out a template message composed by different argumentd passed to constructors.

<br><br>

## **Exception**

> ### <a href="https://github.com/Gabriele-P03/Libraries/blob/main/exception/src/AbstractException.hpp" style="color:yellow"> AbstractException</a>
>- It is the parent class of every exception thrown
<br><br>
---
> ### RuntimeException(<span style="color:brown">runtime</span>)
> - Thrown due to an event occurred in runtime
<br>
>> 1. ### <a href="https://github.com/Gabriele-P03/Libraries/blob/main/exception/src/runtime/RuntimeException.hpp" style="color:yellow">RuntimeException</a>
>> - Thrown when the exception is occurred in runtime but its cause could not be evaluated 
<br><br>
>> 2. ### <a href="https://github.com/Gabriele-P03/Libraries/blob/main/exception/src/runtime/IllegalArgumentException.hpp" style="color:yellow">IllegalArgumentException</a>
>> - Thrown when an invalid parameter is passed to a function
>> <br><br>1. <span style="color:orange">*object*</span> is the invalid argument passed
<br><br>
>> 3. ### <a href="https://github.com/Gabriele-P03/Libraries/blob/main/exception/src/runtime/IllegalStateException.hpp" style="color:yellow">IllegalStateException</a>
>> - Thrown whenever any function is called at a bad time, i.e. wheter an another function had to be called before the one which threw this exception
<br><br>
>> 4. ### <a href="https://github.com/Gabriele-P03/Libraries/blob/main/exception/src/runtime/IndexOutOfBoundsException.hpp" style="color:yellow">IndexOutOfBoundsException</a>
>> - Thrown whenever getting an element whose index is out-of-range of a list is attempted.
<br><br>
>> - <span style="color:red">IllegalArgumentException</span> whether <span style="color:orange">max</span> is greater than <span style="color:orange">attempted</span>
<br>
>><br>1. <span style="color:orange">*object*</span> the list which the operation has been attempted on
>> <br>2. <span style="color:orange">*max*</span> size of the argument *list*
>> <br>3. <span style="color:orange">*attempted*</span> index attempted to reach at
<br><br>
>> 5. ### <a href="https://github.com/Gabriele-P03/Libraries/blob/main/exception/src/runtime/NotFoundException.hpp" style="color:yellow">NotFoundException</a>
>> - Thrown whenever a field has not been found into a list of objects
>> <br><br>1. <span style="color:orange">*object*</span> item which has been attempted to get from list
<br><br>
>> 6. ### <a href="https://github.com/Gabriele-P03/Libraries/blob/main/exception/src/runtime/NotFoundException.hpp" style="color:yellow">NullPointerException</a>
>> - Thrown when an operation is attempted either a NULL field or on a nullptr
<br><br>
>> 7. ### <a href="https://github.com/Gabriele-P03/Libraries/blob/main/exception/src/runtime/NotFoundException.hpp" style="color:yellow">ArithmeticException</a>
>> - Thrown when an invalid operation is attempted on a wrong math value
>> <br><br>1. <span style="color:orange">*object*</span> is the invalid math variable
<br><br>
>> 8. ### <a href="https://github.com/Gabriele-P03/Libraries/blob/main/exception/src/runtime/NotFoundException.hpp" style="color:yellow">IllegalCastException</a>
>> - Thrown whenever an invalid cast on an object is attempted
>><br><br> 1. <span style="color:orange">*object*</span> is the object which the invalid cast has been attempted on
>> <br>&nbsp;2. <span style="color:orange">*cast_attempted*</span> type which object has been cast to 
>> <br>&nbsp;3. <span style="color:orange">*cast_needed*</span> cast required 