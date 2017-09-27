// Wavefront.cpp

#include <iomanip>
#include "Wavefront.h"

//#define WAVEFRONT_CONSOLE_DEBUG

void loadFromOBJ_error( char const* sourcefile_, int source_, int inp_file_line_count_, char const* filename_ )
{
    std::cout << "\a\t*** Error parsing file " << filename_ << " line #" << inp_file_line_count_ << std::endl;
    std::cout << "\t*** Source file " << sourcefile_ << ";" << source_ << std::endl;
}

IWavefrontFaceReader* construct_wavefront_face_reader( std::string const& line_, int inp_file_line_count_, char const* filename_ )
{
    // Determine the format of the face and construct the appropriate reader

    std::stringstream buffer( line_ );
    int itmp;
    char ch_tmp;

    buffer >> ch_tmp; // skip f

    // skip first int:
    if ( !( buffer >> itmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, filename_ ); return NULL; }
    // we got this far: f v1

    if ( buffer.peek() == '/' ) {
        if ( !( buffer >> ch_tmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, filename_ ); return NULL; }
        // we got this far: f v1/
        // there is texture-coordinate and/or normal
        // read one more char after /:
        if ( buffer.peek() == '/' ) {
            if ( !( buffer >> ch_tmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, filename_ ); return NULL; }
            // we got this far: f v1//
            // read int after //:
            if ( !( buffer >> itmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, filename_ ); return NULL; }
            // this is Vertex/normal format
            // v1//N
            return new WavefrontFaceVertexNormal( filename_ );

        } else if ( isdigit( buffer.peek() ) ) {
            if ( !( buffer >> itmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, filename_ ); return NULL; }
            // we got this far: f v1/T
            if ( buffer.peek() == '/' ) {
                if ( !( buffer >> ch_tmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, filename_ ); return NULL; }
                // we got this far: f v1/T/
                if ( !( buffer >> itmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, filename_ ); return NULL; }
                // we got this far: f v1/T/N
                return new WavefrontFaceVertexTextureNormal( filename_ );
            } else {
                // assuming this format: f v1/T
                return new WavefrontFaceVertexTexture( filename_ );
            }
        } else {
            loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, filename_ ); return NULL;
        }
    } else {
        // there is no texture-coordinate or normal
        return new WavefrontFaceVertexOnly( filename_ );
    }
}


bool WavefrontFaceVertexOnly::read_face( std::stringstream& buffer_, int inp_file_line_count_ )
{
    //                           Vertex format: f v1 v2 v3
    int itmp;
    char ch_tmp;

    // skip f
    if ( !( buffer_ >> ch_tmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, m_obj_filename ); return false; }
    assert( ch_tmp == 'f' );

    while ( buffer_ >> itmp ) {
        m_vect_faces.push_back( itmp - 1 ); // v1, v2, v3
    }
    return true;
}

bool WavefrontFaceVertexOnly::next_face( size_t& vertex_idx_, size_t& texture_idx_, size_t& normal_idx_ )
{
#ifdef WAVEFRONT_CONSOLE_DEBUG
    //std::cout << m_current_idx / WAVEFRONT_FACE_SIZE << " ";
    std::cout << m_current_idx / WAVEFRONT_FACE_SIZE << "(" << m_vect_faces[ m_current_idx ] << ") ";
#endif
    if ( m_current_idx >= m_vect_faces.size()) { loadFromOBJ_error( __FILE__, __LINE__, 0, m_obj_filename ); return false; }
    vertex_idx_  = m_vect_faces[ m_current_idx ];
    texture_idx_ = -1;
    normal_idx_  = -1;
    m_current_idx += WAVEFRONT_FACE_SIZE;
    return m_current_idx < m_vect_faces.size();
}

bool WavefrontFaceVertexTexture::read_face( std::stringstream& buffer_, int inp_file_line_count_ )
{
    //        Vertex/texture-coordinate format: f v1/T v2/T v3/T
    int itmp;
    char ch_tmp;

    // skip f
    if ( !( buffer_ >> ch_tmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, m_obj_filename ); return false; }
    assert( ch_tmp == 'f' );

    while ( buffer_ >> itmp ) {
        m_vect_faces.push_back( itmp - 1 ); // store v1

        if ( !( buffer_ >> ch_tmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, m_obj_filename ); return false; }
        assert( ch_tmp == '/' );

        if ( !( buffer_ >> itmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, m_obj_filename ); return false; }
        m_vect_faces.push_back( itmp - 1 ); // store T
    }
    return true;
}

