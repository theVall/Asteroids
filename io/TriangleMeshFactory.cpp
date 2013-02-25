/**
 * TriangleMeshFactory.cpp
 *
 *  @date 10.12.2011
 *  @author Thomas Wiemann
 */

#include <iostream>
using std::cout;
using std::endl;

#include "TriangleMeshFactory.hpp"

#include "io/Read3DS.hpp"
#include "io/ReadPLY.hpp"

TriangleMesh* TriangleMeshFactory::getMesh(const string &filename) const
{
    // A mesh pointer and MeshIO pointer
    MeshIO* io = 0;
    TriangleMesh* mesh = 0;
    std::string fname = "res/models/";
    fname += filename;
    cout << fname << endl;

    // Get file extension
    if(filename.substr(fname.find_last_of(".") + 1) == "ply")
    {
        io = new ReadPLY(fname);
    }
    else if(filename.substr(fname.find_last_of(".") + 1) == "3ds")
    {
        io = new Read3DS(fname);
    }

    // Get mesh from io
    if(io)
    {
        mesh = io->getMesh();
    }
    else
    {
        cout << "Unable to parse file " << filename << "." << endl;
    }

    return mesh;
}

TriangleMeshFactory& TriangleMeshFactory::instance()
{
    // Just crate on instance
    static TriangleMeshFactory instance;
    return instance;
}
