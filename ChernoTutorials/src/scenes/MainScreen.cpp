#include "MainScreen.h"
#include <GL/glew.h>
#include "../Renderer.h"
#include "../vendor/imgui/imgui.h"

namespace scene {
	MainScreen::MainScreen() {
		activeScene = -1;
	}
	MainScreen::~MainScreen() {

	}

	void MainScreen::AddToList(Scene* scene, std::string name) {
		sceneList.push_back(scene);
		scnNames[name] = sceneList.size() - 1;
	}

	void MainScreen::RemoveFromSceneList(std::string name) {
		std::unordered_map<std::string, int>::iterator it = scnNames.find(name);
		if (it != scnNames.end()) {
			sceneList[scnNames[name]]->~Scene();
			sceneList.erase(sceneList.begin() + scnNames[name]);
			it++;
			for (; it != scnNames.end(); it++) {
				it->second--;
			}
			scnNames.erase(name);
		}
		else {
			std::cout << "[SCENE] Attempted to delete scene which doesn't exist! " << name << " could not be found!\n";
			__debugbreak();
		}
	}

	void MainScreen::BindScene(std::string name) {
		if (scnNames.find(name) != scnNames.end()) {
			activeScene = scnNames[name];
		}
		else {
			std::cout << "[SCENE] The requested scene " << name << " could not be found!\n";
			__debugbreak();
		}
	}

	void MainScreen::OnRender() {
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		if (activeScene != -1) {
			sceneList[activeScene]->OnRender();
		}
	}

	void MainScreen::OnImguiRender() {
		ImGui::Begin("Scenes");
		ImGui::Text("Click on a scene to load it");
		if (ImGui::Button("Main Menu")) {
			activeScene = -1;
		}
		for (std::unordered_map<std::string, int>::iterator it = scnNames.begin(); it != scnNames.end(); it++) {
			if (ImGui::Button(it->first.c_str())) {
				BindScene(it->first);
				debugMessages = "Active scene: " + it->first;
			}
		}
		if (activeScene == -1) {
			debugMessages = "Active scene: None";
		}
		ImGui::Text(debugMessages.c_str());
		ImGui::End();
		
		if (activeScene != -1) {
			sceneList[activeScene]->OnImguiRender();
		}
		
	}

	void MainScreen::OnUpdate(float deltaTime) {
		if (activeScene != -1) {
			sceneList[activeScene]->OnUpdate(deltaTime);
		}
	}
}