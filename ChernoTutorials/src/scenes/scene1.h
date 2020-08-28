#pragma once

#include "scene.h"
#include <string>

namespace scene {
	class Scene1 : public Scene {
	public:
		Scene1();
		~Scene1();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;
	private:
		float m_ClearColor[4];
	};
}