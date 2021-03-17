#include <GL/glut.h>
#include <cstdlib>
#include <list>
#include <algorithm>
#include <iostream>
#include "triangulate.h"
#include <vector>
#include <assert.h>
#include "Header.h"
//#include <Sourse.cpp>

GLint flag = 0, t = 0, k = 0, z = 0;
bool f = true;
GLsizei height = 500, width = 600;
int counter = 0,  numofp = 0;
GLfloat a = 0.0f, af = 1.0f;
GLfloat b = 0.0f, bf = 1.0f;
GLfloat c = 0.0f, cf = 1.0f;
int triangle = 0;//gia to perigrama twn trigwnwn
const int max = 100;

class points {
public:
	GLint x, y;
};
static std::list<points> List;
static std::list<Vector2dVector> triangles;

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 500.0, 0.0, 600.0);
}
void drawPolygon() {

	Vector2dVector t = triangles.back();
	int tcount = t.size() / 3;
	points pt1, pt2, pt3;
	for (int i = 0; i < tcount; i++) {
		const Vector2d &p1 = t[i * 3 + 0];
		const Vector2d &p2 = t[i * 3 + 1];
		const Vector2d &p3 = t[i * 3 + 2];
		pt1.x = p1.GetX();pt1.y = p1.GetY();
		pt2.x = p2.GetX();pt2.y = p2.GetY();
		pt3.x = p3.GetX();pt3.y = p3.GetY();
		glBegin(GL_POLYGON); {
			glColor3f(af, bf, cf);
			glVertex2f(pt1.x, pt1.y);
			glVertex2f(pt2.x, pt2.y);
			glVertex2f(pt3.x, pt3.y);
		}
		glEnd();
	}
	glFlush();
}
void drawLine(points endPt1, points endPt2) {

	if (triangle == 1) {
		a = 0.0f;
		b = 1.0f;
		c = 0.0f;
	}
	glColor3f(a, b, c);
	glutPostRedisplay();
	glBegin(GL_LINES); {
		glVertex2i(endPt1.x, endPt1.y);
		glVertex2i(endPt2.x, endPt2.y);
	}
	glEnd();
	glFlush();
}
void winReshapeFcn(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(w), 0.0, GLdouble(h));

	width = w;
	height = h;
}

void display(void) {
	//glClear(GL_COLOR_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);  
	//glLoadIdentity();
	//glutSwapBuffers();
}

int orientation(points p, points q, points r) {

	double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);//Find the four orientations needed 
	if (val == 0) return 0;
	return (val > 0) ? 1 : 2;
}

bool intersect(std::list<points> &a, int b) {//The main function that returns true if line segment 'p1q1' and 'p2q2' intersect. 
	int i = 0;
	int j = 0;
	static points A0, A1, A2, A3;
	points s[1000];
	std::list<points>::iterator it = a.begin();
	for (it;it!=a.end();++it) {
		s[j] = *it;
		j++;
	}
	A3 = s[j - 1];
	A2 = s[j - 2];
	while (b != 2) {
		A0 = s[i];
		A1 = s[i + 1];
		int o1 = orientation(A0, A1, A2);
		int o2 = orientation(A0, A1, A3);
		int o3 = orientation(A2, A3, A0);
		int o4 = orientation(A2, A3, A1);
		if (o1 != o2 && o3 != o4) {
			return true;
		}
		b--;
		i = i + 1;
	}
	return false;
}

void save(std::list<points> l) {

	std::list<points>::iterator it;//save to the main list
	numofp++;
	for (it = l.begin(); it != l.end(); ++it)
		List.push_back(*it);
}

