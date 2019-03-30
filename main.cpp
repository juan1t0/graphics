#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>
using namespace std;
#define KEY_A 97
#define KEY_Q 113
#define KEY_S 115
#define KEY_W 119
#define KEY_D 100
#define KEY_E 101

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


	glutInitWindowSize(600, 600);
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

void parte(float ancho, float largo, float a, float b, float c){
    glColor3b(a,b,c);
    glBegin(GL_QUADS);
        glVertex2f(0,-largo/2.0f);
        glVertex2f(ancho,-largo/2.0f);
        glVertex2f(ancho,largo/2.0f);
        glVertex2f(0,largo/2.0f);
    glEnd();
}
void cuerda( float largo, float r, float g, float b){
    glLineWidth(2.0);
    glColor3f(r,g,b);
    glBegin(GL_LINES);
        glVertex2d(0,0);
        glVertex2d(0,-largo);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(-2.5f,-largo-5.0);
        glVertex2f(-2.5f,-largo);
        glVertex2f(2.5f,-largo);
        glVertex2f(2.5f,-largo-5.0);
    glEnd();
}

float x1=0.0,x2=0.0,x3=0.0,c1=0.0;
float variant=0.03;

int time=0;
int timebase=0;
int lar=50;
GLvoid window_display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -2.0f, 2.0f);
    glBegin(GL_QUADS);
        glColor3f(255.0f,255.0f,255.0f);
        glVertex2f(-20/2.0f,-12/2.0f);
        glVertex2f(20/2.0f,-12/2.0f);
        glVertex2f(20/2.0f,12/2.0f);
        glVertex2f(-20/2.0f,12/2.0f);
    glEnd();
    glPushMatrix();
        glRotated(x1,0.0,0.0,1.0);
        parte(30,10,200.0f,100.0f,150.0f);
        glPushMatrix();
            glTranslated(30.0,0.0,0.0);
            glRotated(x2,0.0,0.0,1.0);
            parte(25,7,100.0f,200.0f,255.0f);
            glPushMatrix();
                glTranslated(25.0,0.0,0.0);
                glRotated(x3,0.0,0.0,1.0);
                cuerda(lar,255.0f,255.0f,0.0f);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
/*
    time = glutGet(GLUT_ELAPSED_TIME); /// recupera el tiempo ,que paso desde el incio de programa
    float dt = float(time -timebase)/1000.0;// delta time
    timebase = time;
*/
	glutSwapBuffers();
	glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -2.0f, 2.0f);

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
    case KEY_A:{
        x1-=0.8;
        x3+=0.8;
        cout<<"a"<<endl;
        break;
    }
    case KEY_Q:{
        x1+=0.8;
        x3-=0.8;
        cout<<"q"<<endl;
        break;
    }
    case KEY_W:{
        cout<<"w"<<endl;
        x2+=0.8;
        x3-=0.8;
        break;
    }
    case KEY_S:{
        x2-=0.8;
        x3+=0.8;
        cout<<"s"<<endl;
        break;
    }
    case KEY_D:{
        lar+=1;
        cout<<"d"<<endl;
        break;
        }
    case KEY_E:{
        lar-=0.5;
        cout<<"e"<<endl;
        break;
        }
	default:
		break;
	}
}


//function called on each frame
GLvoid window_idle()
{
	glutPostRedisplay();
}
