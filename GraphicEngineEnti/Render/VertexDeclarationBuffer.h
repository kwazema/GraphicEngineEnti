#pragma once
static const struct vertices
{
	float x, y;
	float r, g, b;
};



class VertexDeclarationBuffer
{
	GLuint vertexBuffer,posLocation,colLocation;
	GLuint indexBuffer;
	std::vector<vertices> buffer;
	std::vector<unsigned int> idb;
	
	uint32_t nelements = 0;
	uint32_t bytesPerVertex = 0;
public:
	VertexDeclarationBuffer(const uint32_t & nelements,const uint32_t & bytes_per_vertex);
	void setVertexAttribArray() const;

	std::vector<vertices>& getVertexBuffer();
	std::vector<unsigned int>& getIndexBuffer();

	

	~VertexDeclarationBuffer();
};

