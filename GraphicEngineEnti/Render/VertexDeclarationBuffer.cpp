#include "precompiledHeader.h"
#include "VertexDeclarationBuffer.h"


void VertexDeclarationBuffer::setVertexAttribArray() const
{

}

std::vector<vertices>& VertexDeclarationBuffer::getVertexBuffer()
{
	return buffer;
}

std::vector<unsigned int>& VertexDeclarationBuffer::getIndexBuffer()
{
	return idb;
}

VertexDeclarationBuffer::VertexDeclarationBuffer(const uint32_t & nelements,const uint32_t & bytes_per_vertex)
{
	buffer.push_back({ -0.5f,  -0.5f, 0.f, 0.f, 1.f }); //0
	buffer.push_back({ 0.5f, -0.5f, 1.f, 0.f, 0.f });//1
	buffer.push_back({ 0.5f, 0.5f, 0.f, 1.f, 0.f });//2
	buffer.push_back({ -0.5f, 0.5f, 1.f, 1.f, 1.f });//3

	idb = {
		0,1,2,
		2,3,0 };

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * buffer.size(), buffer.data(), GL_STATIC_DRAW);


	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * idb.size(), idb.data(), GL_STATIC_DRAW);
}

VertexDeclarationBuffer::~VertexDeclarationBuffer()
{
}
