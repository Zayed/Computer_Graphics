/// Lab Assignment 5: Basic Transformation.cpp

/// Template by Zayed ///


#include <iostream>
#include <cstdio>

#include <GL/glut.h>

#include <string>
#include <cstring>
#include <sstream>

#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <map>
#include <set>


#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdlib>

using namespace std;

#define NL '\n'
#define CLR(ar) memset(ar, 0, sizeof(ar))
#define SET(ar) memset(ar, -1, sizeof(ar))

#define INF (1 << 31) - 1
#define MOD 1000000007
#define PRIME 999998727899999 			// (largest prime below 10^16)
#define PB push_back
#define pii pair<int, int>
#define pic pair<int, char>
#define pci pair<char, int>
#define pLL pair<LL, LL>
#define pis pair<int, string>
#define psi pair<string, int>
#define pss pair<string, string>
#define PI 2 * acos(0.0)
#define EPS 1e-11


/*
*******4 Direction Array*******
int dx[] = {0, 0, - 1, 1}, dy[] = {-1, 1, 0, 0};
*******8 Direction Array*******
int dx[] = {0, 0, -1, +1, -1, -1, +1, +1}, dy[] = {-1, +1, 0, 0, -1, +1, -1, +1};
********Knight Moves********
int dx[] = {-2, -2, -1, -1, +1, +1, +2, +2}, dy[] = {-1, +1, -2, +2, -2, +2, -1, +1};
*/

const int SIZE = 10;
vector<pii> v;
int dx, dy, choice;


void Translation()
{
	/// Draw Polygon after Translation Transformations
	glBegin(GL_POLYGON);
	glVertex2i(v[0].first + dx, v[0].second + dy);
	glVertex2i(v[1].first + dx, v[1].second + dy);
	glVertex2i(v[2].first + dx, v[2].second + dy);
	glVertex2i(v[3].first + dx, v[3].second + dy);
	glEnd();
}

void Scaling()
{
	/// Draw Polygon after Scaling Transformations
	glBegin(GL_POLYGON);
	glVertex2i(v[0].first * dx, v[0].second * dy);
	glVertex2i(v[1].first * dx, v[1].second * dy);
	glVertex2i(v[2].first * dx, v[2].second * dy);
	glVertex2i(v[3].first * dx, v[3].second * dy);
	glEnd();
}


void MyDisplay(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (0.0, 0.0, 0.0);
	glPointSize(4.0);

	/// Draw Original Polygon
	glBegin(GL_POLYGON);
	glVertex2i(v[0].first, v[0].second);
	glVertex2i(v[1].first, v[1].second);
	glVertex2i(v[2].first, v[2].second);
	glVertex2i(v[3].first, v[3].second);
	glEnd();


	if(choice == 1)
		Translation();
	else if(choice == 2)
		Scaling();

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

void Solve()
{
	int I, E, cnt = 1, x, y;


	v.clear();

	cout << "Enter your choice:\n1. Translation\n2. Scaling\n3. Exit\n";
	cin >> choice;

	if(choice == 3)
		return;

	cout << "Enter the number of Edges: ";
	cin >> E;

	for(I = 0; I < E; I++)
	{
		cout << "Enter the co-ordinates of vertex " << cnt++ << ":- ";
		cin >> x >> y;
		v.PB(pii(x, y));
	}

	cout << "Enter the Translation factor for x and y:- ";
	cin >> dx >> dy;

	glutCreateWindow ("Lab Assignment 5: Basic Transformation");
	glutDisplayFunc(MyDisplay);
	MyInit ();



}

int main(int argc, char** argv)
{
	int T, I, J, K, N, n, m, cnt = 0, len;

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (1024, 650);
	glutInitWindowPosition (0, 0);

	Solve();

	glutMainLoop();

	return 0;
}


/*
2
4
30 30
30 90
90 90
90 30
2 2

1
4
400 100
500 100
500 200
400 200

*/



