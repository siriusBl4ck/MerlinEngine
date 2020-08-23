#include<iostream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<fstream>
#include<string>
#include<sstream>

#include "Renderer.h"

#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

const char* glsl_version = "#version 330 core";

glm::vec3 dir(0.0f, 0.0f, 0.0f);

void keyboardControls(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (key) {
    case GLFW_KEY_A:
        dir.x = -1;
        break;
    case GLFW_KEY_D:
        dir.x = 1;
        break;
    case GLFW_KEY_S:
        dir.y = -1;
        break;
    case GLFW_KEY_W:
        dir.y = 1;
        break;
    }
}

int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_DECORATED, false);

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());    

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    //glfwSetWindowPos(window, (mode->width / 2) - 422, (mode->height / 2) - 338);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, keyboardControls);

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    if (glewInit() != GLEW_OK) {
        std::cout << "ERROR!\n";
    }
    {
        float positions[4 * 4] = {
            -0.8f, -0.8f, 0.0f, 0.0f, //d
            0.8f, -0.8f, 1.0f, 0.0f,//c
            0.8f, 0.8f, 1.0f, 1.0f,//b
            -0.8f, 0.8f, 0.0f, 1.0f//a
        };

        unsigned int indices[6]{
            0, 2, 3,
            0, 1, 2,
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        
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
        shader.SetUniformMat4("u_Transform", transMatrix);

        Texture texture("res/textures/siriusBl4ckLogo.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        GLCall(glUseProgram(0));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        GLCall(glBindVertexArray(0));

        Renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;
        float speed = 0.1f;
        float time = 0;
        glm::vec3 pos(0.0f, 0.0f, 0.0f);

        bool show_demo_window = false;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            proj = glm::ortho(-2.0f, 2.0f, -1.125f, 1.125f);
            transMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

            time += 0.0005;

            pos += dir * speed;
            /* Render here */
            renderer.Clear();

            shader.Bind();

            renderer.Draw(va, ib, shader);

            shader.SetUniform4f("u_Color", clear_color.x, clear_color.y, clear_color.z, 1.0f);

            transMatrix = glm::rotate(glm::mat4(1.0f), r * 2 * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
            transMatrix = glm::translate(glm::mat4(1.0f), pos) * transMatrix;
            dir = glm::vec3(0.0f, 0.0f, 0.0f);
            shader.SetUniformMat4("u_MVP", proj * transMatrix);

            if (r >= 1.0f) {
                increment = -0.025f;
            }
            else if (r <= 0.0f) {
                increment = 0.025f;
            }

            r += increment;

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                ImGui::Checkbox("Another Window", &show_another_window);

                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            // 3. Show another simple window.
            if (show_another_window)
            {
                ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                ImGui::Text("Hello from another window!");
                if (ImGui::Button("Close Me"))
                    show_another_window = false;
                ImGui::End();
            }

            // Rendering
            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}