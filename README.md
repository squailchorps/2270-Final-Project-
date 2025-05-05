# Project Overview:

For my Final Project, I decided to implement a Quad tree. The Original goal of the project was to make a small game that could utilize the quad tree collision ability to allow objects to interact, but that did not end up working out for myself due to time and complexity. What I did get working overall was quad tree, point storing, and intersection checking of two rectangles and the points within their intersection within the quad tree. 

## Data Structure Description:

A quad tree is a data structure that is like that of a btree with different invariants. The quad tree allows for 4 children max on each node, and each node will either be a leaf, or point to the next node. This data structure is used as a way to divide up space and quickly allow for checking a quarter of the space for data rather than the entire space. This allows you to improve the efficiency by around 50%-75%. To start, since this is meant to divide out space, we would need a root, or a main space. Lets define it as (10,10). We would insert items until we get to 4, and once we get to 4 children our space is full, so we start to split the tree and create new children. Each parent can have 4 children, so the data from the parent would go to the child, while the parent becomes a pointer to the child. Some invariants of the tree are: 

1. All data is stored in the leafs.
2. All parents can have at max 4 children. 
3. If the node is internal, it will always point to its child and the parent will hold no data.

The specific type of quad tree I have made are regional quadtrees, which are the division of space equally into 4 parts.

## Project Successes/Failures:

Some small notes before I get into this portion:
1. I could not figure out how to change the names of the files without breaking the entire program. Each time I changed it, cmake would fail and i would be stuck. I ended up reverting and it ended up working, so just know that the files are titled btree, but it is definitely NOT a btree.
2. The only files I edited are under code folder, and under the tests folder. I ended up not making a main file for this and just utlized the test function. 
3. The olcPixelGameEngine.h is not used.
4. I could have made the tests actual functions. Since they only relied on one thing, it would not have been difficult to add it directly into the functions or make them their own seperate helper functions. 

When I set out on this project, I had originally wanted to make a game that could utilize the quad tree for collision detection. As the items get closer and closer, each check could see how far they were from one another, and once they overlapped, that would allow me to do something within the game through events. However, a number of issues popped up as I went.

#### 1.	Window Rendering:
One of the things Professor Quinn and I found was that when in the Jupyterhub VScode IDE, you cannot open a window as it is considered a terminal. This meant that any graphics engine would not work since it needed a window to be opened. We tried a few different methods, SFML, OLpixel game engine, and a few ASCII graphics, but the first two did not work at all due to the window issue, and the ASCII graphics were not what I needed to show the information. That means the idea of displaying items was cut.
  
#### 2.	Velocity:
Had I been able to use the window, I would have had to find a way to update physics within the engine to accommodate the constant checks of the quad tree with limited capacity. This added a dual issue, inefficiency and difficulty. Quad trees are great for collision detection, but there are other ways to do this in a more efficient way, like AABB trees, Octree’s, or KD trees. As well, the difficulty comes from how to utilize the SFML engine to call the quad tree to detect the collision. I thought of simple bool statements for it, but due to being unable to get the window to work it meant I could not test it to begin with. The only solution would be to install a local IDE, but that would have taken too much time and I was advised to not do it and move on from this point. 
  
#### 3.	Time:
I spent a lot of time trying to understand the structure of a quad tree. It confused me for awhile on how the tree split, or why it split at all. I read numerous threads from a lengthy stack overflow post here: https://stackoverflow.com/questions/41946007/efficient-and-well-explained-implementation-of-a-quadtree-for-2d-collision-det?noredirect=1&lq=1 , to this awesome information here on geeks for geeks : https://www.geeksforgeeks.org/quad-tree/ . These helped me understand the general idea of quad trees, but I struggled for so long on the why. My recovery from surgery as well as travel for work, meant my time was drastically cut from what I had hoped it to be. Given a few extra days, I believe I could have implemented a system to allow user input to check if two squares on a given grid were near each other. 

Over all, these 4 things led to me missing my goals. That does not mean I did a terrible job through this project and brought nothing! This project led to some amazing discoveries and learning opportunities, like:

#### 1.	Points within space:
Quad trees focus heavily on positional data. This proved to be difficult to tackle at first, but clicked in after some playing around. I was working within what was originally just code and index’s. Adding in two-dimensional data was an interesting challenge that did result in me starting to deeply understand struct and classes! This also led to better understanding of geometry, although I still feel a bit rusty. 

