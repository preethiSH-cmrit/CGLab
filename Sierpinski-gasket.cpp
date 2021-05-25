
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include<GL/gl.h>
#include<GL/glu.h>
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
using namespace std;
typedef float point[3];

void method1(){
float vertices[][2]={{-1,-1}, {1,-1}, {0,1} };
int r_v = rand()%3; //
float p[] = {0,0}; // random initial point
float q[]={0,0};

glBegin(GL_POINTS);
    for (int i = 0; i<10000; i++){
        q[0] = (vertices[r_v][0]+p[0]) / 2;
        q[1] = (vertices[r_v][1]+p[1]) / 2;
        //cout<<q[0]<<","<<q[1]<<endl;
        glVertex2fv(q);
        p[0]= q[0]; p[1] = q[1];
        r_v = rand()%3; //
    }
    glEnd();
}
void display_triangle(point a, point b, point c){
    glBegin(GL_POLYGON);
    glColor3f(1,0,0);
    glVertex2fv(a);
     glColor3f(0.6,0,0);
    glVertex2fv(b);
     glColor3f(1,1,1);
    glVertex2fv(c);
    glEnd();
}
void divide_triangle(point a, point b, point c, int k){
    point v1, v2, v3;
    if(k>0){
        v1[0] = (a[0]+b[0]) / 2;
        v1[1] = (a[1]+b[1]) / 2;

        v2[0] = (a[0]+c[0]) / 2;
        v2[1] = (a[1]+c[1]) / 2;

        v3[0] = (b[0]+c[0]) / 2;
        v3[1] = (b[1]+c[1]) / 2;

        divide_triangle(a, v1, v2, k-1);
        divide_triangle(b, v1, v3, k-1);
        divide_triangle(c, v2, v3,k-1);


    }
    else
        display_triangle(a,b,c);


}

void method2() {
point v[]={{0,0,1},{-1,-1,-1}, {1,-1,-1}, {0,1,-1} };
int m = 2; //0 subdivisions


glColor3f(0,1,0);
divide_triangle(v[1],v[2],v[3],m);

glColor3f(1,0,0);
divide_triangle(v[0],v[1],v[2],m);

glColor3f(0,0,1);
divide_triangle(v[0],v[3],v[1],m);

glColor3f(0,0,0);
divide_triangle(v[0],v[2],v[3],m);

}
void display(){
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glColor3f(1,0,0);
method1();
//method2();

glFlush();

}
void myinit(){
glClearColor(1,1,1,1);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(-2, 2,-2,2,-2,2);
glMatrixMode(GL_MODELVIEW);

}
int main(int argc, char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("Sierpinski Gasket-2D using points");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
}
