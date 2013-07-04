libsf
=====
_A lightweight framework of core types for modern C programs._

`libsf` is a small framework for C composed of lightweight, dynamically allocated, immutable, reference counted types.  Core types in `libsf` include:

 - `sf_array_t`, a C array of `libsf` types
 - `sf_hash_t`, a hash table
 - `sf_list_t`, a linked list of `libsf` types
 - `sf_string_t`, a null-terminated C string

`libsf_test` is a companion framework for writing unit tests.  `libsf_test` is built on top of `libsf`.

`libsf` requires a C99 compiler, a 32-bit or larger processor and an execution environment where heap allocation with `malloc()` is not constrained.

Currently, `libsf` is developed on OS X 10.8.4 with Apple's LLVM 4.2 compiler.
