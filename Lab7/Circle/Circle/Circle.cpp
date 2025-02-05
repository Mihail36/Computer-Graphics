#include <GLEW/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
// для чего служит location
const char* vertexShaderSource = R"(
    #version 330 core
	layout (location = 0) in vec2 position;
	uniform float radius;
	uniform float centerX;
	uniform float centerY;

	void main()
	{
		float angle = position.x * 3.14159f / 180.0f;
		float x = centerX + radius * cos(angle);
		float y = centerY + radius * sin(angle);

		gl_Position = vec4(x, y, 0.0, 1.0);
	}
)";

//что такое фрагмент
const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 color;
    void main()
    {
        color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
)";


const int WIDTH = 640;
const int HEIGHT = 480;

GLuint vertexShader, fragmentShader, shaderProgram;

vector <float> InitCoordsCircle() {
	vector <float> res;

	for (int i = 180; i >= 0; i--)
	{
		res.push_back(i * -1);
		res.push_back(0);
	}

	for (int i = 1; i < 181; i++)
	{
		res.push_back(i);
		res.push_back(0);
	}

	return res;
}

void init() {
	glewInit();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint ok;
	GLchar log[2000];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &ok);
	if (!ok)
	{
		glGetShaderInfoLog(vertexShader, 2000, NULL, log);
		printf("%s\n", log);
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &ok);
	if (!ok)
	{
		glGetShaderInfoLog(fragmentShader, 2000, NULL, log);
		printf("%s\n", log);
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &ok);
	if (!ok)
	{
		glGetProgramInfoLog(shaderProgram, 2000, NULL, log);
		printf("%s\n", log);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
// поправить программу так, чтоб окружность сохраняла свою форму
// уметь объяснить какие вид есть как отличаются.
// каким образом задаются эти значения из основной программ в шейдерную
void Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)w / h, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgram);

	GLint radiusLoc = glGetUniformLocation(shaderProgram, "radius");
	GLint centerXLoc = glGetUniformLocation(shaderProgram, "centerX");
	GLint centerYLoc = glGetUniformLocation(shaderProgram, "centerY");
	glUniform1f(radiusLoc, 0.5f);
	glUniform1f(centerXLoc, 0.0f);
	glUniform1f(centerYLoc, 0.0f);

	vector<float> vertices = InitCoordsCircle();

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < vertices.size(); i++) {
		glColor3f(1, 0, 0);
		if (!(i*2 + 1 >= vertices.size()))
		{
			glVertex2f(vertices[i * 2], vertices[i * 2 + 1]);
		}
	}
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);

	glutCreateWindow("Black Circle");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(Reshape);
	glutMainLoop();

	return 0;
}