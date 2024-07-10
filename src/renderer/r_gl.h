#include "dependencies.h"

#define _ROPENGL

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
    } RenderData;

    void rglSetUpDefaultVertexAttributes();
    unsigned int rglCreateVertexArrayObject();
    unsigned int rglCreateVertexBufferObject(const float vertexData[], size_t bufferSize);
    unsigned int rglCreateElementBufferObject(const int index[], size_t bufferSize);
    RenderData rglCreateRenderData(const float vertexData[], size_t vertexDataSize, const int index[], size_t indexSize);
    void rglDestroyRenderData(RenderData rData);

    void rglDrawElements(RenderData rData, size_t indexSize);
    void rglClear();

#ifdef __cplusplus
}
#endif
