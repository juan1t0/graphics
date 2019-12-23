#include "OcTree.h"

bool findPoint(vector<Point> vec, Point p){
    for(size_t i=0;i<vec.size();++i){
        if(vec[i]==p)
            return true;
    }
    return false;
}


OcTree::OcTree(coordenada xMin, coordenada xMax, coordenada yMin, coordenada yMax, coordenada zMin, coordenada zMax, int maxP):minX(xMin),maxX(xMax),minY(yMin),maxY(yMax),minZ(zMin),maxZ(zMax),maxPoints(maxP){
    midX=(minX+maxX)/2;
    midY=(minY+maxY)/2;
    midZ=(minZ+maxZ)/2;
    for(int i=0;i<8;++i)
        regions[i]=NULL;
}

void OcTree::split(){
    OcTree* p;
    regions[0]=new OcTree(minX,midX,midY,maxY,minZ,midZ,maxPoints);
    regions[1]=new OcTree(midX,maxX,midY,maxY,minZ,midZ,maxPoints);
    regions[2]=new OcTree(minX,midX,minY,midY,minZ,midZ,maxPoints);
    regions[3]=new OcTree(midX,maxX,minY,midY,minZ,midZ,maxPoints);
    regions[4]=new OcTree(minX,midX,midY,maxY,midZ,maxZ,maxPoints);
    regions[5]=new OcTree(midX,maxX,midY,maxY,midZ,maxZ,maxPoints);
    regions[6]=new OcTree(minX,midX,minY,midY,midZ,maxZ,maxPoints);
    regions[7]=new OcTree(midX,maxX,minY,midY,midZ,maxZ,maxPoints);
    for(unsigned int i=0;i<=maxPoints;++i){
        p=regions[points[i].region(midX,midY,midZ)];
        p->insertPoint(points[i],p);
    }
    points.clear();
}

bool OcTree::searchPoint(Point punto, OcTree *&ot){
    if(!regions[0])
        return findPoint(points,punto);
    else{
        ot=(regions[punto.region(midX,midY,midZ)]);
        return ot->searchPoint(punto,ot);
    }
}

void OcTree::insertPoint(Point punto, OcTree * p){
    if(!searchPoint(punto,p)){
        p->points.push_back(punto);
            if(p->points.size()>maxPoints)
                p->split();
    }
}

vector<Point> OcTree::getPoints(){
    vector<Point> puntos;
    if (!regions[0]) {
        puntos.insert(puntos.end(),points.begin(),points.end());
    }
    else {
        vector<Point> aux;
        for (int i = 0; i < 8; ++i) {
            aux = regions[i]->getPoints();
            puntos.insert(puntos.end(),aux.begin(),aux.end());
        }
    }
	return puntos;
}

vector<Line> OcTree::getBorderLines(){
    vector<Line> lines;
    if(regions[0]){
        for(int i=0;i<8;++i){
            vector<Line> aux=regions[i]->getBorderLines();
            lines.insert(lines.end(),aux.begin(),aux.end());
        }
    }
//        cout<<<<endl;
        Point
        a(maxX,minY,minZ),///1
        b(minX,minY,minZ),///2
        c(maxX,maxY,minZ),///3
        d(minX,maxY,minZ),///4
        e(maxX,minY,maxZ),///5
        f(minX,minY,maxZ),///6
        g(maxX,maxY,maxZ),///7
        h(minX,maxY,maxZ);///8

        lines.push_back(Line(a,b));///1
        lines.push_back(Line(c,d));///2
        lines.push_back(Line(e,f));///3
        lines.push_back(Line(g,h));///4
        lines.push_back(Line(a,e));///5
        lines.push_back(Line(b,f));///6
        lines.push_back(Line(c,g));///7
        lines.push_back(Line(d,h));///8
        lines.push_back(Line(a,c));///9
        lines.push_back(Line(b,d));///10
        lines.push_back(Line(e,g));///11
        lines.push_back(Line(f,h));///12

	return lines;
}

