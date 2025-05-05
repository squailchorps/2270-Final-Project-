#ifndef BTREE_H__
#define BTREE_H__

#include <memory>
#include <string>
#include <vector>


using namespace std;

// The QUADTREE_MAX_DEPTH definition sets the quad trees maximum depth. 
// This was unused as I just made the structure below have 4 quadrants at each qtree creation.
#define QUADTREE_MAX_DEPTH 4
//The MAX_CHILDREN definition helps to keep the maximum children to 4 per node. While unused, was a helpful reminder!
#define MAX_CHILDREN 4

//This is a point that stores the positional data of an item. 
struct point {
  int x,y;
  point(int _x, int _y)
  {
    x=_x;
    y=_y;
  }
  point() : x(0), y(0) {}
  };

struct node{

  point pos;
  int data;

  node(point _pos, int _data){
    pos=_pos;
    data=_data;
  }

//This constructor assigns data to 0 FIRST before the constructor runs.
//while not really nessecary for this samll of a project, 
//it is a great practice for future usage in all my classes! I learned about this
//by looking at others code and wondering why it existed that way, and found https://www.geeksforgeeks.org/when-do-we-use-initializer-list-in-c/ . 
  node() : data(0) {}
};

//i had originaly wanted to make rectangles, but ended up going with poitns instead using some range determination from x and y to make the rectangles.
//While using the rect would have been nice, it become difficult to wrap my head around. 
// two points was already hard enough!  
// struct rect{
//   int x;
//   int y;
//   int w;
//   int h;

//   rect(int x, int y, int h, int w){
//     this->x=x;
//     this->y=y;
//     this->w=w;
//     this->h=h;
//   }
//}

class qtree{
//the distance bounds for the nodes of this tree.
  point topleft;
  point botright;

//the data for the nodes of the tree. Just set as an int. Can be made anything! 
  node* n;

//Children for the specific tree. Includes 4 sections that can have 
//children placed within it. These are pointers to allow pointing to 
//the next tree, rather than just being the data. 
  qtree* topleft_tree;
  qtree* topright_tree;
  qtree* botleft_tree;
  qtree* botright_tree;


public:
  qtree() : topleft(point(0,0)), botright(point(0,0)), n(NULL), topleft_tree(NULL),
            topright_tree(NULL), botleft_tree(NULL), botright_tree(NULL) {}  

  qtree(point topl,point botr): topleft(topl), botright(botr), n(NULL),
                                topleft_tree(NULL), topright_tree(NULL), 
                                botleft_tree(NULL), botright_tree(NULL) {}

//inserts a node into the quad tree. Has no return. 
//This insert will insert into a leaf, and nowhere else. If there is no leafs available due to depth being reached, the insertion will fail. 
//If there is a duplicate, the insertion will NOT insert the new data, and will fail.
  void insert(node*);

//This method will look for a point inside of the given quad-tree. It will return the node where the point is at. 
//if no node exists, returns NULL. 
  node* search(point);

//Helper function. This method will see if the current point is inside the quad tree. Will return true if it is within, false if not. 
  bool inboundary(point);

//used to initialize the bounds of the q tree.
//Takes inputs of x and y for upper and lower bounds.
  void initializebounds(int x1, int y1, int x2, int y2);

// this function allows me to subdivide once max children are reached.
//it will assign all parts of tree to the new child, having them point to the new area.
  void subdivide();

//helper function for printing out whats in the tree
  void printtree(string prefix);

//helper function for counting total nodes inside of the tree.
  int countnodes();

/* Range Search allows you to take a quad tree, input a topleft and bottom right
query, allowing you to check that, within the given quad tree and the given
bounds, is there any data there. This will need a list to add the points to. Any points
inside of the vector will be points within the bounds, including on the bnounds of the square
as that counts as "within".
*/
  void rangesearch(point range_topl, point range_botr, vector<point>& found_points);

  /* This intersects is a helper function for my range search. 
  this takes in the cordinates for the bottom right and top left of the quadtrees node boundary
  and the topleft and bottom right of the query range. 
  This will allow me to check both above and below, as well as left and right by using || in two statements. 
  If it returns true, that means there is an intersection, while false would mean zero intersect. 
  */
  bool intersect(point top_left1, point bot_right1, point top_left2, point bot_right2);
  
  /* while this is similar to my inbounds check, this allows for placing the top_left and bottom_right
  points to allow for custom checks for specific ranges. Only used as a helper function within range search.
  */
  bool contain(point top_left, point bot_right, point p);

  void rectintersect(point top_left1, point bot_right1, point top_left2, point bot_right2,vector<point>& found_points);
private:
//I ended up not needing/using these. I had orignally made them to make a max depth,
//but by avoiding duplicate insert, it ended up being fine! 
//Max Children was solved by giving every tree 4 quadrants at start. 
int depth= QUADTREE_MAX_DEPTH;
int max_children=MAX_CHILDREN;
};

#endif // BTREE_H__