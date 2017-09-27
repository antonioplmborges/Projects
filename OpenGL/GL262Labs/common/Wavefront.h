#ifndef WAVEFRONT_H_INCLUDED_
#define WAVEFRONT_H_INCLUDED_

// Wavefront.h

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include <GL/glew.h>

// this macro calculates the size of vertex array in bytes, e.g.
// SIZEOF_VERTICES_IN_BYTES( 3, num_vertices )
// SIZEOF_VERTICES_IN_BYTES( 4, num_vertices ) -- if using homogenious coordinates
#define SIZEOF_VERTICES_IN_BYTES( X_3_or_4_, X_num_vertices_ ) (X_3_or_4_*X_num_vertices_*sizeof(GLfloat))

// Face definitions -- see http://en.wikipedia.org/wiki/Wavefront_.obj_file
// "structure" to store properties of any kind of face
// indices of vertex, texture and normal vectors

//                           Vertex format: f v1 v2 v3
//        Vertex/texture-coordinate format: f v1/T v2/T v3/T
// Vertex/texture-coordinate/normal format: f v1/T/N v2/T/N v3/T/N
//                    Vertex/normal format: f v1//N v2//N v3//N


class IWavefrontFaceReader {
protected:
    std::vector< int >     m_vect_faces;
    char const* m_obj_filename;
    size_t m_current_idx;
public:
    IWavefrontFaceReader( char const* filename_ )
        : m_obj_filename( filename_ ), m_current_idx( 0 )
    {
    }
    virtual ~IWavefrontFaceReader() {}

    // Pass 1: read faces from the OBJ file, line-by -line:
    virtual bool read_face( std::stringstream& buffer_, int inp_file_line_count_ ) = 0;

    // Pass 2: iterate over faces loaded in pass 1:

    // Uses m_current_idx to return info about vertex attributes.
    // Advances m_current_idx forward.
    // Returns false if no more faces are available.
    virtual bool next_face( size_t& vertex_idx_, size_t& texture_idx_, size_t& normal_idx_ ) = 0;

    virtual GLuint* faces_2_vertex_index( int* index_size_ ) = 0;

    size_t size() const
    {
        return m_vect_faces.size();
    }

};//class IWavefrontFaceReader


class WavefrontFaceVertexOnly : public IWavefrontFaceReader {
    static const int WAVEFRONT_FACE_SIZE = 1; // how many integers stored in m_vect_faces per vertex
public:
    WavefrontFaceVertexOnly( char const* filename_ )
        : IWavefrontFaceReader( filename_ )
    {
    }
    virtual bool read_face( std::stringstream& buffer_, int inp_file_line_count_ );
    virtual bool next_face( size_t& vertex_idx_, size_t& texture_idx_, size_t& normal_idx_ );
    virtual GLuint* faces_2_vertex_index( int* index_size_ );

};//WavefrontFaceVertexOnly


class WavefrontFaceVertexTexture : public IWavefrontFaceReader {
    static const int WAVEFRONT_FACE_SIZE = 2; // how many integers stored in m_vect_faces per vertex
public:
    WavefrontFaceVertexTexture( char const* filename_ )
        : IWavefrontFaceReader( filename_ )
    {
    }
    virtual bool read_face( std::stringstream& buffer_, int inp_file_line_count_ );
    virtual bool next_face( size_t& vertex_idx_, size_t& texture_idx_, size_t& normal_idx_ );
    virtual GLuint* faces_2_vertex_index( int* index_size_ );

};//WavefrontFaceVertexTexture


class WavefrontFaceVertexTextureNormal : public IWavefrontFaceReader {
    static const int WAVEFRONT_FACE_SIZE = 3; // how many integers stored in m_vect_faces per vertex
public:
    WavefrontFaceVertexTextureNormal( char const* filename_ )
        : IWavefrontFaceReader( filename_ )
    {
    }
    virtual bool read_face( std::stringstream& buffer_, int inp_file_line_count_ );
    virtual bool next_face( size_t& vertex_idx_, size_t& texture_idx_, size_t& normal_idx_ );
    virtual GLuint* faces_2_vertex_index( int* index_size_ );

};//WavefrontFaceVertexTextureNormal


class WavefrontFaceVertexNormal : public IWavefrontFaceReader {
    static const int WAVEFRONT_FACE_SIZE = 2; // how many integers stored in m_vect_faces per vertex
public:
    WavefrontFaceVertexNormal( char const* filename_ )
        : IWavefrontFaceReader( filename_ )
    {
    }
    virtual bool read_face( std::stringstream& buffer_, int inp_file_line_count_ );
    virtual bool next_face( size_t& vertex_idx_, size_t& texture_idx_, size_t& normal_idx_ );
    virtual GLuint* faces_2_vertex_index( int* index_size_ );

};//WavefrontFaceVertexNormal

void loadFromOBJ_error( char const* sourcefile_, int source_, int inp_file_line_count_, char const* filename_ );
IWavefrontFaceReader* construct_wavefront_face_reader( std::string const& line_, int inp_file_line_count_, char const* filename_ );

//this was v2 developed in Lab6_solution
//bool loadModelFromOBJ( Model* model_, char const* filename_ );

class WavefrontObjLoader {
public:
    char const* filename;
    GLfloat* vertices; // { x, y, x }, { x, y, x }, ...vertices array contains (num_vertices*3) GLfloat numbers
    GLfloat* normals;  // { x, y, x }, { x, y, x }, ...normals array contains (num_normals*3) GLfloat numbers
    GLfloat* UVs;      // { u, v }, { u, v }, .........UVs array contains (num_uvs*2) GLfloat numbers
    GLuint* indices;   // array of GLuint numbers -- one number for every vertex in the model

    int num_indices;   // this is (number-of-faces*3), in other words (number-of-triangles*3)
    int num_vertices;  // same as num_indices
    int num_normals;   // same as num_vertices, zero if no normals specified
    int num_uvs;       // same as num_vertices, zero if no texture coordinates specified

    WavefrontObjLoader( char const* filename_ )
        :
        filename( filename_ ),
        vertices( NULL ),
        normals( NULL ),
        UVs( NULL ),
        indices( NULL ),
        num_indices( 0 ),
        num_vertices( 0 ),
        num_normals( 0 ),
        num_uvs( 0 )
    {
    }

    bool load( int vertex_size_ = 3 ); // alternatively, it can be 4

};//class WavefrontObjLoader

#endif //WAVEFRONT_H_INCLUDED_