vector<Line> OcTree::getLines(){
    vector<Line> lines;
    Point
        a(maxX,midY,midZ),
        b(minX,midY,midZ),
        c(midX,maxY,midZ),
        d(midX,minY,midZ),
        e(midX,midY,maxZ),
        f(midX,midY,minZ);
    if(regions[0]){
        lines.push_back(Line(a,b));
        lines.push_back(Line(c,d));
        lines.push_back(Line(e,f));
        for(int i=0;i<8;++i){
            vector<Line> aux=regions[i]->getLines();
            lines.insert(lines.end(),aux.begin(),aux.end());
        }
    }
    return lines;
}

bool OcTree::onCircle(Point punto, float distancia){
    bool result=true;
    vector<vector<coordenada> > ps;
    vector<coordenada> p1={minX,minY,minZ};
    vector<coordenada> p2={maxX,maxY,maxZ};
    ps.push_back(p1);
    ps.push_back(p2);
    for(int i=0; i<2;++i){
        for(int j=0;j<2;++j){
            for(int k=0; k<2; ++k){
                Point p(ps[i][0],ps[j][1],ps[k][2]);
                result = result && (euclidean(punto,p)<=distancia);
            }
        }
    }
    return result;
}

bool OcTree::corner(Point punto, float distancia){
    bool result=false;
    vector<vector<coordenada> > ps;
    vector<coordenada> p1={minX,minY,minZ};
    vector<coordenada> p2={maxX,maxY,maxZ};
    ps.push_back(p1);
    ps.push_back(p2);
    for(int i=0; i<2;++i){
        for(int j=0;j<2;++j){
            for(int k=0; k<2; ++k){
                Point p(ps[i][0],ps[j][1],ps[k][2]);
                result = result || (euclidean(punto,p)<=distancia);
            }
        }
    }
    return result;
}

bool OcTree::inCube(Point punto){
    bool result=true;
    vector<vector<coordenada> > ps;
    vector<coordenada> p1={minX,minY,minZ};
    vector<coordenada> p2={maxX,maxY,maxZ};
    vector<coordenada> p={punto.x,punto.y,punto.z};
    ps.push_back(p1);
    ps.push_back(p2);
    for(int i=0; i<ps[0].size();++i){
        result = result && (p[i]>p1[i]);
        result = result && (p[i]<p2[i]);
    }
    return result;
}

bool OcTree::outCube(Point punto, float distancia){
    bool result=false;
    vector<vector<coordenada> > ps;
    vector<coordenada> p1={minX,minY,minZ};
    vector<coordenada> p2={maxX,maxY,maxZ};
    vector<coordenada> p={punto.x,punto.y,punto.z};
    ps.push_back(p1);
    ps.push_back(p2);
    for(int i=0; i<ps[0].size();++i){
        result = result || (p[i]<p1[i] && (p[i]+distancia)>p1[i]);
        result = result || (p[i]>p2[i] && (p[i]-distancia)<p2[i]);
    }
    return result;
}

bool OcTree::inRegion(Point punto, float distancia){
    bool result=false;
    if(corner(punto,distancia)){
        result=true;
    }
    else{
        if(inCube(punto)){
            result = true;
        }
        else{
            if(outCube(punto,distancia)){
                result = true;
            }
        }
    }
    return result;
}

vector<Point> OcTree::cercanos(Point centro, float radio){
    vector<Point> puntos;
    if(onCircle(centro,radio)){
        return getPoints();
    }
    else if(inRegion(centro, radio)){
        if (!regions[0]) {
            for (size_t i = 0; i < points.size(); ++i) {
                if (euclidean(points[i], centro) <= radio)
                    puntos.push_back(points[i]);
            }
        }
        else {
            vector<Point> aux;
            for (int i = 0; i < 8; ++i) {
                aux = regions[i]->cercanos(centro, radio);
                puntos.insert(puntos.end(),aux.begin(),aux.end());
            }
        }
    }
    return puntos;
}


