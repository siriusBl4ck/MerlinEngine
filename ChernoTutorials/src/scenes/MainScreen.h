#pragma once

#include "scene.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include <iostream>


namespace scene {
	class MainScreen : public Scene {
	public:
		MainScreen(Scene* currentScnPtr);
		~MainScreen();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;

		template<typename T>
		void BindScene(std::string name) {
			std::cout << "[MAINSCREEN] Binding scene " << name << "\n";
			scenes.push_back(std::make_pair(name, []() { return new T(); }));
		}

		void AddToList(Scene* scene);
		void RemoveFromSceneList(std::string name);
		void RemoveFromSceneList(int scnIndex);
	private:
		std::vector<std::pair<std::string, std::function<Scene* ()>>> scenes;
		
		Scene* activeScn = nullptr;
		std::vector<Scene*> sceneList;
		std::unordered_map<std::string, int> scnNames;
		std::string debugMessages = "";
	};
}