# JPL #
JPL is intended to be an independent multi-module open-source library for general engineering purposes. <br>
Although each module is meant to be independent from the others, some of them might include another one (OD), or even mutually (OMD); particularly, the Utils one is included by most of them (CM).<br>
<i>You can read about acronyms meaning at the end of this README file...</i> 
<br><br>
Every modules' documentation are written following a chromatic regulamantation. 
<br>
<b>(Actually it could not be striclty followed by all of them since they're still in WIP)</b>:
<br>![#7b4039](https://placehold.co/15x15/7b4039/7b4039.png) Package
<br>![#808000](https://placehold.co/15x15/808000/808000.png) Header
<br>![#ffff00](https://placehold.co/15x15/ffff00/ffff00.png) Class
<br>![#ffa8e2](https://placehold.co/15x15/ffa8e2/ffa8e2.png) Constructor
<br>![#0000ff](https://placehold.co/15x15/0000ff/0000ff.png) Field
<br>![#00ff00](https://placehold.co/15x15/00ff00/00ff00.png) Function
<br>![#ff5500](https://placehold.co/15x15/ff5500/ff5500.png) Argument
<br>![#ff0000](https://placehold.co/15x15/ff0000/ff0000.png) Exception
<br>![#80fdf8](https://placehold.co/15x15/80fdf8/80fdf8.png) Module
<br>![#8810ff](https://placehold.co/15x15/8810ff/8810ff.png) Macro
<br><br>
## Modules:

> ## Exception
> Exception

> ## Utils
> Utility functions, DS, Debug tools and so on...

> ## Logger
> Logger sub-system

<br><br>
# Dictionary

>## CM  (*Common Module*)
>> A module which is included by other ones without letting choose to the programmer. Beyond Utils one, it happens hardly ever

>## OD (*Optional Dependency*)
>> A module could include another one in order to do its tasks, but if the latter was not loaded successfully, program will not exit with failure. The first one will keep running such as it had never asked help to the other one

>## OMD (*Optional Mutual Dependency*)
>> Just like the OD, but they include each others.