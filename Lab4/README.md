# Lab #4 (tool Valgrind)

* ### Purpose

~~~
- find ... 
- memory leaks
- uninitialized variables
- bad memory accesses
~~~

* ### Valgrind Usage

just download with terminal,
`$ sudo apt-get install valgrind`

~~~
$ g++ -Wall exp1.cc
$ valgrind ./a.out
~~~

* ### Lab 

>1. Compile - Valgrind - Fix

~~~
g++ -Wall -g exp1.cc -o exp1
valgrind ./exp1
~~~

>2. Pick one of your 10 fixed examples.

* ### Source of Example codes & FAQ

~~~
https://www.cs.colostate.edu/~cs253/Labs/Valgrind/

https://www.cs.cmu.edu/afs/cs.cmu.edu/project/cmt-40/Nice/RuleRefinement/bin/valgrind-3.2.0/docs/html/faq.html#faq.pronounce
~~~