#### 2.	Efficient Constructors:
Originally, I had created my constructors like this: node(): { data=0}. I learned that this was fine to do, but is inefficient. From what I understand, this makes an initializer list and then create the variable data with random data, which then is assigned 0. While this is fine to use, best practice is to create the variables with their assignments at declaration, then create an empty list. This means that data gets put into the list immediately equaling zero, meaning it is more efficient. I have also read that it is better practice, but I cannot remember where I found that information at. Either way, I like this way better, as to me it is a little more clear. It looks like this: node() : data(0) {}.

#### 3.	Better understanding of code:
This project tested my abilities. I felt like I was struggling every step of the way, but I feel I grew immensely from the amount of reading, trial and error, and bug fixing I went through. While I realize this might not be a tangible boon from this project, I feel much more confident as a coder than I did at the beginning of this class. This project allowed me to learn how to read through a data structure, implement a rudimentary one, and understand overall how it functions to be able to utilize it in other areas. Already I can see what I could have done with more time, and that really makes me proud of myself and my work. 

Given both my short comings and my gains throughout this project, I am very happy with how this went. I hope that what I have given is enough to show my growth throughout the semester! 


## Explanation of each function within Project File:

I was unable to provide visuals from my code to showcase the properties, so below I have given descriptions with images I created to show how the code functions. This also goes in detail on how each part works, and examples of the functions results or usages. 

### Inintalize a Qtree:
To initalize a Qtree,  we would set a new variable and assgin it two points:
qtree tree(point(0,10),point(10,0));
The points are meant to represent the top left, and bottom right of the space. This menas the above quad tree initalization would give us a grid like this:
![quad tree setup](./images/basic%20quad.png)



### Insert: 
The insert function takes a node as an input that will be inserted into the tree. it will not have a return type. The function will first check if the node is real and has data. If it does not it will return and do nothing to the quad tree.

Next, The function will make sure that the node is within the boundary of the quad tree the function is being used on. If not, it will then return nothing since it cannot add anything to a space that does not exist. 

Last pre check is that we check to see if there is a node with the same positional data as the one we want to insert. If that’s the case, we will do nothing and return. These above cases help get us out of our recursion loops below. 

Now that we are outside of our initial set up checks, we will immediately see if the current spot we are in has any data in it already (in on of the 4 quadrants) and make sure that the node is a leaf node. If this is, we  will set the nodes n data to the node being inserted and return, meaning we have placed the node and the insert was completed. I put this check first as if the root is the only thing that exists with no data in it, then we can insert into the root before any other calculations occur. Afterwards, We start the fun math portion.

To begin, we need to set a midx and mid y point. The reason being is we are figuring out what the sub parts are to each of the given qtrees. Once we have found this and we know that the current node has data within it(as in, is not null), we subdivide it out. We subdivide here as the node we are looking at is technically where we want to place the inserting node, but since we cannot double stack, we must make the space smaller to put the current and new node into. This subdivide will be explained below. 

From here, the loops we are checking are to see which quadrant our old point (the this->n) should go into. Each if statement checks if it is within the topleft, top right, bottom left, or bottom right. We can do this by just checking the positions of the x and y to the mid point of the x and y we calculated before (midx and middy). I originally had this in a really unintuitive way, checking each quadrant with 4 separate nested if statements. I found another way where, using the points, we can check if its in the upper half, and then check if it is in the left half.  The first statement checks to see if it is in the left half, then checks directly afert to see if it is in the top half. If it is in that left part, but not the top part, it must be in the bottom left part! Rather than separating out each quadrant, we can just check through dividing up and saying true or false to each direction.

Once we have found the specific quadrant our data should go to, we call insert on that node into that quadrant. Afterwards, we want to make sure we define that old node (this-> n) as nothing, as I learned the hard way. Not doing this causes the qtree to say “oh there is data here, and that data exists over here and we can point to both positions at the same time”. That disobeys the invariants for a quad tree, so we have to make sure we remove that this->n data! 

Finally, once we have subdivided, we can insert the new point. However, we will perform the same checks to see what area it would go into. We would check to see if it is in the left half, and then in the top half, and if both are tree then it is in the top left half, just like our arguments from before, only instead of at the end inserting this->n, we insert the node now (called node).

Since we are calling insert again, it is going to check each time, in each quadrant, until it finds that the current quadrant is a leaf node and will insert there. Thus, completing the insert sequence. 

## Search: 
This function will search for a POINT within the given quad tree and return the node that the point coordinates are at. 

First we do an in boundary check, which allows us to see if the point is within the boundary of the quad tree. If it is not, we will return nothing, since we cannot find a node outside of the quadtree. 

Then, the next if statement is a double check to see that the node is not empty, and that the positional data in the node is the same as the positional data from the given point. If it is, we have found our node and can close this function out by returning the node. 

