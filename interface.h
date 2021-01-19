/*
 * interface.h
 *
 * interface for the client to use file system
 *
 *
*/


#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED
#include"threaded_tree.h"
#include<fstream>
using namespace std;

class interface
{
    private:
        //file-system data structure
        threaded_tree* filesystem;
        ofstream output;

    public:
        interface( const char* filename );
        ~interface() { delete filesystem; }
        void command( char* line );



};

#endif // INTERFACE_H_INCLUDED
