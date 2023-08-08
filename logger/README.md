# Logger (CM)

This module offers to JPL project a Logger which is able to print on terminal and write on a log file.

As you can see if you take a look at the header file, there's
a static instance which is used by JPL's modules that 
need to print occurred events.<br>
This instance is always initialized unless you define either <span style="color:purple">CUSTOM_LOGGER_JPL</span> or <span style="color:purple">DISABLE_LOGGER_JPL</span> macro which prevent the automatic definition of it and delegate to you the duty of defining it.<br>
Acutally, you may even let modules use that static instance without writing on file, check QUIET MODE for more details.


In other words, for your project's function you can use either an another instance of Logger or the static one; but you cannot leave JPL's module without a logger instance.<br><br>

> <h2><i>ENABLE LOGGER</i></h2>
> Most of all JPL's modules, by default, are able to log events via this module.<br>
> In order to enable this feature, you have to define <span style="color:purple">USE_LOGGER_JPL</span>.

> <h2><i>DISABLE LOGGER</i></h2>
> It prevent printing for all JPL's module which invoke <span style="color:green">print()</span><br>
> <span style="color:purple">DISABLE_LOGGER_JPL</span>.

> <h2><i>QUIET MODE</i></h2>
> The quiet mode does not allow to logger to write on file (it will only print on terminal).<br>
> To achieve this feature, if you are going to use the default static instance - or rather you have not defined <span style="color:purple">CUSTOM_LOGGER_JPL</span> - you just have to define even <span style="color:purple">QUIET_LOGGER_JPL</span>.<br> 
>If you are going to use your own static instance, the quiet mode can be achieved via the quiet parameter of the constructor (true value). It means that, you do not need to define that macro, too.

> <h2><i>UNFORCED WRITING</i></h2>
> The unforced writing mode does allow to program to keep running although the output file could not be created (Only printing on terminal will be performed).<br>Define <span style="color:purple">UFW_LOGGER_JPL</span> to enable this feature. 

> <h2><i>CUSTOM LOGGER</i></h2>
> By default - always if you have at least defined <span style="color:purple">USE_LOGGER_JPL</span> - a default static instance of this module is initialized. If you would like to instance your, you have to define <span style="color:purple">CUSTOM_LOGGER_JPL</span> 
<br>
<h2><strong>Please Note</strong></h2>
Everytime you define either <span style="color:purple">CUSTOM_LOGGER_JPL</span> or <span style="color:purple">QUIET_LOGGER_JPL</span> or <span style="color:purple">UFW_LOGGER_JPL</span>, implicitly you are going to define even <span style="color:purple">USE_LOGGER_JPL</span>; it means that you do not need to define this latter macro, too.
<br><br>
Everytime you define <span style="color:purple">DISABLE_LOGGER_JPL</span> and any other Logger's macro, an #error is printed  
<br><br>
<span style="color:purple">CUSTOM_LOGGER_JPL</span> and <span style="color:purple">QUIET_LOGGER_JPL</span> are checked into the source file, therefore you have to define them when you are building this module via cmake.
<br><br>
If you have defined <span style="color:purple">QUIET_LOGGER_JPL</span> (or quiet parameter as true in case of custom instance) and <span style="color:purple">UFW_LOGGER_JPL</span> both, the quiet mode has the priority - since it is checked before trying to create the output file.
<br><br>
If you have NOT defined <span style="color:purple">UFW_LOGGER_JPL</span> and an error occurred during output-file creation, no exception are thrown, it is just printed on terminal and then the program will exit with an EXIT_FAILURE code.<br> 
Otherwise, if you need to ensure if no error occurred, you should check <span style="color:green">Logger::isWriting()</span>.
<br><br>
If you wanna disable logging for all JPL's module but you wanna do it in other context of you program, the best way you can go through is to define the 
disabling macro and include directly Logger.hpp (not LoggerWrapper.hpp) since all JPL's module include the latter header file and furthermore macro-checks are done into it, too