# JPL #
A C++ project composed of several modules which are independent by each other. There are some of them, i.e. Common Modules (CM), which are used by other ones; they will be
marked as "CM".
<br><br>
Keep in mind that all modules contains a README_external.md which is the documentation of the current module. It is not named as "README.md" just to not be rendered by GitHub, since its md-parser does not work properly. I suggest you to take a look at them through an IDE, e.g. vs-code (which is that one used to develop this project).
<br><br>
There's a chromatic protocol in order to understand the documentation of the whole project, which is, of course, observed by all of single modules' ones:
<br>![#7b4039](https://placehold.co/15x15/7b4039/7b4039.png) Brown: package
<br>![#ffff00](https://placehold.co/15x15/ffff00/ffff00.png) Yellow: class
<br>![#ffa8e2](https://placehold.co/15x15/ffa8e2/ffa8e2.png) Pink: constructor
<br>![#0000ff](https://placehold.co/15x15/0000ff/0000ff.png) Blue: field
<br>![#00ff00](https://placehold.co/15x15/00ff00/00ff00.png) Green: function
<br>![#ff5500](https://placehold.co/15x15/ff5500/ff5500.png) Orange: argument
<br>![#ff0000](https://placehold.co/15x15/ff0000/ff0000.png) Red: exception (which may be thrown by a function/constructor)
<br>![#80fdf8](https://placehold.co/15x15/80fdf8/80fdf8.png) Aqua: module
<br>
<br>
If a module documentation contains a list of argument(orange) below the declaration of any class(yellow), it means that class has only one constructor which accept those list of arguments (then you will not find documentation about any constructor).
<br>
<br>
<br>
<br>
Here you are the list of stable modules already available:
<br>
<br>
1. ## Exception ##
> Exceptions similar to Java's ones
