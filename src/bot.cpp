#include "bot.h"
#include "main.h"

Bot::Bot(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 1);
    this->rotation = 0;
    speed = 1;
    this->erase=0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->bounding_box = { this->position.x, this->position.y, this->position .z, 20, 4 ,24};
    static const GLfloat vertex_buffer_data[] = {
        -10,0,-15,
        10,0,-15,
        0,0,5,

        -5,0,5,
        5,0,5,
        0,0,15
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Bot::draw(glm::mat4 VP) {
    if(this->erase==0){
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (this->position);    // glTranslatef
        glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
        // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
        // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
        Matrices.model *= (translate * rotate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->object);
    }
}

void Bot::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
bounding_box_t Bot :: return_bounding_box () {
    return this->bounding_box;
}

float Bot::getx(){
    return this->position.x;
}

float Bot::gety(){
    return this->position.y;
}


float Bot::getz(){
    return this->position.z;
}


void Bot::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
    int dirx =rand()%3;
    if(dirx ==0){
        this->position.x+=1;
    }
    else if(dirx==1){
        this->position.x-=1;

    }

    int diry=rand()%3;
    if(diry==0){
        this->position.y+=1;
    }
    else if(diry==1){
        this->position.y-=1;
    }
    
}

