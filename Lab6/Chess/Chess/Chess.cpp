#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GLEW/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <lib3ds.h>

//починить вращение

using namespace std;

//освобождать память
const Lib3dsFile* MODEL_BISHOP = lib3ds_file_open("models/Bishop.3ds");
const Lib3dsFile* MODEL_PAWN= lib3ds_file_open("models/Pawn.3ds");
const Lib3dsFile* MODEL_KING = lib3ds_file_open("models/King.3ds");
const Lib3dsFile* MODEL_QUEEN = lib3ds_file_open("models/Queen.3ds");
const Lib3dsFile* MODEL_ROOK = lib3ds_file_open("models/Rook.3ds");
const Lib3dsFile* MODEL_KNIGHT = lib3ds_file_open("models/Knight.3ds");

float rotX = -65.0f;
float rotY = 0.0f;

const GLfloat FIGURE_SIZE = 0.025;

void LoadTexture(GLuint currentTexture, const char* path) {
	int width, height, nrChannels;
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

	//проверка ошибок,
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

void DrawFigure(const Lib3dsFile* model) {
	for (int i = 0; i < model->nmeshes; i++) {
		Lib3dsMesh* mesh = model->meshes[i];

		glBegin(GL_TRIANGLES);
		for (int j = 0; j < mesh->nfaces; j++) {
			Lib3dsFace* face = &mesh->faces[j];
			for (int k = 0; k < 3; k++) {
				int index = face->index[k];
				glTexCoord2fv(mesh->texcos[index]);
				glVertex3fv(mesh->vertices[index]);
			}
		}
		glEnd();
	}
}

void DrawPawns()
{
	//использовать циклы
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 1);
		glTranslatef(0.85, 1.16, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_PAWN);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 1);
		glTranslatef(0.85, 0.82, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_PAWN);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 1);
		glTranslatef(0.85, 0.5, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_PAWN);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 1);
		glTranslatef(0.85, 0.16, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_PAWN);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 1);
		glTranslatef(0.85, -0.16, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_PAWN);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 1);
		glTranslatef(0.85, -0.5, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_PAWN);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 1);
		glTranslatef(0.85, -0.82, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_PAWN);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 1);
		glTranslatef(0.85, -1.16, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_PAWN);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 2);
		glTranslatef(-0.85, 1.16, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_PAWN);
	glPopMatrix();

	//В программе не должно быть магических констант

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 2);
		glTranslatef(-0.85, 0.82, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
	DrawFigure(MODEL_PAWN);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 2);
		glTranslatef(-0.85, 0.5, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_PAWN);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 2);
		glTranslatef(-0.85, 0.16, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_PAWN);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 2);
		glTranslatef(-0.85, -0.16, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_PAWN);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 2);
		glTranslatef(-0.85, -0.5, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_PAWN);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 2);
		glTranslatef(-0.85, -0.82, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_PAWN);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 2);
		glTranslatef(-0.85, -1.16, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_PAWN);
	glPopMatrix();
}

void DrawQueens()
{
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 1);
		glTranslatef(1.2, -0.16, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_QUEEN);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 2);
		glTranslatef(-1.2, 0.16, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_QUEEN);
	glPopMatrix();
}

void DrawKings()
{
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 1);
		glTranslatef(1.2, 0.16, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_KING);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 2);
		glTranslatef(-1.2, -0.16, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_KING);
	glPopMatrix();
}

void DrawRooks()
{
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 1);
		glTranslatef(1.2, 1.16, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_ROOK);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 1);
		glTranslatef(1.2, -1.16, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_ROOK);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 2);
		glTranslatef(-1.2, 1.16, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_ROOK);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 2);
		glTranslatef(-1.2, -1.16, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_ROOK);
	glPopMatrix();
}

void DrawKnights()
{
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 1);
		glTranslatef(1.2, 0.82, 0.005);
		glScalef(FIGURE_SIZE + 0.004, FIGURE_SIZE + 0.004, FIGURE_SIZE + 0.004);
		DrawFigure(MODEL_KNIGHT);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 1);
		glTranslatef(1.2, -0.82, 0.005);
		glScalef(FIGURE_SIZE + 0.004, FIGURE_SIZE + 0.004, FIGURE_SIZE + 0.004);
		DrawFigure(MODEL_KNIGHT);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 2);
		glTranslatef(-1.2, 0.82, 0.005);
		glScalef(FIGURE_SIZE + 0.004, FIGURE_SIZE + 0.004, FIGURE_SIZE + 0.004);
		DrawFigure(MODEL_KNIGHT);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 2);
		glTranslatef(-1.2, -0.82, 0.005);
		glScalef(FIGURE_SIZE + 0.004, FIGURE_SIZE + 0.004, FIGURE_SIZE + 0.004);
		DrawFigure(MODEL_KNIGHT);
	glPopMatrix();
}

void DrawBishops()
{
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 1);
		glTranslatef(1.2, 0.5, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_BISHOP);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 1);
		glTranslatef(1.2, -0.5, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_BISHOP);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 2);
		glTranslatef(-1.2, 0.5, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_BISHOP);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 2);
		glTranslatef(-1.2, -0.5, 0.005);
		glScalef(FIGURE_SIZE, FIGURE_SIZE, FIGURE_SIZE);
		DrawFigure(MODEL_BISHOP);
	glPopMatrix();
}

void DrawFigures()
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
		DrawBishops();
		DrawKings();
		DrawKnights();
		DrawPawns();
		DrawQueens();
		DrawRooks();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void DrawBoard()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 3);

	glPushMatrix();
	glScalef(1.5, 1.5, 1.5);
		glBegin(GL_QUADS);
			glNormal3f(-1.0f, -1.0f, 1.0f);
			glTexCoord2f(1, 0);
			glVertex3f(-1, -1, 0);
			glNormal3f(-1.0f, 1.0f, 1.0f);
			glTexCoord2f(1, 1);
			glVertex3f(-1, 1, 0);
			glNormal3f(1.0f, 1.0f, 1.0f);
			glTexCoord2f(0, 1);
			glVertex3f(1, 1, 0);
			glNormal3f(1.0f, -1.0f, 1.0f);
			glTexCoord2f(0, 0);
			glVertex3f(1, -1, 0);
		glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void Display() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 4, 0, 0, 0, 0, 1, 0);

	GLfloat lightPosition[] = { 0.0f, 0.0f, 4.0f, 0.0f };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glPushMatrix();
		glTranslatef(0, -0.5, 0);
		glRotatef(rotX, 1, 0, 0);
		glRotatef(rotY, 0, 1, 0);
		DrawBoard();
		DrawFigures();
	glPopMatrix();

	glutSwapBuffers();
}

void Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		glutIdleFunc(NULL);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		glutIdleFunc(Display);
	}
}

void Motion(int x, int y) {
	rotX = -65 + (float)(y - 300) / 3.0f;
	rotY = (float)(x - 400) / 3.0f;
	glutPostRedisplay();
}

void Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)w / h, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Chess King");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	LoadTexture(1, "textures/white_figure.jpg");
	LoadTexture(2, "textures/black_figure.jpg");
	LoadTexture(3, "textures/Board.jpg");

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop();

	return 0;
}