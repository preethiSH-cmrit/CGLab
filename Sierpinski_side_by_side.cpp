#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include<GL/gl.h>
#include<GL/glu.h>
#include <GL/glut.h>
#endif

#include <stdlib.h>

typedef float point[3];
int m =3; // obtain from user

//point v[] = {{0,0,1}, {-1,-1,-1}, {1,-1,-1}, {0,1,-1}};

void display_triangle(point a, point b, point c){
    glBegin(GL_POLYGON);
       glVertex3fv(a); glVertex3fv(b); glVertex3fv(c);
    glEnd();
}

void divide_triangle(point a, point b, point c, int k){
    if (k>0){
        point v1,v2,v3;
        //mp of a and b
        v1[0] = (a[0]+b[0]) /2; //x
        v1[1] = (a[1]+b[1]) /2; // y
        v1[2] = (a[2]+b[2]) /2; //z
        // mp of a and c
        v2[0] = (a[0]+c[0]) /2; //x
        v2[1] = (a[1]+c[1]) /2; // y
        v2[2] = (a[2]+c[2]) /2; //z
        // mp of b and c
        v3[0] = (b[0]+c[0]) /2; //x
        v3[1] = (b[1]+c[1]) /2; // y
        v3[2] = (b[2]+c[2]) /2; //z
        divide_triangle(a, v1,v2, k-1);
        divide_triangle(b, v1, v3, k-1);
        divide_triangle(c, v2, v3, k-1);
    }else
       display_triangle(a,b,c);
}

void sierpinski(point v[], int m){
glColor3f(0,1,0);
divide_triangle(v[1],v[2],v[3], m);  // bottom face

glColor3f(1,0,0); // side face in red
divide_triangle(v[0], v[1],v[2],m);

glColor3f(0,0,1); // side face blue
divide_triangle(v[0], v[1],v[3],m);

glColor3f(0,0,0); // side face black
divide_triangle(v[0], v[2],v[3],m);
}
void display(){
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

float x1=0, y1=0, z1=1, x2=-1, y2=-1, z2=-1, x3=1, y3=-1, z3=-1, x4=0, y4=1, z4=-1;

float inc = 0;
for (int i = 0; i<3; i++){

    point v[] = {{(x1+inc),y1,z1},{(x2+inc),y2,z2},{(x3+inc),y3,z3},{(x4+inc),y4,z4}};
    sierpinski(v, i);
    inc+=3;
}
glFlush();
}

void myinit(){
    glClearColor(1,1,1,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2,10,-2,2,-2,2);
    glMatrixMode(GL_MODELVIEW);

}
int main(int argc, char **argv){
    // get user input for m - number of subdivisions

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH); //3D
    glEnable(GL_DEPTH_TEST); // z- buffer algorithm
    glutInitWindowSize(800,400);
    glutCreateWindow("Sierpinski - ");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
}