From here, we start the actual function:

We begin by calculating the middle of the y and x like we did for insert to see the quadrants. 

From there, we can check to see if the points x is smaller than the midx we know the point is somewhere on the left, and if the points y is bigger than the midpoints y, then we know for sure the point is within the top left quadrant. To catch any times where the tree is a leaf and has no data within it, we return null since that means we have gone down the tree as far as it can go and it does not contain the point. If the top left tree is not null, then we know we can search this part of the tree ONLY and not have to search every other quadrant, just the ones where the mid points contain the point. WE would continue to call the search until we either find the point, or find nothing, at which point we return and exit the search.

## In Boundary Check:

This simple function is a helper function for our major search and insert functions. All this does is compare the point to the bounds of the quad tree by accessing its top left and bottom right x and y values, and comparing them to the point x and y make sure they are within those bounds. If they are not, it will return false. Otherwise, it will return false! 

## Initialize bounds of Quad Tree:

I made this as I thought I would use it, but ended up just not using it due to being able to set the bounds when creating the quad tree. If the need arises that you need to change the bounds, you can utilize this to change the bounds by inputting the x and y for top left, and x and y for bottom right. 

## Subdivide: 
This function is meant to subdivide a given quadtree by assigning pointers to new quad trees that are for the 4 quadrants of the quad tree. All this does is calculate the mid point, and then create new quadrants using the mid points of x and y, and the current top left through bottom right quadrants points. 

To get more specific, I made this visual to understand for myself as I was calculating which points would go where to be able to reference as I go that is within the code. To make it a little more simplified here:

The new top left tree would be the old trees top left x and y value, with the midx and middy points. 

The new top right tree would be the mid x and top left’s y, and the bottom right x with mid y.

The  bottom left would be the top left x and mid y, and the mid x, bot right y.
And lastly, the bottom right would be the mid x and mid y, with the bottom rights x and y. 

This allows the creation of new quadtrees that are a quarter the size of the old tree. 

## Print Tree:
Ironically, this function took the longest to make! I had to do a lot of research to understand how to simply print a tree without the ASCII graphics .h file, which proved difficult.

This function just works as a way to visualize the quad tree by showing connections between all the parts, and allowing you to see where the children lead to! 

The way this functions is by first, defining the starting node. ( I could not find a way to set the first node as root without messing everything up afterwards, so it is always labeled as node). 

Since this function is supposed to be recursive, we want to make sure the node we are checking is not null. If it is not null, that means it is a leaf node and has some positional data we can print. If it IS null, that means we have an internal node, and it goes nowhere. 

From here, I made a way to count the child nodes by checking if each of the quadrants was not null. If it is not null, that means there are children, so we can count up! By checking all four, we can get anywhere from 1-4 total children. 
Once we have figured out how many children there are, we check each quadrant to make sure there is something there. If there is something there, we will increment a counter for total printed that compares to the number of children. If it is equal to the number of children, then we know we can close out this section of the node and use a └── . We add some extra spaces at the end as well, so that we can give it some space for the other nodes below it.

Otherwise, it means it MUST have a connection somewhere else, so it must have a connector that looks like this ├── and adds | to it to extend it down to connect another child later on.

This will be done for every quadrant, and then calls the print tree at the end of each of the statements to dive down those trees. This builds out the tree in a nice readable format! 

Thew implementation of this with a quad tree with points (2,4), (3,1), (3,3), (1,2), and (1,3) would look like this:

node: Internal node
├── Top Left:
│   node: Internal node
│   ├── Top Left:
│   │   node: Leaf Node: Point(1,3) - data: 4
│   ├── Top Right:
│   │   node: Leaf Node: Point(2,4) - data: 0
│   ├── Bottom Right:
│   │   node: Internal node
│   └── Bottom Left:
│       node: Leaf Node: Point(1,2) - data: 3
├── Top Right:
│   node: Leaf Node: Point(3,3) - data: 2
├── Bottom Right:
│   node: Leaf Node: Point(3,1) - data: 1
└── Bottom Left:
    node: Internal node


## Count Nodes:
This is an easy function that returns an int with no input for a quad tree by recursively searching each tree, then returning the count. Each recursive call adds 1 to the count, so it allows us to search the entire tree and count every node that exists. This will count all nodes that exist within the bounds of the quad tree. 

## Range Search: 
This function has you entre in the top left and bottom right of a rectangle that you want to search within on the attached quad tree. This will not return anything, but add the points to a vector given, so that there is a list of points within the given range. 

This will first check if the current bounded are within the range provided. If they aren’t, then we will just return and get out of this function, since this means the range is outside the trees bounds. 

