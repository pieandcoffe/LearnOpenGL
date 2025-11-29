//
// Created by Kyrylo Pylinskyi on 22/11/2025.
//

#ifndef LEARNOPENGL_VERTEX_BUFFER_H
#define LEARNOPENGL_VERTEX_BUFFER_H

#include <glad/glad.h>
#include <vector>

/**
 * @brief RAII wrapper for an OpenGL Vertex Buffer Object (VBO).
 *
 * The VertexBuffer class encapsulates the creation, binding, updating,
 * and deletion of an OpenGL Vertex Buffer Object. This ensures clean
 * resource management by preventing accidental copying and enabling
 * efficient moving of buffers.
 */
class VertexBuffer
{
  public:
    /**
     * @brief Constructs a VBO from a raw pointer and size.
     *
     * @param data  Pointer to vertex data.
     * @param size  Size in bytes of the data.
     * @param usage OpenGL buffer usage hint (e.g., GL_STATIC_DRAW).
     */
    explicit VertexBuffer(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW);

    /**
     * @brief Constructs a VBO from a std::vector of floats.
     *
     * @param vertices Vector containing vertex data.
     * @param usage    OpenGL buffer usage hint (e.g., GL_STATIC_DRAW).
     */
    explicit VertexBuffer(const std::vector<float>& vertices, GLenum usage = GL_STATIC_DRAW);

    /**
     * @brief Deleted copy constructor.
     *
     * OpenGL buffer objects should not be copied because their internal
     * GPU-side resources cannot be meaningfully duplicated.
     */
    VertexBuffer(const VertexBuffer&) = delete;

    /**
     * @brief Deleted copy assignment.
     *
     * Prevents accidental copying of GPU buffer objects.
     */
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    /**
     * @brief Move constructor.
     *
     * Transfers ownership of the VBO from another instance.
     *
     * @param other VertexBuffer being moved from.
     */
    VertexBuffer(VertexBuffer&& other) noexcept;

    /**
     * @brief Move assignment operator.
     *
     * Releases the current buffer (if any) and transfers ownership from `other`.
     *
     * @param other VertexBuffer being moved from.
     * @return Reference to this object.
     */
    VertexBuffer& operator=(VertexBuffer&& other) noexcept;

    /**
     * @brief Destructor. Automatically deletes the OpenGL VBO.
     */
    ~VertexBuffer();

    /**
     * @brief Binds the VBO to the GL_ARRAY_BUFFER target.
     */
    void bind() const;

    /**
     * @brief Unbinds any VBO from GL_ARRAY_BUFFER target.
     */
    void unbind() const;

    /**
     * @brief Updates a portion or all of the buffer's data.
     *
     * @param data   Pointer to the new data.
     * @param size   Size of the new data in bytes.
     * @param offset Offset into the buffer where data should be written.
     *
     * @note The buffer must already be bound before calling this function.
     */
    void updateData(const void* data, size_t size, size_t offset = 0);

    /**
     * @brief Returns the OpenGL buffer ID.
     */
    unsigned int getID() const
    {
        return m_id;
    }

    /**
     * @brief Returns the total allocated size of the buffer, in bytes.
     */
    size_t getSize() const
    {
        return m_size;
    }

  private:
    unsigned int m_id; ///< The OpenGL-generated buffer ID.
    size_t m_size;     ///< Size of the buffer (in bytes).

    /**
     * @brief Creates the VBO and uploads initial data.
     *
     * @param data  Pointer to the vertex data.
     * @param size  Size in bytes of the data.
     * @param usage OpenGL buffer usage hint (e.g., GL_STATIC_DRAW).
     */
    void createBuffer(const void* data, size_t size, GLenum usage);
};

#endif // LEARNOPENGL_VERTEX_BUFFER_H
