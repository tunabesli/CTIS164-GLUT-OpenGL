/*********
   CTIS164 - Template Source Program
----------
STUDENT :EMÝR TUNA BEÞLÝ    
SECTION :002
HOMEWORK:
----------
PROBLEMS: THERE IS A DELAY AFTER LAST OBJECT LEAVES THE AREA AND ONCLICK FUNCTION WORKS AGAIN. 
          DISPLAY AND ONTIME ARE NOT WORKING SIMULTANEOUS.
----------
ADDITIONAL FEATURES:STARS ARE CHANGING COLORS.
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
#define WINDOW_HEIGHT 600

#define TIMER_PERIOD  5// Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer
#define STRCTR 100

#define D2R 0.0174532

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height
int x[STRCTR], y[STRCTR], r[STRCTR], g[STRCTR], b[STRCTR];
int click = 0, index=0;
int j = 0;
bool activetimer = 0;
int arrx[10], arry[10], last=0;
int inside[10] ={ 1,1,1,1,1,1,1,1,1,1};//TO ELIMINATE OBJECTS ONE BY ONE IF THEY LEAVE THE SCREEN.

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
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
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

//
// To display onto window using OpenGL commands
//
void drawufo(int x, int y)
{
    //FIRE
    glBegin(GL_POLYGON);
    glColor3ub(255, 100, 0);
    glVertex2f(x - 20, y - 16);
    glVertex2f(x + 20, y - 16);
    glColor3ub(255, 0, 0);
    glVertex2f(x + 10, y - 40);
    glColor3ub(255, 50, 0);
    glVertex2f(x + 5, y - 35);
    glColor3ub(99, 0, 148);
    glVertex2f(x + 2, y - 45);
    glColor3ub(255, 50, 0);
    glVertex2f(x - 5, y - 35);
    glColor3ub(255, 0, 0);
    glVertex2f(x - 10, y - 40);
    glEnd();
    //DOTS ON THE UFO AND CIRCLES
    float angle;
    glColor3f(0.7, 0.7, 0.7);
    circle(x, y, 30);
    glColor3f(0.5, 0.5, 0.5);
    circle(x, y, 12);
    glColor3f(1, 0, 0);
    glPointSize(2);
    glBegin(GL_POINTS);
    for (int i = 0; i < 100; i += 10)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + 20 * cos(angle), y + 20 * sin(angle));
    }
    glEnd();
    //
    //FLAG
    glBegin(GL_LINE_STRIP);
    glColor3ub(171, 0, 255);
    glVertex2f(x-25, y);
    glVertex2f(x - 25, y + 25);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 255, 247);
    glVertex2f(x-25, y+25);
    glColor3ub(94, 255, 0);
    glVertex2f(x-25, y+10);
    glColor3ub(255, 94, 0);
    glVertex2f(x-40, y+20);
    glEnd();
    //
    

   
   /* glEnd();*/
}
void Sun() {
#define PI 3.1415
    glLineWidth(2);
    float angle;
    glColor3f(1, 1, 0);
    circle(300, 150, 100);
    glBegin(GL_LINES);
    for (int i = 0; i < 100; i += 5)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(300 + 100 * cos(angle), 150 + 100 * sin(angle));
        glVertex2f(300+ 150 * cos(angle), 150 + 150 * sin(angle));
    }
    glEnd();
}
void Myname()
{
    glColor3ub(0, 158, 116);
    glRectf(-80, 220, 80, 290);
    glColor3ub(0, 255, 188);
    glRectf(-70,230 , 70, 280);
    glColor3ub(0, 0, 255);
    vprint(-60, 260, GLUT_BITMAP_8_BY_13, "EMIR TUNA BESLI");
    vprint(-30, 240, GLUT_BITMAP_8_BY_13, "22102039");
}
void display() {
    glClearColor(0.1, 0, 0.1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < STRCTR; i++) {
        r[i] = rand() % 255;
        g[i] = rand() % 255;
        b[i] = rand() % 255;
    }

    //PLANETS
    //EARTH
    glColor3ub(41, 90, 223);
    circle(-300, 100, 60);
    //
    //MARS
    glColor3ub(193,68,14);
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
    Sun();

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
        glColor3ub(r[i], g[i], b[i]);
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

    //
    //COMPLEX OBJECT
    //
    int i, count = 0;
    for (i = 0; i < click; i++)
    {
        if (inside[i])
            drawufo(arrx[i], arry[i]);
        if (arry[i] == 300)//IF OBJECT LEAVES THE ARE IT DISSAPPEARS.
            inside[i] = 0;
        if (arry[i] < arry[last])//LAST OBJECT THAT LEAVES.
            last = i;
    }
    if (arry[last] > 290)//RESTART THE PROGRAM.
    {
        activetimer = !activetimer;
        click = 0;
        for (i = 0; i < 10; i++)
            inside[i] = 1;
    }
    Myname();

    
    
    glColor3f(1, 1, 1); // white
    if (click != 10)
        vprint(-(winWidth / 2) + 20, -(winHeight / 2) + 20, GLUT_BITMAP_8_BY_13, "Click on the screen to create an object. (Maxium 10 objects.)");
    if(click>=1)
        vprint(+(winWidth / 2) - 250, -(winHeight / 2) + 20, GLUT_BITMAP_8_BY_13, "Press F1 to fly all UFO's.");
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
    if (key == GLUT_KEY_F1)
    {
        activetimer = !activetimer;
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
    if (!activetimer)
    {
        if (click < 10)
            if (button == 0 && stat == GLUT_DOWN)
            {
                arrx[click] = x - winWidth / 2;
                arry[click] = winHeight / 2 - y;
                click++;
            }
    }
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
void onTimer(int v)
{

    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    if (activetimer)

        for (int i = 0; i < click; i++)
            arry[i] += 1;

    // to refresh the window it calls display() function
    glutPostRedisplay(); // display()

}
#endif

void Init() {

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {
    for (int i = 0; i < STRCTR; i++) {
        x[i] = rand() % 1000 - 500;
        y[i] = rand() % 600 - 300;
        r[i] = rand() % 255;
        g[i] = rand() % 255;
        b[i] = rand() % 255;
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("SPACE");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);

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