/*********
   CTIS164 - Template Source Program
----------
STUDENT :EMÝR TUNA BEÞLÝ
SECTION :
HOMEWORK:HOMEWORK 3
STUDENT NUMBER: 22102039
----------
PROBLEMS:
----------
ADDITIONAL FEATURES: You can choose a color and move it as you wish as long as you are in borders of the window. You can choose color 1 as red, 2 as green and 3 as blue. After you chose the color, you can not choose other colors while you are still moving that color and when you leave, it goes back to it's orbit. Then you can choose any other color.
*********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include "vec.h"
#include <time.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800

#define TIMER_PERIOD  16 // Period for the timer.
#define TIMER_ON         1// 0:disable timer, 1:enable timer

#define D2R 0.0174532
#define NUM 3

#define winlefttopx -400
#define winlefttopy 400

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
bool restart = 0, redon = 1, blueon = 1, greenon = 1, animation = 1, playeron = 0, redplayer = 0, greenplayer = 0, blueplayer = 0;
int  winWidth, winHeight; // current Window width and height

typedef struct {
    float r, g, b;
} color_t;

typedef struct {
    vec_t   pos;
    color_t color;
    int rad;
    float vel;
    float angle;
} light_t;

typedef struct {
    vec_t pos;
    vec_t N;
} vertex_t;

light_t light[3] = {
   { {    0, 0 }, { 1, 0, 0 } },
   { {  0, 0 }, { 0, 1, 0 } },
   { { 0, 0 }, { 0, 0, 1 }}
};

color_t mulColor(float k, color_t c) {
    color_t tmp = { k * c.r, k * c.g, k * c.b };
    return tmp;
}

color_t addColor(color_t c1, color_t c2) {
    color_t tmp = { c1.r + c2.r, c1.g + c2.g, c1.b + c2.b };
    return tmp;
}

// To add distance into calculation
// when distance is 0  => its impact is 1.0
// when distance is 350 => impact is 0.0
// Linear impact of distance on light calculation.
double distanceImpact(double d) {
    return (-1.0 / 700.0) * d + 1.0;
}

color_t calculateColor(light_t source, vertex_t v) {
    vec_t L = subV(source.pos, v.pos);
    vec_t uL = unitV(L);
    float factor = dotP(uL, v.N) * distanceImpact(magV(L));
    return mulColor(factor, source.color);
};


void cirlceTriangle(int x, int y, int r) {
    vec_t pos;
    pos.x = x;
    pos.y = y;
    float angle;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0, 0, 0);
    glVertex2f(x, y);
    for (int i = 0; i < 361; i++) {
        pos.x = x + r * cos(i * D2R);
        pos.y = y + r * sin(i * D2R);
        vertex_t P = { { pos.x, pos.y }, { cos(i * D2R), sin(i * D2R)} };
        color_t res = { 0, 0, 0 };
        for (int i = 0; i < NUM; i++) {
            res = addColor(res, calculateColor(light[i], P));
        }
        glColor3f(res.r, res.g, res.b);
        glVertex2f(x + r * cos(i * D2R), y + r * sin(i * D2R));
    }
    glEnd();
}
//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i += 1)
    {
        angle = 2 * PI * i / 360;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void print(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}
void content() {
    glColor3ub(175, 119, 225);
    print(winlefttopx + 20, winlefttopy - 45, "HOMEWORK#3", GLUT_BITMAP_9_BY_15);
    print(winlefttopx + 10, winlefttopy - 60, "Emir Tuna Besli", GLUT_BITMAP_9_BY_15);
    glColor3f(1, 1, 1);
    if (redon)
        print(-350, -380, "F1(RED):ON", GLUT_BITMAP_9_BY_15);
    else {
        glColor3f(1, 0, 0);
        print(-350, -380, "F1(RED):OFF", GLUT_BITMAP_9_BY_15);
        glColor3f(1, 1, 1);
    }
    if (greenon)
        print(-200, -380, "F2(GREEN):ON", GLUT_BITMAP_9_BY_15);
    else {
        glColor3f(1, 0, 0);
        print(-200, -380, "F2(GREEN):OFF", GLUT_BITMAP_9_BY_15);
        glColor3f(1, 1, 1);
    }
    if (blueon)
        print(-50, -380, "F3(BLUE):ON", GLUT_BITMAP_9_BY_15);
    else {
        glColor3f(1, 0, 0);
        print(-50, -380, "F3(BLUE):OFF", GLUT_BITMAP_9_BY_15);
        glColor3f(1, 1, 1);
    }
    if (animation)
        print(80, -380, "F4(ANIMATION):ON", GLUT_BITMAP_9_BY_15);
    else {
        glColor3f(1, 0, 0);
        print(80, -380, "F4(ANIMATION):OFF", GLUT_BITMAP_9_BY_15);
        glColor3f(1, 1, 1);
    }
    print(280, -380, "F5:RESTART", GLUT_BITMAP_9_BY_15);
    if (!playeron)
    {
        print(-170, 380, "Choose color: 1:RED 2:GREEN 3:BLUE", GLUT_BITMAP_9_BY_15);
    }
    if (redplayer) {
        glColor3f(1, 0, 0);
        print(-100, 380, "Color Red choosen.", GLUT_BITMAP_9_BY_15);
        print(-170,360, "SPACE to LEAVE | Arrow keys to MOVE", GLUT_BITMAP_9_BY_15);
    }
    else if (greenplayer) {
        glColor3f(0, 1, 0);
        print(-100, 380, "Color Green choosen.", GLUT_BITMAP_9_BY_15);
        print(-170, 360, "SPACE to LEAVE | Arrow keys to MOVE", GLUT_BITMAP_9_BY_15);
    }
    else if (blueplayer) {
        glColor3f(0, 0, 1);
        print(-100, 380, "Color Blue choosen.", GLUT_BITMAP_9_BY_15);
        print(-170, 360, "SPACE to LEAVE | Arrow keys to MOVE", GLUT_BITMAP_9_BY_15);
    }

}
//
// To display onto window using OpenGL commands
//
void display() {
    //
    // clear window to black
    //
    glClearColor(0.1, 0.1, 0.1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < NUM; i++) {
        glColor3f(1, 1, 1);
        circle_wire(0, 0, light[i].rad);
        cirlceTriangle(0, 0, 70);
    }
    if (redon) {
        light[0].color = { 1,0,0 };
        glColor3f(light[0].color.r, light[0].color.g, light[0].color.b);
        circle(light[0].pos.x, light[0].pos.y, 10);
    }
    else
        light[0].color = { 0,0,0 };
    if (greenon) {
        light[1].color = { 0,1,0 };
        glColor3f(light[1].color.r, light[1].color.g, light[1].color.b);
        circle(light[1].pos.x, light[1].pos.y, 10);
    }
    else
        light[1].color = { 0,0,0 };
    if (blueon) {
        light[2].color = { 0,0,1 };
        glColor3f(light[2].color.r, light[2].color.g, light[2].color.b);
        circle(light[2].pos.x, light[2].pos.y, 10);
    }
    else {
        light[2].color = { 0,0,0 };
    }
    content();



    glutSwapBuffers();
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);
    if (key == ' ' && playeron == 1) {
        playeron = !playeron;
        redplayer = 0;
        greenplayer = 0;
        blueplayer = 0;
    }

    if (!playeron) {
        if (key == '1')
        {
            playeron = !playeron;
            redplayer = !redplayer;
        }
        if (key == '2') {
            playeron = !playeron;
            greenplayer = !greenplayer;
        }
        if (key == '3') {
            playeron = !playeron;
            blueplayer = !blueplayer;
        }
    }
    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = true; break;
    case GLUT_KEY_DOWN: down = true; break;
    case GLUT_KEY_LEFT: left = true; break;
    case GLUT_KEY_RIGHT: right = true; break;
    }
    if (key == GLUT_KEY_F5)
        restart = !restart;
    if (key == GLUT_KEY_F1)
        redon = !redon;
    if (key == GLUT_KEY_F2)
        greenon = !greenon;
    if (key == GLUT_KEY_F3)
        blueon = !blueon;
    if (key == GLUT_KEY_F4)
        animation = !animation;

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = false; break;
    case GLUT_KEY_DOWN: down = false; break;
    case GLUT_KEY_LEFT: left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y)
{
    // Write your codes here.



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}

void onMoveDown(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function   
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function
    glutPostRedisplay();
}
void resetpos() {
    int x;
    light[0].rad = ((rand() % 50) + 150);
    light[1].rad = ((rand() % 50) + 225);
    light[2].rad = ((rand() % 50) + 300);
    for (int i = 0; i < NUM; i++) {
        x = (rand() % 360) + 1;
        light[i].angle = 2 * PI * x / 360.0;
        light[i].pos.x = light[i].rad * cos(light[i].angle);
        light[i].pos.y = light[i].rad * sin(light[i].angle);
        int direction = (rand() % 2 ? 1 : -1);
        light[i].vel = ((((rand() % 5) + 3) / 250.0) * direction);
    }

}


#if TIMER_ON == 1
void onTimer(int v) {

    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    // Write your codes here.

    if (restart) {
        resetpos();
        restart = !restart;
    }
    if (animation) {
        if (redplayer && playeron) {
            if (light[0].pos.x < 390 && light[0].pos.x > -390 && light[0].pos.y > -390 && light[0].pos.y < 390) {
                if (left) light[0].angle += 3;
                if (right) light[0].angle -= 3;
                if (up)  light[0].pos = addV(light[0].pos, pol2rec({ light[0].vel * 150, light[0].angle }));
                if (down)  light[0].pos = subV(light[0].pos, pol2rec({ light[0].vel * 150, light[0].angle }));
            }
            else {
                if (light[0].pos.x < 0)
                    light[0].pos.x += 1;
                else
                    light[0].pos.x -= 1;
                if (light[0].pos.y > 0)
                    light[0].pos.y -= 1;
                else
                    light[0].pos.y += 1;
            }
        }
        else {
            light[0].angle += light[0].vel;
            light[0].pos.x = light[0].rad * cos(light[0].angle);
            light[0].pos.y = light[0].rad * sin(light[0].angle);
        }
        if (greenplayer && playeron) {
            if (light[1].pos.x < 390 && light[1].pos.x > -390 && light[1].pos.y > -390 && light[1].pos.y < 390) {
                if (left) light[1].angle += 3;
                if (right) light[1].angle -= 3;
                if (up)  light[1].pos = addV(light[1].pos, pol2rec({ light[1].vel * 150, light[1].angle }));
                if (down)  light[1].pos = subV(light[1].pos, pol2rec({ light[1].vel * 150, light[1].angle }));
            }
            else {
                if (light[1].pos.x < 0)
                    light[1].pos.x += 1;
                else
                    light[1].pos.x -= 1;
                if (light[1].pos.y > 0)
                    light[1].pos.y -= 1;
                else
                    light[1].pos.y += 1;
            }
        }
        else {
            light[1].angle += light[1].vel;
            light[1].pos.x = light[1].rad * cos(light[1].angle);
            light[1].pos.y = light[1].rad * sin(light[1].angle);
        }
        if (blueplayer && playeron) {
            if (light[2].pos.x < 390 && light[2].pos.x > -390 && light[2].pos.y > -390 && light[2].pos.y < 390) {
                if (left) light[2].angle += 3;
                if (right) light[2].angle -= 3;
                if (up)  light[2].pos = addV(light[2].pos, pol2rec({ light[2].vel * 150, light[2].angle }));
                if (down)  light[2].pos = subV(light[2].pos, pol2rec({ light[2].vel * 150, light[2].angle }));
            }
            else {
                if (light[2].pos.x < 0)
                    light[2].pos.x += 1;
                else
                    light[2].pos.x -= 1;
                if (light[2].pos.y > 0)
                    light[2].pos.y -= 1;
                else
                    light[2].pos.y += 1;
            }
        }
        else
        {
            light[2].angle += light[2].vel;
            light[2].pos.x = light[2].rad * cos(light[2].angle);
            light[2].pos.y = light[2].rad * sin(light[2].angle);
        }
    }
    // to refresh the window it calls display() function
    glutPostRedisplay(); // display()

}
#endif

void Init() {

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    srand(time(NULL));
    resetpos();
}

void main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("HOMEWORK #4 LIGHTING SIMULATION - EMIR TUNA BESLI");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    //
    // mouse registration
    //
    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
    // timer event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    Init();

    glutMainLoop();
}