void showPolygons() {
	static points endPt1, endPt2, firstPt;
	std::list<points>::iterator it;
	for (it = List.begin(); it != List.end();++it) {
		if ((*it).x != -1) {
			if (t == 0) {
				firstPt = *it;
				t = 1;
			}
			if (k == 0) {
				endPt1 = *it;
				k++;
			}
			if (k == 1) {
				endPt2 = *it;
				drawLine(endPt1, endPt2);
			}
			endPt1 = endPt2;
		}
		else {
			drawLine(endPt1, firstPt);
			t = 0;k = 0;
		}
	}
}
int erase(std::list<points> temp) {
	static points endPt1, endPt2, firstPt;
	std::list<points>::iterator it;
	a = 1.0f;b = 1.0f;c = 1.0f;//erase previous lines
	for (it = temp.begin(); it != temp.end();++it) {
		if (t == 0) {
			firstPt = *it;
			t = 1;
		}
		if (k == 0) {
			endPt1 = *it;
			k++;
		}
		if (k == 1) {
			endPt2 = *it;
			drawLine(endPt1, endPt2);
		}
		endPt1 = endPt2;
	}
	t = 0;k = 0;
	a = 0.0f;b = 0.0f;c = 0.0f;
	return 0;
}
void showTriangles(Vector2dVector &result) {
	int tcount = result.size() / 3;
	points pt1, pt2, pt3;

	for (int i = 0; i < tcount; i++) {
		const Vector2d &p1 = result[i * 3 + 0];
		const Vector2d &p2 = result[i * 3 + 1];
		const Vector2d &p3 = result[i * 3 + 2];
		pt1.x = p1.GetX();pt1.y = p1.GetY();
		pt2.x = p2.GetX();pt2.y = p2.GetY();
		pt3.x = p3.GetX();pt3.y = p3.GetY();
		drawLine(pt1, pt2);
		drawLine(pt1, pt3);
		drawLine(pt2, pt3);
	}
}
void mainMenu(GLint option) {
	glutPostRedisplay();
}
void triangulate(std::list<points> &tr) {
	std::list<points>::iterator it;
	Vector2dVector a, result;
	//std::cout << a.size();
	for (it = tr.begin(); it != tr.end();++it) {
		if ((*it).x != -1) {
			float k = (*it).x;
			float l = (*it).y;
			a.push_back(Vector2d(k, l));
		}
		else {
			a.pop_back();
			Triangulate::Process(a, result);
			a.clear();
			triangles.push_back(result);
			result.clear();
		}
	}
	glFlush();
}

void keyBoard(GLubyte key, GLint x, GLint y) {
	switch (key) {
	case'T':
		if (f) {
			triangle = 1;
			std::list<Vector2dVector>::iterator it;
			for (it = triangles.begin(); it != triangles.end();++it) {
				showTriangles(*it);
			}
			triangle = 0;
			//showPolygons();
			f = !f;
			glFlush();
		}
		else {
			f = !f;
			glClear(GL_COLOR_BUFFER_BIT);
			glFlush();
		}
	}
}
void polygon(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	std::list<points>::iterator it;
	static points endPt1, endPt2, firstPt;
	static std::list<points> tl;
	if (flag == 0) {
		if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
			endPt1.x = xMouse;
			endPt1.y = height - yMouse;
			firstPt.x = endPt1.x;
			firstPt.y = endPt1.y;
			flag = 1;
			tl.push_back(endPt1);
			glutDetachMenu(GLUT_RIGHT_BUTTON);
		}
	}
	else {
		if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
			endPt2.x = xMouse;
			endPt2.y = height - yMouse;
			tl.push_back(endPt2);
			counter = counter + 1;;
			if (counter > 2) {
				if (intersect(tl, counter)) {
					if (erase(tl) == 0) {
						glutAttachMenu(GLUT_RIGHT_BUTTON);
						flag = 0;
						tl.clear();
						counter = 0;
						glutMouseFunc(NULL);
						return;
					}
				}
			}
			drawLine(endPt1, endPt2);
			endPt1 = endPt2;
		}
		else {
			if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN) {
				glutAttachMenu(GLUT_RIGHT_BUTTON);
				flag = 0;
				drawLine(firstPt, endPt2);
				tl.push_back(firstPt);
				firstPt.x = -1;
				firstPt.y = -1;
				tl.push_back(firstPt);
				triangulate(tl);
				save(tl);
				drawPolygon();
				tl.clear();
				counter = 0;
				glutMouseFunc(NULL);
			}
		}
	}
	glFlush();
}
void newPolygons(std::list<points> &temp, Vector2dVector p) {
	static points point;
	static std::list<points> t;t.clear();
	for (int i = 0;i < p.size();i++) {
		point.x = p[i].GetX();
		point.y = p[i].GetY();//new polygons after clipping
		temp.push_back(point);
		t.push_back(point);
	}
	temp.push_back(point);
	t.push_back(point);
	point.x = -1;point.y = -1;
	t.push_back(point);
	triangulate(t);
	temp.push_back(point);
}

