#include <windows.h>
#include <GL/glut.h> //includes the opengl, glu, and glut header files
#include<stdlib.h> //includes the standard library header file
#include<iostream>
#include <math.h>
#define PI 3.141632

using namespace std;

GLsizei winWidth = 400, winHeight = 300; // Tamaño inicial de la ventana
int xAnt[20],yAnt[20];
int i=0,rotar=0;float vy=0,vx=0,escala=1;
double posCentrx=0,posCetry=0;

// de visualización.
void init (void)
{
glClearColor (0.0, 0.0, 1.0, 1.0); // Establecer azul como color ventana de
// visualización.
glMatrixMode (GL_MODELVIEW);
gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}
void displayFcn (void)
{
glClear (GL_COLOR_BUFFER_BIT); // Borrar ventana de visualización.
glColor3f (1.0, 0.0, 0.0);    // Establecer rojo como color de punto.
glPointSize (3.0);           // Definir tamaño de punto 3.0.
}
void winReshapeFcn (GLint newWidth, GLint newHeight)
{
/*  Reinicializar parámetros de proyección y visor */
glViewport (0, 0, newWidth, newHeight);
glMatrixMode (GL_MODELVIEW);
glLoadIdentity ( );
gluOrtho2D (0.0, GLdouble (newWidth), 0.0, GLdouble (newHeight));
/*  Reinicializar parámetros de tamaño ventana de visualización. */ winWidth = newWidth; winHeight = newHeight;
}
void plotPoint (GLint x, GLint y)
{
glBegin (GL_POINTS);
glVertex2i (x, y);
glEnd ( );
}

void lineDDA (int x0, int y0, int xEnd, int yEnd)
{
    int dx = xEnd - x0, dy = yEnd - y0, steps, k;
    float xIncrement, yIncrement, x = x0, y = y0;
    if (fabs (dx) > fabs (dy))
        steps = fabs (dx);
    else
    steps = fabs (dy);
    cout<<"llega "<<x0<<" "<<y0<<" "<<xEnd<<" "<<yEnd<<endl;
    xIncrement = float (dx) / float (steps);
    yIncrement = float (dy) / float (steps);
    plotPoint (round (x), round (y));
    for (k = 0; k < steps; k++) {
        x += xIncrement;
        y += yIncrement;
        cout<<"llega"<<endl;
        plotPoint (round (x), round (y));
    }
}

void poligono()
{
    glClear (GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    //glTranslatef(0+vx,0+vy,0);
    glRotated(rotar,0,0,1);
    //glScalef(1+escala,1+escala,1+escala);
    glBegin(GL_POLYGON);
    cout<<"dibujand"<<endl;
    for (int a=0;a<i;a++)
    {
        glVertex2d(xAnt[a],yAnt[a]);
    }
    glVertex2d(xAnt[0],yAnt[0]);
    //glPopMatrix();
    glEnd();
    glFlush();

}

void trasladar()
{
    int centrox=-xAnt[0];
    int centroy=-yAnt[0];
    //trasladar al origen
    for(int a=0;a<i;a++)
    {
        xAnt[a]=xAnt[a]+centrox;
        yAnt[a]=yAnt[a]+centroy;
    }
    cout<<xAnt[0]<<" "<<yAnt[0]<<endl;

    for(int a=0;a<i;a++)
    {
        xAnt[a]=xAnt[a]+vx;
        yAnt[a]=yAnt[a]+vy;
    }

    for(int a=0;a<i;a++)
    {
        xAnt[a]=xAnt[a]-centrox;
        yAnt[a]=yAnt[a]-centroy;
    }
    cout<<xAnt[0]<<" "<<yAnt[0]<<endl;
    poligono();
}


void funescalar()
{
    int centrox=-xAnt[0];
    int centroy=-yAnt[0];
    //trasladar al origen
    for(int a=0;a<i;a++)
    {
        xAnt[a]=xAnt[a]+centrox;
        yAnt[a]=yAnt[a]+centroy;
    }
    cout<<xAnt[0]<<" "<<yAnt[0]<<endl;

    for(int a=0;a<i;a++)
    {
        xAnt[a]=xAnt[a]*escala;
        yAnt[a]=yAnt[a]*escala;
    }

    for(int a=0;a<i;a++)
    {
        xAnt[a]=xAnt[a]-centrox;
        yAnt[a]=yAnt[a]-centroy;
    }
    cout<<xAnt[0]<<" "<<yAnt[0]<<endl;
    poligono();
}

void funrotar()
{
    int centrox=-xAnt[0];
    int centroy=-yAnt[0];

    double variaC=cos(rotar);
    double variaS=sin(rotar);
    //trasladar al origen
    for(int a=0;a<i;a++)
    {
        xAnt[a]=xAnt[a]+centrox;
        yAnt[a]=yAnt[a]+centroy;
    }
    cout<<xAnt[0]<<" "<<yAnt[0]<<endl;

    for(int a=0;a<i;a++)
    {
        xAnt[a]=round(xAnt[a]*variaC+yAnt[a]*-variaS);
        yAnt[a]=round(xAnt[a]*variaS+yAnt[a]*variaC);
    }

    for(int a=0;a<i;a++)
    {
        xAnt[a]=xAnt[a]-centrox;
        yAnt[a]=yAnt[a]-centroy;
    }
    cout<<xAnt[0]<<" "<<yAnt[0]<<endl;
    poligono();
}

void mousePtPlot (int button, int action, int xMouse, int yMouse)
{

    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
    {
        plotPoint (xMouse, winHeight - yMouse);

        if(xAnt[0]!=NULL)
        {
            lineDDA (xAnt[i-1],yAnt[i-1],xMouse,winHeight - yMouse);
        }

        xAnt[i]=xMouse;
        yAnt[i]=winHeight - yMouse;
        i++;
    }
    if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN)
    {
        poligono();
    }
    glFlush ( );
}


void teclado(unsigned char tecla,int x,int y)
{
    //teclas designadas para cada funcion especifica
    switch (tecla)
    {
        case 'w': vy=1;trasladar();vy=0;break;
        case 's': vy=-1;trasladar();vy=0;break;
        case 'd': vx=1;trasladar();vx=0;break;
        case 'a': vx=-1;trasladar();vx=0;break;

        case '}': rotar=1;trasladar();rotar=0;break;
        case '{': rotar=-1;trasladar();rotar=0;break;

        case '+': escala=1.1;funescalar();escala=1;break;
        case '-': escala=0.9;funescalar();escala=1;break;
    }
}

int main (int argc, char** argv)
{
glutInit (&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
glutInitWindowPosition (200, 200);
glutInitWindowSize (winWidth, winHeight);
glutCreateWindow ("Mouse Plot Points");
init ( );
glutDisplayFunc (displayFcn);
glutReshapeFunc (winReshapeFcn);
glutKeyboardFunc(teclado);
glutMouseFunc (mousePtPlot);
glutMainLoop ( );
}