bool WavefrontFaceVertexTexture::next_face( size_t& vertex_idx_, size_t& texture_idx_, size_t& normal_idx_ )
{
    if ( m_current_idx >= m_vect_faces.size()) { loadFromOBJ_error( __FILE__, __LINE__, 0, m_obj_filename ); return false; }
    vertex_idx_  = m_vect_faces[ m_current_idx ];
    texture_idx_ = m_vect_faces[ m_current_idx + 1 ];
    normal_idx_  = -1;
    m_current_idx += 2;
    return m_current_idx < m_vect_faces.size();
}

bool WavefrontFaceVertexTextureNormal::read_face( std::stringstream& buffer_, int inp_file_line_count_ )
{
    // Vertex/texture-coordinate/normal format: f v1/T/N v2/T/N v3/T/N
    int itmp;
    char ch_tmp;

    // skip f
    if ( !( buffer_ >> ch_tmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, m_obj_filename ); return false; }
    assert( ch_tmp == 'f' );

    while ( buffer_ >> itmp ) {
        m_vect_faces.push_back( itmp - 1 ); // store v1

        if ( !( buffer_ >> ch_tmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, m_obj_filename ); return false; }
        assert( ch_tmp == '/' );

        if ( !( buffer_ >> itmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, m_obj_filename ); return false; }
        m_vect_faces.push_back( itmp - 1 ); // store T

        if ( !( buffer_ >> ch_tmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, m_obj_filename ); return false; }
        assert( ch_tmp == '/' );

        if ( !( buffer_ >> itmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, m_obj_filename ); return false; }
        m_vect_faces.push_back( itmp - 1 ); // store N
    }
    return true;
}

bool WavefrontFaceVertexTextureNormal::next_face( size_t& vertex_idx_, size_t& texture_idx_, size_t& normal_idx_ )
{
    if ( m_current_idx >= m_vect_faces.size()) { loadFromOBJ_error( __FILE__, __LINE__, 0, m_obj_filename ); return false; }
    vertex_idx_  = m_vect_faces[ m_current_idx ];
    texture_idx_ = m_vect_faces[ m_current_idx + 1 ];
    normal_idx_  = m_vect_faces[ m_current_idx + 2 ];
    m_current_idx += 3;
    return m_current_idx < m_vect_faces.size();
}

bool WavefrontFaceVertexNormal::read_face( std::stringstream& buffer_, int inp_file_line_count_ )
{
    //                    Vertex/normal format: f v1//N v2//N v3//N
    int itmp;
    char ch_tmp;

    // skip f
    if ( !( buffer_ >> ch_tmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, m_obj_filename ); return false; }
    assert( ch_tmp == 'f' );

    while ( buffer_ >> itmp ) {
        m_vect_faces.push_back( itmp - 1 ); // store v1

        if ( !( buffer_ >> ch_tmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, m_obj_filename ); return false; }
        if ( ch_tmp != '/' ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, m_obj_filename ); return false; }

        if ( !( buffer_ >> ch_tmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, m_obj_filename ); return false; }
        if ( ch_tmp != '/' ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, m_obj_filename ); return false; }

        if ( !( buffer_ >> itmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count_, m_obj_filename ); return false; }
        m_vect_faces.push_back( itmp - 1 ); // store N
    }
    return true;
}

bool WavefrontFaceVertexNormal::next_face( size_t& vertex_idx_, size_t& texture_idx_, size_t& normal_idx_ )
{
#ifdef WAVEFRONT_CONSOLE_DEBUG
    //std::cout << m_current_idx / WAVEFRONT_FACE_SIZE << " ";
    std::cout << m_current_idx / WAVEFRONT_FACE_SIZE << "=" << m_vect_faces[ m_current_idx ] << " ";
#endif
    if ( m_current_idx >= m_vect_faces.size()) { loadFromOBJ_error( __FILE__, __LINE__, 0, m_obj_filename ); return false; }
    vertex_idx_  = m_vect_faces[ m_current_idx ];
    texture_idx_ = -1;
    normal_idx_  = m_vect_faces[ m_current_idx + 1 ];
    m_current_idx += WAVEFRONT_FACE_SIZE;
    return m_current_idx < m_vect_faces.size();
}

