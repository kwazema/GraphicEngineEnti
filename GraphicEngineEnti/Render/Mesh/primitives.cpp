#include "precompiledHeader.h"
#include "primitives.h"
#include "../VertexDeclarationBuffer.h"

Mesh quad;

bool createPrimitives()
{
	std::vector<VtxPosColor> quadVertices;
	quadVertices.push_back({ -0.5f,  -0.5f, 0.f, 0.f, 1.f }); //0
	quadVertices.push_back({ 0.5f, -0.5f, 1.f, 0.f, 0.f });//1
	quadVertices.push_back({ 0.5f, 0.5f, 0.f, 1.f, 0.f });//2
	quadVertices.push_back({ -0.5f, 0.5f, 1.f, 1.f, 1.f });//3

	
	std::vector<unsigned int>  idb = {
		0,1,2,
		2,3,0 };
	
	
	

	return quad.create(quadVertices.data(),
		quadVertices.size(),
		sizeof(VtxPosColor),
		idb,
		idb.size(), sizeof(unsigned int)* idb.size(),
		Mesh::eTopology::TRIANGLES);

	
}

void destroyPrimitives()
{

}

void setObjRenderCtes(glm::mat4 world, glm::vec4 color)
{
	
}
