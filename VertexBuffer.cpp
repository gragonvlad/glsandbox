#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#ifndef FREEGLUT_STATIC
#define FREEGLUT_STATIC
#endif

#include <gl/glew.h>
#include <gl/gl.h>		
#include <GL/glut.h>

#include <cassert>
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	size = 0;
	GLuint Ids[ 3 ];

	glGenBuffers( 3, Ids );
	if( Ids[ 0 ] == 0 || Ids[ 1 ] == 0 || Ids[ 2 ] == 0 )
		assert( false );
	
	vId = Ids[ 0 ];
	tId = Ids[ 1 ];
	nId = Ids[ 2 ];
	vBuffered = false;
	tBuffered = false;
	nBuffered = false;
}

VertexBuffer::~VertexBuffer()
{
	GLuint Ids[ 3 ];
	Ids[ 0 ] = vId;
	Ids[ 1 ] = tId;
	Ids[ 2 ] = nId;
	glDeleteBuffers( 3, Ids );
}

void VertexBuffer::buffer( unsigned long nVertices, void *vertices, void *texCoords, void *normals )
{
	if( vertices != NULL )
	{
		glBindBuffer( GL_ARRAY_BUFFER, vId );
		glBufferData( GL_ARRAY_BUFFER, nVertices * 3 * sizeof( GLfloat ), vertices, GL_STATIC_DRAW );
		vBuffered = true;
	}

	if( texCoords != NULL )
	{
		glBindBuffer( GL_ARRAY_BUFFER, tId );
		glBufferData( GL_ARRAY_BUFFER, nVertices * 2 * sizeof( GLfloat ), texCoords, GL_STATIC_DRAW );
		tBuffered = true;
	}

	if( normals != NULL )
	{
		glBindBuffer( GL_ARRAY_BUFFER, tId );
		glBufferData( GL_ARRAY_BUFFER, nVertices * 3 * sizeof( GLfloat ), normals, GL_STATIC_DRAW );
		nBuffered = true;
	}

	size = nVertices;
}

void VertexBuffer::draw( unsigned int primitive )
{
	if( primitive == 0 )
		primitive = GL_TRIANGLES;

	if( !vBuffered && !tBuffered && !nBuffered )
		assert( false );

	if( vBuffered )
	{
		glBindBuffer( GL_ARRAY_BUFFER, vId );
		glEnableVertexAttribArray( 0 );
		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
	}

	if( tBuffered )
	{
		glBindBuffer( GL_ARRAY_BUFFER, tId );
		glEnableVertexAttribArray( 1 );
		glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, 0 );
	}

	if( nBuffered )
	{
		glBindBuffer( GL_ARRAY_BUFFER, nId );
		glEnableVertexAttribArray( 2 );
		glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, 0 );
	}

	glDrawArrays( primitive, 0, size );

	glDisableVertexAttribArray( 0 );
	glDisableVertexAttribArray( 1 );
	glDisableVertexAttribArray( 2 );
}

