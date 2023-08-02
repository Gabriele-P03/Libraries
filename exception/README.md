# **Exception (CM)**
<h2><i>Exception</i></h2>
<br>
This module provides you some exception which could be useful in order to give more information about errors encourented during the life of your program. 
<br>All exception are extended as an hierarchy which as you can read in this documentation 
<br><br>
Keep in mind that, although JPL provide <a href="https://github.com/Gabriele-P03/Libraries/tree/main/logger" style="color:aqua">Logger</a>, it is not used in this module to print messages of occurred exception, it will be your duty to do it.
<br><br>
The message of the thrown exception can be retrieved via <span style="color:green">what()</span> function. Some of these exception override it in order to take out a template message composed by different argumentd passed to constructors.
<br>
This module needs Boost's Stacktrace in order to work since it even provides getStacktrace() which returns a stacktrace of the exception thrown
