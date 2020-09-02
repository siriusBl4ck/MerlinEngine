#include "scene3.h"

namespace scene {
	Scene3::Scene3() {
		name = "scene3";
	}

	Scene3::~Scene3() {

	}

	void Scene3::OnUpdate(float deltaTime) {
		if (!dataLoaded) {
			if (object.loadObj("res/models/suzanne.obj")) {

			}
			else {
				std::cout << "[SCENE 3] Model failed to load!\n";
			}

			dataLoaded = true;
		}
	}

	void Scene3::OnRender() {
		object.renderObj();
	}
}