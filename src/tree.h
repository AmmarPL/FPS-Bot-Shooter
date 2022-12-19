#include "main.h"

#ifndef TREE_H
#define TREE_H


class Tree {
public:
    Tree() {}
    Tree(float x, float y, color_t color);
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

#endif // TREE_H
