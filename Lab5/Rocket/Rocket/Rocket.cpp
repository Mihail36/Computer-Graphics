#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GLEW/glew.h>
#include <GL/glut.h>
#include <math.h>

const int SLICES = 100; 

const const char* PATH_TEXTURE = "assets/rocket.jpg";
const float CAMERA_ROTATION_SPEED = 0.3;

float angle_rotate = 0;

float angle_camera_x = 0.0;
float angle_camera_y = 0.0;
float angle_camera_z = 0.0;

bool isMousePressed = false;
int mouseX = 0, mouseY = 0;

void LoadTexture(GLuint currentTexture, const char* path) {
	int width, height, nrChannels;
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

	glGenTextures(1, &currentTexture);

	glBindTexture(GL_TEXTURE_2D, currentTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPLACE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

void DrawCylinder(GLfloat radius, GLfloat height) {
	glBindTexture(GL_TEXTURE_2D, 1); 
	glBegin(GL_TRIANGLE_STRIP); // стенка
	for (int i = 0; i <= SLICES; i++) {
		GLfloat theta = 2.0 * 3.14159265358979323846 * float(i) / float(SLICES);
		GLfloat x = radius * cos(theta);
		GLfloat y = radius * sin(theta);
		glNormal3f(x / radius, y / radius, height);
		glTexCoord2f(float(i) / float(SLICES), -1.0);
		glVertex3f(x, y, height);

		glNormal3f(x / radius, y / radius, 0);
		glTexCoord2f(float(i) / float(SLICES), 0.0);
		glVertex3f(x, y, 0.0);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);// верх
	glVertex3f(0.0, 0.0, height);
	for (int i = 0; i <= SLICES; i++) {
		GLfloat theta = 2.0 * 3.14159265358979323846 * float(i) / float(SLICES);
		GLfloat x = radius * cos(theta);
		GLfloat y = radius * sin(theta);
		glNormal3f(x / radius, y / radius, height);
		glTexCoord2f(0.5 + 0.5 * cos(theta), 0.5 + 0.5 * sin(theta));
		glVertex3f(x, y, height);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN); // низ
	glVertex3f(0.0, 0.0, 0);
	for (int i = 0; i <= SLICES; i++) {
		GLfloat theta = 2.0 * 3.14159265358979323846 * float(i) / float(SLICES);
		GLfloat x = radius * cos(theta);
		GLfloat y = radius * sin(theta);
		glNormal3f(x / radius, y / radius, 0);
		glTexCoord2f(0.5 + 0.5 * cos(theta), 0.5 + 0.5 * sin(theta));
		glVertex3f(x, y, 0);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
}

void DrawCone(GLfloat radius, GLfloat height , GLfloat x_center, GLfloat y_center) {
	glBindTexture(GL_TEXTURE_2D, 1);
	glBegin(GL_TRIANGLE_FAN); // бок
	glNormal3f(x_center, y_center, height);
	glVertex3f(x_center, y_center, height);
	for (int i = 0; i <= SLICES; i++) {
		GLfloat theta = 2.0 * 3.14159265358979323846 * float(i) / float(SLICES);
		GLfloat x = radius * cos(theta);
		GLfloat y = radius * sin(theta);
		glNormal3f(x / radius, y / radius, 0);
		glTexCoord2f(0.5 + 0.5 * cos(theta), 0.5 + 0.5 * sin(theta)); 
		glVertex3f(x, y, 0.0);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN); // низ
	glVertex3f(0.0, 0.0, 0);
	for (int i = 0; i <= SLICES; i++) {
		GLfloat theta = 2.0 * 3.14159265358979323846 * float(i) / float(SLICES);
		GLfloat x = radius * cos(theta);
		GLfloat y = radius * sin(theta);
		glNormal3f(x / radius, y / radius, 0);
		glTexCoord2f(0.5 + 0.5 * cos(theta), 0.5 + 0.5 * sin(theta));
		glVertex3f(x, y, 0);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0); 
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 4, 0, 0, 0, 0, 1, 0);

	GLfloat lightPosition[] = { 0.0, 0.0, 5.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	glTranslatef(0, -0.5, 0);

	/*glRotatef(angle_rotate, 1, 0, 1);*/
	glRotatef(angle_camera_z, 0, 1, 1);
	glRotatef(angle_camera_y, 1, 0, 0);

	glColor3f(1, 1, 1);
	glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		
		glPushMatrix();
			glTranslatef(0, 0, 2);
			DrawCone(0.4, 1.0, 0, 0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 0, 1);
			DrawCylinder(0.4, 1.0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 0, 0);
			DrawCylinder(0.4, 1.0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 0, -1);
			DrawCylinder(0.4, 1.0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.5, -0.4, -1.1);
			DrawCone(0.25, 1.0, 0.25, 0.2);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.5, -0.4, -1.1);
			DrawCone(0.25, 1.0, -0.25, 0.2);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.5, 0.4, -1.1);
			DrawCone(0.25, 1.0, 0.25, -0.2);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.5, 0.4, -1.1);
			DrawCone(0.25, 1.0, -0.25, -0.2);
		glPopMatrix();
	glPopMatrix();
	angle_rotate++;
	glFlush();
}

void Init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

void Update(int value) {
	glutPostRedisplay();
	glutTimerFunc(16, Update, 0);
}

void Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)w / h, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void MouseFunction(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			isMousePressed = true;
			mouseX = x;
			mouseY = y;
		}
		else if (state == GLUT_UP) {
			isMousePressed = false;
		}
	}
}

void MotionFunction(int x, int y) {
	if (isMousePressed) {
		float deltaX = (mouseX - x) * CAMERA_ROTATION_SPEED;
		float deltaY = (y - mouseY) * CAMERA_ROTATION_SPEED;

		angle_camera_x += deltaX;
		angle_camera_y += deltaY;
		angle_camera_z += deltaX + deltaY;

		mouseX = x;
		mouseY = y;
		glutPostRedisplay();
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Green Cylinder");
	Init();
	LoadTexture(1, PATH_TEXTURE);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(MouseFunction);
	glutMotionFunc(MotionFunction);
	glutTimerFunc(0, Update, 0);
	glutMainLoop();
	return 0;
}
// исправить освещение 
// исправить натяжение текстур