void clip(points p1, points p2) {

	std::list<points>::iterator it;
	static std::list<points> temp;
	static Vector2dVector p,old;
	int clipper[4][2] = { {p1.x,p1.y},{p1.x,p2.y},{p2.x,p2.y},{p2.x,p1.y}};
	triangles.clear();temp.clear();
	for (it = List.begin(); it != List.end();++it) {
		if ((*it).x != -1) {
			float k = (*it).x;
			float l = (*it).y;
			p.push_back(Vector2d(k, l));
		}
		else {
			p.pop_back();
			old = p;
			Cliping::suthHodgClip(p,p.size(),clipper,4);
			if (!p.empty()) {
				newPolygons(temp, p);
				p.clear();
				old.clear();
			}
			else {
				newPolygons(temp, old);
				p.clear();
				old.clear();
			}
		}
	}
	List.clear();
	List = temp;
	a = 0;b = 0;b = 0;
	//showPolygons();
	glFlush();
}
void getClipper(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	static points minp, maxp,pa,pb;
	
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		if (z == 0) {
			minp.x = xMouse;
			minp.y = height - yMouse;z = 1;
		}
		else {
			maxp.x = xMouse;
			maxp.y = height - yMouse;z = 0;
			pa.x = maxp.x;
			pa.y = minp.y;
			pb.x = minp.x;
			pb.y = maxp.y;
			drawLine(maxp,pa);
			drawLine(pa,minp);
			drawLine(minp,pb);
			drawLine(pb, maxp);
			clip(minp, maxp);
			glutMouseFunc(NULL);
		}
	}
	glFlush();
}

