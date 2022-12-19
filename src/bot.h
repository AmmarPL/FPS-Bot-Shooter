#include "main.h"

#ifndef BOT_H
#define BOT_H


class Bot {
public:
    Bot() {}
    Bot(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box;
    void set_position(float x, float y);
    void tick();
    float getx();
    float gety();
    float getz();
    int erase;
    bounding_box_t return_bounding_box();
    double speed;
private:
    VAO *object;
};

#endif // BOT_H
