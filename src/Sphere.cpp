//
// Created by Paolo on 21/01/2018.
//

#include "Sphere.h"

using glm::vec3;
using glm::vec2;

void _generateVerts(float * verts, float * norms, float * tex, uint32_t * el, const uint32_t slices, const uint32_t stacks, const float radius) {
    float theta, phi;       // Generate positions and normals
    float thetaFac = (float)((2.0 * M_PI) / slices);
    float phiFac = (float)(M_PI / stacks);
    float nx, ny, nz, s, t;
    uint32_t idx = 0, tIdx = 0;
    for (uint8_t i = 0; i <= slices; i++) {
        theta = i * thetaFac;
        s = (float)i / slices;
        for (uint8_t j = 0; j <= stacks; j++) {
            phi = j * phiFac;
            t = (float)j / stacks;
            nx = sinf(phi) * cosf(theta);
            ny = sinf(phi) * sinf(theta);
            nz = cosf(phi);
            verts[idx] = radius * nx;
            verts[idx + 1] = radius * ny;
            verts[idx + 2] = radius * nz;
            norms[idx] = nx;
            norms[idx + 1] = ny;
            norms[idx + 2] = nz;
            idx += 3;

            tex[tIdx] = s;
            tex[tIdx + 1] = t;
            tIdx += 2;
        }
    }

    idx = 0;                      // Generate the element list
    for (uint8_t i = 0; i < slices; i++) {
        uint32_t stackStart = i * (stacks + 1);
        uint32_t nextStackStart = (i + 1) * (stacks + 1);
        for (uint8_t j = 0; j < stacks; j++) {
            if (j == 0) {
                el[idx] = stackStart;
                el[idx + 1] = stackStart + 1;
                el[idx + 2] = nextStackStart + 1;
                idx += 3;
            }
            else if (j == stacks - 1) {
                el[idx] = stackStart + j;
                el[idx + 1] = stackStart + j + 1;
                el[idx + 2] = nextStackStart + j;
                idx += 3;
            }
            else {
                el[idx] = stackStart + j;
                el[idx + 1] = stackStart + j + 1;
                el[idx + 2] = nextStackStart + j + 1;
                el[idx + 3] = nextStackStart + j;
                el[idx + 4] = stackStart + j;
                el[idx + 5] = nextStackStart + j + 1;
                idx += 6;
            }
        }
    }
}

GLuint Sphere::createVertexData(GLuint* VBO, GLuint* EBO, const vec3 center = vec3(0,0,0), const float radius = 1) {
    constexpr uint32_t slices = 10;
    constexpr uint32_t stacks = 10;

    constexpr uint32_t nVerts = (slices + 1) * (stacks + 1);
    constexpr uint32_t elements = slices * 2 * (stacks - 1) * 3;
    constexpr int _dataPerRow = 8;

    float v[3 * nVerts];        // Verts
    float n[3 * nVerts];        // Normals
    float tex[2 * nVerts];      // Tex coords
    uint32_t indices[elements];      // Elements

    _generateVerts(v, n, tex, indices, slices, stacks, radius);

    float vertices[_dataPerRow * nVerts];

    for (int i = nVerts; i--;) {
        int rowIndex = i * _dataPerRow;
        vertices[rowIndex] = v[i*3];
        vertices[rowIndex+1] = v[i*3+1];
        vertices[rowIndex+2] = v[i*3+2];
        vertices[rowIndex+3] = tex[i*2];
        vertices[rowIndex+4] = tex[i*2+1];
        vertices[rowIndex+5] = n[i*3];
        vertices[rowIndex+6] = n[i*3+1];
        vertices[rowIndex+7] = n[i*3+2];
    }

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _dataPerRow * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, _dataPerRow * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, _dataPerRow * sizeof(float), (void *) (5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return VAO;
}