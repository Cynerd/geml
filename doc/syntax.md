Syntax
------
Syntax consist from commands and variables. Both are defined in code with
initial character. In default `$`, but others can be used if specified as
argument to program. After this character is name of variable or command. Names
are case sensitive, without spaces and special character.

If you want use initial character without preprocessing, you should write it
two times. So if our initial character is `$`, you should use `$$`.
Also you can use `--permissive` argument to disable error when initial character is
not followed by known name. In such case is preprocessor threating it as it is
part of code and let it be without change. Be aware that collisions with names can
occur and no typing errors will be reported.

### Variables
Only variables preprocessor knows are text based. So even if some calculation has
to be made it is made with text. This slows down calculations, but removes
requirement of types definition. Special case are arrays.

If you use variable in file, it will be replaced directly with its value. So for
example if there would be defined variable "VAR" with value "Hello", result after
preprocessing of line
```
$VAR World!
```
would be
```
Hello World!
```

To set variable, see "set" command. To do mathematical operations see "eval"
command.

#### Arrays
Arrays are variables containing multiple texts. This can be handy when you want
store unknown number of text strings. Arrays in this preprocessor can have only
one dimension. They are created by command "set" and can be walked through with
command "for". Command "size" returns number of elements in array. Command "unset"
is removing elements from array.

Elements in array are indexed. Accessing some value is done with square bracket
and number. For example value of 0 index of array with name "ARRAY" would be
accessed with this syntax: "$ARRAY[0]". If array is referenced without brackets,
only first value is used. So value of index 0 is also accessible with "$ARRAY".

#### Special variables
Some variable names are reserved. Such variables can be used for various purposes.
##### SGP_VERSION
Contains version of sgp tool.
##### FILE
Array with names of all files that preprocessor is now working with. They are
ordered so current file is on index 0 and file including this file is on index 1
and so on.
##### LINE
Array with numbers of lines where preprocessor is now reading. They are ordered so
current line of current file is on index 0 and line in file including current file
is on index 1 and so on.

### Commands
Every command consist of its name and possible arguments. Arguments are enclosed
in brackets and between name and brackets are no other characters. Every argument
can be specified on multiple lines and separated from others with comma. Because
all evaluation is text based, arguments are also threated as text. Every empty
character (null, new line, space, tabulator) is removed from beginning and end of
argument. Also `"` and `'` characters are removed from beginning and end of
argument, but no other character is removed from beginning after them and after
last one on end should be only empty character. This allows common string
enclosures. Also if command has fixed number of arguments, last argument can
contains comas without being enclosured with `"` or `'`.

Some commands can be paired with some other commands. Common example is "if" with
its paired commands "else", "elif" and "endif"
##### include
##### set
##### unset
##### eval
##### if
##### ifdef
##### ifndef
##### if*
##### elif
##### else
##### endif
##### for
##### endfor
##### while
##### endwhile
##### exec
##### error
##### warning
##### define
##### undefine

#### Defining more commands
