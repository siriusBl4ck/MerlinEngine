#include "ErrorLogging.h"
#include<GL/glew.h>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OPENGL ERROR] " << error << function << " " << file << ":" << line << "\n";
        return false;
    }
    return true;
}