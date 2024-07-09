#include "r_gl.h"

#include <stdio.h>

unsigned int rglCreateVertexArrayObject() {
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    return VAO;
}

unsigned int rglCreateVertexBufferObject(const float vertexData[], size_t vertexDataSize) {
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return VBO;
}

unsigned int rglCreateElementBufferObject(const int index[], size_t indexSize) {
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, index, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return EBO;
}

RenderData rglCreateRenderData(const float vertexData[], size_t vertexDataSize, const int index[], size_t indexSize){
    RenderData rData;

    rData.VAO = rglCreateVertexArrayObject();
    glBindVertexArray(rData.VAO);

    rData.VBO = rglCreateVertexBufferObject(vertexData, vertexDataSize);
    rData.EBO = rglCreateElementBufferObject(index, indexSize);

    printf("Render data created! VAO: %i, VBO: %i, EBO: %i.\n", rData.VAO, rData.VBO, rData.EBO);

    glBindVertexArray(0);
    return rData;
}

void rglDestroyRenderData(RenderData rData){
    glDeleteBuffers(1, &rData.EBO);
    glDeleteBuffers(1, &rData.VBO);
    glDeleteVertexArrays(1, &rData.VAO);

    printf("Render data destroyed.\n");
}

void rglDrawElements(RenderData rData, size_t indexSize){
    glBindVertexArray(rData.VAO);
    glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void rglClear(){
    glClear(GL_COLOR_BUFFER_BIT);
}