bool WavefrontObjLoader::load( int vertex_size_ )
{
    std::vector< GLfloat > vect_vertices;
    std::vector< GLfloat > vect_normals;
    std::vector< GLfloat > vect_uvs;

    //ik-12/14/2013 added this function
    std::ifstream file_stream( filename );
    if ( !file_stream.is_open() ) {
        std::cout << "\a\t*** Unable to open OBJ file " << filename << std::endl;
        return false;
    }
    int inp_file_line_count = 0;
    int face_count = 0;
    IWavefrontFaceReader* face_reader = NULL;
    while ( !file_stream.eof() ) {
        ++inp_file_line_count;
        // Input line of text:
        std::string line;
        std::getline( file_stream, line );
        // Display each line on the screen:
        //cout << line << endl;
        if ( !line.length() || line[ 0 ] == '#' ) {
            // #comment or an empty line
            continue;
        }
        std::stringstream buffer( line );
        GLfloat fl_tmp;
        char    ch_tmp;
        if ( line[ 0 ] == 'v' && line[ 1 ] == ' ' ) {
            // this is a vertex
            buffer >> ch_tmp; // skip v
            assert( ch_tmp == 'v' );
            if ( !( buffer >> fl_tmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count, filename ); return false; }
            vect_vertices.push_back( fl_tmp );
            if ( !( buffer >> fl_tmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count, filename ); return false; }
            vect_vertices.push_back( fl_tmp );
            if ( !( buffer >> fl_tmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count, filename ); return false; }
            vect_vertices.push_back( fl_tmp );

#ifdef WAVEFRONT_CONSOLE_DEBUG
            //DEBUG//std::cout << "vertex " << line << std::endl;
            //TODO: attempt to read the W coordinate
            std::cout << "v [ " << vect_vertices[ vect_vertices.size() - 3 ] << " ";
            std::cout << vect_vertices[ vect_vertices.size() - 2 ] << " ";
            std::cout << vect_vertices[ vect_vertices.size() - 1 ] << " ]" << std::endl;
#endif

        } else if ( line[ 0 ] == 'v' && line[ 1 ] == 'n' ) {
            // this is a normal vector
            // skip vn
            buffer >> ch_tmp;
            assert( ch_tmp == 'v' );
            buffer >> ch_tmp;
            assert( ch_tmp == 'n' );

            if ( !( buffer >> fl_tmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count, filename ); return false; }
            vect_normals.push_back( fl_tmp );
            if ( !( buffer >> fl_tmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count, filename ); return false; }
            vect_normals.push_back( fl_tmp );
            if ( !( buffer >> fl_tmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count, filename ); return false; }
            vect_normals.push_back( fl_tmp );

#ifdef WAVEFRONT_CONSOLE_DEBUG
            //DEBUG//
            std::cout << "READING NORMAL: " << line << " -> ";
            std::cout << "vn [ " << vect_normals[ vect_normals.size() - 3 ] << " ";
            std::cout << vect_normals[ vect_normals.size() - 2 ] << " ";
            std::cout << vect_normals[ vect_normals.size() - 1 ] << " ]" << std::endl;
#endif

        } else if ( line[ 0 ] == 'f' ) {
            //------------------------------------------------------
            // this is a face
            //------------------------------------------------------
            if ( !face_reader ) {
                // this is first face
                face_reader = construct_wavefront_face_reader( line, inp_file_line_count, filename );
                if ( !face_reader ) {
                    // something's wrong
                    loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count, filename ); return false;
                }
            }
            ++face_count;
            if ( !face_reader->read_face( buffer, inp_file_line_count ) ) {
                // something's wrong
                loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count, filename ); return false;
            }
            //DEBUG//std::cout << "face [" << face_reader->size() << "] " << line << std::endl;

        } else if ( line[ 0 ] == 'u' && line[ 1 ] == 's' && line[ 2 ] == 'e' ) {
            // use material material_name
            //TODO
        } else if ( line[ 0 ] == 'm' && line[ 1 ] == 't' && line[ 2 ] == 'l' && line[ 2 ] == 'l' ) {
            // mtllib
            // material library, a file, which contains
            // all of the materials
            //TODO

        } else if ( line[ 0 ] == 'v' && line[ 1 ] == 't' ) {
            // this is a texture coorinate
            // read the uv coordinate
            // skip vt
            buffer >> ch_tmp;
            assert( ch_tmp == 'v' );
            buffer >> ch_tmp;
            assert( ch_tmp == 't' );

            if ( !( buffer >> fl_tmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count, filename ); return false; }
            vect_uvs.push_back( fl_tmp );
            if ( !( buffer >> fl_tmp ) ) { loadFromOBJ_error( __FILE__, __LINE__, inp_file_line_count, filename ); return false; }
            vect_uvs.push_back( fl_tmp );

        } else if ( line[ 0 ] == 'g' && line[ 1 ] == ' ' ) {
            // this is an object group name
            std::cout << "\t Reading object group [" << line << "]" << std::endl;
            std::cout << "\t\t from file " << filename << std::endl;

        } else if ( line[ 0 ] == 'o' && line[ 1 ] == ' ' ) {
            // this is an object name
            std::cout << "\t Reading object [" << line << "]" << std::endl;
            std::cout << "\t\t from file " << filename << std::endl;

        } else if ( line[ 0 ] != ' ' && line[ line.length() - 1 ] != ' ' ) {
            std::cout << "\t *** WARNING: unrecognizable line: " << line << std::endl;
            std::cout << "\t\t in file " << filename << " line #" << inp_file_line_count << std::endl;
        }
    }
    file_stream.close();

    //-----------------------
    // Pass 1 results
    //-----------------------
    std::cout << filename << " pass 1 results:" << std::endl;
    std::cout << "          face_count == " << face_count << std::endl;
    std::cout << "vect_vertices.size() == " << vect_vertices.size() << std::endl;
    std::cout << "     vect_uvs.size() == " << vect_uvs.size() << std::endl;
    std::cout << " vect_normals.size() == " << vect_normals.size() << std::endl;

    //-----------------------
    // Pass 2
    //-----------------------
    //GLfloat* tempVerts = NULL;    // { x, y, x }, { x, y, x }, ...
    //GLfloat* tempNormals = NULL;  // { x, y, x }, { x, y, x }, ...
    //GLfloat* tempUVs = NULL;      // { u, v }, { u, v }, ...
    assert( vect_vertices.size() );
    assert( face_count );

    //WRONG--this should be based on the number of vertices specified in faces//num_vertices = int( vect_vertices.size() / 3 );
    //std::copy( vect_vertices.begin(), vect_vertices.end(), vertices ); // bad

    //-----------------------
    // New code v.3
    //-----------------------