OcTree::~OcTree(){
    //dtor
}
void OcTree::drawquads(){

}
vector<Quad> OcTree::getQuads(){
    vector<Quad> quads;
    if(regions[0]){
        for(int i=0;i<8;++i){
            vector<Quad> aux=regions[i]->getQuads();
            quads.insert(quads.end(),aux.begin(),aux.end());
        }
    }else if (points.size()>0){//(!regions[0]){
//        cout<<<<endl;
        Point
        a(maxX,minY,minZ),///1
        b(minX,minY,minZ),///2
        c(maxX,maxY,minZ),///3
        d(minX,maxY,minZ),///4
        e(maxX,minY,maxZ),///5
        f(minX,minY,maxZ),///6
        g(maxX,maxY,maxZ),///7
        h(minX,maxY,maxZ);///8

        quads.push_back(Quad(a,c,d,b,0,0,-1));///1
        quads.push_back(Quad(b,d,h,f,-1,0,0));///2
        quads.push_back(Quad(f,h,g,e,0,0,1));///3
        quads.push_back(Quad(e,g,c,a,1,0,0));///4
        quads.push_back(Quad(g,c,d,h,0,1,0));///5
        quads.push_back(Quad(e,f,b,a,0,-1,0));///6
    }

	return quads;
}
vector<Voxel> OcTree::getBoxs(short xmin,short xmax,short ymin,short ymax,short zmin,short zmax){
    vector<Voxel> boxs;
//    bool dentro = true;
    if(!((minX >= xmin) && (maxX <= xmax) && (minY >= ymin) && (maxY <= ymax) && (minZ >= zmin) && (maxZ <= zmax))){
   //     cout<<"- "<<minX<<" "<<maxX<<" "<<minY<<" "<<maxY<<" "<<minZ<<" "<<maxZ<<endl;
     //   cout<<"+ "<<xmin<<" "<<maxX<<" "<<ymin<<" "<<zmax<<" "<<zmin<<" "<<zmax<<endl;
        for(int i=0;i<8;++i){
            if(regions[i]){
                vector<Voxel> aux = regions[i]->getBoxs(xmin,xmax,ymin,ymax,zmin,zmax);
                if(!aux.empty())boxs.insert(boxs.end(),aux.begin(),aux.end());
            }
        }
        return boxs;
    }
    if(regions[0]){
        vector<vector<Voxel>> deMisHijos(8);
        for(int i=0;i<8;++i){
            vector<Voxel> aux = regions[i]->getBoxs(xmin,xmax,ymin,ymax,zmin,zmax);
            deMisHijos[i] = aux;
//            boxs.insert(boxs.end(),aux.begin(),aux.end());
        }
        int cont =0;
        for(int i=0;i<8;++i){
 //           cout<<deMisHijos[i].size()<<"- "<<i<<endl;
            if(deMisHijos[i].size()==1)
                cont++;
        }
//        cout<<"cont: "<<cont<<endl;
        if(cont == 8){
            Point
            a(maxX,minY,minZ),///1
            b(minX,minY,minZ),///2
            c(maxX,maxY,minZ),///3
            d(minX,maxY,minZ),///4
            e(maxX,minY,maxZ),///5
            f(minX,minY,maxZ),///6
            g(maxX,maxY,maxZ),///7
            h(minX,maxY,maxZ);///8

            Quad
            ar(a,c,d,b,0,0,-1),///1
            ab(b,d,h,f,-1,0,0),///2
            de(f,h,g,e,0,0,1),///3
            iz(e,g,c,a,1,0,0),///4
            fr(g,c,d,h,0,1,0),///5
            az(e,f,b,a,0,-1,0);///6

            boxs.push_back(Voxel(ar,ab,de,iz,fr,az));
        }else{
            for(int i=0;i<8;++i){
                boxs.insert(boxs.end(),deMisHijos[i].begin(),deMisHijos[i].end());
            }
        }
    }else if (points.size()>0){//(!regions[0]){
//        cout<<<<endl;
        Point
        a(maxX,minY,minZ),///1
        b(minX,minY,minZ),///2
        c(maxX,maxY,minZ),///3
        d(minX,maxY,minZ),///4
        e(maxX,minY,maxZ),///5
        f(minX,minY,maxZ),///6
        g(maxX,maxY,maxZ),///7
        h(minX,maxY,maxZ);///8
        if(euclidean(b,g)<5.0){
            Quad
            ar(a,c,d,b,0,0,-1),///1
            ab(b,d,h,f,-1,0,0),///2
            de(f,h,g,e,0,0,1),///3
            iz(e,g,c,a,1,0,0),///4
            fr(g,c,d,h,0,1,0),///5
            az(e,f,b,a,0,-1,0);///6

            boxs.push_back(Voxel(ar,ab,de,iz,fr,az));
        }
    }

	return boxs;
}
