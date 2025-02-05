#include <GL/glut.h>
#include <cmath>

const float VERTICES[] = {
	-1,-1,0,
	 0,-1,1,
	 1,-1,0,
	 0,-1,-1,
	-1,0,-1,
	 1,0,-1,
	 1,1,0,
	 1,0,1,
	 0,1,-1,
	 0,1,1,
	-1,1,0,
	-1,0,1
};

const GLuint TRIANGLE_FACES[] = {
	11, 10, 9,
	9, 7, 6,
	0, 1, 11,
	1, 2 , 7,
	4, 10, 8,
	8, 6, 5,
	0, 4, 3,
	3, 5, 2
};

const GLuint SQUARE_FACES[] = {
	11, 1, 7, 9,
	4, 8, 5, 3,
	7, 2, 5, 6,
	0, 11, 10, 4,
	1, 0, 3, 2,
	10, 9, 6, 8
};

float rotationAngle = 0.0f;
float width = 800;
float height = 600;

void Draw() {
	glRotatef(rotationAngle, 1.0f, 1.0f, 1.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &VERTICES);

	glColor3f(1, 0, 0);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, &TRIANGLE_FACES);

	glColor3f(0, 1, 0);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, &SQUARE_FACES);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width/400, width/400, -height/300, height/300, -2, 2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Draw();

	rotationAngle += 1.0f;

	glutSwapBuffers();
}

void Update(int value) {
	glutPostRedisplay();
	glutTimerFunc(16, Update, 0);
}

void Init() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

void Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)w / h, 0.1, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Кубооктаэдр");

	Init();

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutTimerFunc(0, Update, 0);

	glutMainLoop();

	return 0;
}
// Сделать так, чтобы ширина и высота кубооктаэдра были одинаковыми
