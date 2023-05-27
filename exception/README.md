# **Module: Exception**
<h2><i>Java similar exception</i></h2>
<br>
This module provides you some exception which could be useful in order to give more information about errors encourented during the life of your program. 
<br>All exception extends the same parent class, i.e. <span style="color:yellow">AbstractException</span>, although there is a defined hierarchy - packaging - as you can see below.  
<br><br>
Keep in mind that, although JPL provide <a href="https://github.com/Gabriele-P03/Libraries/tree/main/logger" style="color:aqua">Logger</a>, it is not used in this
module to print messages of occurred exception, it will be your duty to perform it.
<br><br>
The message of thrown exception can be retrieved via <span style="color:green">what()</span> function. Some of these exception override it in order to take out a template message composed by different argumentd passed to constructors.
