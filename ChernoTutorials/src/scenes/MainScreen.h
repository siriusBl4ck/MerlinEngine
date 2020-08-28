#pragma once

#include "scene.h"
#include <vector>
#include <unordered_map>
#include <string>

namespace scene {
	class MainScreen : public Scene {
	public:
		MainScreen();
		~MainScreen();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;

		void BindScene(std::string name);

		void AddToList(Scene* scene, std::string name);
		void RemoveFromSceneList(std::string name);
	private:
		std::vector<Scene*> sceneList;
		std::unordered_map<std::string, int> scnNames;
		int activeScene;
		std::string debugMessages = "";
	};
}