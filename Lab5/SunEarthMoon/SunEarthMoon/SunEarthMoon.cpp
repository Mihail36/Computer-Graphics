#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GLEW/glew.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

const float PI = 3.14159265358979323846;
const float EARTH_RADIUS = 1.0;
const float MOON_RADIUS = 0.272;
const float SUN_RADIUS = 5.0;
const float EARTH_MOON_DIST = 2.0;
const float EARTH_SUN_DIST = 10.0;
const float DAY_IN_SECONDS = 500.0;
const int SKYBOX_SIZE = 5;

const const char* TEX_SKYBOX_PATH[] = {
	"assets/Galaxy_RT.png",
	"assets/Galaxy_LT.png",
	"assets/Galaxy_UP.png",
	"assets/Galaxy_DN.png",
	"assets/Galaxy_FT.png",
	"assets/Galaxy_BK.png"
};
const float VERTICES_CUBE[] = {
	-1,-1,1, //0
	1,-1,1,	 //1
	1,1,1,	 //2
	-1,1,1,	 //3
	-1,-1,-1,//4
	1,-1,-1, //5
	1,1,-1,  //6
	-1,1,-1  //7
};

const GLuint FACES_CUBE[] = {
	 4, 7, 3, 0,
	 5, 1, 2, 6,
	 4, 0, 1, 5,
	 7, 6, 2, 3,
	 0, 3, 2, 1,
	 4, 5, 6, 7
};

const GLfloat TEX_VERTICES_CUBE[] = {
	1, 0, 0, 0, 0, 1, 1, 1, // left
	1, 0, 0, 0, 0, 1, 1, 1, // right
	0, 1, 0, 0, 1, 0, 1, 1, // bottom
	0, 0, 1, 0, 1, 1, 0, 1, // top
	0, 1, 0, 0, 1, 0, 1, 1, // front
	0, 0, 1, 0, 1, 1, 0, 1  //back
};

const const char* PLANET_TEXTURE_PATH[] = {
	"assets/sun_texture.jpg", 
	"assets/earth_texture.jpg", 
	"assets/moon_texture.jpg"
};

float angle_earth = 0.0;
float angle_moon = 0.0;

float angle_camera_x = 0.0;
float angle_camera_y = 0.0;
float angle_camera_z = 20.0;

bool isMousePressed = false;
int mouseX = 0, mouseY = 0;
float cameraRotationSpeed = 0.1;


void LoadTexture(GLuint currentTexture, const char* pathTexture) {
	int width, height, nrChannels;
	unsigned char *data = stbi_load(pathTexture, &width, &height, &nrChannels, 0);

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


void LoadTextures() {
	for (GLuint i = 1; i < 9; i++)
	{
		if (i <= 6)
			LoadTexture(i, TEX_SKYBOX_PATH[i-1]);
		else
			LoadTexture(i, PLANET_TEXTURE_PATH[i - 7]);
	}
	LoadTexture(10, PLANET_TEXTURE_PATH[2]);
}

void DrawSkybox() {

	int temp = 8;
	int handle = 0;
	GLfloat temp_vertices[24];

	for (int i = 0; i < 24; i++)
	{
		temp_vertices[i] = VERTICES_CUBE[i] * SKYBOX_SIZE * temp;
	}

	int textures = 1;

	glPushMatrix();
	glColor3f(1, 1, 1);
	for (int i = 0; i < 24; i+=4)
	{
		glBindTexture(GL_TEXTURE_2D, textures);
		glBegin(GL_QUADS);
		{
			for (int j = 0; j < 4; j++)
			{
				glTexCoord2f(TEX_VERTICES_CUBE[j + handle], TEX_VERTICES_CUBE[j + handle + 1]);
				glVertex3f(temp_vertices[FACES_CUBE[i+j]*3], temp_vertices[FACES_CUBE[i + j] * 3 + 1], temp_vertices[FACES_CUBE[i + j] * 3 + 2]);
				handle++;
			}
		}
		glEnd();
		handle += 4;
		textures++;
	}
	glPopMatrix();

}

void DrawSphere(float radius, int slices, int stacks) {
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= slices; i++) {
		float theta = 2 * PI * i / slices;
		float nextTheta = 2 * PI * (i + 1) / slices;

		for (int j = 0; j <= stacks; j++) {
			float phi = PI * j / stacks;
			float nextPhi = PI * (j + 1) / stacks;

			glNormal3f(cos(theta) * sin(phi), sin(theta) * sin(phi), cos(phi));
			glTexCoord2f(i / (float)slices, j / (float)stacks);
			glVertex3f(cos(theta) * sin(phi) * radius, sin(theta) * sin(phi) * radius, cos(phi) * radius);

			glNormal3f(cos(nextTheta) * sin(phi), sin(nextTheta) * sin(phi), cos(phi));
			glTexCoord2f((i + 1) / (float)slices, j / (float)stacks);
			glVertex3f(cos(nextTheta) * sin(phi) * radius, sin(nextTheta) * sin(phi) * radius, cos(phi) * radius);

			glNormal3f(cos(theta) * sin(nextPhi), sin(theta) * sin(nextPhi), cos(nextPhi));
			glTexCoord2f(i / (float)slices, (j + 1) / (float)stacks);
			glVertex3f(cos(theta) * sin(nextPhi) * radius, sin(theta) * sin(nextPhi) * radius, cos(nextPhi) * radius);

			glNormal3f(cos(nextTheta) * sin(nextPhi), sin(nextTheta) * sin(nextPhi), cos(nextPhi));
			glTexCoord2f((i + 1) / (float)slices, (j + 1) / (float)stacks);
			glVertex3f(cos(nextTheta) * sin(nextPhi) * radius, sin(nextTheta) * sin(nextPhi) * radius, cos(nextPhi) * radius);
		}
	}
	glEnd();
}

