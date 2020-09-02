#include "customObjLoader.h"


namespace modelLoading {
	bool myObj::loadObj(std::string _filepath){
		std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
		std::vector<float> temp_verts;
		std::vector<float> temp_uvs;
		std::vector<float> temp_normals;

		filepath = _filepath;

		/*std::ifstream objfile;
		objfile.open(filepath.c_str());*/
		FILE* file;
		fopen_s(&file, filepath.c_str(), "r");
		
		if (file == NULL) {
			std::cout << "[MODEL LOAD] File " << filepath << " not found!\n";
			return false;
		}
		//std::cout << "[DEBUG] file opened!\n";
		
		while (true) {
			char lineHeader[128];
			// read the first word of the line
			auto res = fscanf_s(file, "%s", lineHeader, sizeof(lineHeader));
			
			if (res == EOF) {
				break;
				std::cout << "[DEBUG] eof encountered!\n";
			}

			//parse first word
			if (!strcmp(lineHeader, "v")) {
				glm::vec3 vertex;
				fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z); //read the vertex in from file
				//add to our "vertex buffer data"
				temp_verts.push_back(vertex.x / 2);
				temp_verts.push_back(vertex.y / 2);
				temp_verts.push_back(vertex.z / 2);
			}
			else if (!strcmp(lineHeader, "vt")) {
				glm::vec2 uv;
				fscanf_s(file, "%f %f\n", &uv.x, &uv.y); //read the uv
				//add to uv buffer
				temp_uvs.push_back(uv.x);
				temp_uvs.push_back(uv.y);
			}
			else if (!strcmp(lineHeader, "vn")) {
				glm::vec3 normal;
				fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z); //read the normal
				//add to normal buffer
				temp_normals.push_back(normal.x);
				temp_normals.push_back(normal.y);
				temp_normals.push_back(normal.z);
			}
			else if (!strcmp(lineHeader, "f")) {
				std::string vert1, vert2, vert3;
				unsigned int vertIndex[3], uvIndex[3], normIndex[3];
				auto err = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertIndex[0], &uvIndex[0], &normIndex[0], &vertIndex[1], &uvIndex[1], &normIndex[1], &vertIndex[2], &uvIndex[2], &normIndex[2]);

				if (err == 0) {
					break;
				}

				/*if (matches != 9) {
					std::cout << "[MODEL LOAD] File cannot be read by custom simple parser! Use ASSIMP or while exporting use:\n 1. Include normals, 2. Include UVs 3. Triangulate Faces\n";
				}*/
				//add the indices to index buffer
				vertexIndices.push_back(vertIndex[0]);
				vertexIndices.push_back(vertIndex[1]);
				vertexIndices.push_back(vertIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normIndex[0]);
				normalIndices.push_back(normIndex[1]);
				normalIndices.push_back(normIndex[2]);
			}
		}

		//std::cout << "[DEBUG] data read!\n";

		//add this temporary data into our custom classes for vertex array, vertex buffer and index buffer	
		va = new VertexArray();
		va->Bind();
		//std::cout << "[DEBUG] va bound!\n";

		vb = new VertexBuffer(temp_verts.data(), temp_verts.size() * sizeof(float));
		vb->Bind();
		VertexBufferLayout layout;
		layout.Push<float>(3);
		va->AddBuffer(*vb, layout);

		ib = new IndexBuffer(vertexIndices.data(), vertexIndices.size());
		
		shader = new Shader("res/shaders/blankShader.shader");
		shader->Bind();
		//std::cout << "[DEBUG] shader bound!\n";
		
		renderer = new Renderer();
		//std::cout << "[DEBUG] RENDER!\n";
		
	}

	void myObj::renderObj() {
		renderer->Draw(*va, *ib, *shader);
	}
}