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


float a= 0.0f,a2 = 0.0f,a3=0.0f;
float x= 0.0f;
float variant=0.03;

int time=0;
int timebase=0;
GLvoid window_display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_COLOR_MATERIAL_FACE);
   // glDisable(GL_DITHER);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);
    glTranslatef(x,0.0,0.0);
    //glColor3f(0.0f,0.0f,20.0f);
    glutSolidSphere(1.5d,100,100);
   // glColor3f(200.0f,20.0f,20.0f);
    glPushMatrix();
        glRotatef(a3,1.0,0.0,0.0);
        glTranslatef(0.0,7.0,0.0);
        glutSolidCube(2.0f);
    glPopMatrix();

    //glRotatef(a,0.0,0.0,1.0);
    glTranslatef(13.0*cos(a),13.0*sin(a),0.0);
    //glTranslatef(13.0,0.0,0.0);
	/*dibujar aqui*/
    glutSolidTeapot(4.0);
    glPushMatrix();
        glRotatef(a2,0.0,1.0,0.0);
        glTranslatef(5.0,5.0,0.0);

        glutSolidTorus(0.5f,0.8f,100,100);
    glPopMatrix();
    //a+=0.5;
    time = glutGet(GLUT_ELAPSED_TIME); /// recupera el tiempo ,que paso desde el incio de programa
    float dt = float(time -timebase)/1000.0;// delta time
    timebase = time;
    a+= (2) * dt;
    a2=a*30;
    a3+=0.25;
    if(x<-8.0 || x>8.0)
        variant*=-1;
    x+=variant;
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
