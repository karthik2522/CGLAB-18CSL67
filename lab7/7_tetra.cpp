#include<stdio.h>
#include<GL/glut.h>

GLfloat vertices[4][3]={{0.0,0.0,1.0},{0.0,0.94,-0.33},{-0.82,-0.47,-0.33},{0.82,-0.47,-                    
	0.33}};                            
GLfloat colors[4][3]={{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{0.0,0.0,0.0}};
int n;

void triangle(GLfloat *va,GLfloat *vb,GLfloat *vc)
{
		glVertex3fv(va);
		glVertex3fv(vb);
		glVertex3fv(vc);
}

void tetra(GLfloat *a,GLfloat *b,GLfloat *c,GLfloat *d)
{
		glColor3fv(colors[0]);
		triangle(a,b,c);
		glColor3fv(colors[1]);
		triangle(a,c,d);
		glColor3fv(colors[2]);
		triangle(a,d,b);
		glColor3fv(colors[3]);
		triangle(b,d,c);
}

void divide_tetra(GLfloat *a,GLfloat *b,GLfloat *c,GLfloat *d,int m)
{
		GLfloat mid[6][3];
		int J;
		if(m>0)
		{
			for(J=0;J<3;J++) mid[0][J]=(a[J]+b[J])/2;
			for(J=0;J<3;J++) mid[1][J]=(a[J]+c[J])/2;
			for(J=0;J<3;J++) mid[2][J]=(a[J]+d[J])/2;
			for(J=0;J<3;J++) mid[3][J]=(b[J]+c[J])/2;
			for(J=0;J<3;J++) mid[4][J]=(b[J]+d[J])/2;
			for(J=0;J<3;J++) mid[5][J]=(c[J]+d[J])/2;

divide_tetra(a,mid[0],mid[1],mid[2],m-1);
			divide_tetra(mid[0],b,mid[3],mid[4],m-1);				
			divide_tetra(mid[1],mid[3],c,mid[5],m-1);				
		           divide_tetra(mid[2],mid[4],mid[5],d,m-1);
		}
		else
			tetra(a,b,c,d);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	divide_tetra(vertices[0],vertices[1],vertices[2],vertices[3],n);
	glEnd();
	glFlush();
}

void myReshape(int w,int h)
{
 glViewport(0,0,w,h);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();

 if(w<=h)
      glOrtho(-2.0,2.0,- 2.0*(GLfloat)h/(GLfloat)w,2.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);

else
       glOrtho(-2.0*(GLfloat)h/(GLfloat)w,2.0*(GLfloat)h/(GLfloat)w,-2.0,2.0,-10.0,10.0);

glMatrixMode(GL_MODELVIEW);
glutPostRedisplay();
}	

int main(int argc, char** argv)
{
	printf("Enter no of recursive steps to divide tetrahedron : ");
	scanf("%d",&n);
        glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutCreateWindow("3D Sierpinski Gasket");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0,1.0,1.0,0.0);
	glutMainLoop();
	return 0;

}
