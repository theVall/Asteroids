/**
 * @file TexturedMesh.hpp
 * @author Gruppe 2
 */

#ifndef TEXTUREDMESH_HPP_
#define TEXTUREDMESH_HPP_

#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;

#include "Materials.hpp"
#include "TriangleMesh.hpp"
#include "Texture.hpp"

/**
 * @brief       Represents a texured TriangleMesh
 */
class TexturedMesh : public TriangleMesh
{
public:

    /**
     * @brief   Ctor
     */
    TexturedMesh();

    /**
     * @brief   Copy Ctor.
     */
    TexturedMesh(const TexturedMesh &mesh);

    /**
     * @brief   Destructor
     */
    virtual ~TexturedMesh();

    /**
     * @brief   Adds a material to the internal material list
     */
    void addMaterial(Material* mat);

    /**
     * @brief   Adds a new list with faces that share the same materials
     */
    void addMaterialFaceList(MaterialFaceList* l)   {m_matFaceLists.push_back(l);}

    /**
     * @brief   Sets the internal buffer with texture coordinates
     */
    void setTextureBuffer(float* texCoords)         {m_textureCoords = texCoords;}

    /**
     * @brief   Renders the object
     */
    virtual void render();

    vector<Material*>* getMaterials();

    void setMaterials(vector<Material*> mat);

/*private:*/

    /**
     * @brief   Compiles a display list to render the object
     */
    void compileDisplayList();

    /**
     * @brief   Sets color and material values for rendering
     */
    void setColorMaterial(Color &ambient, Color &diffuse, Color &specular, float shininess);

    // The material descriptions
    vector<Material*>   m_materials;

    // Lists of faces that share a material
    MaterialFaceLists   m_matFaceLists;

    // Texture coordinate buffer
    float*              m_textureCoords;



};

#endif /* TexturedMesh.hpp */
