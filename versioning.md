## versioning

_software versioning is the process of numbering different releases of a particular software program for both internal use and release designation. It allows programmers to know when changes have been made and track changes enforced in the software._

##### project versioning

Common convention for project versioning is in the form **X.Y.Z**, where:

- **X**: major version
- **Y**: minor version
- **Z**: errata (or "patch") version

**major** version is for when you make incompatible API changes. **minor** version is for when you add functionality in a backwards compatible manner, and **errata** version is for when you make backwards compatible bug fixes.

Many projects follow these guidelines generally, but there are times when a project might not follow these principles exactly; they might interpret the version numbers differently.

_note: if the major number is < 1, the project is considered to be "in development." 1.Y.X is when the project has reached some maturity/stableness. This, again, can be a judgment call._

**minor** version has some different interpretations. Some view it as "decent changes," like a bug fix. Others view it as "added features." Regardless, the key for increasing a minor version number is that backwards compatibility is still maintained.

**errata** version is also up to some judgment when it comes to "minor bug fixes," something like a typo or adding/editing some documentation.

##### library versioning

An example:

Let's say we have a library **(1.0.0)** with the following functions:

```c
foo(int a);
bar(int b);
```

Then, we add a new function `baz(int c)`:

```c
foo(int a);
bar(int b);
baz(int c);
```

What should the new library version number be? Going off the rules above, we aren't adding a bug fix. The thing to notice here is that `foo()` and `bar()` did not change; they remain the same. We need the major version number to stay the same to indicate backwards compatibility for anyone who was using **(1.0.0)**. So, we'll actually want to number this **(1.1.0)**.

A person who relies on **(1.0.0)** can check the updated library and be confident that as long as the version is **(1.Y.Z)**, it doesn't matter. But someone who relies on `baz()` has to check that **X = 1** and **Y >= 1** in the version number.

Another example:

```c
foo(int a);
bar(int b);
baz(int c);
```

Now we make this change to `foo()`:

```c
foo(char *a);
bar(int b);
baz(int c);
```

We no longer have backwards compatibility. Anyone who was using `foo()` will have to edit their code. The new version number for this library should be **(2.0.0)**.

Generally speaking, companies like RedHat, with a product version, they promise application binary interface (ABI) stability / backwards compatibility during the entire lifetime of a product version. There are rare exceptions, like when there exists a severe security problem. But when a new major version comes out, nothing is promised. A bunch of libraries may change, and it will force re-compilation of code if the library major version number increased. 
