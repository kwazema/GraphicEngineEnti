#include "precompiledHeader.h"
#include "primitives.h"
#include "../VertexDeclarationBuffer.h"

Mesh quad;
Mesh cube;

bool createQuad()
{

	std::vector<VtxPosColor> quadVertices;
	quadVertices.push_back({ -1.0f,  -1.0f,0.f, 0.f, 0.f, 1.f }); //0
	quadVertices.push_back({ -1.0f, 1.0f,0.f, 1.f, 0.f, 0.f });//1
	quadVertices.push_back({ 1.0, 1.0f,0.f, 0.f, 1.f, 0.f });//2
	quadVertices.push_back({ 1.0f, -1.0f,0.f, 1.f, 1.f, 1.f });//3


	std::vector<unsigned int>  idb = {
		0,1,2,
		0,2,3 };


	return quad.create(quadVertices.data(),
		quadVertices.size(),
		sizeof(VtxPosColor),
		idb,
		idb.size(), sizeof(unsigned int) * idb.size(),
		Mesh::eTopology::TRIANGLES);
}

bool createCube()
{
	std::vector<VtxPosColor> quadVertices = 
	{
		
		// front
		VtxPosColor(-1.0f, -1.0f,  1.0f,1.0f, 0.0f, 1.0f),
		VtxPosColor(1.0f, -1.0f,  1.0f, 0.0f, 1.0f,1.0f),
		VtxPosColor( 1.0,  1.0,  1.0, 0.0f,0.0f,0.1f),
		VtxPosColor (-1.0,  1.0,  1.0, 1.0f,1.0f,1.0f),
		// back
		VtxPosColor (-1.0, -1.0, -1.0, 1.0f,1.0f,1.0f),
		 VtxPosColor(1.0, -1.0, -1.0,  1.0f,1.0f,1.0f),
		VtxPosColor( 1.0,  1.0, -1.0,  1.0f,1.0f,1.0f),
		VtxPosColor(-1.0,  1.0, -1.0, 1.0f,1.0f,1.0f)
	  };
	std::vector<unsigned int> idb = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	return cube.create(quadVertices.data(),
		quadVertices.size(),
		sizeof(VtxPosColor),
		idb,
		idb.size(), sizeof(unsigned int) * idb.size(),
		Mesh::eTopology::TRIANGLES);
	
}
bool createPrimitives()
{
	bool ok = true;
	ok &= createQuad();
	ok &= createCube();
	return  ok;
	
}

void destroyPrimitives()
{

}

void setObjRenderCtes(glm::mat4 world, glm::vec4 color)
{
	
}
