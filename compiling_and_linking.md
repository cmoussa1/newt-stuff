## GCC Compiler Options and Linking

Put the following into a file called **foo.c**:

```
#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>

int main(void) {
  int a;
  json_t *o = json_string("hello world");
  printf("%s\n", json_dumps(o, JSON_ENCODE_ANY));
}
```

If you try to compile this with just `gcc`, you'll get the following error:

```
$ gcc foo.c
/var/tmp/moussa1/cclPASbd.o: In function `main':
foo3.c:(.text+0xe): undefined reference to `json_string'
foo3.c:(.text+0x23): undefined reference to `json_dumps'
collect2: error: ld returned 1 exit status
```

Some functions aren't in C natively, they are in a library, so we have to
link them with `-l`:

`$ gcc foo.c -l jansson`

Basically, when symbols/references are missing, it's often because a library is missing. Another common option is `-W` to help gcc give you warnings about your code. Most people do `-Wall` to generate warnings for everything.

If you type `man gcc` there are tons of warning options.

```
$ gcc -Wall foo.c -l jansson
foo3.c: In function 'main':
foo3.c:8:7: warning: unused variable 'a' [-Wunused-variable]
   int a;
       ^
foo3.c:11:1: warning: control reaches end of non-void function [-Wreturn-type]
 }
 ^
 ```

We could remove the statement for declaring variable `a`, as well as add a `return 0` to remove the warnings.

---

##### More common compiling options

The `-c` option is next. **Compiling** can be thought of as two steps: compiling and linking. `gcc` does both by default.

`gcc -c foo.c` will produce a **foo.o** file. Now we can link the file with `gcc foo.o -ljansson`. The `-o` option will allow us to specify an output filename

The `-O` option is for optimization . There are different optimization levels; most of the time, people pass in `-O2`.

`-g` is for debugging, but we don't turn that on for production use because you want code to work faster (although we often turn it on for code that is more experimental, because we know we'll need to debug it). So if you aren't turning on debugging you can turn on optimization, which will tell the compiler to do extra optimizations.

**CFLAGS** is the config variable via `configure` that'll tell you if you want to set special gcc compiler options.

---

###### To make our own library

In a file named **mylib.h**:

```
void helloworld(void);
```

In a file named **mylib.c**:

```
#include <stdio.h>
#include <stdlib.h>

void helloworld(void) {
  printf("lib hello world\n");
}
```

And in a file named **main.c**:

```
#include <stdlib.h>
#include <mylib.h>

int main()
{
  helloworld();
}
```

First, we need to compile and create an object file for our library:

`$ gcc -c -Wall -fpic mylib.c`

The `-f` option is passed for various compiler special options.

Now we can make a "shared library file":

`$ gcc -shared -o libmylib.so mylib.o`

Now we set LD_LIBRARY_PATH to where the shared library is.

`$ export LD_LIBRARY_PATH=<path/to/shared_library>`

Then we do:

`$ gcc -I. -L. main.c -lmylib`

One more tiny option for gcc:

```
#include <stdio.h>
#include <stdlib.h>
#define FOOBAR "hello foo"

int main(void) {
  printf("%s\n", FOOBAR);
}
```

We can comment out FOOBAR and instead define it in the gcc instruction:

`gcc -DFOOBAR='"lalala"' test.c`
