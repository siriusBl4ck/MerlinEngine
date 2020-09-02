#include "MainScreen.h"
#include <GL/glew.h>
#include "../Renderer.h"
#include "../vendor/imgui/imgui.h"
#include "../scenes/scene1.h"
#include "../scenes/Scene2.h"
#include <utility>

namespace scene {
	MainScreen::MainScreen(Scene* currentScnPtr) :activeScn(currentScnPtr)
	{
	}
	MainScreen::~MainScreen() {

	}

	void MainScreen::AddToList(Scene* scene) {
		sceneList.push_back(scene);
		scnNames[scene->name] = sceneList.size() - 1;
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
	
	void MainScreen::RemoveFromSceneList(int scnIndex) {
		if (scnIndex < sceneList.size()) {
			sceneList[scnIndex]->~Scene();
			sceneList.erase(sceneList.begin() + scnIndex);
			std::unordered_map<std::string, int>::iterator it = scnNames.begin();
			for (int i = 0; i < scnIndex; i++) {
				it++;
			}
			std::string name = it->first;
			it++;
			scnNames.erase(name);

			while (it != scnNames.end()) {
				it->second--;
			}
		}
		else {
			std::cout << "[SCENE] Attempted to delete scene which doesn't exist! Scene index " << scnIndex << " out of bounds!\n";
			__debugbreak();
		}
	}

	void MainScreen::OnRender() {
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		if (activeScn != nullptr) {
			activeScn->OnRender();
		}
		else {
			//render the extra bits, like the MerlinEngine logo
		}
	}

	void MainScreen::OnImguiRender() {
		ImGui::Begin("Scenes");
		ImGui::Text("Click on a scene to load it");
		if (ImGui::Button("Main Menu")) {
			activeScn = nullptr;
		}
		for (auto it = scenes.begin(); it != scenes.end(); it++) {
			if (ImGui::Button(it->first.c_str())) {
				if (activeScn != nullptr) {
					delete activeScn;
				}
				activeScn = it->second();
				debugMessages = "Active scene: ";
				debugMessages.append(it->first.c_str());
			}
		}
		if (scenes.size() == 0) {
			debugMessages = "Active scene: None";
		}
		ImGui::Text(debugMessages.c_str());
		/*if (ImGui::Button("Delete Active Scene")) {
			if (activeScn != nullptr) {
				RemoveFromSceneList(activeScn->name);
				activeScn = nullptr;

			}
		}*/
		ImGui::End();
		
		if (activeScn != nullptr) {
			activeScn->OnImguiRender();
		}
		else {
			//main screen exclusive buttons, like create new scene, manage scenes, etc
		}
	}

	void MainScreen::OnUpdate(float deltaTime) {
		if (activeScn != nullptr) {
			activeScn->OnUpdate(deltaTime);
		}
	}
}