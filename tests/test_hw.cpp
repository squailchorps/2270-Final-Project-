// If you change anything in this file, your changes will be ignored
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include "../code/BTree.h"
#include <gtest/gtest.h>

#include "quadtree.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <cstdlib> 
#include <ctime>


using namespace std;

class test_BTree : public ::testing::Test {
protected:
  // This function runs only once before any TEST_F function
  static void SetUpTestCase() {
    std::ofstream outgrade("./total_grade.txt");
    if (outgrade.is_open()) {
      outgrade.clear();
      outgrade << (int)0;
      outgrade.close();
    }
  }

  // This function runs after all TEST_F functions have been executed
  static void TearDownTestCase() {
    std::ofstream outgrade("./total_grade.txt");
    if (outgrade.is_open()) {
      int final_grade = (int)std::ceil(100 * total_grade / max_grade);
      outgrade.clear();
      outgrade << final_grade;
      outgrade.close();
      std::cout << "tests passed, no system errors. " << std::endl;
    
    }
  }

  void add_points_to_grade(double points) {
    if (!::testing::Test::HasFailure()) {
      total_grade += points;
    }
  }

  // this function runs before every TEST_F function
  void SetUp() override {}

  // this function runs after every TEST_F function
  void TearDown() override {
    std::ofstream outgrade("./total_grade.txt");
    if (outgrade.is_open()) {
      outgrade.clear();
      outgrade << (int)std::ceil(100 * total_grade / max_grade);
      outgrade.close();
    }
  }

  static double total_grade;
  static double max_grade;
};

 double test_BTree::total_grade = 3720;
 double test_BTree::max_grade = 3720;

TEST_F(test_BTree, CountNodes) {

  qtree tree(point(0,100),point(100,0));

  srand(time(NULL)); 

  for (int i=0; i < 100; i++){
    int x=rand()%101;
    int y = rand()%101;
    int value= i; 

    node* n = new node(point(x,y),value);
    cout << "Inserting: (" << x << "," << y << ") with value: " << value << endl;
    tree.insert(n);
  }

  cout << "Qtree Structure:"<< endl << endl;
  tree.printtree("");
  cout << "Node count: " << tree.countnodes() << endl;

  vector<point> list = {};

  point rangesearchpoint1(0,50);
  point rangesearchpoint2(50,0);
  tree.rangesearch(rangesearchpoint1,rangesearchpoint2,list);

  cout << "Range search inside box sized (" << rangesearchpoint1.x << "," << rangesearchpoint1.y << ") by"
     << rangesearchpoint2.x << "," << rangesearchpoint2.y << ").";

  for(auto p : list){
    cout << "(" << p.x << ", "<< p.y << ")"<< endl;
  }
  cout << "total points in range: ";
  int count = 0;
  for (auto p : list){
    count++;
  }
  cout << count << endl;
  vector<point> found_points = {};
  point topleftbox_1 = point(0,20);
  point botrightbox_1= point(20,0);
  point topleftbox_2= point(0,10);
  point botrightbox_2= point(10,0);
  
  tree.rectintersect(topleftbox_1, botrightbox_1, topleftbox_2, botrightbox_2,found_points);
  cout<< "Checking 2 bounding boxes with given points " 
  << "(" << topleftbox_1.x << "," << topleftbox_1.y << "), " 
  << "(" << botrightbox_1.x << "," << botrightbox_1.y << "), " <<
  "for rectangle 1 and "
  << "(" << topleftbox_2.x << "," << topleftbox_2.y << "), "
  << "(" << botrightbox_2.x << "," << botrightbox_2.y << "), " << 
  "for rectangle 2." << endl;

if (found_points.size() > 0){
 cout << "rectangles overlap, printing cordinates within bounds: " << endl;
 int count = 0; 
  for(auto p : found_points){
    cout << "(" << p.x << ", "<< p.y << ")"<< endl;
    count++;
  }
  cout<< "Total nodes within intersection: "<< count << endl;
}

else{
  cout << "No overlap found." << endl;
}
}
