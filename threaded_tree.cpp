/*
 * thread_tree.cpp
 *
 * Threaded Tree implementation used to represent a file system
 *
*/

#include<iostream>
#include<cstring>
#include "threaded_tree.h"
using namespace std;

/*****************************
*    Default constructor
******************************/
threaded_tree::threaded_tree()
{
    // constructor sets up the tree with
    // the root node "/".
    // cwd is "/" by default until changed.
    root = new TREENODE;
    root->name = "/";
    root->isDirectory = true;
    root->next = root->child = NULL;
    root->parent = root;
    cwd = root;
}

/***************************
*       Destructor
****************************/
threaded_tree::~threaded_tree()
{
    //call clearHelper to delete everything
    //including the root
    clearHelper(root);
}

/*****************************
*   Insert by pointer into the cwd
*   kept in lexicographical order
******************************/
bool threaded_tree::Insert( TREENODE* c )
{
    // insertion happens in the cwd,
    // all files/directories are kept in
    // lexicographical order.
    TREENODE* p = cwd->child;
    TREENODE* q = NULL;

    //Set threaded pointer to cwd
    c->parent = cwd;
    //scan until place is found or until a duplicate name is found
    while( p && (p->name != c->name) && (p->name < c->name) )
    {
        q = p;
        p = p->next;
    }
    //if a duplicate name is found, don't add it to the directory
    if( p && p->name == c->name )
    {
        delete c; // delete the node passed in
        return false;
    }

    else if( q == NULL ) // empty or goes in first position
    {
        c->next = p;
        cwd->child = c;
        return true;
    }
    else // goes in the middle or last position
    {
        q->next = c;
        c->next = p;
        return true;
    }
}

/*******************************
*   Remove by name and type
*******************************/
bool threaded_tree::Remove( string NAME, bool directory )
{
    // remove from cwd, directory is a flag passed in
    // to indicated if removal is for a directory or file.
    TREENODE* p = cwd->child;
    TREENODE* q = NULL;
    //search for the name
    while( p && p->name != NAME )
    {
        q = p;
        p = p->next;
    }
    if( p == NULL ) // name not found
    {
        return false;
    }
    //Name was found and the types match
    else if( directory == p->isDirectory )
    {
        if( q == NULL ) // Removal of first node in directory
        {
            cwd->child = p->next;
        }
        else // removal of a middle or last node
        {
            q->next = p->next;
        }
        p->next = NULL;
        // delete the file or directory.
        // clearHelper also deletes any subdirectories if needed
        clearHelper(p);
        return true;
    }
    else // Name was found but it is the wrong type
    {
        return false;
    }
}

/***********************************
* List everything in the CWD, file names are given normally
* directory names have a "/" appended to them
*************************************/
void threaded_tree::listInCWD(ostream &out)
{
    //Start with the first node in the cwd
    // and loop through printing the names
    // of each node.
    TREENODE* p = cwd->child;
    while( p )
    {
        out << p->name;
        if( p->isDirectory )
        {
            out<<"/ ";
        }
        out<< " " <<endl;
        p = p->next;
    }
    return;
}

void threaded_tree::printPath(ostream &out)
{
    printPathHelper( cwd, out);
}

/************************************
* Recursively deletes given node and
* all subdirectories that may hang off.
*********************************/
void threaded_tree::clearHelper( TREENODE* c )
{
    if( c )
    {
        clearHelper( c->next );
        clearHelper( c->child );
        delete c;
    }
    return;
}

/***************************
* Recursively travels back up to the root.
* Prints out each directory's name on the way back down
* from the recursion.
****************************/
void threaded_tree::printPathHelper( TREENODE* c, ostream& out)
{
    if( c != root)
    {
        printPathHelper( c->parent, out);
    }
    if( c == root)
    {
        out<<"/";
    }
    else
    {
        out<<c->name<<"/"<<flush;
    }
    return;
}

void threaded_tree::printCWD( ostream &out )
{
    out<<cwd->name<<flush;
}

/**************************
* The method will either change directory or not.
* It uses a temp work pointer to travel the given path.
* IF the path is valid the cwd will be assigned to the temp.
* Else no change will happen
* Supports "..", ".", "/" and relative or absolute paths.
**************************/
bool threaded_tree::changeDirectory( string path )
{
    TREENODE* temp = cwd; // pointer to work with
    bool valid = true; // flag indicating if a valid path was found or not
    //create a cstring using the given path to use strtok on.
    char* cstr = new char[ path.length()+1 ];
    strcpy( cstr, path.c_str() );
    //Go to root if first char is a '/'
    if( cstr[0] == '/' )
    {
        temp = root;
    }
    //break path into tokens, and use the work pointer
    // to travel the path.
    char* pstr = strtok( cstr, "/\n");
    while( pstr != NULL && valid )
    {
        string s = pstr;
        valid = changeDirectHelp( &temp, s );
        pstr = strtok( NULL, "/\n" );
    }

    delete []cstr;
    if( valid )
    {
        cwd = temp;
        return true;
    }
    else
    {
        return false;
    }
}

/**********
* Helps move to another directory
***********/
bool threaded_tree::changeDirectHelp( TREENODE** temp, string path )
{
    TREENODE* d = (*temp)->child;
    //Supports ".." for parent
    if( path == ".." )
    {
        *temp = (*temp)->parent;
        return true;
    }
    //supports "." for self
    else if( path == "." )
    {
        return true;
    }
    else // look for directory name
    {
        while( d && d->name != path )
        {
            d = d->next;
        }
        //if the name was not found or it is not a directory
        if( d == NULL || !d->isDirectory )
        {
            return false;
        }
        else // found and is directory
        {
            *temp = d;
            return true;
        }
    }
}

void threaded_tree::listRecursively( ostream& out )
{
    // use the recursive helper function
    // starting with 0 spaces for indentation
    printRecursiveHelp(cwd->child, 0, out);
}

/*******************
* Loops through the given directory and prints out the names
* If a directory is encountered it will call itself with that directory
* Prints 3 spaces per level of recursion
*********************/
void threaded_tree::printRecursiveHelp( TREENODE* c, int spaces, ostream& out )
{
    while( c )
    {
        for( int i = 0; i < spaces * 3; i++)
        {
            out <<" ";
        }
        out << c->name;
        if( c->isDirectory )
        {
            out << "/";
        }
        out << endl;
        if( c->isDirectory )
        {
            printRecursiveHelp( c->child, spaces+1, out );
        }
        c = c->next;
    }
    return;
}






