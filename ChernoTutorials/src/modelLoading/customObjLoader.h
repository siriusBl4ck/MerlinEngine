#pragma once
#include <vector>
#include <string>
#include "glm/glm.hpp"
#include <iostream>
#include <stdio.h>
#include "../Renderer.h"
#include "../VertexArray.h"
#include "../VertexBufferLayout.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../Shader.h"

namespace modelLoading {
	class myObj {
	private:
		std::string filepath = "";
		VertexArray* va;
		VertexBuffer* vb;
		IndexBuffer* ib;
		Shader* shader;
		Renderer* renderer;
	public:
		bool loadObj(std::string _filepath);
		myObj() {
		}
		~myObj() {
			delete va, vb, ib, shader;
		}
		void renderObj();
	};
}