void DrawSun(int currentTexture) {
	GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glPushMatrix();
		glRotatef(angle_earth * 180 / PI / 3, 0, 1, 0);
		glTranslatef(0, 0, 0);
		glBindTexture(GL_TEXTURE_2D, currentTexture);
		DrawSphere(SUN_RADIUS, 64, 64);
	glPopMatrix();

}

void DrawMoon(int currentTexture) {
	glPushMatrix();
		glRotatef(angle_moon * 180 / PI, 0, 1, 0);
		glTranslatef(EARTH_MOON_DIST, 0, 0);
		glBindTexture(GL_TEXTURE_2D, currentTexture);
		DrawSphere(MOON_RADIUS, 16, 16);
	glPopMatrix();
}

void DrawEarth(int currentTexture) {
	glPushMatrix();
		glRotatef(angle_earth * 180 / PI, 0, 1, 0);
		glTranslatef(EARTH_SUN_DIST, 0, 0);
		glRotatef(23.43, 1, 0, 0);
		glRotatef(angle_earth * 180 / PI, 0, 1, 0);
		glBindTexture(GL_TEXTURE_2D, currentTexture);
		DrawSphere(EARTH_RADIUS, 32, 32);
		currentTexture++;
		DrawMoon(currentTexture);
	glPopMatrix();

}

void Display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(angle_camera_x, angle_camera_y, angle_camera_z, 0, 0, 0, 0, 1, 0);
	DrawSkybox();
	glColor3f(1, 1, 1);
	int currentTexture = 7;
	DrawSun(currentTexture);
	currentTexture ++;
	DrawEarth(currentTexture);
	glutSwapBuffers();
}

void Idle() {
	angle_earth += 2 * PI / DAY_IN_SECONDS / 1.1;
	angle_moon += 2 * PI / DAY_IN_SECONDS * 5;
	glutPostRedisplay();
}

void Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)w / h, 1, 200);
	glMatrixMode(GL_MODELVIEW);
}

void KeyboardFunction(unsigned char key, int x, int y) {

	switch (key) {
	case 27:
		exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay();
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
		float deltaX = (x - mouseX) * cameraRotationSpeed;
		float deltaY = (y - mouseY) * cameraRotationSpeed;

		angle_camera_x += deltaX;
		angle_camera_y += deltaY;
		angle_camera_z  += deltaX + deltaY;

		if (angle_camera_x < -30)
			angle_camera_x = -30;
		else if (angle_camera_x > 30)
			angle_camera_x = 30;

		if (angle_camera_y < -30)
			angle_camera_y = -30;
		else if (angle_camera_y > 30)
			angle_camera_y = 30;

		if (angle_camera_z < -30)
			angle_camera_z = -30;
		else if (angle_camera_z > 30)
			angle_camera_z = 30;

		mouseX = x;
		mouseY = y;
		glutPostRedisplay();
	}
}

void Init() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Solar System");
	Init();
	LoadTextures();
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyboardFunction);
	glutMouseFunc(MouseFunction);
	glutMotionFunc(MotionFunction);
	glutMainLoop();
	return 0;
}
// избавиться от артефактов внутри сферы
// исправить освещение
// исправить текстурирование Земли
// исправить вращение
// исправить skybox