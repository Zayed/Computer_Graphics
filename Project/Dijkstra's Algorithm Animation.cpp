// Visualization of Dijkstra’s Algorithm (Single-Source Shortest Path) through animation.cpp

#include <iostream>
#include <cstdio>

#include <string>
#include <cstring>
#include <sstream>

#include<GL/gl.h>
#include <GL/glut.h>


#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <cstdlib>


using namespace std;
int caseno = 1;

#define NL '\n'
#define SF scanf
#define PF printf
#define PC() printf("Case %d: ", caseno++)//NOTES:printf

#define CLR(ar) memset(ar, 0, sizeof(ar))
#define SET(ar) memset(ar, -1, sizeof(ar))
#define READ() freopen("input.txt", "r", stdin)
#define WRITE() freopen("output.txt", "w", stdout)
#define BOOST std::ios_base::sync_with_stdio(0);

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

string ToString(int n) { string s; stringstream convert; convert << n; s = convert.str(); return s; }//NOTES:ToString(

/// Data Structure
const int SIZE = 100;
vector<pii> G[SIZE];		/// Stores the graph
vector<int> G2[SIZE];	///
vector<int> path;				/// Stores the shortest path
priority_queue<pii, vector<pii>, greater <pii> > pq;		/// Priority Queue
int dis[SIZE], parent[SIZE];
int N, E;

map<int, pii> MAP1; 		/// Stores coordinates of Lower-left(x, y) corners
map<pii, int> MAP2;
map<pii, pii> MAP3;

string S, P, C;
/// Data Structure


void Dijkstra(int source, int destination)
{

	pq.push(pii(0, source));
	dis[source] = 0;
	parent[source] = 1;

	pii temp;
	int I, u, v, costUV;

	while(!pq.empty())
	{
        temp = pq.top();
        u = temp.second;

		pq.pop();

        for(I = 0; I < G[u].size(); I++)
		{
			v = G[u][I].first;
			costUV = G[u][I].second;

			if(dis[u] + costUV < dis[v])
			{
				dis[v] = dis[u] + costUV;
				parent[v] = u;
				pq.push(pii(dis[v], v));

			}

		}

	}

}

int flag = 0;
void PrintText(int x, int y, int n)
{
    int I, len;

	if(n != -1)
		S = ToString(n);

	if(flag == 1)
	{
		string temp = ToString(n);
		S =  "Node ";
		S += temp;
	}


    len = S.length(); 			// See how many characters are in text string.

    if(flag == 0)
		glColor3f(0.0, 0.0, 0.0);
	else
		glColor3f(0.0, 0.0, 1.0);

    glRasterPos2f( x, y); 		// Location to start printing text
    for(I = 0; I < len; I++) 			// Loop until i is greater then l
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, S[I]);

}



void DrawNode(int x, int y, int flag)
{

	if(flag == 0)
	{
		glColor3f(0.0,1.0,0.7);
		glPointSize(4.0);
	}
	else if(flag == 1)
	{
		glColor3f (1.0, 0.5, 0.0);
		glPointSize(4.0);
	}


	/// Draw Rectangle
	glBegin(GL_POLYGON);
	glVertex2i(x, y);
	glVertex2i(x + 40, y);
	glVertex2i(x + 40, y + 40);
	glVertex2i(x, y + 40);
	glEnd();


}


void MakeText()
{
	int I = 0;
	P = "";

	P += char(path[path.size() - 1] + '0');


	for(I = path.size() - 2; I >= 0; I--)
	{
		P += ' ';
		P += ' ';
		P += '-';
		P += '>';
		P += ' ';
		P += ' ';
		P += char(path[I] + '0');
	}

	S = P;

	string temp = "  (Shortest-Path)";

	for(I = 0; I < temp.size(); I++)
		S += temp[I];

	//cout << "P = " << P << NL;
	PrintText(170, 60, -1);

}


void MakeCost()
{
	int I = 0, J;
	C = "";

	string temp = "";

	temp = ToString(dis[path[path.size() - 1]]);

	for(I = 0; I < temp.size(); I++)
		C += temp[I];

	//cout << "C = " << C << NL;
	//C += char(path[path.size() - 1] + '0');


	for(I = path.size() - 2; I >= 0; I--)
	{
		temp = ToString(dis[path[I]]);

		for(J = 0; J < temp.size(); J++)
		{
			C += ' ';
			C += ' ';
			C += ' ';
			C += '+';
			C += ' ';
			C += ' ';
			C += ' ';
			C += temp[J];
		}

	}

	S = C;

	temp = "   (Total cost of the Shortest-Path)";

	for(I = 0; I < temp.size(); I++)
		S += temp[I];

	//cout << "C = " << C << NL;
	PrintText(170, 40, -1);
}


