/*
 * thread_tree.h
 *
 * A threaded Tree header file used to represent a file system
 *
*/

#ifndef THREADED_TREE_H_INCLUDED
#define THREADED_TREE_H_INCLUDED

#include "treenode.h"
using namespace std;

class threaded_tree
{
    private:
        TREENODE* root; // root of the tree
        TREENODE* cwd; // current working directory
        void clearHelper( TREENODE* c ); // help to delete nodes
        void printPathHelper( TREENODE* c, ostream& out );
        //change directory help
        bool changeDirectHelp( TREENODE** temp, string path );
        //listRecursively help
        void printRecursiveHelp( TREENODE* c, int spaces, ostream& out );


    public:
        //constructor and destructor
        threaded_tree();
        ~threaded_tree();
        //Insert and Remove methods
        bool Insert( TREENODE* c );
        bool Remove( string NAME, bool directory );
        //List all files and directories in CWD
        void listInCWD( ostream &out );
        //print path from root to cwd
        void printPath( ostream &out );
        void printCWD( ostream &out );
        //change to a different directory if given valid path
        bool changeDirectory( string path );
        //list all in cwd and all sub directories
        void listRecursively( ostream& out );
};

#endif // THREADED_TREE_H_INCLUDED
