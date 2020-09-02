#pragma once

class IndexBuffer {
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer() { m_Count = 0; m_RendererID = -1; }
	//count : number of elements
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void unBind() const;

	unsigned int GetCount() const;
};