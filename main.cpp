//
//  main.cpp
//  MP1DanceI
//
//  Created by Jiexin Lyu on 1/31/15.
//  Copyright (c) 2015 Jiexin Lyu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <ctime>
#include <math.h>
#include <string.h>

int nFPS = 30;
float fRotateAngle = 0.f;
clock_t startClock=0,curClock;
long long int prevF=0,curF=0;
int dipMode=1;
static double xoffset1, xoffset2, xoffset3;
static double yoffset1, yoffset2, yoffset3;


void init(void)
{
    glClearColor(0.9,0.9,0.9,1.0); // clear color is gray
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // uncomment this function if you only want to draw wireframe model
    // GL_POINT / GL_LINE / GL_FILL (default)
    glPointSize(4.0);
}



void printStr(int x, int y, char *string)
{
    glColor3f(0,0,0);
    glRasterPos2f(x, y);
    int len, i;
    len = (int)strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}



void display(void)
{
    if(dipMode==1)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }else{
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    
    
    curF++;
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(0.8,0.8,0.8,1.0); // clear color is gray
    
   
    // reset OpenGL transformation matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // reset transformation matrix to identity
    
    // setup look at transformation so that
    // eye is at : (0,0,3)
    // look at center is at : (0,0,0)
    // up direction is +y axis
    gluLookAt(0.f,0.f,3.f,0.f,0.f,0.f,0.f,1.f,0.f);
    printStr(-2.0, 1.9, "nFPS=30");
    glRotatef(fRotateAngle,0.f,1.f,0.f);
    
    glColor3f(1.0,0.5,0.0);
    
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0,0.5,0.0); // Red
    glVertex2f(0.6+xoffset1, 1+yoffset1);
    glVertex2f(-0.6+xoffset2, 1+yoffset2);
    glVertex2f(-0.6+xoffset3, 0.6+yoffset3);
    glVertex2f(-0.2+xoffset1, 0.6+yoffset1);
    glColor3f(1.0,0.5,0.0);
    glVertex2f(0.2+xoffset2, 0.6+yoffset2);
    glVertex2f(0.6+xoffset3, 0.6+yoffset3);
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0+xoffset1, -1+yoffset1);
    glVertex2f(-0.6+xoffset2, -1+yoffset2);
    glColor3f(0.2, 0.3, 0.8);
    glVertex2f(-0.6+xoffset3, -0.6+yoffset3);
    glColor3f(0.3, 0.5, 0.6);
    glVertex2f(-0.2+xoffset1, -0.6+yoffset1);
    glColor3f(1.0, 0.5, 0.0);
    glVertex2f(-0.2+xoffset1, 0.6+yoffset1);
    glColor3f(1.0, 0.5, 0.0);
    glVertex2f(0.2+xoffset2, 0.6+yoffset2);
    glColor3f(0.3, 0.5, 0.6);
    glVertex2f(0.2+xoffset3, -0.6+yoffset3);
    glColor3f(0.2, 0.3, 0.8);
    glVertex2f(0.6+xoffset2, -0.6+yoffset2);
    glColor3f(0.0,0.0,1.0);
    glVertex2f(0.6+xoffset3, -1+yoffset3);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-0.6+xoffset2, 1+yoffset2);
    glVertex2f(-0.6+xoffset3, 0.6+yoffset3);
    glVertex2f(-0.2+xoffset1, 0.6+yoffset1);
    glVertex2f(-0.2+xoffset1, -0.6+yoffset1);
    glVertex2f(-0.6+xoffset3, -0.6+yoffset3);
    glVertex2f(-0.6+xoffset2, -1+yoffset2);
    glVertex2f(0+xoffset1, -1+yoffset1);
    glVertex2f(0.6+xoffset3, -1+yoffset3);
    glVertex2f(0.6+xoffset2, -0.6+yoffset2);
    glVertex2f(0.2+xoffset3, -0.6+yoffset3);
    glVertex2f(0.2+xoffset2, 0.6+yoffset2);
    glVertex2f(0.6+xoffset3, 0.6+yoffset3);
    glVertex2f(0.6+xoffset1, 1+yoffset1);
    glEnd();
    
    glutSwapBuffers();	// swap front/back framebuffer to avoid flickering
    
    curClock=clock();
    float elapsed=(curClock-startClock)/(float)CLOCKS_PER_SEC;
    if(elapsed>1.0f){
        float fps=(float)(curF-prevF)/elapsed;
        printf("fps:%f\n",fps);
        prevF=curF;
        startClock=curClock;
    }
}

void reshape (int w, int h)
{
    // reset viewport ( drawing screen ) size
    glViewport(0, 0, w, h);
    float fAspect = ((float)w)/h;
    // reset OpenGL projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.f,fAspect,0.001f,30.f);
}


void keyboard(unsigned char key, int x, int y)
{
    if (key == 27)
    {
        // ESC hit, so quit
        printf("demonstration finished.\n");
        exit(0);
    }
    if( key == 'h'){
        printf("press 'h'.\n");
    }
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        dipMode = 1-dipMode;
}


void timer(int v)
{
    fRotateAngle += 1.f; // change rotation angles

    xoffset1 = (rand()%10-5)*0.02;
    yoffset1 = (rand()%10-5)*0.02;
    xoffset2 = (rand()%10-5)*0.02;
    yoffset2 = (rand()%10-5)*0.02;
    xoffset3 = (rand()%10-5)*0.02;
    yoffset3 = (rand()%10-5)*0.02;
    glutPostRedisplay(); // trigger display function by sending redraw into message queue
    glutTimerFunc(1000/nFPS,timer,v); // restart timer again
}

int main(int argc, char* argv[])
{
    glutInit(&argc, (char**)argv);
    // set up for double-buffering & RGB color buffer & depth test
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ((const char*)"MP1DanceI");
    glEnable(GL_DEPTH_TEST);
    
    init(); // setting up user data & OpenGL environment
    
    // set up the call-back functions
    glutDisplayFunc(display);  // called when drawing
    glutReshapeFunc(reshape);  // called when change window size
    glutKeyboardFunc(keyboard); // called when received keyboard interaction
    glutMouseFunc(mouse);	    // called when received mouse interaction
    glutTimerFunc(100,timer,nFPS); // a periodic timer. Usually used for updating animation
    
    startClock=clock();
    
    glutMainLoop(); // start the main message-callback loop
    
    return 0;
}
