#include "r_gl.h"

#include <stdio.h>

void rglSetUpDefaultVertexAttributes() {
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // uv attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

unsigned int rglCreateVertexArrayObject() {
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    return VAO;
}

unsigned int rglCreateVertexBufferObject(const float vertexData[], size_t bufferSize) {
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return VBO;
}

unsigned int rglCreateElementBufferObject(const int index[], size_t bufferSize) {
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, index, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return EBO;
}

RenderData rglCreateRenderData(const float vertexData[], size_t vertexDataSize, const int index[], size_t indexSize){
    RenderData rData;

    rData.VAO = rglCreateVertexArrayObject();
    glBindVertexArray(rData.VAO);

    rData.VBO = rglCreateVertexBufferObject(vertexData, vertexDataSize * sizeof(float));
    rData.EBO = rglCreateElementBufferObject(index, indexSize * sizeof(int));

    glBindBuffer(GL_ARRAY_BUFFER, rData.VBO);
    rglSetUpDefaultVertexAttributes();
    glBindBuffer(GL_ARRAY_BUFFER, 0);

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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rData.EBO);
    glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void rglClear(){
    glClear(GL_COLOR_BUFFER_BIT);
}
