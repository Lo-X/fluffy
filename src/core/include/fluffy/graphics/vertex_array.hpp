#pragma once

#include <fluffy/graphics/platform/opengl.hpp>
#include <fluffy/graphics/vertex.hpp>
#include <fluffy/pch.hpp>
#include <glad/glad.h>

namespace Fluffy {

enum class PrimitiveType
{
    Points        = GL_POINTS,         // List of individual points
    Lines         = GL_LINES,          // List of individual lines
    LineStrip     = GL_LINE_STRIP,     // List of connected lines, a point uses the previous point to form a line
    Triangles     = GL_TRIANGLES,      // List of individual triangles
    TriangleStrip = GL_TRIANGLE_STRIP, // List of connected triangles, a point uses the two previous points to form a triangle
    TriangleFan   = GL_TRIANGLE_FAN,   // List of connected triangles, a point uses the common center and the previous point to form a triangle
    Quads         = GL_QUADS,
};

class VertexArray
{
public:
    VertexArray();
    explicit VertexArray(PrimitiveType type, std::size_t count = 0);
    ~VertexArray();

    void                      resize(std::size_t count);
    [[nodiscard]] std::size_t getVerticesCount() const;
    [[nodiscard]] std::size_t getByteSize() const;

    void append(const Vertex& vertex);
    void setVertex(std::size_t position, const Vertex& vertex);
    void clear();

    void bind();

    // @todo : temp function, remove it when proper Drawable / Renderer classes in place
    void draw()
    {
        bind();

        unsigned int VBO;
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        GlCall(glBufferData(GL_ARRAY_BUFFER, getByteSize(), mVerticesData.data(), GL_STATIC_DRAW));

        // Position
        GlCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0));
        glEnableVertexAttribArray(0);
        // Color
        GlCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float))));
        glEnableVertexAttribArray(1);
        // Texture
        GlCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float))));
        glEnableVertexAttribArray(2);

        GlCall(glDrawArrays((GLenum)mPrimitiveType, 0, static_cast<GLsizei>(getVerticesCount())));

        glDeleteBuffers(1, &VBO);
    }

private:
    unsigned int       mId;
    std::vector<float> mVerticesData;
    PrimitiveType      mPrimitiveType;
};
}
