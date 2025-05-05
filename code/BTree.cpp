#include "BTree.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>

void qtree::insert(node* node) {
//Check to make sure that the node we are inserting is not nothing.
    if (node==NULL){
        return;
    }

//check to make sure that the nodes position can even be inside of the given qtree.
    if (!inboundary(node->pos)){
        return;
    }

//check to make sure there is not already a point that exists at the point provided.
    if  (this->search(node->pos) != NULL){
        return;
    }    


//If the node we are in has nothing (no point or int data), and the tree has not yet been subdivided at all, we can insert a point here!
    if (this->n ==NULL&& this->topleft_tree==NULL){
        this->n=node;
        return;
}

    int midx = (topleft.x + botright.x)/2;
    int midy = (topleft.y + botright.y)/2;


    if (this->n != NULL){

        this->subdivide();

        if(this->n->pos.x <= midx){
            if(this->n->pos.y >=midy){
                topleft_tree->insert(this->n);
            }
            else{
                botleft_tree->insert(this->n);
            }
        }
        else{
            if( this->n->pos.y >= midy){
                topright_tree->insert(this->n);
            }
            else{
                botright_tree->insert(this->n);
            }
    }

    this->n=NULL;
}

    if (node->pos.x <= midx){
        if (node->pos.y >= midy){
            topleft_tree->insert(node);
        }
        else{
            botleft_tree->insert(node);
        }
    }
    else{
        if (node->pos.y >= midy){
            topright_tree->insert(node);
        }
        else{
            botright_tree->insert(node);
        }
    }
}

node* qtree::search(point p){
//check if point is within the boundary set for the qtree.
    if (!inboundary(p)){
        return NULL;
    }

//Check to see if the node has data and check to see that the nodes x and y match the search point parameters. 
//if so, return the current node.  
    if (this->n != NULL && this->n->pos.x == p.x && this->n->pos.y == p.y){
        return n;
    }

//calculate mid point 

    int midx = (topleft.x + botright.x)/2;
    int midy = (topleft.y + botright.y)/2;

    if (p.x <= midx){
        if (p.y >= midy){
            if (topleft_tree == NULL){
                return NULL;
            }
            return topleft_tree->search(p);
        }
        else{
            if (botleft_tree == NULL){
                return NULL;
            }
            return botleft_tree->search(p);
        }
    }
    else{ 
        if (p.y >=midy){
            if (topright_tree == NULL){
                return NULL;
            }
            return topright_tree->search(p);
        }
        else{
            if (botright_tree==NULL){
                return NULL;
            }
            return botright_tree->search(p);
        }
    }
}

bool qtree::inboundary(point p){
    return (p.x >= topleft.x && p.x <= botright.x && 
            p.y <= topleft.y && p.y >=botright.y);
}

void qtree::initializebounds(int x1, int y1, int x2, int y2){
    topleft=point(x1,y1);
    botright=point(x2,y2);
}

void qtree::subdivide(){

    int midx = (topleft.x + botright.x)/2;
    int midy = (topleft.y + botright.y)/2;

    topleft_tree= new qtree(point(topleft.x,topleft.y),point(midx,midy));
    topright_tree= new qtree(point(midx,topleft.y),point(botright.x, midy));
    botleft_tree= new qtree(point(topleft.x, midy),point(midx,botright.y));
    botright_tree= new qtree(point(midx,midy),point(botright.x,botright.y));

/* 
    This is to help me visualize what exactly the subdivide is doing 
    and get a better read on how to structure each point. 

  (0,10)              (5,10)             (10,10)
    +-------------------+-------------------+
    |                   |                   |
    |    topleft_tree   |   topright_tree   |
    |   (0,10)-(5,5)    |   (5,10)-(10,5)   |
    +-------------------+-------------------+
    |                   |                   |
    |   botleft_tree    |   botright_tree   |
    |   (0,5)-(5,0)     |   (5,5)-(10,0)    |
    +-------------------+-------------------+
  (0,0)               (5,0)              (10,0)

*/

}

