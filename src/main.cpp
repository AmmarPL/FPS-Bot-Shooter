#include "main.h"
#include "timer.h"
#include "ball.h"
#include "plane.h"
#include "grass.h"
#include "tree.h"
#include "leaves.h"
#include "rock.h"
#include "bot.h"
#include "bullet.h"
#include "seven_segment_display.h"
// #include "gun.h"

using namespace std;

GLMatrices Matrices;
GLMatrices Matrices1;
GLMatrices Matrices2;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;

Plane plane1;


Seven_Segment_Display kills;
Seven_Segment_Display botsleft;
Seven_Segment_Display bullets1;
Seven_Segment_Display bullets2;
Seven_Segment_Display bullets3;

Seven_Segment_Display health1;
Seven_Segment_Display health2;
Seven_Segment_Display health3;


int treeno=100;
int grassno=200000;
int rockno=100;


int healthno=1000;
int bulletno=500;
int bulletind=0;
float bulletdirx=0;
float bulletdiry=0;
float bulletdirz=0;

int score=0;



int botno=10;

Tree tree1[100];
Grass grass1[200000];
Leaves leaves1[100];
Bullet bullet1[500];
Rock rock1[100];




Bot bot1[10];


// Gun gun1;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

float zoom=5;
std::vector<glm::vec3> vertices1;
std::vector<glm::vec2> uvs1;
std::vector<glm::vec3> normals1; // Won't be used at the moment.

std::vector<glm::vec3> vertices2;
std::vector<glm::vec2> uvs2;
std::vector<glm::vec3> normals2; // Won't be used at the moment.


float gunx;
float guny;
float gunz;
float oldgunx=0;
float oldguny=0;
float oldgunz=0;

int windowx=1000;
int windowy=1000;


float diffx=0;
float diffy=0;
float diffz=0;

float mvalx=0;
float mvalz=0;
double mxdiff;
double mydiff;

double oldx=windowx/2;
double oldy=windowy/2;





GLuint uvbuffer1;

GLuint vertexbuffer1;

GLuint uvbuffer2;

GLuint vertexbuffer2;


Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know     what you are doing
    glUseProgram (programID);


    // printf("x %f y %f z %f ubalubadubdub\n",diffx,diffz,diffy);
    oldgunx+=diffx;
    oldguny+=diffy;
    oldgunz+=diffz;
