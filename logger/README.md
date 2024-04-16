# Logger (CM)

It is a logging system which is used by most of all JPL's modules.<br>
There's a static instance already available which you ougtha always opt to use, since it is even the one used by JPL's modules.<br>
You should never include <span style="color:olive">Logger.hpp</span> directly, whereas <span style="color:olive">LoggerWrapper.hpp</span> checks whether use either Logger or just print on terminal or even inhibiting it.
<br><br>
<h3><i>CUSTOM MODE</i></h3>
As just read above, there's a static instance which is used by JPL's modules. Building logger
source file, passing to cmake <span style="color:purple">CUSTOM_LOGGER_JPL</span> you will inhibit the default instancing.<br>
<b><i>YOU WILL HAVE TO INSTANCE IT BY YOURSELF</i></b> otherwise undefined behaviours may occur

<!-- -->
<br><br>
<h3><i>QUIET MODE</i></h3>
Building logger source file, passing to cmake <span style="color:purple">QUIET_LOGGER_JPL</span> you will inhibit writing on file but it will keep printing on terminal.<br>
This quiet mode is available only for the default static instance, since it is done via cmake. If you are interested into QUIET MODE for your own, you must pass 
<span style="color:#ff5500">quiet as <i>false</i></span> to <span style="color:#ffa8e2">Logger(</span><span style="color:#ff5500">pathToFile</span>,<span style="color:#ff5500">quiet</span><span style="color:#ffa8e2">)</span>

<!-- Explaining Unforced Writing Mode-->
<br><br>
<h3><i>UNFORCED WRITING MODE</i></h3>
Logger, unless QUIET MODE has been enabled, needs an output file to print on; an error may occurs due to any reason while it is creating out file. This mode will not cause the exiting of the program once the error occurred. You just have to define <span style="color:purple">UFW_LOGGER_JPL</span> in order to achieve it.
If you wanna 