Built-in commands
=================
Here is full list of all build in commands including its description and sometime
usage examples. For more information see syntax documentation.

All build in commands are defined in lover case as they are presented here, but
also in upper case. Also you can change initial character, we use here default one
(`$`).

###	$include(PATH)
Includes file content to its place. `PATH` is system path relative to current file
folder or absolute path.

With this command you can nest any other file content and this content. Note that
because of evaluation principles, content can be evaluated multiple times. If it
is not what you want, common idiom would be use:
```
$limit(0)$include(file)$endlimit
```

### $load(...)
This loads additional modules. Geml searches with precedence for modules in file
directory and in paths defined by environment variable `GEMLMODULES`. `NAME` is in
such case relative path to module, but also absolute path can be used.

Be aware that modules stays loaded even after current file preprocessing is
finished. They are not unloaded automatically after return from include.

For more information see module documentation.

### $unload(...)
Serves as opposite to `load` command. It is as it says unloading modules. But it
is not paired with load.

Without any argument `unload` will unload all loaded modules.

### $limit(NUM)
This command limits number of evaluation cycles for some text (see evaluation
documentation).  After this command all text will be evaluated only `NUM` times.
So `NUM` should be number. Passing empty string results in disabled evaluation
until end of limit command. Default value if not limit command is used is `inf`,
that means no limit.  Limit can be ended using `endlimit` command.

Because of how limit works. Most likely you will use limit without any argument or
with `inf`, or with `1`. Lets see once again what every one does. No argument is
same as `0` so no evaluation is done until `endlimit` command. `inf` removes any
limit and allows any number of nested evaluations. `1` specifies that evaluation
should be done only once.

You can nest limits together. This results to situation when content is evaluated
limited times but some part of it that is wrapped in another limit block will be
evaluated few times more without sucking up its root limit.

### $endlimit
This ends previous evaluation limit. Text after this command is not limited by
that.

### $"
### $'
This is almost same command as `$"`. It has same behavior as if you would write:
```
$"$limit $Text $endlimit$"
```
Where result would be:
```
 $Text 
```
So its also limits evaluation.

### $set(VAR,VALUE)
### $define(VAR,...)
### $enddefine
### $undefine(VAR)
### $math(EQ)
### $if(COND)
### $ifdef(VAR)
### $ifndef(VAR)
### $elif(COND)
### $else
### $endif
### $for(VAR,COND,EQ)
### $endfor
### $while(COND)
### $endwhile
### $switch(VAR)
### $case(VAL)
### $default
### $break
### $continue
### $exec(EXEC,...)
Calls executable `EXEC` with rest of arguments as arguments for executed program.
Standard output from this program is than included to same place as `exec`.

### $shell(CMD)
This is same as exec, except that instead of defining executable and command line
arguments separately they are defined together in `CMD` argument. In fact you can
specify any shell command in `CMD`.

### $error(TEXT)
`TEXT` is printed to error output and spg is terminated.

### $warning(TEXT)
`TEXT` is printed to error output, but geml continuous preprocessing text.

### $info(TEXT)
Simply prints `TEXT` to standard output. If standard output is used as output of
result, info is printed to error output.
