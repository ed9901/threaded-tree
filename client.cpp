/*
 * client.cpp
 *
 * Client to use the threaded tree file system
 *
 *
*/

#include<iostream>
#include<fstream>
#include"interface.h"

using namespace std;

int main( int argc, char* argv[] )
{
    if( argc < 3)
    {
        cout<<"USAGE: prognam, input, output"<<endl;
        return -1;
    }

    ifstream input;
    input.open(argv[1]);
    if( !input )
    {
        cout<<"ERROR OPENING FILE!"<<endl;
        return -1;
    }
    char line[256];
    interface CLIENT_INTERFACE( argv[2] );
    while( input.getline( line, 256, '\n' ) )
    {
        CLIENT_INTERFACE.command(line);
    }
    input.close();
    return 0;
}
