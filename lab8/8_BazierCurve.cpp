#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#define PI 3.1416

GLsizei winwidth = 600, winheight = 600;
GLfloat xwcmin = 0.0, xwcmax = 130.0;
GLfloat ywcmin = 0.0, ywcmax = 130.0;

typedef struct wcpt3d
{
    GLfloat x, y, z;
};

void bino(GLint n, GLint *C)
{
    GLint k, j;
    for(k=0;k<=n;k++)
    {
        C[k] = 1;
        for(j=n; j>=k+1; j--)
            C[k] *= j;
        for(j=n-k; j>=2; j--)
            C[k]/=j;
    }
}

void computebezpt(GLfloat u, wcpt3d *bezpt, GLint nctrlpts, wcpt3d *ctrlpts, GLint *C)
{
    GLint k, n = nctrlpts-1;
    GLfloat bezblendfcn;
    bezpt->x = bezpt->y = bezpt->z = 0.0;
    for(k=0; k<nctrlpts; k++)
    {
        bezblendfcn = C[k]*pow(u, k) * pow(1-u, n-k);
        bezpt->x += ctrlpts[k].x *bezblendfcn;
        bezpt->y += ctrlpts[k].y *bezblendfcn;
        bezpt->z += ctrlpts[k].z *bezblendfcn;
    }
}

void bezier(wcpt3d *ctrlpts, GLint nctrlpts, GLint nbezcurvepts)
{
    wcpt3d bezcurvept;
    GLfloat u;
    GLint *C, k;
    C = new GLint[nctrlpts];
    bino(nctrlpts-1, C);
    glBegin(GL_LINE_STRIP);
    for(k=0; k<=nbezcurvepts; k++)
    {
        u = GLfloat(k)/GLfloat(nbezcurvepts);
        computebezpt(u, &bezcurvept, nctrlpts, ctrlpts, C);
        glVertex2f(bezcurvept.x, bezcurvept.y);
    }
    glEnd();
    delete[]C;
}

void displayfcn()
{
    GLint nctrlpts = 4, nbezcurvepts = 20;
    static float theta = 0;
    wcpt3d ctrlpts[4] = {{20, 100, 0}, {30, 110, 0}, {50, 90, 0}, {60, 100, 0}};
    ctrlpts[1].x +=10*sin(theta * PI/180.0);
    ctrlpts[1].y +=5*sin(theta * PI/180.0);
    ctrlpts[2].x -= 10*sin((theta+30) * PI/180.0);
    ctrlpts[2].y -= 10*sin((theta+30) * PI/180.0);
    ctrlpts[3].x-= 4*sin((theta) * PI/180.0);
    ctrlpts[3].y += sin((theta-30) * PI/180.0);
    theta+=0.1;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(5);
    glPushMatrix();
    glLineWidth(5);
    glColor3f(255/255, 153/255.0, 51/255.0); //Indian flag: saffron color code
    for(int i=0;i<8;i++)
    {
        glTranslatef(0, -0.8, 0);
        bezier(ctrlpts, nctrlpts, nbezcurvepts);
    }

    glColor3f(1, 1, 1); //Indian flag: white color code
    for(int i=0;i<8;i++)
    {
        glTranslatef(0, -0.8, 0);
        bezier(ctrlpts, nctrlpts, nbezcurvepts);
    }

    glColor3f(19/255.0, 136/255.0, 8/255.0); //Indian flag: green color code
    for(int i=0;i<8;i++)
    {
        glTranslatef(0, -0.8, 0);
        bezier(ctrlpts, nctrlpts, nbezcurvepts);
    }

    glPopMatrix();
    glColor3f(0.7, 0.5,0.3);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(20,100);
    glVertex2f(20,40);
    glEnd();
    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();

}

void winreshapefun(GLint new_width, GLint new_height)
{
    glViewport(0, 0, new_width, new_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xwcmin, xwcmax, ywcmin, ywcmax);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(winwidth, winheight);
    glutCreateWindow("Bezier Curve");
    glutDisplayFunc(displayfcn);
    glutReshapeFunc(winreshapefun);
    glutMainLoop();
    return 0;
}