/*
static GLuint static_indices[] = {
	0,	6,	4,
	0,	2,	6,
	0,	3,	2,
	0,	1,	3,
	2,	7,	6,

	2,	3,	7,
	4,	6,	7,
	4,	7,	5,
	0,	4,	5,
	0,	5,	1,

	1,	5,	7,
	1,	7, 3
};
*/
    //DEBUG//indices = static_indices;
    // Populate the indices array and set the number of indices
    indices = face_reader->faces_2_vertex_index( &num_indices );
    num_vertices = num_indices;
    vertices = new GLfloat[ num_vertices * vertex_size_ ];

    if ( vect_normals.size() ) {
        //num_normals = vect_normals.size() / 3; // array size of normals is the same as vertices
        //normals = new GLfloat[ num_normals * 3 ];
        // The array of normals will be populated for each vertex:
        num_normals = num_vertices; // array size of normals is the same as vertices
        normals = new GLfloat[ num_normals * 3 ];
        //std::copy( vect_normals.begin(), vect_normals.end(), normals ); // this is wrong!!
    }
    if ( vect_uvs.size() ) {
        // The array of UVs will be populated for each vertex:
        num_uvs = num_vertices;     // array size of UVs is the same as vertices
        UVs = new GLfloat[ num_uvs * 2 ];
        //std::copy( vect_uvs.begin(), vect_uvs.end(), UVs ); // this is wrong!
    }
    // sequential indices for arrays of vertices and normals, and UVs
    int vertex_seq = 0;
    int normal_seq = 0;
    int uv_seq = 0;                 // sequential index for UVs

    size_t vertex_idx;   // vertex index 0, 1, 2, 3, ... specified by the face
    size_t texture_idx;  // UV index 0, 1, 2, 3, ... specified by the face
    size_t normal_idx;   // normal index 0, 1, 2, 3, ... specified by the face

    bool has_next;
    do {
        has_next = face_reader->next_face( vertex_idx, texture_idx, normal_idx );
        assert( vertex_idx * 3 + 2 < int( vect_vertices.size() ) );
        assert( vertex_seq + 2 < num_vertices * vertex_size_ );
#ifdef WAVEFRONT_CONSOLE_DEBUG
        //DEBUG//
        //std::cout << "v" << vertex_idx << /*" t" << texture_idx <<*/ " n" << normal_idx;
        std::cout << "\t v [ " << std::setw( 4 ) << vect_vertices[ vertex_idx * 3 ] << " ";
        std::cout << std::setw( 4 ) << vect_vertices[ vertex_idx * 3 + 1 ] << " ";
        std::cout << std::setw( 4 ) << vect_vertices[ vertex_idx * 3 + 2 ] << " ]";

        if ( vect_normals.size() ) {
            assert( normal_idx * 3 + 2 < int( vect_normals.size() ) );
            std::cout << " vn [ " << std::setw( 4 ) << vect_normals[ normal_idx * 3 ] << " ";
            std::cout << std::setw( 4 ) << vect_normals[ normal_idx * 3 + 1 ] << " ";
            std::cout << std::setw( 4 ) << vect_normals[ normal_idx * 3 + 2 ] << " ]";
        }

        std::cout << std::endl;
#endif
/*
        vertices[ vertex_seq ] = vect_vertices[ vertex_idx * 3 ];
        vertices[ vertex_seq + 1 ] = vect_vertices[ vertex_idx * 3 + 1 ];
        vertices[ vertex_seq + 2 ] = vect_vertices[ vertex_idx * 3 + 2 ];
*/
        vertices[ vertex_seq ] = vect_vertices[ vertex_idx * 3 ];
        vertices[ vertex_seq + 1 ] = vect_vertices[ vertex_idx * 3 + 1 ];
        vertices[ vertex_seq + 2 ] = vect_vertices[ vertex_idx * 3 + 2 ];
        if ( vertex_size_ == 4 ) vertices[ vertex_seq + 3 ] = 1.0f;

        if ( normal_idx != -1 ) {
            // normals are specified per-vertex
            assert( normal_idx * 3 + 2 < int( vect_normals.size() ) );
            normals[ normal_seq ] = vect_normals[ normal_idx * 3 ];
            normals[ normal_seq + 1 ] = vect_normals[ normal_idx * 3 + 1 ];
            normals[ normal_seq + 2 ] = vect_normals[ normal_idx * 3 + 2 ];
        } else {
            // the normals are present but faces don't use them...
            num_normals = 0;
        }

        if ( texture_idx != -1 ) {
            assert( texture_idx < int( vect_uvs.size() ) );
            assert( uv_seq + 1 < num_uvs * 2 );
            UVs[ uv_seq ] = vect_uvs[ texture_idx * 2 ];
            UVs[ uv_seq + 1 ] = vect_uvs[ texture_idx * 2 + 1 ];
            //UVs[ texture_idx ] = vect_uvs[ texture_idx ];
            //UVs[ texture_idx + 1 ] = vect_uvs[ texture_idx + 1 ];
        } else {
            // the UVs are present but faces don't use them...
            num_uvs = 0;
        }

        vertex_seq += vertex_size_;
        normal_seq += 3;
        uv_seq += 2;
    } while ( has_next );

    //-----------------------
    // Pass 2 results
    //-----------------------
    std::cout << std::endl << "Pass 2 report card:" << std::endl;
    std::cout << "         num_indices == " << num_indices << std::endl;
    std::cout << "        num_vertices == " << num_vertices << std::endl;
    std::cout << "             num_uvs == " << num_uvs << std::endl;
    std::cout << "         num_normals == " << num_normals << std::endl;

    int idx = 0;
    for ( ; idx < num_indices; ++idx ) {
        indices[ idx ] = idx;
    }
