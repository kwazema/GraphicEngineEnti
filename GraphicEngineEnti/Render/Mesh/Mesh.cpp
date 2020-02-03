#include "precompiledHeader.h"
#include "Mesh.h"
bool Mesh::create(
	const void* vertices,
	uint32_t new_nvertexs,
	uint32_t new_bytes_per_vertex,
	std::vector<unsigned int> indices,
	uint32_t new_nindices,
	uint32_t new_bytes_per_index,
	eTopology new_topology
) {

	nindices = new_nindices;
	nvertexs = new_nvertexs;
	bytes_per_vertex = new_bytes_per_vertex;
	bytes_per_index = new_bytes_per_index;
	topology = new_topology;

	vb = &vertices;
	ib = indices;
	assert(vertices);
	assert(nvertexs > 0);
	assert(new_bytes_per_vertex > 0);
	assert(topology != UNDEFINED);
	

	//assert(indices.empty());
	assert(nindices > 0);
	
	glGenBuffers(1, &VAO);
	glGenBuffers(1, &vbId);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, vbId);
	glBufferData(GL_ARRAY_BUFFER, bytes_per_vertex * nvertexs,vertices, GL_STATIC_DRAW);



	glGenBuffers(1, &ibId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * ib.size(), ib.data(), GL_STATIC_DRAW);
	
	glBindVertexArray(0);

	return true;
}

void Mesh::destroy()
{
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &vbId);
	glDeleteBuffers(1, &ibId);
}

void Mesh::render() const
{
	glDrawElements(topology, nindices, GL_UNSIGNED_INT, nullptr);
}

void Mesh::activate() const
{
	glBindVertexArray(VAO);
}

void Mesh::activateAndRender() const
{
	activate();
	render();
}
