#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <math.h>

using namespace std;

typedef float coordenada;

class Point
{
    public:
        coordenada x,y,z;
        Point();
        Point(coordenada a, coordenada b, coordenada c);
        int region(coordenada xMid, coordenada yMid, coordenada zMid);
    protected:

    private:
};

ostream& operator<<(ostream& os, Point p);

bool operator==(Point a, Point b);

bool operator!=(Point a, Point b);

float euclidean(Point a, Point b);

struct Line{
    Line(Point a, Point b);
    Point u,v;
};
struct Quad{
    Point uno,dos,tre,cua;
    Quad(Point a,Point b,Point c,Point d,float na,float nb,float nc);
    float Nx,Ny,Nz;
};
class Voxel{
public:
    Quad arriba, abajo, izquierda, derecha, frente , atraz;
    Voxel(Quad A, Quad B, Quad I, Quad D, Quad F, Quad Z);
};

#endif // POINT_H
