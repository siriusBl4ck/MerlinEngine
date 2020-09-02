#pragma once
#include "scene.h"
#include "../modelLoading/customObjLoader.h"

namespace scene {
	class Scene3 : public Scene
	{
	public:
		//using Scene::Scene;
		Scene3();
		~Scene3();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		//void OnImguiRender() override
	private:
		modelLoading::myObj object;
		bool dataLoaded = false;
	};
}