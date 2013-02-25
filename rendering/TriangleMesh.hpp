/**
 * @file TriangleMesh.hpp
 * @author Gruppe 2
 */

#ifndef TRIANGLEMESH_HPP_
#define TRIANGLEMESH_HPP_

#include <string>               // Header for c++ strings
#include <GL/gl.h>              // Header File For The OpenGL Library
#include <iostream>

#include "Transformable.hpp"

/**
 * @brief   A simple triangle mesh. The mesh can be instantiated from
 *          an ASCII .ply-File
 */
class TriangleMesh : public Transformable
{
    public:

        /**
         * @brief   Default contructor. Initializes with empty buffers
         */
        TriangleMesh();

        /**
         * @brief   Renders the mesh
         */
        virtual void render();

        /**
         * @brief   Destructor
         */
        ~TriangleMesh();

        /**
         * @brief   Sets the normal buffer of the mesh
         * @param normals The new normal buffer
	 */
        void setNormalBuffer(float* normals) { m_normalBuffer = normals;}

        /**
         * @brief   Sets the vertex buffer of the mesh
         *
         * @param vertices  The new vertex buffer
         * @param n         The number of vertices in the mesh
         */
        void setVertexBuffer(float* vertices, int n)
        {
            m_vertexBuffer = vertices;
            m_numVertices = n;
        }

        /**
         * @brief   Sets the index buffer of the mesh
         *
         * @param faces     The new index buffer
         * @param n         The number of faces in the mesh
         */
        void setIndexBuffer(int* faces, int n)
        {
            m_indexBuffer = faces;
            m_numFaces = n;
        }


   /* protected:*/
        // index buffer containing the triangle definitions
        int *m_indexBuffer;

        // vertex buffer (vertex def.) and normal buffer (vertex normal info.)
        float *m_vertexBuffer, *m_normalBuffer;

        // number of triangles (faces) and vertices in the mesh
        int m_numFaces, m_numVertices;
};

#endif
