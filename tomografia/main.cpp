#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include "OcTree.h"
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <fstream>
#define KEY_ESC 27

using namespace std;
using namespace std::chrono;

int mx = 0;
int my = 0;

float ax=0.0;
float ay=0.0;
float var_z = -100.0;
float speed = 0.1;

float sphereX=0.0,sphereY=0.0,sphereZ=0.0,sphereRadius=15.0;
float moveX,moveY,moveZ;
GLfloat lightPos[4] = { -20.0,-6.0,1.0,1.0 };

vector<Line> lines;
vector<Line> lines2;
vector<Quad> quadss;
vector<Voxel> vox;
vector<Point> points;
vector<Point> points2;
short limitX = -25;
short LimitX = 25;
short limitY = -25;
short LimitY = 25;
short limitZ = -60;
short LimitZ = 60;
OcTree* ot;

void displayGizmo()
{
	glBegin(GL_LINES);
        glColor3d(255,0,0);
        glVertex3d(-30, 0,0);
        glVertex3d(30, 0,0);
        glColor3d(0, 255, 0);
        glVertex3d(0, -30,0);
        glVertex3d(0, 30,0);
        glColor3d(255, 0, 255);
        glVertex3d(0, 0,-30);
        glVertex3d(0, 0,30);
	glEnd();
}

