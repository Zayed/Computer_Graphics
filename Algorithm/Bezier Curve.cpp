// Bezier Curve.cpp

#include<iostream>
#include <cstdio>
#include <cmath>

#include <GL/glut.h>

#define pdd pair<double, double>
#define NL '\n'

using namespace std;



void DrawDot(double x, double y)
{
	glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}



/// Draw Linear Bezier Curve
/// Formula : B(t) = p1 + t * (p2 - p1) = (1 - t) * p1 + t * p2
void DrawLineBezierCurve(pdd p1, pdd p2)
{

	double Bx, By, x1 = p1.first, y1 = p1.second, x2 = p2.first, y2 = p2.second;

	Bx = x1, By = y1;
	for(double t = 0; t <= 1; t += 0.00001)
	{
		DrawDot(Bx, By);

		/// Calculate the next point
		Bx = (1 - t) * x1 + t * x2;
		By = (1 - t) * y1 + t * y2;
	}

}

/// Draw Quadratic Bezier Curve
/// Formula : B(t) = (1 - t)^2 * p1 + 2 * (1 - t) * t * p2 + t^2 * p3
void DrawQuadraticBezierCurve(pdd p1, pdd p2, pdd p3)
{

	double Bx, By, x1 = p1.first, y1 = p1.second, x2 = p2.first, y2 = p2.second, x3 = p3.first, y3 = p3.second;

	Bx = x1, By = y1;
	for(double t = 0; t <= 1; t += 0.00001)
	{
		DrawDot(Bx, By);

		/// Calculate the next point
		Bx = pow((1 - t), 2) * x1 +  2 * (1 - t) * t * x2 + pow(t, 2) * x3;
		By = pow((1 - t), 2) * y1 +  2 * (1 - t) * t * y2 + pow(t, 2) * y3;
	}

}


/// Draw Cubic Bezier Curve
/// Formula : B(t) = (1 - t)^3 * p1 + 3 * (1 - t)^2 * t * p2 + 3 * (1 - t) * t^2 * p3 + t^3* p3
void DrawCubicBezierCurve(pdd p1, pdd p2, pdd p3, pdd p4)
{

	double Bx, By, x1 = p1.first, y1 = p1.second, x2 = p2.first, y2 = p2.second, x3 = p3.first, y3 = p3.second,
	x4 = p4.first, y4 = p4.second;

	Bx = x1, By = y1;
	for(double t = 0; t <= 1; t += 0.00001)
	{
		DrawDot(Bx, By);

		/// Calculate the next point
		Bx = pow((1 - t), 3) * x1 + 3 * pow((1 - t), 2) * t * x2 + 3 * (1 - t) * pow(t, 2) * x3 + pow(t, 3) * x4;
		By = pow((1 - t), 3) * y1 + 3 * pow((1 - t), 2) * t * y2 + 3 * (1 - t) * pow(t, 2) * y3 + pow(t, 3) * y4;
	}

}



void MyDisplay(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (0.0, 0.0, 0.0);
	glPointSize(4.0);

	pdd p1, p2, p3, p4, p5, p6, p7, p8;

	/// Curve 1
	p1.first = 100, p1.second = 300;
	p2.first = 150, p2.second = 400;
	DrawLineBezierCurve(p1, p2);

	/// Curve 2
	p1.first = 300, p1.second = 300;
	p2.first = 400, p2.second = 550;
	p3.first = 450, p3.second = 400;
	DrawQuadraticBezierCurve(p1, p2, p3);

	/// Curve 3
	p1.first = 200, p1.second = 100;
	p2.first = 250, p2.second = 300;
	p3.first = 350, p3.second = 300;
	p4.first = 400, p4.second = 100;
	DrawCubicBezierCurve(p1, p2, p3, p4);


	glFlush ();

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
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (1366, 690);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("Bezier Curve");
	glutDisplayFunc(MyDisplay);
	MyInit ();
	glutMainLoop();

	return 0;
}



