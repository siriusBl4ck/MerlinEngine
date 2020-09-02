#pragma once

#include "scene.h"
#include <string>

namespace scene {
	class Scene1 : public Scene {
	public:
		using Scene::Scene;
		~Scene1();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;
	private:
		float m_ClearColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	};
}