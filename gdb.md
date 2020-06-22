## GDB

_GNU debugger for computer programs_

The following code can be placed in a file called **foo.c**:
```
#include <stdio.h>
#include <stdlib.h>

struct foo {
  int m;
  int n;
};

void foo (void *ptr)
{
  struct foo lf = { .m = 3338, .n = 33329 };
  int *a = NULL;
  int b = 5;
  (*a) = 1;
}

int
main (void)
{
  struct foo f = { .m = 8, .n = 29 };
  printf ("hello world\n");
  foo (&f);
}
```

Once we compile (with debugging symbols: `-g`), this code basically prints **hello world**, passes some data to the `foo()` function, and then it will seg fault via the `(*a) = 1` statement, which is setting a number to a bad pointer (the `NULL` above).

```
$ ./a.out
hello world
Segmentation fault (core dumped)
```

A core file gets created in the directory:

```
-rw------- 1 moussa1 moussa1 16384 Apr 28 10:05 quartz386-a.out-46971.core
```

To get into gdb, we use the following command:

`gdb ./a.out <name-of-core-file>`

_note: make sure the core file size is set to unlimited. you can do this with the following command:_ `ulimit -c unlimited`

Once in gdb, we can type in `bt`, for backtrace:

```
(gdb) bt
#0  0x000000000040058f in foo ()
#1  0x00000000004005c3 in main ()
```

This basically says that the segfault happened in the `foo()` function. In a big program, it can help you get to the innards of how a seg fault happened.

We can print the values of variables with the following:

`p b` will print the value of **b**:

```
(gdb) p b
$1 = 5
```

You can also attach gdb to running programs too (like `strace`) for more advanced debugging with the command `run`:

```
Program received signal SIGSEGV, Segmentation fault.
0x0000000000400556 in foo (ptr=0x7fffffffdf20) at test.c:14
14	  (*a) = 1;
```

With the debugging symbols, it can tell you the file and line number (**foo.c:14**). Hypothetically, we wouldn't know what is causing badness, so we need to run the program step by step. To do this, we set breakpoints:

```
break foo
break test.c:12
break test.c:13
```

Then, with `run`, it will stop at the first breakpoint:

```

Starting program: /g/g0/moussa1/src/chat-about-stuffs/gdb-stuff/./a.out
hello world
Breakpoint 1, foo (ptr=0x7fffffffc8d0) at foo.c:11
11	  struct foo lf = { .m = 3338, .n = 33329 };
```

To move along to the next line, we use `step`:

```
Breakpoint 2, foo (ptr=0x7fffffffc8d0) at foo.c:12
12	  int *a = NULL;
```

To move to the next breakpoint, use `continue`.
