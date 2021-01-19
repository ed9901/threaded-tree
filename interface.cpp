/*
 * interface.cpp
 *
 * interface for the client to use file system
 *
 *
*/

#include<iostream>
#include<fstream>
#include<cstring>
#include"interface.h"

using namespace std;
interface::interface( const char* filename )
{
    filesystem = new threaded_tree;
    output.open(filename);
    if( !output )
    {
        cout<<"ERROR OPENING FILE!";
    }

}

void interface::command( char* line )
{
    TREENODE* t = NULL;
    char* pstr = NULL;
    //Echo print the command given
    output<<line<<"*"<<endl;
    char* tok = strtok(line, " \n");

    string command = tok;
    if( command == "mkdir" )
    {
        pstr = strtok( NULL, " \n" );
        string name = pstr;
        if( name == "" )
        {
            output<<"Cannot create directory with no name!"
                  <<endl;
            return;
        }
        else
        {
            bool inserted;
            t = new TREENODE;
            t->name = name;
            t->child = t->next = t->parent = NULL;
            t->isDirectory = true;
            inserted = filesystem->Insert( t );
            if( inserted )
            {
                output<<"Directory with name '"<<name
                      <<"' was made"<<endl;
            }
            else
            {
                output<<"ERROR, the name: '"<<name
                      <<"' already exists in this cwd!"<<endl;
            }

        }

    }
    else if( command == "rmdir" )
    {
        pstr = strtok( NULL, " \n" );
        string name = pstr;
        if( name == "" )
        {
            output<<"Cannot delete directory without a name!"
                  <<endl;
            return;
        }
        else
        {
            bool removed;
            removed = filesystem->Remove(name, true);
            if( removed )
            {
                output<<"The directory named '"<<name
                      <<"' was removed."<<endl;
            }
            else
            {
                output<<"A directory with the name '"<<name
                      <<"' was not found for removal."<<endl;
            }
        }


    }
    else if( command == "chdir" )
    {
        pstr = strtok( NULL, " \n" );
        string name = pstr;
        bool changed = filesystem->changeDirectory( name );
        if( changed )
        {
            output<<"cwd has been changed to '";
            filesystem->printCWD(output);
            output<<"'"<<endl;
        }
        else
        {
            output<<"cwd could not be changed to '"<<name
                  <<"', it was an invalid path"<<endl;
        }

    }
    else if( command == "ls" )
    {
        filesystem->listInCWD( output );
    }
    else if( command == "lsr" )
    {
        filesystem->listRecursively( output );
    }
    else if( command == "mkfile" )
    {
        pstr = strtok( NULL, " \n" );
        string name = pstr;
        if( name == "" )
        {
            output<<"Cannot create a file with no name!"
                  <<endl;
            return;
        }
        else
        {
            bool inserted;
            t = new TREENODE;
            t->name = name;
            t->child = t->next = t->parent = NULL;
            t->isDirectory = false;
            inserted = filesystem->Insert( t );
            if( inserted )
            {
                output<<"The file with name '"<<name
                      <<"' was made"<<endl;
            }
            else
            {
                output<<"ERROR, the name '"<<name
                      <<"' already exists in this cwd!"<<endl;
            }
        }

    }
    else if( command == "rmfile" )
    {
        pstr = strtok( NULL, " \n" );
        string name = pstr;
        if( name == "" )
        {
            output<<"Cannot delete a file without a name!"
                  <<endl;
            return;
        }
        else
        {
            bool removed;
            removed = filesystem->Remove(name, false);
            if( removed )
            {
                output<<"The file named '"<<name
                      <<"' was removed."<<endl;
            }
            else
            {
                output<<"A file with the name '"<<name
                      <<"' was not found for removal."<<endl;
            }
        }

    }
    else if( command == "pwd" )
    {
        filesystem->printPath( output );
        output<<endl;

    }
    else
    {
        output<<"INVALID COMMAND!"<<endl;
    }
}

