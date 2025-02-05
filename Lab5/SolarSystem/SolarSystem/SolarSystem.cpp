#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>


const float PI = 3.14159265358979323846;
const float EARTH_RADIUS = 1.0;
const float MOON_RADIUS = 0.272;
const float SUN_RADIUS = 5.0;
const float EARTH_MOON_DIST = 2.0;
const float EARTH_SUN_DIST = 10.0;
const float DAY_IN_SECONDS = 500.0;

float angle_earth = 0.0;
float angle_moon = 0.0;
float angle_camera = 0.0;

GLuint texture_sun = 0;
GLuint texture_earth = 0;
GLuint texture_moon = 0;


void loadTextures() {
	// Загрузка текстур из файлов
	int width, height, nrChannels;
	unsigned char* data;

	// Солнце
	data = stbi_load("sun_texture.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glGenTextures(1, &texture_sun);
		glBindTexture(GL_TEXTURE_2D, texture_sun);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}
	else {
		std::cout << "Failed to load sun texture" << std::endl;
	}

	stbi_image_free(data);
	// Земля
	data = stbi_load("earth_texture.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glGenTextures(1, &texture_earth);
		glBindTexture(GL_TEXTURE_2D, texture_earth);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else {
		std::cout << "Failed to load earth texture" << std::endl;
	}
	stbi_image_free(data);

	// Луна
	data = stbi_load("moon_texture.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glGenTextures(1, &texture_moon);
		glBindTexture(GL_TEXTURE_2D, texture_moon);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else {
		std::cout << "Failed to load moon texture" << std::endl;
	}
	stbi_image_free(data);
}

void drawSphere(float radius, int slices, int stacks) {
	glColor3f(0, 1, 0);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= slices; i++) {
		float theta = 2 * PI * i / slices;
		float nextTheta = 2 * PI * (i + 1) / slices;

		for (int j = 0; j <= stacks; j++) {
			float phi = PI * j / stacks;
			float nextPhi = PI * (j + 1) / stacks;

			glNormal3f(cos(theta) * sin(phi), sin(theta) * sin(phi), cos(phi));
			glVertex3f(cos(theta) * sin(phi) * radius, sin(theta) * sin(phi) * radius, cos(phi) * radius);

			glNormal3f(cos(nextTheta) * sin(phi), sin(nextTheta) * sin(phi), cos(phi));
			glVertex3f(cos(nextTheta) * sin(phi) * radius, sin(nextTheta) * sin(phi) * radius, cos(phi) * radius);

			glNormal3f(cos(theta) * sin(nextPhi), sin(theta) * sin(nextPhi), cos(nextPhi));
			glVertex3f(cos(theta) * sin(nextPhi) * radius, sin(theta) * sin(nextPhi) * radius, cos(nextPhi) * radius);

			glNormal3f(cos(nextTheta) * sin(nextPhi), sin(nextTheta) * sin(nextPhi), cos(nextPhi));
			glVertex3f(cos(nextTheta) * sin(nextPhi) * radius, sin(nextTheta) * sin(nextPhi) * radius, cos(nextPhi) * radius);
		}
	}
	glEnd();
}

void drawSun() {
	/* Отрисовка Солнца как точечного источника света*/
	GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 }; // Позиция источника света
	GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glRotatef(angle_camera, 0, 1, 0);

	glPushMatrix();
	glTranslatef(0, 0, 0);
	glBindTexture(GL_TEXTURE_2D, texture_sun);
	drawSphere(SUN_RADIUS, 64, 64);
	glPopMatrix();

}

void drawMoon() {
	glPushMatrix();
	glRotatef(angle_moon * 180 / PI, 0, 1, 0);
	glTranslatef(EARTH_MOON_DIST, 0, 0);
	glBindTexture(GL_TEXTURE_2D, texture_moon);
	drawSphere(MOON_RADIUS, 16, 16);
	glPopMatrix();
}

void drawEarth() {

	glPushMatrix();
	glRotatef(angle_earth * 180 / PI, 0, 1, 0);
	glTranslatef(EARTH_SUN_DIST, 0, 0);
	glRotatef(23.43, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, texture_earth);
	drawSphere(EARTH_RADIUS, 32, 32);
	drawMoon();
	glPopMatrix();

}

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(angle_camera, 0, 20, 0, 0, 0, 0, 1, 0);
	drawSun();
	drawEarth();
	glutSwapBuffers();
}

void idle() {
	angle_earth += 2 * PI / DAY_IN_SECONDS;
	angle_moon += 2 * PI / DAY_IN_SECONDS;
	glutPostRedisplay();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)w / h, 1, 100);
	glMatrixMode(GL_MODELVIEW);
}

void keyboardFunction(unsigned char key, int x, int y) {

	switch (key) {
	case 'd':
		angle_camera++;;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Solar System");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	/*loadTextures();*/
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardFunction);
	glutMainLoop();
	return 0;
}