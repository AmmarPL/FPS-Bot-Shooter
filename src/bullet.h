#include "main.h"

#ifndef BULLET_H
#define BULLET_H


class Bullet {
public:
    Bullet() {}
    Bullet(float x, float y,float z,float xv, float yv, float zv, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box;
    void set_position(float x, float y);
    void tick();
    float getx();
    float gety();
    float getz();
    bounding_box_t return_bounding_box();
    float xv;
    float yv;
    float zv;
    double speed;
private:
    VAO *object;
};

#endif // BULLET_H
