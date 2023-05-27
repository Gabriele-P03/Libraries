# **Utils (CM)**
## Utils Function
<br>
This module provides you several useful function which are used
through all JPL's module.
It is splitted into headers file which can be considered as 
sub-modules
<br><br>
This module may be seen even as a SDM (Self-Dependency Module) since some of its headers include some others of this same module.
<br><br>
Since all its headers can be considered as sub-modules, you can download those ones you need and discard all other ones (unless they are not included by those ones you need). 
<br>
<br>

## List of Sub-Modules:
> BitsUtils
>> To operate on bits (boolean array)

> CharUtils
>> To manage chars array

> ConversionUtils
>> To perform conversion between data-type

> ErrorUtils
>> To enhance checking of last error occurred

> FilesUtils
>> To reading/getting file and path<br><br>
>> <span style="color:orange">*Required Sub-Modules:*</span> 
>>> ErrorUtils 

> DebugUtils
>> To provides some function whilst debugger is attached<br><br>
>> <span style="color:orange">*Required Sub-Modules:*</span> 
>>> ErrorUtils 