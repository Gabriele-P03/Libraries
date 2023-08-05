# **Exception (CM) 1.0.0**
<h2><i>Exception</i></h2>
<br>
This module provides you some exception which could be useful in order to give more information about errors encourented during the life of your program. 
<br>All exception are extended as an hierarchy which as you can read in this documentation 
<br><br>
Keep in mind that, although JPL provide <a href="https://github.com/Gabriele-P03/Libraries/tree/main/logger" style="color:aqua">Logger</a>, it is not used in this module to print messages of occurred exception, it will be your duty to do it.<br>
Otherwise, you have to define <span style="color:purple">USE_EXCEPTION_W_LOGGER_JPL</span> before to include <a href="https://github.com/Gabriele-P03/JPL/blob/main/logger/src/LoggerWrapper.hpp" style="color:olive">LoggerWrapper.hpp</a>
<br><br>
The message of the thrown exception can be retrieved via <span style="color:green">what()</span> function.<br>
Some of those override this function in order to take out a template message composed by different arguments.<br>
Check each of them to get more information.
<br><br>
This module can be involved into using JPL's Stacktrace feature - provided by <a href="https://github.com/Gabriele-P03/Libraries/tree/main/utils" style="color:aqua">Utils</a> (into <span style="color:brown">debug</span>) - 
defining <span style="color:purple">USE_STACKTRACE_W_EXCEPTION_JPL</span>, then
you will be able to get stacktrace of the thrown exception via <span style="color:green">getStacktrace()</span>. <br>
Also, defining that macro, the stacktrace will be printed when the exception instance is passed to std::cout.<br>
Before to use this feature, you should take a look at <a href="https://github.com/Gabriele-P03/Libraries/tree/main/utils" style="color:aqua">Utils</a>'s DebugUtils paragraph in order to get more information about symbols and .pdb files   
