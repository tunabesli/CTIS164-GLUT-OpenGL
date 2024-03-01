/*********
   CTIS164 - Template Source Program
----------
STUDENT :EMIR TUNA BESLÝ
NUMBER :22102039
SECTION :
HOMEWORK:HW2
----------
PROBLEMS:gl polygon function fails in some points but they are in correct order. ý could not understand.
----------
ADDITIONAL FEATURES:WHEN WEAPON OBJECT LEAVES THE WINDOW FROM ONE SIDE, IT COMES FROM OTHERSIDE OF THE WINDOW, THE TARGET OBJECTS COMES FROM BOTH SIDES OF THE WINDOW. 
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

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 700

#define TIMER_PERIOD  16 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532
#define TARGET_RADIUS 20

#define MAX_FIRE 20
#define FIRE_RATE 10
#define STRCTR 50

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height
int sec= 99, min = 19;
int fire_rate = 0;
bool active = 0;
bool spacebar = 0;
int rocket = 0, rockety = -250;
int x[STRCTR], y[STRCTR], r[STRCTR], g[STRCTR], b[STRCTR];
typedef struct {
    int y;
    int x;
    bool create;
}bullet_t;

bullet_t bullet[MAX_FIRE];

typedef struct {
    int x;
    int y;
    float radius;
    float speed;
    int r, g, b;
} target_t;

target_t target[5];


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
void circle2(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    for (int i = 50; i < 100; i++)
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
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}
void pie_wire(float x, float y, float r, float start, float end) {
    glBegin(GL_LINE_STRIP);
    for (float angle = start; angle < end; angle += 10) {
        glVertex2f(r * cos(angle * D2R) + x, r * sin(angle * D2R) + y);
    }
    glEnd();
}
void pie_filled(float x, float y, float r, float start, float end) {
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    for (float angle = start; angle < end; angle += 10) {
        glVertex2f(r * cos(angle * D2R) + x, r * sin(angle * D2R) + y);
    }
    glVertex2f(r * cos(end * D2R) + x, r * sin(end * D2R) + y);
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
    for (i = 0; i < len; i++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}

void drawBackground() {

    //PLANETS
    //EARTH
    glColor3ub(41, 90, 223);
    circle(-300, 100, 60);
    //
    //MARS
    glColor3ub(193, 68, 14);
    circle(-40, 120, 15);
    //
    //JUPITER   
    glColor3ub(216, 202, 117);
    circle(0, -100, 80);
    glColor3ub(202, 182, 116);
    circle(-20, -140, 20);
    glColor3ub(202, 182, 116);
    circle(20, -80, 30);
    //
    //MOON
    glColor3ub(100, 100, 100);
    circle(-400, 200, 15);
    glColor3ub(120, 120, 120);
    circle(-395, 205, 5);
    glLineWidth(2);
    float angle;
    glColor3f(1, 1, 0);
    circle(300, 150, 100);
    glBegin(GL_LINES);
    for (int i = 0; i < 100; i += 5)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(300 + 100 * cos(angle), 150 + 100 * sin(angle));
        glVertex2f(300 + 150 * cos(angle), 150 + 150 * sin(angle));
    }
    glEnd();


    //CLOUD
    glColor3ub(52, 165, 111);
    circle(-300, 130, 12);
    glColor3ub(52, 165, 111);
    circle(-260, 100, 8);
    glColor3ub(52, 165, 111);
    circle(-330, 80, 16);
    //
    //  STARS
    //
    for (int i = 0; i < STRCTR / 2; i++)
    {
        glColor3ub(r[i], g[i], 255);
        glBegin(GL_POLYGON);
        glVertex2f(x[i] + 2, y[i] + 8);
        glVertex2f(x[i] + 10, y[i] + 10);
        glVertex2f(x[i] + 2, y[i] + 12);
        glVertex2f(x[i], y[i] + 20);
        glVertex2f(x[i] - 2, y[i] + 12);
        glVertex2f(x[i] - 10, y[i] + 10);
        glVertex2f(x[i] - 2, y[i] + 8);
        glVertex2f(x[i], y[i]);
        glEnd();
    }for (int i = STRCTR / 2; i < STRCTR; i++)
    {
        glColor3ub(r[i], g[i], 255);
        glBegin(GL_POLYGON);
        glVertex2f(x[i] + 3, y[i] + 12);
        glVertex2f(x[i] + 15, y[i] + 15);
        glVertex2f(x[i] + 3, y[i] + 18);
        glVertex2f(x[i], y[i] + 30);
        glVertex2f(x[i] - 3, y[i] + 18);
        glVertex2f(x[i] - 15, y[i] + 15);
        glVertex2f(x[i] - 3, y[i] + 12);
        glVertex2f(x[i], y[i]);
        glEnd();
    }
}

void createBullet()
{
    for (int k = 0; k < MAX_FIRE; k++)
        if (bullet[k].create) {
            glRectf(bullet[k].x, bullet[k].y, bullet[k].x + 5, bullet[k].y + 10);
        }
}
void drawTarget(target_t target[]) {
    for (int i = 0; i < 5; i++) {
        glColor3ub(target[i].r, target[i].g, target[i].b);
        pie_filled(target[i].x, target[i].y, target[i].radius, -30, 30);
        pie_filled(target[i].x, target[i].y, target[i].radius, -210, -150 );
        glColor3f(1, 0, 0);
        circle(target[i].x, target[i].y, target[i].radius - 13);
        glColor3f(0, 0, 0);
        pie_wire(target[i].x, target[i].y, target[i].radius, -60,60);
        pie_wire(target[i].x, target[i].y, target[i].radius, -240, -120);

    }

}
void drawspaceshipp() {
    //HEAD
    glColor3ub(147, 136, 138);
    glBegin(GL_POLYGON);
    glVertex2f(rocket + 20, rockety + 20);
    glVertex2f(rocket + 20, rockety + 50);
    glVertex2f(rocket, rockety + 70);
    glVertex2f(rocket - 20, rockety + 50);
    glVertex2f(rocket - 20, rockety + 20);
    glEnd();
    glColor3f(0, 0, 0);
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    glVertex2f(rocket + 20, rockety + 20);
    glVertex2f(rocket + 20, rockety + 50);
    glVertex2f(rocket, rockety + 70);
    glVertex2f(rocket - 20, rockety + 50);
    glVertex2f(rocket - 20, rockety + 20);
    glEnd();
    glColor3ub(99, 150, 218);
    glBegin(GL_POLYGON);
    glVertex2f(rocket + 8, rockety + 50);
    glVertex2f(rocket + 4, rockety + 53);
    glVertex2f(rocket + 0, rockety + 56);
    glVertex2f(rocket - 4, rockety + 53);
    glVertex2f(rocket -8, rockety + 50);
    glVertex2f(rocket -8, rockety + 30);
    glVertex2f(rocket + -4, rockety + 27);
    glVertex2f(rocket , rockety + 24);
    glVertex2f(rocket + 4, rockety + 27);
    glVertex2f(rocket + 8, rockety + 30);
    glEnd();
    glColor3ub(0, 0, 0);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex2f(rocket + 8, rockety + 50);
    glVertex2f(rocket + 4, rockety + 53);
    glVertex2f(rocket + 0, rockety + 56);
    glVertex2f(rocket - 4, rockety + 53);
    glVertex2f(rocket - 8, rockety + 50);
    glVertex2f(rocket - 8, rockety + 30);
    glVertex2f(rocket + -4, rockety + 27);
    glVertex2f(rocket, rockety + 24);
    glVertex2f(rocket + 4, rockety + 27);
    glVertex2f(rocket + 8, rockety + 30);
    glEnd();
    glColor3f(1, 1, 1);
    glRectf(rocket - 7, rockety + 40, rocket + 7, rockety + 45);
    //
    glColor3ub(147, 136, 138);
    glBegin(GL_POLYGON);
    glVertex2f(rocket - 20, rockety + 20);
    glVertex2f(rocket - 25, rockety + 20);
    glVertex2f(rocket - 45, rockety - 32);
    glVertex2f(rocket - 45, rockety - 62);
    glVertex2f(rocket - 40, rockety - 62);
    glVertex2f(rocket - 25, rockety - 32);
    glVertex2f(rocket + 25, rockety - 32);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(rocket + 25, rockety - 32);
    glVertex2f(rocket + 40, rockety - 62);
    glVertex2f(rocket + 45, rockety - 62);
    glVertex2f(rocket + 45, rockety - 32);
    glVertex2f(rocket + 25, rockety + 20);
    glVertex2f(rocket + 20, rockety + 20);
    glVertex2f(rocket - 20, rockety + 20);
    glEnd();
    glColor3f(0, 0, 0);
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    glVertex2f(rocket - 20, rockety + 20);
    glVertex2f(rocket - 25, rockety + 20);
    glVertex2f(rocket - 45, rockety - 32);
    glVertex2f(rocket - 45, rockety - 62);
    glVertex2f(rocket - 40, rockety - 62);
    glVertex2f(rocket - 25, rockety - 32);
    glVertex2f(rocket + 25, rockety - 32);
    glVertex2f(rocket + 40, rockety - 62);
    glVertex2f(rocket + 45, rockety - 62);
    glVertex2f(rocket + 45, rockety - 32);
    glVertex2f(rocket + 25, rockety + 20);
    glVertex2f(rocket + 20, rockety + 20);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2f(rocket - 45, rockety - 32);
        glVertex2f(rocket - 45, rockety - 64);
        glVertex2f(rocket - 55, rockety - 70);
        glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2f(rocket + 45, rockety - 32);
        glVertex2f(rocket + 45, rockety - 64);
        glVertex2f(rocket + 55, rockety - 70);
        glEnd();
        glColor3ub(233, 91, 19);
    glBegin(GL_POLYGON);
        glVertex2f(rocket-12 , rockety - 32);
        glVertex2f(rocket -12, rockety - 36);
        glVertex2f(rocket -8 , rockety - 36);
        glVertex2f(rocket - 8, rockety - 40);
        glVertex2f(rocket - 4, rockety - 40);
        glVertex2f(rocket - 4, rockety - 44);
        glVertex2f(rocket , rockety - 44);
        glVertex2f(rocket +4, rockety - 44);
        glVertex2f(rocket + 4, rockety - 40);
        glVertex2f(rocket + 8, rockety - 40);
        glVertex2f(rocket + 8, rockety - 36);
        glVertex2f(rocket + 12, rockety - 36);
        glVertex2f(rocket + 12, rockety - 32);
        glEnd();
        glColor3ub(255, 151, 0);
        glBegin(GL_POLYGON);
        glVertex2f(rocket - 9, rockety - 32);
        glVertex2f(rocket - 9, rockety - 35);
        glVertex2f(rocket - 6, rockety - 35);
        glVertex2f(rocket - 6, rockety - 38);
        glVertex2f(rocket - 3, rockety - 38);
        glVertex2f(rocket - 3, rockety - 41);
        glVertex2f(rocket, rockety - 41);
        glVertex2f(rocket + 3, rockety - 41);
        glVertex2f(rocket + 3, rockety - 38);
        glVertex2f(rocket + 6, rockety - 38);
        glVertex2f(rocket + 6, rockety - 35);
        glVertex2f(rocket + 9, rockety - 35);
        glVertex2f(rocket +9, rockety - 32);
        glEnd();
        glColor3ub(255, 246, 0);
        glBegin(GL_POLYGON);
        glVertex2f(rocket - 6, rockety - 32);
        glVertex2f(rocket - 6, rockety - 34);
        glVertex2f(rocket - 4, rockety - 34);
        glVertex2f(rocket - 4, rockety - 36);
        glVertex2f(rocket - 2, rockety - 36);
        glVertex2f(rocket - 2, rockety - 38);
        glVertex2f(rocket, rockety - 38);
        glVertex2f(rocket + 2, rockety - 38);
        glVertex2f(rocket + 2, rockety - 36);
        glVertex2f(rocket + 4, rockety - 36);
        glVertex2f(rocket + 4, rockety - 34);
        glVertex2f(rocket + 6, rockety - 34);
        glVertex2f(rocket + 6, rockety - 32);
        glEnd();
        glColor3ub(99, 150, 218);
        glRectf(rocket +4, rockety+13,rocket-4,rockety-20);
        glRectf(rocket + 2, rockety + 15, rocket - 2, rockety +10);
        glRectf(rocket +8, rockety+5, rocket - 8, rockety -10); 
        glRectf(rocket + 2, rockety - 22, rocket - 2, rockety - 20);
        glColor3f(1, 1, 1);
        glRectf(rocket + 8, rockety + 2, rocket - 8, rockety - 1);
        glRectf(rocket + 4, rockety + 8, rocket - 4, rockety + 10);
        glColor3f(0, 0, 0);
        glLineWidth(2);
        glBegin(GL_LINE_LOOP);
        glVertex2f(rocket + 4, rockety + 13);
        glVertex2f(rocket - 4, rockety + 13);
        glVertex2f(rocket - 4, rockety + 5);
        glVertex2f(rocket - 8, rockety + 5);
        glVertex2f(rocket -8, rockety -10);
        glVertex2f(rocket - 4, rockety - 10);
        glVertex2f(rocket - 4, rockety - 20);
        glVertex2f(rocket +4, rockety - 20);
        glVertex2f(rocket + 4, rockety - 10);
        glVertex2f(rocket + 8, rockety - 10);
        glVertex2f(rocket + 8, rockety + 5);
        glVertex2f(rocket + 4, rockety + 5);
        glEnd();
        





}
void display() {
    //
    // clear window to black
    //
    glClearColor(72.0/255.0, 0.0/255.0, 130.0/255.0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    drawBackground();
    // TIMER 
    glColor3f(1, 1, 1);
    vprint2(385, 300, .1, "Remaining Time");
    if (sec == 99 && min == 19) {
        glColor3f(1, 0, 1);
        vprint2(400, 320, 0.20, "%02d:%02d", 0, 0);
        glColor3f(1, 1, 1);
        vprint(-80, -340, GLUT_BITMAP_HELVETICA_12, "Press <F1> to start a new game.");
    }
    else {
        glColor3f(1, 0, 1);
        vprint2(400, 320, 0.20, "%02d:%02d", min, sec);
        if ((min == 0 && sec == 0) != 1) {
            glColor3f(1, 1, 1);
            vprint(-140, -340, GLUT_BITMAP_HELVETICA_12, "<SPACEBAR> to Fire, <F1> to resume or pause.");
        }
    }
    createBullet();
    drawspaceshipp();
    drawTarget(target);
    
    glutSwapBuffers();
    
}

int findAvailableFire() {
    for (int i = 0; i < MAX_FIRE; i++) {
        if (bullet[i].create == false) 
            return i;
    }
    return -1;
}
bool testCollision(bullet_t bullet, target_t t) {
    float dx = t.x - bullet.x;
    float dy = t.y - bullet.y;
    float d = sqrt(dx * dx + dy * dy);
    return d <= t.radius;
}
void resetTarget(target_t target[], int i) {
    float yPos = (rand() % 515) -170 ;
    float xPos = rand() % 2 ? 600 : -600;
    target[i].x = xPos;
    target[i].y = yPos;
    target[i].r = rand() % 256;
    target[i].g = rand() % 256;
    target[i].b = rand() % 256;
    target[i].radius = TARGET_RADIUS;
    if (xPos < -500)
        target[i].speed = 3.0 * (rand() % 100) / 100.0 + 0.5;
    else if (xPos > 500 )
        target[i].speed = 3.0 * ((rand() % 100) - 100) / 100.0 + 0.5;
}



void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);
    if (key == ' ') {
        spacebar= 1;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);
    if (key == ' ')
        spacebar = 0;


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
    if (key == GLUT_KEY_F1)
    {
        active = !active;
    }
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

#if TIMER_ON == 1
void onTimer(int v) {

    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    // Write your codes here.
    if (active)
    {
        sec--;
        if (sec == 0 && min != 0)
        {
            min--;
            sec = 99;
        }
        if (min == 0 && sec == 0) {
        min = 19;
        sec = 99;

        active = !active;
        }
        if (right) {
            rocket += 5;
            if (rocket == 500 && right)
                rocket = -500;
        }

        if (left) {
            rocket -= 5;
            if (rocket == -500 && left)
                rocket = 500;
        }
        if (spacebar && fire_rate == 0) {
            int availFire = findAvailableFire();
            if (availFire != -1) {
                bullet[availFire].x = rocket;
                bullet[availFire].y = rockety+20;
                bullet[availFire].create = true;
                fire_rate = FIRE_RATE;
            }
        }
        if (fire_rate > 0) fire_rate--;

        for (int i = 0; i < MAX_FIRE; i++) {
            if (bullet[i].create) {
                bullet[i].y += 10;

                if (bullet[i].y > 350) {
                    bullet[i].create = false;
                }
                
            }
            for (int j = 0; j < 5; j++) {
                if (testCollision(bullet[i], target[j])) {
                    if (bullet[i].create) {
                        resetTarget(target, j);
                        bullet[i].create = false;
                    }
                }
            }
        }

        for(int i=0;i<5;i++){
            target[i].x += target[i].speed;
            if (target[i].x > 600 || target[i].x < -600)
                resetTarget(target,i);
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
    for(int i=0;i<5;i++)
        resetTarget(target, i);
    for (int i = 0; i < STRCTR; i++) {
        x[i] = rand() % 1000 - 500;
        y[i] = rand() % 600 - 300;
        r[i] = rand() % 355 -150;
        g[i] = rand() % 355 -150;
        b[i] = rand() % 355 -150;
    }
    //for (int i = 0; i < MAX_FIRE; i++) {
    //    bullet[i].x = rocket;
    //    bullet[i].y = rockety + 20;
    //}
}

void main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("EmirTunaBeþli - Shooting Airplanes");

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