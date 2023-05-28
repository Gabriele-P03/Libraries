# Logger (CM)

This module offers to JPL project a Logger which is able to print onto terminal and write into a log file.

As you can see if you take a look at the header file, there's
a static instance which is used by JPL's modules that 
need to tell occurred events.<br>
This instance is always initialized unless you define CUSTOM_LOGGER_JPL macro which prevent the automatic definition of it and delegate to you the duty of defining it.

You should never avoid any definition of that, since no modules check a NullPointer on that static-member before to have called
<span style="color:green">print()</span> and therefore a Exception will be thrown (not JPL's one).<br>

In other words, for your project's function you can use either an another instance of Logger or the static one; but you cannot leave JPL's module without a logger instance.<br><br>

> <h2><i>QUIET MODE</i></h2>
> The quiet mode do not allow to logger to write on file (it will only print on terminal). It can be achieved with the true boolean flag passed to constructor.<br>This mode is available for the static instance used by JPL's modules even without defining CUSTOM_LOGGER_JPL and then call a constructor. You just need to define QUIET_MODULES_LOGGER_JPL macro
<br>

> <h2><i>UNFORCED WRITING</i></h2>
> The unforced writing mode does allow to program to keep running although the output file could not be created. Printing on terminal will be performed.<br>Define UFW_LOGGER_JPL macro to enable this feature 
<br>
<h2><strong>Please Note</strong></h2>
If UNFORCED WRITING's macro has been defined and, either QUIET MODE's macro is even defined or quiet parameter is set as true, they will not cause any errors.<br>
Of course, QUIET MODE has an higher priority rather than the other one
<br><br>
This module needs to be compiled as shared one in order to be used, and then you have to include the 
library (.so/.dll) in compile-time and run-time.<br>
By the way, I have already provided you the CMakeLists.txt file; since this project has been developed under Ubuntu, the text file has uncommented istruction for linux kernel (windows' ones are commented).<br>
A toolchain file is provided, too, with windows compiler.