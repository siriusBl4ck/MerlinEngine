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
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            time += 0.0005;

            pos += dir * speed;
            /* Render here */
            renderer.Clear();

            shader.Bind();

            renderer.Draw(va, ib, shader);

            shader.SetUniform4f("u_Color", 1 - r, 1.0f, r, 1.0f);

            transMatrix = glm::rotate(glm::mat4(1.0f), r * 2 * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
            transMatrix = glm::translate(glm::mat4(1.0f), pos) * transMatrix;
            dir = glm::vec3(0.0f, 0.0f, 0.0f);
            shader.SetUniformMat4("u_Transform", transMatrix);

            if (r >= 1.0f) {
                increment = -0.025f;
            }
            else if (r <= 0.0f) {
                increment = 0.025f;
            }

            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}