void DrawEdge(int x1, int y1, int x2, int y2, int flag)
{
	if(flag == 0)
	{
		glColor3f(0.0,1.0,0.7);
		glPointSize(4.0);
	}
	else if(flag == 1)
	{
		glColor3f (1.0, 0.5, 0.0);
		glPointSize(4.0);
	}

	/// Draw Rectangle
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();


}



void MyDisplay(void)
{
	glClear (GL_COLOR_BUFFER_BIT);

	int I, J, cnt = 0, x, y, u, v;

	for(I = 1; I <= N; I++)
	{
		x = MAP1[I].first;
		y = MAP1[I].second;

		flag = 1;
		PrintText(x + 7, y + 42, I);

		DrawNode(x, y, 0);

	}

	flag = 0;

	int x1, x2, y1, y2;

	for(I = 1; I <= N; I++)
	{

		for(J = 0; J < G2[I].size(); J++)
		{

			u = I, v = G2[u][J];

			x1 = MAP1[u].first;
			y1= MAP1[u].second;


			x2 = MAP1[v].first;
			y2 = MAP1[v].second;

			DrawEdge(x1, y1, x2, y2, 0);

			int cost = MAP2[pii(u, v)];

			PrintText((x1 + x2) /2, (y1 + y2) / 2, cost);

		}

	}


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


void Solve()
{
	int T, I, J, K, n, m, cnt = 0, len, u, v, w, source, destination;

	/// Initialization
	while(!pq.empty())
		pq.pop();

	SET(parent);

	for(I = 0; I < SIZE; I++)
		dis[I] = INF;


	/// Set Coordinates of the nodes
	MAP1[1] = pii(320, 420);
	MAP1[2] = pii(170, 415);
	MAP1[3] = pii(50, 350);
	MAP1[4] = pii(50, 250);		/// 3 == 4
	MAP1[5] = pii(170, 120);		/// 2 == 5
	MAP1[6] = pii(320, 100);		/// 1 == 6
	MAP1[7] = pii(450, 120);
	MAP1[8] = pii(480, 250);
	MAP1[9] = pii(480, 350);
	//MAP1[10] = pii(480, 350);


	/// Initialization



	/// Input

	PF("Enter the number of nodes and edges respectively: ");
	SF("%d%d", &N, &E);

	PF("Enter the undirected Graph:-\n");
	for(I = 0; I < E; I++)
	{
		SF("%d%d%d", &u, &v, &w);

		G2[u].PB(v);

		MAP2[pii(u, v)] = w;
		MAP2[pii(v, u)] = w;

		G[u].PB(pii(v, w));
		G[v].PB(pii(u, w));

	}

	PF("Enter the start node: ");
	SF("%d", &source);
	PF("Enter the end node: ");
	SF("%d", &destination);

	/// Input


	/// Find Shortest Path
	Dijkstra(source, destination);


	/// Print the Shortest Path
	int p, child = destination;

	path.PB(destination);

	while(1)
	{

		p = parent[child];
		path.PB(p);

		if(p == source)
			break;

		child = p;
	}

//	for(I = path.size() - 1; I >= 0; I--)
//		PF("%d(%d) ", path[I], dis[path[I]]);
	/// Print the Shortest Path


}



void Mouse(int button, int state, int x, int y)
 {
	if (button == GLUT_LEFT_BUTTON)
	{
		int I, u, v, x, y, x1, y1, x2, y2;
		for(I = 0; I < path.size() - 1; I++)
		{
			u = path[I];
			v = path[I + 1];

			x = MAP1[u].first;
			y = MAP1[u].second;

			DrawNode(x, y, 1);

			x1 = MAP1[u].first;
			y1= MAP1[u].second;


			x2 = MAP1[v].first;
			y2 = MAP1[v].second;

			DrawEdge(x1, y1, x2, y2, 1);

			x = MAP1[v].first;
			y = MAP1[v].second;

			DrawNode(x, y, 1);


		}
	}

	MakeText();
	MakeCost();


	glutSwapBuffers();

}


int main(int argc, char** argv)
{
	///BOOST
	READ();
	///WRITE();


	/// OpenGL Segement
	glutInit(&argc, argv);
	//glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (1366, 690);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("Visualization of Dijkstra’s Algorithm (Single-Source Shortest Path) through Animation");

	Solve();

	glutDisplayFunc(MyDisplay);

	//glutSpecialFunc(specialKeys); //Special Key Handler
	//glutKeyboardFunc(keyboard);   //Basic keyboard key handler
	glutMouseFunc(Mouse);         //Mouse Handler

	MyInit ();
	glutMainLoop();
	/// OpenGL Segement


	return 0;
}

/*
Input 1:
9 15
1 2 2
2 5 5
2 3 4
1 4 1
4 3 3
3 5 1
1 7 2
7 4 0
8 2 3
4 6 18
5 9 9
9 4 7
1 9 6
9 6 10
7 9 17

1
5

Input 2:
6 9
1 2 1
1 3 2
1 4 100
2 5 1
2 4 105
3 4 3
4 6 1
5 4 1
3 6 6

1
6
*/




