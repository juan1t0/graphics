#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>
using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);

//function called on each frame
GLvoid window_idle();

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TP 2 : Transformaciones");


	initGL();
	init_scene();

	glutDisplayFunc(&window_display);

	glutReshapeFunc(&window_reshape);

	glutKeyboardFunc(&window_key);

	//function called on each frame
	glutIdleFunc(&window_idle);

	glutMainLoop();

	return 1;
}



GLvoid initGL()
{
	GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };

	//enable light : try without it
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	//light 0 "on": try without it
	glEnable(GL_LIGHT0);

	//shading model : try GL_FLAT
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);

	//enable material : try without it
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(RED, GREEN, BLUE, ALPHA);
}


float a= 0.0f,a2 = 0.0f;
float b= 0.0f,b2 = 0.0f,b3 = 0.0f;
float x= 0.0f;
float variant=0.03;

int time=0;
int timebase=0;
float tx=0.0,ty=0.0,tz=0.0;
GLvoid window_display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);
    gluPerspective(45.0,1.0,1.0,100.0);
    gluLookAt(0.0f,0.0f,30,
              15.0f,0.0f,0.0f,
              0.0,1.0,0.0);
//    glTranslatef(0.0,0.0,-30.0);
    glPushMatrix();
        glColor3f(1.0f,1.0f,0.0f);
        glRotated(b,0.0,1.0,0.0);
        glutSolidSphere(8.0d,10,10);
    glPopMatrix();
    glPushMatrix();
        glRotatef(a,0.0,1.0,0.0);
        glTranslatef(15.0,0.0,0.0);
        glRotated(b2,0.0,1.0,1.0);
        glColor3f(0.0f,0.0f,1.0f);
        glutSolidSphere(2.0f,10,10);
        glPushMatrix();
            glRotated(a2,0.0,1.0,0.0);
            glTranslated(2.5,2.5,0.0);
            glRotated(b3,0.0,1.0,0.0);
            glColor3f(1.0f,1.0f,1.0f);
            glutSolidSphere(0.75f,8,8);
        glPopMatrix();
    glPopMatrix();
        glPushMatrix();
        glRotatef(a+0.01,0.0,1.0,0.0);
        glTranslatef(25.0,0.0,0.0);
        glRotated(b2,0.0,1.0,0.0);
        glColor3f(1.0f,0.0f,0.0f);
        glutSolidSphere(2.25f,10,10);
    glPopMatrix();
/*    glPushMatrix();
        glRotatef(a3,1.0,0.0,0.0);
        glTranslatef(0.0,7.0,0.0);
        glutSolidCube(2.0f);
    glPopMatrix();
    glRotatef(a,0.0,0.0,1.0);
    glTranslatef(13.0,0.0,0.0);
    glutSolidTeapot(4.0);
    glPushMatrix();
        glRotatef(a,0.0,1.0,0.0);
        glTranslatef(5.0,5.0,0.0);
        glutSolidTorus(0.5f,0.8f,100,100);
    glPopMatrix();*/
    //a+=0.5;
    time = glutGet(GLUT_ELAPSED_TIME); /// recupera el tiempo ,que paso desde el incio de programa
    float dt = float(time -timebase)/1000.0;// delta time
    timebase = time;
    a+= (18) * dt;
    a2=a*2;
/*    if(x<-8.0 || x>8.0)
        variant*=-1;
    x+=variant;*/
    b+= (10) * dt;
    b2=3*b;
    b3=1.5*b2;
	glutSwapBuffers();
	glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);

	glMatrixMode(GL_MODELVIEW);
}



void init_scene()
{

}

GLvoid window_key(unsigned char key, int x, int y)
{
	switch (key) {
	case ECHAP:
		exit(1);
		break;

	default:
		printf("La touche %d non active.\n", key);
		break;
	}
}


//function called on each frame
GLvoid window_idle()
{
	glutPostRedisplay();
}

