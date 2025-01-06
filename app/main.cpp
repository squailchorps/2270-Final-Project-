#include "../code/BTree.h"
#include "../tests/BTreeTestHelp.h"
#include <iostream>

using namespace std;

int main() {

  // Do some printing
  int var;
  cout << "Hello World, please enter a number " << endl;
  cin >> var;

  btree* something = init_node(); // proof that the BTreeTestHelp symbols work
  cout << "your number was : " << var
       << " and the btree node has address: " << something << endl;
  return 0;
}