//prefix should always be at the root with "". 
void qtree::printtree(string prefix){
    cout << prefix << "node: ";
    if( n != NULL){
        cout << "Leaf Node: Point(" << n->pos.x << "," << n->pos.y << ") - data: " << n->data << endl;
    }
    else{ 
        cout << "Internal node" << endl;
    }

    int children_count=0;

    if (topleft_tree != NULL){
        children_count++;
    }
    if (topright_tree != NULL){
        children_count++;
    }
    if (botleft_tree != NULL){
        children_count++;
    }
    if (botright_tree != NULL){
        children_count++;
    }

    int total_printed= 0;
    string connector="";
    string prefix2="";

    if (topleft_tree != NULL){
        total_printed++;
        if(total_printed == children_count){
            connector= "└── ";
            prefix2 = prefix + "    ";
        }
        else{
            connector = "├── ";
            prefix2 = prefix + "│   ";
        }

        cout << prefix << connector << "Top Left:" << endl;
        topleft_tree->printtree(prefix2);
    }

    if (topright_tree != NULL){
        total_printed++;
        if(total_printed == children_count){
            connector= "└── ";
            prefix2 = prefix + "    ";
        }
        else{
            connector = "├── ";
            prefix2 = prefix + "│   ";
        }

        cout << prefix << connector << "Top Right:" << endl;
        topright_tree->printtree(prefix2);
    }

    if (botright_tree != NULL){
        total_printed++;
        if(total_printed == children_count){
            connector= "└── ";
            prefix2 = prefix + "    ";
        }
        else{
            connector = "├── ";
            prefix2 = prefix + "│   ";
        }

        cout << prefix << connector << "Bottom Right:" << endl;
        botright_tree->printtree(prefix2);
    }

    if (botleft_tree != NULL){
        total_printed++;
        if(total_printed == children_count){
            connector= "└── ";
            prefix2 = prefix + "    ";
        }
        else{
            connector = "├── ";
            prefix2 = prefix + "│   ";
        }

        cout << prefix << connector << "Bottom Left:" << endl;
        botleft_tree->printtree(prefix2);
    }
  
}

int qtree::countnodes(){
    int count=0;

    if (n != NULL){
    count++;
    }

    if (topleft_tree != NULL){
        count += topleft_tree->countnodes();
    }
    if (topright_tree != NULL){
        count += topright_tree->countnodes();
    }
    if (botleft_tree != NULL){
        count += botleft_tree->countnodes();
    }
    if (botright_tree != NULL){
        count += botright_tree->countnodes();
    }

    return count;
}


void qtree::rangesearch(point range_topl, point range_botr, vector<point>& found_points){

    //check if node bounds are within search range. Allows me to look at specific areas
    //rather than the entire tree. 
    if (!intersect(this->topleft,this->botright,range_topl,range_botr)){
        return;
    }

    //if the node has a point in it, add it to the vector list.
    if (this->n != NULL){
        if(contain(range_topl,range_botr,n->pos)){
            found_points.push_back(n->pos);
        }
    }

    //if the node has children, recurse into them until we reach NULL.
    if (this->topleft_tree != NULL){
        this->topleft_tree->rangesearch(range_topl,range_botr,found_points);
        this->topright_tree->rangesearch(range_topl,range_botr,found_points);
        this->botleft_tree->rangesearch(range_topl,range_botr,found_points);
        this->botright_tree->rangesearch(range_topl,range_botr,found_points);
    }
}

// Add an intersects of two rectangles (from given top_left and bottom_right points) given within a tree. Then, give what POINTS are within that area of intersection.
void qtree::rectintersect(point top_left1, point bot_right1, point top_left2, point bot_right2,vector<point>& found_points){

    //if the two given rectangles do not intersect, return function and do nothing.
    if(!intersect(top_left1, bot_right1, top_left2, bot_right2)){
        return;
    }

    else{
        int topleft_x= max(top_left1.x,top_left2.x);
        int topleft_y= min(top_left1.y,top_left2.y);
        int botright_x= min(bot_right1.x,bot_right2.x);
        int botright_y= max(bot_right1.y,bot_right2.y);

        point intersectbox_topleft= point(topleft_x,topleft_y);
        point intersectbox_botright= point(botright_x, botright_y);

        this->rangesearch(intersectbox_topleft,intersectbox_botright,found_points);
    }
}

bool qtree::intersect(point top_left1, point bot_right1, point top_left2, point bot_right2){

    if (top_left1.x > bot_right2.x || top_left2.x > bot_right1.x){

        return false;
    }

    if (bot_right1.y > top_left2.y || bot_right2.y > top_left1.y){
        return false;
    }

    return true;
}

bool qtree::contain(point top_left, point bot_right, point p){
    return (p.x >= top_left.x && p.x <= bot_right.x 
           && p.y >= bot_right.y && p.y <= top_left.y);
}