void pintar_lineas(){
    glLineWidth(2.0f);
    glColor3d(0.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
	for(unsigned int i=0;i<lines.size();++i){
        if(i%3==0)
            glColor3d(255, 0, 0);
        if(i%3==1)
            glColor3d(0, 255, 0);
        if(i%3==2)
            glColor3d(0, 0, 255);
        glVertex3d(lines[i].u.x, lines[i].u.y, lines[i].u.z);
        glVertex3d(lines[i].v.x, lines[i].v.y, lines[i].v.z);
	}
	glEnd();
}

void pintar_lineas2(){
    glLineWidth(2.0f);
    glBegin(GL_LINES);
/*    float r = (float)(rand()%256)/256.0;
    float g = (float)(rand()%256)/256.0;
    float b = (float)(rand()%256)/256.0;
	glColor3f(r,g,b);*/
	glColor3f(1.0f,1.0f,1.0f);
	for(unsigned int i=0;i<lines2.size();i+=4){
        glVertex3d(lines2[i].u.x, lines2[i].u.y, lines2[i].u.z);
        glVertex3d(lines2[i].v.x, lines2[i].v.y, lines2[i].v.z);
        glVertex3d(lines2[i+1].u.x, lines2[i+1].u.y, lines2[i+1].u.z);
        glVertex3d(lines2[i+1].v.x, lines2[i+1].v.y, lines2[i+1].v.z);
        glVertex3d(lines2[i+2].u.x, lines2[i+2].u.y, lines2[i+2].u.z);
        glVertex3d(lines2[i+2].v.x, lines2[i+2].v.y, lines2[i+2].v.z);
        glVertex3d(lines2[i+3].u.x, lines2[i+3].u.y, lines2[i+3].u.z);
        glVertex3d(lines2[i+3].v.x, lines2[i+3].v.y, lines2[i+4].v.z);
	}
	glEnd();
}
void pintar_Quads(){
    glLineWidth(2.0f);
    glBegin(GL_QUADS);
/*    float r = (float)(rand()%256)/256.0;
    float g = (float)(rand()%256)/256.0;
    float b = (float)(rand()%256)/256.0;
	glColor3f(r,g,b);*/
	glColor3f(1.0f,1.0f,1.0f);
	for(unsigned int i=0;i<quadss.size();++i){
        glNormal3f(quadss[i].Nx,quadss[i].Ny,quadss[i].Nz);

        glVertex3f(quadss[i].uno.x,quadss[i].uno.y,quadss[i].uno.z);
        glVertex3f(quadss[i].cua.x,quadss[i].cua.y,quadss[i].cua.z);
        glVertex3f(quadss[i].tre.x,quadss[i].tre.y,quadss[i].tre.z);
        glVertex3f(quadss[i].dos.x,quadss[i].dos.y,quadss[i].dos.z);

	}
	glEnd();
}
void pintar_Voxels(){
//    glLineWidth(2.0f);
    glBegin(GL_QUADS);
/*    float r = (float)(rand()%256)/256.0;
    float g = (float)(rand()%256)/256.0;
    float b = (float)(rand()%256)/256.0;
	glColor3f(r,g,b);*/
	glColor3f(1.0f,1.0f,1.0f);
	for(unsigned int i=0;i<vox.size();++i){
        Quad aux = vox[i].abajo;
        glNormal3f(aux.Nx,aux.Ny,aux.Nz);
        glVertex3f(aux.uno.x,aux.uno.y,aux.uno.z);
        glVertex3f(aux.cua.x,aux.cua.y,aux.cua.z);
        glVertex3f(aux.tre.x,aux.tre.y,aux.tre.z);
        glVertex3f(aux.dos.x,aux.dos.y,aux.dos.z);
        aux = vox[i].arriba;
        glNormal3f(aux.Nx,aux.Ny,aux.Nz);
        glVertex3f(aux.uno.x,aux.uno.y,aux.uno.z);
        glVertex3f(aux.cua.x,aux.cua.y,aux.cua.z);
        glVertex3f(aux.tre.x,aux.tre.y,aux.tre.z);
        glVertex3f(aux.dos.x,aux.dos.y,aux.dos.z);
        aux = vox[i].atraz;
        glNormal3f(aux.Nx,aux.Ny,aux.Nz);
        glVertex3f(aux.uno.x,aux.uno.y,aux.uno.z);
        glVertex3f(aux.cua.x,aux.cua.y,aux.cua.z);
        glVertex3f(aux.tre.x,aux.tre.y,aux.tre.z);
        glVertex3f(aux.dos.x,aux.dos.y,aux.dos.z);
        aux = vox[i].derecha;
        glNormal3f(aux.Nx,aux.Ny,aux.Nz);
        glVertex3f(aux.uno.x,aux.uno.y,aux.uno.z);
        glVertex3f(aux.cua.x,aux.cua.y,aux.cua.z);
        glVertex3f(aux.tre.x,aux.tre.y,aux.tre.z);
        glVertex3f(aux.dos.x,aux.dos.y,aux.dos.z);
        aux = vox[i].frente;
        glNormal3f(aux.Nx,aux.Ny,aux.Nz);
        glVertex3f(aux.uno.x,aux.uno.y,aux.uno.z);
        glVertex3f(aux.cua.x,aux.cua.y,aux.cua.z);
        glVertex3f(aux.tre.x,aux.tre.y,aux.tre.z);
        glVertex3f(aux.dos.x,aux.dos.y,aux.dos.z);
        aux = vox[i].izquierda;
        glNormal3f(aux.Nx,aux.Ny,aux.Nz);
        glVertex3f(aux.uno.x,aux.uno.y,aux.uno.z);
        glVertex3f(aux.cua.x,aux.cua.y,aux.cua.z);
        glVertex3f(aux.tre.x,aux.tre.y,aux.tre.z);
        glVertex3f(aux.dos.x,aux.dos.y,aux.dos.z);

	}
	glEnd();
}
void pintar_puntos(){
    glPointSize(5.0f);
    glBegin(GL_POINTS);
        glColor3d(1.0,1.0,1.0);
        for(unsigned int i=0;i<points.size();++i){
            glVertex3d(points[i].x, points[i].y, points[i].z);
        }
	glEnd();/**
	glColor3f(1.0,1.0,1.0);
	for(size_t i=0; i<points.size();++i){
        glPushMatrix();
            glTranslatef(points[i].x, points[i].y, points[i].z);
            glutSolidCube(0.5);
        glPopMatrix();
	}*/
}

bool r = false;

void OnMouseClick(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    mx=x;
    my=y;
  }else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
    r = true;
  }else if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
    r = false;
  }
}

void OnMouseMotion(int x, int y)
{
    int dx = mx-x;
    int dy = my-y;

    mx=x;
    my=y;

    ax += dx*speed;
    ay += dy*speed;
}
void idle(){ // AGREGAR ESTA FUNCION
	glutPostRedisplay();
}

//funcion llamada a cada imagen
void glPaint(void) {
//    glEnable(GL_COLOR_MATERIAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluPerspective(45.0,1.0,1.0,500.0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glTranslatef(0,0,var_z);
	glRotatef(ax,0,1,0);
	glRotatef(ay,1,0,0);
    //pintar_puntos();
	displayGizmo();

	pintar_lineas2();
//    pintar_Quads();
    pintar_Voxels();
    ///glTranslatef(0.0f,0.0f,var_z);
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glTranslatef(20,20,0);
	glutSwapBuffers();
}

