// LINE CLIPPING - The Liang-Barsky Algorithm.cpp

#include <cstdio>
#include <iostream>

#include <GL/glut.h>

#include <string>
#include <cstring>
#include <sstream>

#include <cmath>
#include <cstdlib>

#define NL '\n'
using namespace std;

#define pdd pair<double, double>


const int SIZE = 10;
pdd pq[SIZE];
int ar[SIZE];
string S = "After Line Clipping";



void PrintText(int x, int y)
{
    int I, len;
	len = S.length();

	glColor3f(0.0, 0.0, 0.0);

    glRasterPos2f( x, y); 		// Location to start printing text
    for(I = 0; I < len; I++) 			// Loop until I is greater then len
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, S[I]);

}



void DrawLine(int x1, int y1, int x2, int y2, int flag)
{
	if(flag == 1)
		glColor3f (0.0, 0.0, 0.0);
	else
		glColor3f (0.6, 0.85, 0.92);

    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
}


/*
/// Formula
p1 = -(x2 - x1)			q1 = x1 - xmin
p2 = (x2 - x1)			q2 = xmax - x1
p3 = -(y2 - y1)			q3 = y1 - ymin
p4 = (y2 - y1)			q4 = ymax - y1
/// Formula
*/


int a1, b1, a2, b2;
void LiangBarsky(int x1, int y1, int x2, int y2)
{
	int I, p1, p2, p3, p4, q1, q2, q3, q4, x3, y3, x4, y4;
	double t1, t2;

	pq[1].first = -(x2 - x1);
	pq[1].second = x1 - 100;


	pq[2].first  = (x2 - x1);
	pq[2].second = 500 - x1;


	pq[3].first = -(y2 - y1);
	pq[3].second  = y1 - 100;


	pq[4].first = (y2 - y1);
	pq[4].second  = 300 - y1;


	for(I = 1; I <= 4; I++)
	{
		if(pq[I].first < 0)
			ar[I] = 1;
		else if(pq[I].second > 0)
			ar[I] = 2;
	}


	/// if pk < 0
	t1 = 0;
	for(I = 1; I <= 4; I++)
	{
		if(ar[I] == 1)
            t1 = max(t1, (double)(pq[I].second / pq[I].first));
	}


	if(t1 != 0)
	{
		x3 = x1 + t1 * (x2 - x1);
		y3 = y1 + t1 * (y2 - y1);
	}


	/// if pk > 0
	t2 = 1;
	for(I = 1; I <= 4; I++)
	{
		if(ar[I] == 2)
            t2 = min(t2, (double)(pq[I].second / pq[I].first));
	}


	if(t2 != 1)
	{
		x4 = x1 + t2 * (x2 - x1);
		y4 = y1 + t2 * (y2 - y1);
	}


	if(t1 > 0.0 && t2 < 1.00)
		DrawLine(x3, y3, x4, y4, 1);
	else if(t1 == 0.00 && t2 == 1)
		DrawLine(x1, y1, x2, y2, 1);
	else if(t1 == 0.0 || t2 < 1)
		DrawLine(x1, y1, x4, y4, 1);
	else if(t1 < 0.0 || t2 == 1.0)
		DrawLine(x3, y3, x2, y2, 1);

}



void Mouse(int button, int state, int x, int y)
 {
	if (button == GLUT_LEFT_BUTTON)
	{
		LiangBarsky(50, 110, 600, 200);
		PrintText(220, 70);
	}

	glutSwapBuffers();

}



void MyDisplay(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (0.6, 0.85, 0.92);
	glPointSize(4.0);


	/// Draw Rectangle
	glBegin(GL_POLYGON);
	glVertex2i(100, 100);
	glVertex2i(500, 100);
	glVertex2i(500, 300);
	glVertex2i(100, 300);
	glEnd();

	/// Before Line Clipping
	DrawLine(50, 110, 600, 200, -1);


	glutSwapBuffers();

}



void MyInit (void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (800, 600);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("LINE CLIPPING - The Liang_Barsky Algorithm");
	glutDisplayFunc(MyDisplay);
	glutMouseFunc(Mouse);
	MyInit ();
	glutMainLoop();

	return 0;
}



