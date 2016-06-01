Syntax
======
Syntax consist from expandable macros and commands. They are both used in code
with initial character. In default `$`, but other can be used if specified as
argument to program. After this character is name of macro. Names are case
sensitive, without spaces and special character, except underscore.

For example this text:
```
$set(VAR, Hello)$VAR World!
```
Is expanded to:
```
Hello World!
```

If you want use initial character without preprocessing, you should write it two
times. So if our initial character is `$`, you should use `$$`.  Also you can use
`--permissive` argument to disable error when initial character is not followed by
known name. In such case is preprocessor treating it as it is part of text and let
it be without change. Be aware that collisions with names can occur and no typing
errors will be reported. Also you can limit preprocessing with `limit` command. If
you set limit, only given number of macros and commands is expanded.

Macros and commands can have arguments. Arguments are used to pass text to them.
Every argument can be specified on multiple lines and separated from others using
coma. All empty characters (spaces, tabulators and new lines) are removed from
beginning and end of argument. You can enclosure argument using `$'` or `$"`, which
will ensure that empty characters will stay in argument. But be aware that even
when `$'` or `$"` is used macros and functions inside argument is evaluated. Another
usage for enclosing argument to `$'` or `$"` is to ignore `)` and `,`.

End of macro or command is identified by other character that is not known. Or
bracket that is used to bound arguments to commands and macros. Or you can use `-`
as special meaning. `-` is removed during processing which allows you to paste
anything anywhere. For example `Without$SPACE-spaces`.

Difference between macros and commands is that macros are defined in text and
allows only simple expansion. Additional commands are defined using modules.
At the end, commands are more versatile than macros, but requires more work to
create.

Some commands can be paired with some other commands. Common example is "if" with
its paired commands "else", "elif" and "endif". Paired commands are defined as
that first of them defines behavior and second one ends it or changes it for next
text. It should newer be that second one somehow defines behavior for previous
processed text. Also to ensure that code is contained inside file, all first
commands allowing pairs has default ending command. If file is read to end and no
pair is found, default end is artificially inserted. Also no paired command opened
before including can be ended in included file.

Special macros
--------------
These macros has special meaning. They can't be redefined, but can be overloaded
using modules. And they are not defined in processed text.
### SGP_VERSION
Expands to version of sgp tool.
### FILE
Expands to name of file that is processed. This macro is not changing during whole
preprocessing. Note that you can use it in included files to identify name of
original preprocessed file.
### LINE
This macro is expanded always to line number on which it is specified in source
text.
### MODULES
This macro specifies coma separated list of active modules.