void init_GL(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
  /*  glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
*/	glEnable(GL_DEPTH_TEST);
///	glEnable(GL_TEXTURE_2D);
//	glClearColor(RED, GREEN, BLUE, ALPHA);
	glShadeModel(GL_SMOOTH); // modelo de shading try GL_FLAT
///	glEnable(GL_CULL_FACE); //no trata las caras escondidas
	glDepthFunc(GL_LEQUAL); //Modo de funcionamiento del Z-Buffer
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Activa la corrección de perspectiv
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//	GLfloat lam

//	glClearColor(RED, GREEN, BLUE, ALPHA);
	GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat difusseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//	GLfloat lightPos[] = { 2.0, 6.0 ,3.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusseLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
//	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}
bool changed = false;
GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case 'e':
		lightPos[2] -= 15;
		break;
	case 'd':
		lightPos[2] += 15;
		break;
	case 'q':
		lightPos[0] -= 15;
		break;
	case 'a':
		lightPos[0] += 15;
		break;
	case 'w':
		lightPos[1] -= 15;
		break;
	case 's':
		lightPos[1] += 15;
		break;
    case 'u':
        if(limitX + 7 < LimitX){
            limitX += 7;
            changed = true;
        }
        break;
    case 'j':
        if(LimitX - 7 > limitX){
            LimitX += -7;
            changed = true;
        }
        break;
    case 'i':
        if(limitY + 7 < LimitY){
            limitY += 7;
            changed = true;
        }
        break;
    case 'k':
        if(LimitY - 7 > limitY){
            LimitY += -7;
            changed = true;
        }
        break;
    case 'o':
        if(limitZ + 7 < LimitZ){
            limitZ += 7;
            changed = true;
        }
        break;
    case 'l':
        if(LimitZ - 7 > limitZ){
            LimitZ += -7;
            changed = true;
        }
        break;
    case 'z':
        var_z+=10;
        break;
    case 'x':
        var_z+=-10;
        break;
    case 'r':
        limitX = -25;LimitX = 25;
        limitY = -25;LimitY = 25;
        limitZ = -60;LimitZ = 60;
        changed=true;
        break;
	default:
		break;
	}
	if(changed == true){
        cout<<limitX<<" "<<LimitX<<" "<<limitY<<" "<<LimitY<<" "<<limitZ<<" "<<LimitZ<<endl;
        vox = ot->getBoxs(limitX,LimitX,limitY,LimitY,limitZ,LimitZ);
        cout<<"hay "<<vox.size()<<" voxels"<<endl;
        changed = false;
    }
}
//
//el programa principal
//
int main(int argc, char** argv) {

	//Inicializacion de la GLUT
	srand(time(NULL));
	auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

	moveX=rand()/double(RAND_MAX)/1;
	moveY=rand()/double(RAND_MAX)/1;
	moveZ=rand()/double(RAND_MAX)/1;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("Tomografia"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);
	glutMouseFunc(&OnMouseClick);
	glutMotionFunc(&OnMouseMotion);
	glutIdleFunc(&idle);
    float x,y,z;
    int cont =0;
    ot=new OcTree(-25,25,-25,25,-60,60,16);
    ifstream file("D:\\tomo\\bin\\Debug\\LV_60_FEM_R.labelsTodo.txt");
//    ifstream file("D:\\tomo\\bin\\Debug\\LV_60_FEM_R.labelsProbe.txt");
    while(!file.eof()){
        file>>x>>y>>z;
            ot->insertPoint(Point(x*50-25,y*50-25,z*120-60),ot);
        cont++;
    }
    cout<<"entro: "<<cont<<endl;
    vox = ot->getBoxs(limitX,LimitX,limitY,LimitY,limitZ,LimitZ);
    cout<<"hay "<<vox.size()<<" voxels"<<endl;
//    lines2 = ot->getBorderLines();
  //  points = ot->getPoints();
 //   lines=ot->getLines();
//    quadss = ot->getQuads();
//    cout<<"hay "<<points.size()<<" puntos"<<endl;
	glutMainLoop();
	return 0;
}
