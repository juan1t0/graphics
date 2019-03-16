#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <GL/glut.h>

#define KEY_ESC 27

//dibuja un simple gizmo
void displayGizmo()
{
	glBegin(GL_LINES);
	glColor3d(255,0,0);
	glVertex2d(0, 0);
	glVertex2d(10, 0);
	glColor3d(0, 255, 0);
	glVertex2d(0, 0);
	glVertex2d(0, 10);
	glEnd();
}
void drawSquad(int x, int y, int a){
    a = a/2;
    glBegin(GL_LINE_LOOP);
        glColor3b(255,0,0);
        glVertex2d(x+a, y+a);
        glVertex2d(x+a, y-a);
        glColor3b(255,0,0);
        glVertex2d(x+a, y-a);
        glVertex2d(x-a, y-a);
        glColor3b(255,0,0);
        glVertex2d(x-a, y-a);
        glVertex2d(x-a, y+a);
    glEnd();
}
/**
 public void circleSimple(int xCenter, int yCenter, int radius, Color c)
    {
        int pix = c.getRGB();
        int x, y, r2;

        r2 = radius * radius;
        for (x = -radius; x <= radius; x++) {
            y = (int) (Math.sqrt(r2 - x*x) + 0.5);
            raster.setPixel(pix, xCenter + x, yCenter + y);
            raster.setPixel(pix, xCenter + x, yCenter - y);
        }
    }
const  double  pi2 = 6.28318530718;
void drawRectangle(int &x, int &y){
    static double radius = 50;
    const double delta_theta = pi2/25;
    double xcenter = x , ycenter = y;
    double xx, yy;
    double theta = 0.0;
    glColor3f(0.255f,0.204f,0.255f);
    glBegin(GL_LINES);
        double auX=xcenter + radius * sin(theta);
        double auY=ycenter + radius * cos(theta);
        while (theta <= pi2) {
            theta += delta_theta;
            xx = xcenter + radius * sin(theta);
            yy = ycenter + radius * cos(theta);
            glVertex2f(auX, auY);
            glVertex2f(xx, yy);
            auX=xx;
            auY=yy;
        }
    glEnd();
}

**/
void drawCircle(float cx, float cy, float r){
   double  pi2 = 6.28318530718;
   double delta_theta = pi2/25 , theta=0.0;
   double xx,yy;
   glColor3f(0.255f,0.204f,0.255f);
   glBegin(GL_LINES);
        double auX=cx + r * sin(theta);
        double auY=cy + r * cos(theta);
        while (theta <= pi2) {
            theta += delta_theta;
            xx = cx + r * sin(theta);
            yy = cy + r * cos(theta);
            glVertex2d(auX, auY);
            glVertex2d(xx, yy);
            auX=xx;
            auY=yy;
        }
    glEnd();

}
void draw1(int c, float p){
    p = 100.0 / p;
    float r=40,x=0.0,y=0.0;

    for(int i=0;i<c;i++){
        drawCircle(x,y,r);
        r= r-(r/p);
        x=-40.0 + r;
    }
}
//
//funcion llamada a cada imagen
void glPaint(void) {

	//El fondo de la escena al color initial
	glClearColor(255.0f, 255.0f, 255.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glLoadIdentity();


	//dibuja el gizmo
	//displayGizmo();
    ///drawSquad(0,0,50);
    ///draw1(10,8);
    draw2();
	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}
//
//inicializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(255.0f, 255.0f, 255.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro

	//modo projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-50.0f,  50.0f,-50.0f, 50.0f, -1.0f, 1.0f);
	// todas la informaciones previas se aplican al la matrice del ModelView
	glMatrixMode(GL_MODELVIEW);
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;

	default:
		break;
	}

}
//
//el programa principal
//
int main(int argc, char** argv) {

	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("TP1 OpenGL : hello_world_OpenGL"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);

	glutMainLoop(); //bucle de rendering

	return 0;
}