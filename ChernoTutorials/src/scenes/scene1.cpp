#include "scene1.h"
#include <GL/glew.h>
#include "../vendor/imgui/imgui.h"
#include "../Renderer.h"

namespace scene {
	Scene1::~Scene1() {

	}

	void Scene1::OnRender() {
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void Scene1::OnUpdate(float deltaTime) {

	}

	void Scene1::OnImguiRender(){
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
	}
}