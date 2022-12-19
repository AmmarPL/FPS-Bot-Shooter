#include "main.h"

#ifndef LEAVES_H
#define LEAVES_H


class Leaves {
public:
    Leaves() {}
    Leaves(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float getx();
    float gety();
    float getz();
    double speed;
private:
    VAO *object;
};

#endif // LEAVES_H
