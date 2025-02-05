#include <GLEW/glew.h>
#include <GL/glut.h>
#include <cmath>
#include <vector>

using namespace std;

const float M_PI = 3.14159265358979323846;

const int NUM_SECTORS = 6;
const float RADIUS = 0.8;
const float START_ANGLE = 0;
const float SECTOR_ANGLE = 2 * M_PI / NUM_SECTORS;

float angle = 0;

const vector<vector <GLfloat>> COLORS = {
	{1.0, 0.0, 0.0},
	{0.0, 1.0, 0.0},
	{0.0, 0.0, 1.0},
	{1.0, 1.0, 0.0},
	{1.0, 0.0, 1.0}, 
	{0.0, 1.0, 1.0}
};

void DrawSector(float start_angle, float end_angle, vector<GLfloat> color, float offset) {
	
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_TRIANGLE_FAN);//верх
		glNormal3f(offset, offset, 0.1);
		glVertex3f(offset, offset, 0.1);
		for (float angle = start_angle; angle <= end_angle; angle += 0.01) {
			float x = RADIUS * cos(angle) + offset;
			float y = RADIUS * sin(angle) + offset;
			glNormal3f(x, y, 0.1);
			glVertex3f(x, y, 0.1);
		}
		glNormal3f(cos(end_angle) + offset, sin(end_angle) + offset, 0.1);
		glVertex3f(RADIUS * cos(end_angle) + offset, RADIUS * sin(end_angle) + offset, 0.1);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);//низ
		glNormal3f(offset, offset, -0.1);
		glVertex3f(offset, offset, -0.1);
		for (float angle = start_angle; angle <= end_angle; angle += 0.01) {
			float x = RADIUS * cos(angle) + offset;
			float y = RADIUS * sin(angle) + offset;
			glNormal3f(x, y, -0.1);
			glVertex3f(x, y, -0.1);
		}
		glNormal3f(cos(end_angle) + offset, sin(end_angle) + offset, -0.1);
		glVertex3f(RADIUS * cos(end_angle) + offset, RADIUS * sin(end_angle) + offset, -0.1);
	glEnd();

	glBegin(GL_QUAD_STRIP);//задняя стенка
		for (float angle = start_angle; angle <= end_angle; angle += 0.01) {
			float x = RADIUS * cos(angle) + offset;
			float y = RADIUS * sin(angle) + offset;
			glNormal3f(x, y, 0.1);
			glVertex3f(x, y, 0.1);
			glNormal3f(x, y, -0.1);
			glVertex3f(x, y, -0.1);
		}
		glNormal3f(cos(end_angle) + offset, sin(end_angle) + offset, 0.1);
		glVertex3f(RADIUS * cos(end_angle) + offset, RADIUS * sin(end_angle) + offset, 0.1);
		glNormal3f(cos(end_angle) + offset, sin(end_angle) + offset, -0.1);
		glVertex3f(RADIUS * cos(end_angle) + offset, RADIUS * sin(end_angle) + offset, -0.1);
	glEnd();

	glBegin(GL_QUAD_STRIP);//левая стенка
		glNormal3f(offset, offset, 0.1);
		glVertex3f(offset, offset, 0.1);

		glNormal3f(offset, offset, -0.1);
		glVertex3f(offset, offset, -0.1);

		glNormal3f(cos(start_angle) + offset, sin(start_angle) + offset, 0.1);
		glVertex3f(RADIUS * cos(start_angle) + offset, RADIUS * sin(start_angle) + offset, 0.1);

		glNormal3f(cos(start_angle) + offset, sin(start_angle) + offset, -0.1);
		glVertex3f(RADIUS * cos(start_angle) + offset, RADIUS * sin(start_angle) + offset, -0.1);
	glEnd();

	glBegin(GL_QUAD_STRIP);//правая стенка
		glNormal3f(offset, offset, 0.1);
		glVertex3f(offset, offset, 0.1);

		glNormal3f(offset, offset, -0.1);
		glVertex3f(offset, offset, -0.1);

		glNormal3f(cos(end_angle) + offset, sin(end_angle) + offset, 0.1);
		glVertex3f(RADIUS * cos(end_angle) + offset, RADIUS * sin(end_angle) + offset, 0.1);

		glNormal3f(cos(end_angle) + offset, sin(end_angle) + offset, -0.1);
		glVertex3f(RADIUS * cos(end_angle) + offset, RADIUS * sin(end_angle) + offset, -0.1);
	glEnd();
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);

	glRotatef(angle, 0, 1, 0);
	glPushMatrix();
	glRotatef(-45, 1.0, 0.0, 0.0);

	for (int i = 0; i < NUM_SECTORS; ++i) {
		float offSet = 0;
		vector<GLfloat> tempColor = COLORS[i];
		float start_angle_i = START_ANGLE + i * SECTOR_ANGLE;
		float end_angle_i = START_ANGLE + (i + 1) * SECTOR_ANGLE;
		if (i == 0) {
			offSet = 0.1;
			start_angle_i += 5 / RADIUS - offSet / 8;
			end_angle_i += 5 / RADIUS - offSet / 8;
		}
		if (i == 3) {
			offSet = -0.1;
			start_angle_i += 5 / RADIUS - offSet / 20;
			end_angle_i += 5 / RADIUS - offSet / 20;
		}
		DrawSector(start_angle_i, end_angle_i, tempColor, offSet);
	}
	glPopMatrix();
	glutSwapBuffers();
}

void Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)w / h, 0.1, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_position[] = { 0.0, 0.0, 2.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
}
void Update(int value) {
	glutPostRedisplay();
	glutTimerFunc(16, Update, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3D Круговая диаграмма");
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);

	glutTimerFunc(0, Update, 0);
	glutMainLoop();
	return 0;
}