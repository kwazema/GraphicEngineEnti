#include "precompiledHeader.h"
#include "VertexDeclarationBuffer.h"

#define MAKE_VERTEX_DECLARATION(name, nbytes) \
  VertexDeclarationBuffer{ \
    #name, nbytes, layout_##name, ARRAYSIZE(layout_##name) \
  }

const LayoutDecl layout_PosClr[] = {
	{"Position",2,GL_FLOAT,GL_FALSE,sizeof(VtxPosColor),(void*)0},
	{"Color", 3, GL_FLOAT, GL_FALSE,sizeof(VtxPosColor), (void*)(sizeof(float) * 2)}
};
static const std::vector<VertexDeclarationBuffer> all_vertex_decl = {
  //MAKE_VERTEX_DECLARATION(PosClr, sizeof(VtxPosColor)),
//VertexDeclarationBuffer{ "PosClr", sizeof(VtxPosColor),}
  
};

void VertexDeclarationBuffer::setVertexAttribArray() const
{

}

std::vector<VtxPosColor>& VertexDeclarationBuffer::getVertexBuffer()
{
	return buffer;
}

std::vector< unsigned int>& VertexDeclarationBuffer::getIndexBuffer()
{
	return idb;
}
VertexDeclarationBuffer::VertexDeclarationBuffer()
{


}

VertexDeclarationBuffer::~VertexDeclarationBuffer()
{
}