#ifdef WAVEFRONT_CONSOLE_DEBUG
    // print C/C++ header file arrays
    std::cout << "GLfloat vertices[] = {" << std::endl;
    vertex_seq = 0;
    for ( ; vertex_seq < num_vertices; ++vertex_seq ) {
        std::cout << vertices[ vertex_seq * 3 ] << ", " << vertices[ vertex_seq * 3 + 1 ] << ", " << vertices[ vertex_seq * 3 + 2 ] << ", " << std::endl;
    }

    std::cout << "};" << std::endl;
    if ( vect_normals.size() ) {
        std::cout << "GLfloat normals[] = {" << std::endl;
        vertex_seq = 0;
        for ( ; vertex_seq < num_normals; ++vertex_seq ) {
            std::cout << normals[ vertex_seq * 3 ] << ", " << normals[ vertex_seq * 3 + 1 ] << ", " << normals[ vertex_seq * 3 + 2 ] << ", " << std::endl;
        }

        std::cout << "};" << std::endl;
    }

    std::cout << "};" << std::endl;
    if ( vect_uvs.size() ) {
        std::cout << "GLfloat UVs[] = {" << std::endl;
        vertex_seq = 0;
        for ( ; vertex_seq < num_uvs; ++vertex_seq ) {
            std::cout << UVs[ vertex_seq * 2 ] << ", " << UVs[ vertex_seq * 2 + 1 ] << ", " << std::endl;
        }

        std::cout << "};" << std::endl;
    }

    std::cout << "GLuint indices[] = {" << std::endl;
    int idx = 0;
    for ( ; idx < num_indices; idx += 3 ) {
        std::cout << indices[ idx ] << ", " << indices[ idx + 1 ] << ", " << indices[ idx + 2 ] << ", " << std::endl;
    }
    std::cout << "};" << std::endl;
