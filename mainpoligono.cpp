#include <windows.h>
#include <GL/glut.h> //includes the opengl, glu, and glut header files
#include<stdlib.h> //includes the standard library header file
#include<iostream>
#include <math.h>


using namespace std;

GLsizei winWidth = 400, winHeight = 300; // Tamaño inicial de la ventana
int xAnt[20],yAnt[20];
int i=0;
double posCentrx=0,posCetry=0;
// de visualización.
void init (void)
{
glClearColor (0.0, 0.0, 1.0, 1.0); // Establecer azul como color ventana de
// visualización.
glMatrixMode (GL_PROJECTION);
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
glMatrixMode (GL_PROJECTION);
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
    glBegin(GL_POLYGON);
    for (int a=0;a<i;a++)
    {
        cout<<"aqui"<<endl;
        glVertex2d(xAnt[a],yAnt[a]);
    }
    glVertex2d(xAnt[0],yAnt[0]);
    glEnd();
    glFlush();
    i=0;
    xAnt[0]=NULL;
    yAnt[0]=NULL;
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

void trasladar()
{
    glPushMatrix();
    glTranslated(0,1,0);
    glEnd();
    cout<<"tecla"<<endl;
    //glPopMatrix();
    glFlush();
}

void teclado(unsigned char tecla,int x,int y)
{

    switch (tecla)
    {
        case 'w': trasladar();break;
    }
}

void actualizar()
{
    glutPostRedisplay();
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
