

#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include<GL/glu.h>
#endif

#include <stdlib.h>
#include "glos.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <glaux.h>
#include <math.h>

void myinit(void);
void initlights(void);
int flag = 1;
GLfloat angle, angle2;
int moving, startx, starty;
GLfloat ctrlpoints[4][2][3] = {
	{ { -1.0, -2.0, 0.0 },{ 1.0, -2.0, 0.0 } },
{ { -0.5, -1.0, 0.0 },{ 0.5, -1.0, 0.0 } },
{ { -0.5, 1.0, 0.0 },{ 0.5, 1.0, 0.0 } },
{ { -1.0, 2.0, 0.0 },{ 1.0, 2.0, 0.0 } }
};
void initlights(void)
{
	GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat position[] = { 0.0, 0.0, 2.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

static void resize(int width, int height)
{
	const float ar = (float)width / (float)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15.0, 15.0, -1.0, 20.0, -15.0, 15.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void makecylinder(float height, float Base)
{
	GLUquadricObj *qobj;
	qobj = gluNewQuadric();
	glColor3f(0.64f, 0.16f, 0.16f);
	glPushMatrix();
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	gluCylinder(qobj, Base*3, Base*3 - (0.2 * Base), height, 20, 20);
	glPopMatrix();
}
void maketree(float height, float Base)
{
	GLfloat ambient[] = { 0.05, 0.0, 0.0, 1.0 };
	GLfloat position[] = { 0.0, 0.0, 2.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.5, 0.4, 0.4, 1.0 };
	GLfloat mat_specular[] = { 0.7, 0.04, 0.04, 1.0 };
	GLfloat mat_shininess[] = { 10.0 };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glPushMatrix();



	float angle;
	makecylinder(height, Base);
	glTranslatef(0.0f, height, 0.0f);
	height -= height * 0.2f;
	Base -= Base * 0.3f;
	for (int a = 0; a<3; a++)
	{


		angle = 20 + ((rand() % 50));
		if (angle >48)
			angle = -(20 + ((rand() % 50)));
		if (height > 1)
		{
			glPushMatrix();
			if (flag)
				glRotatef(angle, 1.0f, 0.0f, 1.0f);
			else
				glRotatef(angle, 0.0f, 1.0f, 1.0f);
			flag = !flag;
			maketree(height, Base); //recursive call
			glPopMatrix();

		}
		else
		{
			GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
			GLfloat position[] = { 0.0, 0.0, 2.0, 1.0 };
			GLfloat mat_diffuse[] = { 0.1, 0.35, 0.1, 1.0 };
			GLfloat mat_specular[] = { 0.45, 0.55, 0.45, 1.0 };
			GLfloat mat_shininess[] = { 32.0 };

			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
			glPushMatrix();
			//glRotatef(180.0, 0.0, 1.0, 0.0);
			glEvalMesh2(GL_FILL, 0, 20, 0, 20);
			glPopMatrix();
		}
	}
	
	glPopMatrix();
}
static void display(void)
{
	const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	const double a = t * 90.0;
	srand(GLUT_ELAPSED_TIME);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(angle, 0, 1, 0);
	glRotatef(angle2, 0, 0, 1);

	maketree(4.0f, 0.1f);
	glutSwapBuffers();
	glFlush();
}


static void key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
	case 'q':
		exit(0);
		break;


	}

	glutPostRedisplay();
}



void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		moving = 1;
		startx = x;
		starty = y;
	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		moving = 0;
	}
}
void motion(int x, int y)
{
	if (moving)
	{
		angle = angle + (x - startx);
		angle2 = angle2 + (y - starty);
		startx = x;
		starty = y;
		glutPostRedisplay();
	}
}


void myinit(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST); 
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
		0, 1, 12, 4, &ctrlpoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3); 
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE); 
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	initlights();   
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(10, 10);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("GLUT Shapes");
	myinit();
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);

	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	glClearColor(1, 1, 1, 1);


	glEnable(GL_DEPTH_TEST);


	glutMainLoop();

	return EXIT_SUCCESS;
}
