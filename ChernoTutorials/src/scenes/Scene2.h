#pragma once
#include "scene.h"
#include <GL/glew.h>
#include "../VertexBufferLayout.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../VertexArray.h"
#include "../Shader.h"
#include "../Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace scene {
	class Scene2 : public Scene
	{
	public:
		//using Scene::Scene;
		Scene2();
		~Scene2();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;

		void InitializeScene();
	private:
		float positions[4 * 4] = {
			-0.8f, -0.8f, 0.0f, 0.0f, //d
			0.8f, -0.8f, 1.0f, 0.0f,//c
			0.8f, 0.8f, 1.0f, 1.0f,//b
			-0.8f, 0.8f, 0.0f, 1.0f//a
		};

		unsigned int indices[6]{
			0, 2, 3,
			0, 1, 2,
		};

		float r = 0.0f;
		float increment = 0.05f;
		float speed = 0.01f;
		float time = 0;
		glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
		glm::mat4 proj;
		VertexArray va;
		glm::mat4 transMatrix;
	};
}