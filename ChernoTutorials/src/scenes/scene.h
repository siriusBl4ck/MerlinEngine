#pragma once
#include <string>

namespace scene {
	class Scene {
	public:
		std::string name = "New Scene";
		Scene() {}
		Scene(std::string _name) : name(_name) {}
		virtual ~Scene() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImguiRender() {}
	};
}