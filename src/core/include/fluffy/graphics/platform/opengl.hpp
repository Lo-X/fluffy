#pragma once

#include <fluffy/assert.hpp>
#include <fluffy/pch.hpp>
#include <glad/glad.h>

#define GlCall(x)            \
    Fluffy::GLClearErrors(); \
    x;                       \
    FLUFFY_ASSERT(Fluffy::GLCheckError(#x, __FILE__, __LINE__), "OpenGL error occured.")

namespace Fluffy {

inline void GLClearErrors()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

inline bool GLCheckError(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError()) {
        FLUFFY_LOG_ERROR("OpenGL error (" + toString(error) + ") in " + function + " in file " + file + ":" + toString(line));

        return false;
    }

    return true;
}
}
