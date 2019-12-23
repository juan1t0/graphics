#include "Point.h"

ostream& operator<<(ostream& os, Point p){
	os << "(" << p.x << ',' << p.y << ',' << p.z<<")";
	return os;
}

bool operator==(Point a, Point b){
    return (a.x==b.x) && (a.y==b.y) && (a.z==b.z);
}

bool operator!=(Point a, Point b){
    return (a.x!=b.x) || (a.y!=b.y) || (a.z!=b.z);
}

Line::Line(Point a, Point b):u(a),v(b){}
Quad::Quad(Point a, Point b, Point c, Point d,float na, float nb, float nc):uno(a),dos(b),tre(c),cua(d),Nx(na),Ny(nb),Nz(nc){}

Point::Point(coordenada a, coordenada b, coordenada c):x(a),y(b),z(c){

}//dtor

Point::Point(){

}

float euclidean(Point a, Point b) {
	return sqrt((pow(a.x - b.x, 2)) + (pow(a.y - b.y, 2)) + (pow(a.z - b.z, 2)));
}

int Point::region(coordenada xMid, coordenada yMid, coordenada zMid){
    int rpta=0;
    if(x>xMid)
        rpta|=1;
    if(y<yMid)
        rpta|=2;
    if(z>zMid)
        rpta|=4;
    return rpta;
}

Voxel::Voxel(Quad A, Quad B, Quad I, Quad D, Quad F, Quad Z): arriba(A), abajo(B), izquierda(I), derecha(D), frente(F), atraz(Z){}
