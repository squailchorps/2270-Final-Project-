#include "BTree.h"

void insert(btree*& root, int key) {}

void remove(btree*& root, int key) {}

btree* find(btree* root, int key) {
btree* cursor = root;
if (cursor != nullptr) {
    if (contains(cursor->keys, cursor->num_keys, key) == true) {
        return cursor; 
        }
}
if (cursor->is_leaf==true){
    return cursor;
}
if (cursor==nullptr || cursor->children[0]==nullptr){
    return nullptr;
}
if (key<cursor->keys[0]){
    return find(cursor->children[0], key);
}
else if (cursor->num_keys < 2 || key < cursor->keys[1]){
    return find(cursor->children[1], key);
}
else if (cursor->num_keys <3 || key< cursor->keys[2]){
    return find(cursor->children[2],key);
}
else {
    return find(cursor->children[3],key);
}
return nullptr;
}

int count_nodes(btree* root){
btree* cursor = root;
if (cursor == nullptr){
    return 0;
}
int count = 1;

for(int i=0;i<cursor->num_keys+1; i++){
    if (cursor->children[i]!=nullptr){
        count += count_nodes(cursor->children[i]);
    }
}
return count;
}

int count_keys(btree* root) {
btree* cursor = root;
if (cursor == nullptr){
    return 0;
}
int count = cursor->num_keys;

for(int i=0;i<cursor->num_keys+1; i++){
    if (cursor->children[i] != nullptr){
        count += count_keys(cursor->children[i]);
    }
}
return count;
}

//a helper function to see if a value is inside of an array.
bool contains(int arr[], int size, int target){
    for (int i=0; i<size; i++){
        if (arr[i] == target){
            return true;
        }
    }
    return false;
}