This will check if the current node contains a node with positional data. It checks to see if it is not null, and then uses contain to see if it is within those bounds. It just checks that the top right and bottom left of the range of the rectangle could have the point from this node within it. If it can, it is added to the list, if not it is not added. 

From here, we go into ALL the children by searching the trees children. We look at this each time by checking the current nodes children by calling the range search all the way down. With our check above to see the intersect, if the bounding box is outside that child, it will return immediately so we aren’t just blinding checking everything. 

## Rectangle Intersect:
This function takes the top left and bottom right of two separate rectangles on a grid and sees if they intersect. If they do intersect, it will show what points are within their intersection by adding those points to the given vector. 
This first will just check to see if the two rectangles intersect. If they do not, we cannot find anything so we do nothing. 

Otherwise, we are going to find the top left x and y and bottom right x and y of the intersection point by using min and max. This allows us to then create a new top left and bottom right point and then range search that box, which would then pushback the points to the vector within that intersection point!

## Intersect: 
This is a helper function that checks if points will intersect. This will return true if they do, and false otherwise. 

This will start first with looking at the top of the box, by comparing the first boxes top left x point to the second boxes bottom left point. If it is greater, then it is NOT intersecting and we can return false. We then check to see if the first rectangles bottom right y is larger than the 2nd rectangles top left y, as well as the second rectangles bottom right y being greater than the first rectangles top left y. If any of these are true, that means no intersection. If they all return false, that means there MUST be an intersection, and so we return true.

In essence, we are looking to see if a rectangle is to the left or right of the other with no overlap, and then if it is completely above or below the other with no overlap. If neither is true, then they must intersect! 

## Contain:
This function is extremely similar to the in boundary check, but this time with custom points to utilize as a rectangle and a point to put in, rather than just checking 1 point against the quad tree.

This will just see if the extremes of the box provided are larger than the point given. If they are, it returns true. If not, it returns false! 


# What can you do with this code? 

What this allows for is the ability to place an infinite amount of points within the quad tree, call them, and even check how random rectangles provided by points intersect. While the initial goal was to provide a visual demonstration of how to utilize collision detection, I used it in a static way to show what the data structure could do. I added in the ability to see how many points were within the intersection point of the two rectangles, which, in a way, means that you can tell if two rectangles are colliding on a grid, or at least if they intersect. 

There is also an included edge case for insert! For insert, you can easily create two points with different data. Instead of allowing that, I make it to where the insert fails and inserts nothing in order to allow the program to continue forward. I would have liked to make a linked list to add data to the points and have their be multiple answer allowed for one point, but time did not allow that. 
In the code provided, it utilizes all the functions to print out a fancy randomly generated quad tree with randomly generated nodes and points. Each go around will yield different results into the quad tree! The space is set to 100x100, and has randomly inserted 100 nodes into the quad tree. The code will then print out the tree with nodes in specific areas! While a tree this big does get a little messy, I wanted to see the number this high to show how the code was able to handle a massive tree! Feel free to modify the initial tree points to be smaller, or the amount of nodes to be less! (modify line 78 for size, and line 82 for amount of nodes).

I also have it print out every node that is being inserted, allowing you to see specifically all points and verify they all made it in. 
There is also the custom range search that allows you to put in the box size you want to search the tree for. This will output those points to a list and print those out at the end. If you want to change the search range, change lines 98 and 99. 

Lastly, I have a rectangle search check to see if two rectangles are intersecting and to provide the points that are within that intersection. To change those, modify lines 115-118! 

A really coll thing is to show what the intersect would do: 

We have our original qtree with size (10,10):

![quad tree setup](./images/basic%20quad.png)

If we have points added to it randomly: 

![quad tree with 10 random points](./images/quad%with%10%points.png)

Then we query inside with two boxes, wiht one box sized (1,8) for top left, and (6,3) for bottom right, and box two sized (3,9) for top left, and (8,6) for bottom left. 

![quad tree with 2 rect](./images/two%rectangles.png)

The intersection area would be a rectangle with dimenssions of top left (3,8) and bottom right being (6,6). So within there is one point, which is (7,5)

The intersect would add only the points WITHIN  the bounds, and only the bounds of the new square. this would give an idea of how many nodes and points are within the intersected area! While this is not techincally showing the intersection, the program can detect that intersection and, had I had a little more time, could have quickly added a bool check to say if two squares were intersecting. While, technically this is that, and the helper function I made does that as well, I felt it would be better to show that I could recall the data just within the intersected area, rather than just saying if two shapes were interesecting. 