#endif

    return true;
}//WavefrontObjLoader::load()

GLuint* WavefrontFaceVertexOnly::faces_2_vertex_index( int* num_indices_ )
{
    // this is 1-to-1 set of indices for WavefrontFaceVertexOnly
    *num_indices_ = int( m_vect_faces.size() );
    GLuint* tmpIndices = new GLuint[ *num_indices_ ];
    std::copy( m_vect_faces.begin(), m_vect_faces.end(), tmpIndices );
    return tmpIndices;
}

GLuint* WavefrontFaceVertexTexture::faces_2_vertex_index( int* num_indices_ )
{
    //assert( !"WavefrontFaceVertexTexture::faces_2_vertex_index() not implemented!" );
    //return NULL;
    *num_indices_ = int( m_vect_faces.size() ) / WAVEFRONT_FACE_SIZE;
    GLuint* tmpIndices = new GLuint[ *num_indices_ ];
    int idx = 0;
    for ( ; idx < *num_indices_; ++idx ) {
        tmpIndices[ idx ] = m_vect_faces[ idx * WAVEFRONT_FACE_SIZE ];
    }
    return tmpIndices;
}

GLuint* WavefrontFaceVertexTextureNormal::faces_2_vertex_index( int* num_indices_ )
{
    //assert( !"WavefrontFaceVertexTextureNormal::faces_2_vertex_index() not implemented!" );
    //return NULL;
    *num_indices_ = int( m_vect_faces.size() ) / WAVEFRONT_FACE_SIZE;
    GLuint* tmpIndices = new GLuint[ *num_indices_ ];
    int idx = 0;
    for ( ; idx < *num_indices_; ++idx ) {
        tmpIndices[ idx ] = m_vect_faces[ idx * WAVEFRONT_FACE_SIZE ];
    }
    return tmpIndices;
}

GLuint* WavefrontFaceVertexNormal::faces_2_vertex_index( int* num_indices_ )
{
    *num_indices_ = int( m_vect_faces.size() ) / WAVEFRONT_FACE_SIZE;
    GLuint* tmpIndices = new GLuint[ *num_indices_ ];
    int idx = 0;
    for ( ; idx < *num_indices_; ++idx ) {
        tmpIndices[ idx ] = m_vect_faces[ idx * WAVEFRONT_FACE_SIZE ];
    }
    return tmpIndices;
}

 /*    5_ _ _6
      /|    /|
    1/_|_ 2/ |      
    | 4|_ _|_|7        
    | /    | / 
    |/_ _ _|/ 
    0      3
*/
