/**
 * TextureFactory.cpp
 *
 *  @date 11.12.2011
 *  @author Thomas Wiemann
 */

#include "TextureFactory.hpp"
#include "ReadPPM.hpp"
#include "ReadTGA.hpp"

#include <iostream>
using std::cout;
using std::endl;

TextureFactory::TextureFactory()
{
    // TODO Auto-generated constructor stub

}

TextureFactory::~TextureFactory()
{
    // TODO Auto-generated destructor stub
}

TextureFactory& TextureFactory::instance()
{
    // Just crate on instance
    static TextureFactory instance;
    return instance;
}

Texture* TextureFactory::getTexture(string filename) const
{
    // A texture object
    Texture* tex = 0;
    //std::string fname = "../res/models/";
    std::string fname = filename;

    // Texture data
    int width = 0;
    int height = 0;
    unsigned char* data = 0;

    // Get file extension
    if(fname.substr(fname.find_last_of(".") + 1) == "ppm")
    {
        ReadPPM reader(fname);
        data    = reader.getPixels();
        width   = reader.getWidth();
        height  = reader.getHeight();


    }
    else if(fname.substr(fname.find_last_of(".") + 1) == "tga")
    {
        fname = "res/models/" + fname;        
        ReadTGA reader;
        reader.load(fname.c_str());
        data = reader.data();
        width = reader.width();
        height = reader.height();

    }

    // Check data and create new texture if possible
    if(data != 0 && width != 0 && height != 0)
    {
        tex = new Texture(data, width, height);
    }
    else
    {
        cout << "TextureFactory: Unable to read file " << fname << "." << endl;
    }

    return tex;
}

