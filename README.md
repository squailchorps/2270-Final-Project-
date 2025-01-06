## Overview

In this assignment you will implement a B-Tree.

In most of the other self-balancing search trees (like AVL and Red-Black Trees),
it is assumed that everything is in main memory. To understand the utility of
B-Trees, think of the huge amount of data that cannot fit in main memory, such
as a database with petabytes of data, or a file system that is backed by
relatively slow disk storage. In those use cases, we accept that there is a
relatively high time cost for traversing the tree's layers, so we would like to
minimize the height of the tree to minimize the number of slow operations.

From a practical perspective, the main idea of using B-Trees is to reduce the
number of disk accesses to get the data.

If you haven't watched the Indiana Jones and the Temple of B-Tree lectures, I
recommend starting there.


## Objectives

This assignment asks you to design and implement a very complex data structure.
The head trip here is that you will almost certainly not be able to just sit
down, hack away without a plan, and end up with a 100%. You might have gotten
away with that with the previous assignments, but this is different. If you just
dive in and start hacking, you might hurt yourself. Instead, you need a plan.

So the objective of this assignment isn't _just_ about building a B-Tree, it is
more so about developing planning skills so that you can do really hard things.

So to be concise, the goals here are:

* Understand what a B-Tree is for, and when and why you'd use one. (Short
  version: databases and file systems).
* Be able to *design* an approach to make implementation more straightforward.
* Write your own test code (unit tests and otherwise)
* Implement a B-Tree
* Become more tenacious

## Planning Advice

You must approach the assignment by developing an overall strategy before coding
anything. With a careful plan of how you're going to work the problem, which
functions need to be implemented first, what helper functions will be needed,
and what algorithms will those functions use. Once you have all these questions
thought out, you can begin to implement and test your code.

I suggest that you begin testing your code by modifying the `main.cpp` code to
make calls to your implementation. Take a look at how the testing application
creates the environment for a test of your program. Create a known data
structure format explicitly and use it test individual functions.  

Study the contents of `BTreeTestHelp.h` and the related implementation file. It
is chock full of patterns and juicy bits from which you can draw inspiration.
You can use any of those functions from within your `main.cpp` test rig. It has
functions to hand-build various B-Trees, and you can always make similar
functions for your own testing.

You'll need helper functions. It is up to you to determine what those should be,
and how (or if) you test them individually. I strongly recommend writing tests
for your helper functions before you even implement the functions themselves.
That way you think through exactly what they should do, what happens if they're
given a NULL input, or a leaf node, or an overly-full node, or whatever else
might be conceivable in the situation.

### Look at the unit tests

The unit tests that come along with the assignment are meant to be read. There
are little hints strewn throughout them. In particular, the print_tree function
should be helpful. (Take a look at the `SanityCheck` unit test for help with
that.)

### Look at the helper functions that are used by unit test

There are some routines that would be useful in creating your own tests for this
assignment. There are helper functions that create trees with known
organizations. Take the `build_two-tier` function that will build a tree that
looks like the the following: 

![build_two_tier()](images/two-tier.png)

Take a look at the code to build this tree.  You can clone the code to
explicitly builds trees of your own.  Then you can use them to test different
cases within your code.

There are other functions that create other tree layouts from simple to full and
multi tier layouts.  See the `images` directory in the repository to view the
different layouts.

### Some things to keep in mind:

The `insert` and `remove` functions must handle cases where adding or removing
keys will grow or shrink the tree. In some cases you'll have to merge nodes and
re-allocate keys; other times you'll have to split nodes and similarly shuffle
keys around. Consider having logic to test the various situations in a function
and the code handle each situation in their own functions.  Now you can set up a
scenario to test each situation.

## Points

Like all the other assignments in this course, this one is worth 100 points.
However, given the difficulty level, you can score up to 200 points (so yay
extra credit).

Getting a 100/100 is super respectable. It shows that you have mastered many of
the techniques for handling B-Trees. Getting a 200/100 is possible, but to be
totally honest not many students get there. 

If you do build this past 100%, email your instructor with a link to your Github
repository, because Moodle doesn't know what to do with the extra points. We'll
grade it by hand to give the extra credit.