void submenu(GLint selectedOption) {
	switch (selectedOption) {
	case 1: exit(-1); break;
	case 2: glutMouseFunc(polygon);break;
	case 3: glutMouseFunc(getClipper);break;
	}
	glutPostRedisplay();
}
void submenu1(GLint selectedOption) {
	switch (selectedOption) {
	case 1://red
		a = 1.0f;b = 0.0f;c = 0.0f;
		glutMouseFunc(NULL);
		break;
	case 2://blue
		a = 0.0f;b = 0.0f;c = 1.0f;
		glutMouseFunc(NULL);
		break;
	case 3://green
		a = 0.0f;b = 1.0f;c = 0.0f;
		glutMouseFunc(NULL);
		break;
	case 4://yellow
		a = 1.0f;b = 1.0f;c = 0.0f;
		glutMouseFunc(NULL);
		break;
	case 5://pink
		a = 1.0f;b = 0.0f;c = 1.0f;
		glutMouseFunc(NULL);
		break;
	case 6://Dark_gray
		a = 0.25f;b = 0.25f;c = 0.25f;
		glutMouseFunc(NULL);
		break;
	case 7://Light_gray
		a = 0.75f;b = 0.75f;c = 0.75f;
		glutMouseFunc(NULL);
		break;
	case 8://Brown
		a = 0.60f;b = 0.40f;c = 0.12f;
		glutMouseFunc(NULL);
		break;
	case 9://Barney Purple
		a = 0.60f;b = 0.40f;c = 0.70f;
		glutMouseFunc(NULL);
		break;
	case 10://Pastel Pink
		a = 0.98f;b = 0.04f;c = 0.7f;
		glutMouseFunc(NULL);
		break;
	case 11://Pumpkin orange
		a = 0.98f;b = 0.625;c = 0.12f;
		glutMouseFunc(NULL);
		break;
	case 12://Gold
		a = 1.0f;b = 0.7f;c = 0.0f;
		glutMouseFunc(NULL);
		break;
	case 13://White
		a = 1.0f;b = 1.0f;c = 1.0f;
		glutMouseFunc(NULL);
		break;
	case 14://Black
		a = 0.0f;b = 0.0f;c = 0.0f;
		glutMouseFunc(NULL);
		break;
	}
	glutPostRedisplay();
}
void submenu2(GLint selectedOption) {
	switch (selectedOption) {
	case 1://red
		af = 1.0f;bf = 0.0f;cf = 0.0f;
		glutMouseFunc(NULL);
		break;
	case 2://blue
		af = 0.0f;bf = 0.0f;cf = 1.0f;
		glutMouseFunc(NULL);
		break;
	case 3://green
		af = 0.0f;bf = 1.0f;cf = 0.0f;
		glutMouseFunc(NULL);
		break;
	case 4://yellow
		af = 1.0f;bf = 1.0f;cf = 0.0f;
		glutMouseFunc(NULL);
		break;
	case 5://pink
		af = 1.0f;bf = 0.0f;cf = 1.0f;
		glutMouseFunc(NULL);
		break;
	case 6://Dark_gray
		af = 0.25f;bf = 0.25f;cf = 0.25f;
		glutMouseFunc(NULL);
		break;
	case 7://Light_gray
		af = 0.75f;bf = 0.75f;cf = 0.75f;
		glutMouseFunc(NULL);
		break;
	case 8://Brown
		af = 0.60f;bf = 0.40f;cf = 0.12f;
		glutMouseFunc(NULL);
		break;
	case 9://Barney Purple
		af = 0.60f;bf = 0.40f;cf = 0.70f;
		glutMouseFunc(NULL);
		break;
	case 10://Pastel Pink
		af = 0.98f;bf = 0.04f;cf = 0.7f;
		glutMouseFunc(NULL);
		break;
	case 11://Pumpkin orange
		af = 0.98f;bf = 0.625;cf = 0.12f;
		glutMouseFunc(NULL);
		break;
	case 12://Gold
		af = 1.0f;bf = 0.7f;cf = 0.0f;
		glutMouseFunc(NULL);
		break;
	case 13://White
		af = 1.0f;bf = 1.0f;cf = 1.0f;
		glutMouseFunc(NULL);
		break;
	case 14://Black
		af = 0.0f;bf = 0.0f;cf = 0.0f;
		glutMouseFunc(NULL);
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {

	GLint subMenu;
	GLint subMenu1;
	GLint subMenu2;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);

	glutCreateWindow("An example of openGL Program");

	subMenu = glutCreateMenu(submenu);
	glutAddMenuEntry("EXIT", 1);
	glutAddMenuEntry("POLYGON", 2);
	glutAddMenuEntry("CLIPPING", 3);

	subMenu1 = glutCreateMenu(submenu1);
	glutAddMenuEntry("RED", 1);
	glutAddMenuEntry("BLUE", 2);
	glutAddMenuEntry("GREEN", 3);
	glutAddMenuEntry("YELLOW", 4);
	glutAddMenuEntry("PINK", 5);
	glutAddMenuEntry("DARK GRAY", 6);
	glutAddMenuEntry("LIGHT GRAY", 7);
	glutAddMenuEntry("BROWN", 8);
	glutAddMenuEntry("BARNEY PURPLE", 9);
	glutAddMenuEntry("PASTEL PINK", 10);
	glutAddMenuEntry("PUMPKIN ORANGE", 11);
	glutAddMenuEntry("GOLD", 12);
	glutAddMenuEntry("WHITE", 13);
	glutAddMenuEntry("BLACK", 14);

	subMenu2 = glutCreateMenu(submenu2);
	glutAddMenuEntry("RED", 1);
	glutAddMenuEntry("BLUE", 2);
	glutAddMenuEntry("GREEN", 3);
	glutAddMenuEntry("YELLOW", 4);
	glutAddMenuEntry("PINK", 5);
	glutAddMenuEntry("DARK GRAY", 6);
	glutAddMenuEntry("LIGHT GRAY", 7);
	glutAddMenuEntry("BROWN", 8);
	glutAddMenuEntry("BARNEY PURPLE", 9);
	glutAddMenuEntry("PASTEL PINK", 10);
	glutAddMenuEntry("PUMPKIN ORANGE", 11);
	glutAddMenuEntry("GOLD", 12);
	glutAddMenuEntry("WHITE", 13);
	glutAddMenuEntry("BLACK", 14);

	glutCreateMenu(mainMenu);
	glutAddSubMenu("ACTION", subMenu);
	glutAddSubMenu("LINE_COLOR", subMenu1);
	glutAddSubMenu("FILL_COLOR", subMenu2);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(winReshapeFcn);
	glutKeyboardFunc(keyBoard);
	//glutReshapeWindow(500, 500);
	glutMainLoop();
	return (EXIT_SUCCESS);
}
