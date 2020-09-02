#pragma once

class VertexBuffer {
private:
	unsigned int m_RendererID;
public:
	//size : in bytes
	VertexBuffer() {}
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void unBind() const;

};