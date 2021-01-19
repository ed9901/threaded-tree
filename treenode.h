/*
 * treenode.h
 *
 * treenode struct for use in
 * the threaded_tree class
 *
*/


#ifndef TREENODE_H_INCLUDED
#define TREENODE_H_INCLUDED
using namespace std;
struct TREENODE
{
    string name;
    bool isDirectory; // True if this node is a directory
    TREENODE* next; // points to next item in directory
    TREENODE* child; // pointer to subdirectory if needed
    TREENODE* parent; // threaded pointer back to parent
};

#endif // TREENODE_H_INCLUDED