// unless you are sure!!
    glm::vec3 eye ( gunx-oldgunx/2-5,guny+oldguny/2-3, gunz+oldgunz/2+5 );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // printf("%f %f\n",mvalx,mvalz);
    glm::vec3 target (gunx-oldgunx/2-5+mvalx,guny+oldguny/2,gunz+oldgunz/2+5-mvalz);

    bulletdirx=mvalx;
    bulletdiry=3;
    bulletdirz=-mvalz;


    glm::vec3 up (0, 0, 1);



    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    Matrices1.model = glm::mat4(1.0f);

    Matrices1.MatrixID = glGetUniformLocation(programID, "MVP");

    // Matrices1.MatrixID = glGetUniformLocation(programID, "MVP");
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
    glm::mat4 translate0 = glm::translate (glm::vec3(gunx, guny, gunz));    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (90 * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate1    = glm::rotate((float) (180 * M_PI / 180.0f), glm::vec3(0, 0, 1));

    
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices1.model *= (scale*translate * rotate1*rotate);
    //gunover






    glm::mat4 translate1 = glm::translate (glm::vec3(gunx-oldgunx/2,guny+oldguny/2, gunz+oldgunz/2));    // glTranslatef

    glm::mat4 rotate2    = glm::rotate((float) (-10*mvalz * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate3    = glm::rotate((float) (-6*mvalx * M_PI / 180.0f), glm::vec3(0, 0, 1));

    printf("%f %f\n",mvalx,mvalz);
    Matrices1.model*=(translate1*rotate3*rotate2 * scale*translate0 * rotate1*rotate);
    glm::mat4 MVP1 = VP * Matrices1.model;

    glUniformMatrix4fv(Matrices1.MatrixID, 1, GL_FALSE, &MVP1[0][0]);
    // draw3DObject(this->object);



    //gun

    // gun1.draw(VP);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
    glVertexAttribPointer(
        0,                  // attribute
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer1);
    glVertexAttribPointer(
        1,                                // attribute
        2,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, vertices1.size() );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    //gunover




    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    plane1.draw(VP);
    ball1.draw(VP);
    for(int i=0;i<grassno;i++){
        if(abs(grass1[i].getx()-(gunx-oldgunx/2-5))<50 && abs(grass1[i].gety()-(guny+oldguny/2-3))<50)
            grass1[i].draw(VP);
    }
    for(int i=0;i<treeno;i++){
        tree1[i].draw(VP);
    }
    for(int i=0;i<treeno;i++){
        leaves1[i].draw(VP);
    }
    for(int i=0;i<rockno;i++){
        rock1[i].draw(VP);
    }
    for(int i=0;i<botno;i++){
        bot1[i].draw(VP);
    }
    for(int i=0;i<bulletind;i++){
        bullet1[i].draw(VP);
    }

    kills.set_number(score);
    kills.draw(VP);
    botsleft.set_number(botno-score);
    botsleft.draw(VP);
    bullets1.set_number((bulletno-bulletind)/100);
    bullets1.draw(VP);
    bullets2.set_number(((bulletno-bulletind)%100)/10);
    bullets2.draw(VP);
    bullets3.set_number(((bulletno-bulletind)%100)%10);
    bullets3.draw(VP);

    health1.set_number(((int)healthno)/100);
    health1.draw(VP);
    health2.set_number((((int)healthno)%100)/10);
    health2.draw(VP);
    health3.set_number((((int)healthno)%100)%10);
    health3.draw(VP);


}

void tick_input(GLFWwindow *window) {
    double xpos, ypos;
    glfwGetCursorPos(window,&xpos, &ypos);
    glfwSetCursorPos(window,windowx/2.0, windowy/2.0);

    mxdiff= (xpos-oldx)*0.1;
    mydiff= (ypos-oldy)*0.1;

    mvalx+=mxdiff;
    mvalz+=mydiff;
    // printf("differencesa are %f %f\n",mxdiff,mydiff);




    


    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    if (left) {
        diffx=0.5;
        diffy=0;
    }
    else if (right) {
        diffx=-0.5;
        diffy=0;
    }
    else if (up) {
        diffy=0.5;
        diffx=0;
    }
    else if (down) {
        diffy=-0.5;
        diffx=0;
    }
    else{
        diffx=0;
        diffy=0;
    }
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS)
    {
        if(bulletind<bulletno){
            bullet1[bulletind++]       = Bullet(gunx-oldgunx/2-5,guny+oldguny/2-3+10, gunz+oldgunz/2-10,bulletdirx,bulletdiry,bulletdirz,COLOR_BLUE);
            // printf("%d bullets remaining\n",bulletno-bulletind);
        }
        else{
            printf("Your score is %d\n",score);
            exit(0);
        }
    }   

    
}

void tick_elements() {

    kills.position.x=gunx-oldgunx/2-5+mvalx-10;
    kills.position.y= guny+oldguny/2+10;
    kills.position.z= gunz+oldgunz/2+5-mvalz+5;

    botsleft.position.x=gunx-oldgunx/2-5+mvalx-10;
    botsleft.position.y= guny+oldguny/2+10;
    botsleft.position.z= gunz+oldgunz/2+5-mvalz+10;


    bullets1.position.x=gunx-oldgunx/2-5+mvalx-10;
    bullets1.position.y= guny+oldguny/2+10;
    bullets1.position.z= gunz+oldgunz/2+5-mvalz+15;

    bullets2.position.x=gunx-oldgunx/2-5+mvalx-5;
    bullets2.position.y= guny+oldguny/2+10;
    bullets2.position.z= gunz+oldgunz/2+5-mvalz+15;

    bullets3.position.x=gunx-oldgunx/2-5+mvalx-0;
    bullets3.position.y= guny+oldguny/2+10;
    bullets3.position.z= gunz+oldgunz/2+5-mvalz+15;

    health1.position.x=gunx-oldgunx/2-5+mvalx-10;
    health1.position.y= guny+oldguny/2+10;
    health1.position.z= gunz+oldgunz/2+5-mvalz+20;

    health2.position.x=gunx-oldgunx/2-5+mvalx-5;
    health2.position.y= guny+oldguny/2+10;
    health2.position.z= gunz+oldgunz/2+5-mvalz+20;

    health3.position.x=gunx-oldgunx/2-5+mvalx-0;
    health3.position.y= guny+oldguny/2+10;
    health3.position.z= gunz+oldgunz/2+5-mvalz+20;

    ball1.tick();
    for(int i=0;i<botno;i++){
        bot1[i].tick();
        if(abs(gunx-oldgunx/2-5 - (bot1[i].position.x))<20 and abs(guny+oldguny/2-3- bot1[i].position.y)<20){
            healthno -=0.05;
        }
    }
    for(int i=0;i<bulletind;i++){
        for(int j=0;j<botno;j++){
            if (detect_collision(bullet1[i].return_bounding_box(), bot1[j].return_bounding_box()) and bot1[j].erase==0) {
                printf("killed bot %d\n",j);
                score+=1;
                bot1[j].erase=1;
            }
        }
    }
    for(int i=0;i<bulletind;i++){
        bullet1[i].tick();
    }

    // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(0,0, COLOR_BLACK);
    plane1 = Plane(0,0,COLOR_BROWN);

    kills =Seven_Segment_Display(3,3,3,0);
    botsleft =Seven_Segment_Display(3,3,3,0);
    bullets1 =Seven_Segment_Display(3,3,3,0);
    bullets2 =Seven_Segment_Display(3,3,3,0);
    bullets3 =Seven_Segment_Display(3,3,3,0);

    health1 =Seven_Segment_Display(3,3,3,0);
    health2 =Seven_Segment_Display(3,3,3,0);
    health3 =Seven_Segment_Display(3,3,3,0);
    // gun1= Gun(0,0,vertices1,uvs1,normals1,uvbuffer1,vertexbuffer1);


    // Matrices1.model = glm::mat4(1.0f);



    //gun

	bool res = loadOBJ("/home/ammar/Downloads/graphics-boilerplate-master/graphics-boilerplate-master/src/m4a1.obj", vertices1, uvs1, normals1);

    gunx=0;
    guny=0;
    gunz=0;

	glGenBuffers(1, &vertexbuffer1);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
	glBufferData(GL_ARRAY_BUFFER, vertices1.size() * sizeof(glm::vec3), &vertices1[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer1);
	glBufferData(GL_ARRAY_BUFFER, uvs1.size() * sizeof(glm::vec2), &uvs1[0], GL_STATIC_DRAW);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");

    // //gunover








    //grass
    for(int i=0;i<grassno;i++){
        grass1[i]=Grass((rand()%3200-1600)/4,(rand()%3200-1600)/4,COLOR_GREEN);
    }

    for(int i=0;i<treeno;i++){
        tree1[i]=Tree(rand()%800-400,rand()%800-400,COLOR_LIGHTBROWN);
    }

    for(int i=0;i<treeno;i++){
        leaves1[i]=Leaves(tree1[i].getx(),tree1[i].gety(),COLOR_GREEN);
    }


    for(int i=0;i<rockno;i++){
        rock1[i]=Rock(rand()%800-400,rand()%800-400,COLOR_GRAY);
    }

    for(int i=0;i<botno;i++){
        bot1[i]=Bot(rand()%400-200,rand()%400-200,COLOR_RED);
    }

    



    //grassover

    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = windowx;
    int height = windowy;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}


void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    // Matrices.projection = glm::ortho(left-zoom, right+zoom, bottom-zoom, top+zoom, 0.1f, 500.0f);
    Matrices.projection = glm::perspective(glm::radians(120.0f), 1.0f, 0.1f, 100.0f);
}
