#include "Scene2.h"

namespace scene {
	Scene2::Scene2() {

	}
	Scene2::~Scene2() {

	}

	void Scene2::InitializeScene() {
        Renderer renderer;

        VertexArray va;
        va.Bind();

        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.125f, 1.125f);

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        shader.SetUniformMat4("u_MVP", proj);

        glm::mat4 transMatrix;
        transMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        //shader.SetUniformMat4("u_Transform", transMatrix);

        Texture texture("res/textures/siriusBl4ckLogo.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        proj = glm::ortho(-2.0f, 2.0f, -1.125f, 1.125f);
        transMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

        time += 0.0005;


        shader.Bind();

        renderer.Draw(va, ib, shader);

        transMatrix = glm::rotate(glm::mat4(1.0f), r * 2 * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
        transMatrix = glm::translate(glm::mat4(1.0f), pos) * transMatrix;
        shader.SetUniformMat4("u_MVP", proj * transMatrix);
	}

	void Scene2::OnRender() {
        InitializeScene();
	}

	void Scene2::OnUpdate(float deltaTime) {

	}

	void Scene2::OnImguiRender() {

	}
}