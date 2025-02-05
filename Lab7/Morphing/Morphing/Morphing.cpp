#include <GLEW/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace std;

//Замечания: 
//1) Поменять отрисовку сферы, не использовать glutSolidSphere
//2) Отрисовку делать через u и v(переделывать из x и y), игнорируя z.

const char* vertexShaderSource = R"(
	#version 330 core
	layout (location = 0) in vec3 position;
	uniform mat4 transform;
	uniform float morphFactor;

	const float R = 1.0;
	const float r = 0.3; 

	vec3 getTorPosition(vec3 pos) {
		float u = pos.x * 2.0 * 3.14159;
		float v = pos.y * 2.0 * 3.14159;
		float x = (R + r * cos(v)) * cos(u);
		float y = (R + r * cos(v)) * sin(u);
		float z = r * sin(v);
		return vec3(x, y, z);
	}

	void main()
	{
		vec3 spherePosition = position * 1.5f;
		vec3 torPosition = getTorPosition(position) * 1.25f;
		gl_Position = transform * vec4(mix(spherePosition, torPosition, morphFactor), 1.0);
	}


)";

const char* fragmentShaderSource = R"(
    #version 330 core
	uniform float morphFactor;
    out vec4 color;
    void main()
    {
        color = vec4(morphFactor, 1.0f, 0.0f, 1.0f);
    }
)";

const int WIDTH = 800;
const int HEIGHT = 600;

const float DELAY = 40;

GLuint vertexShader, fragmentShader, shaderProgram;
GLint positionAttrib;

GLfloat morphFactor = 0.0f;

bool unmorph = false;

void InitGL() {

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

	positionAttrib = glGetAttribLocation(shaderProgram, "position");

	GLint transformLoc = glGetUniformLocation(shaderProgram, "transform");

	glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));

	glUseProgram(shaderProgram);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glUseProgram(0);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void DrawSphere() {
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidSphere(1.0f, 32, 32); 
}

void Display() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgram);
	GLint morphFactorLoc = glGetUniformLocation(shaderProgram, "morphFactor");
	glUniform1f(morphFactorLoc, morphFactor);

	glEnableVertexAttribArray(positionAttrib);
	glVertexAttrib3f(positionAttrib, 0.0f, 0.0f, 0.0f);

	DrawSphere();

	glDisableVertexAttribArray(positionAttrib);
	glUseProgram(0);

	glutSwapBuffers();
}

void Update(int value) {

	if (!unmorph)
		morphFactor += 0.01f;
		
	else
		morphFactor -= 0.01f;

	if (morphFactor >= 1.0f) {
		unmorph = true;
	}
	else if (morphFactor <= 0)
	{
		unmorph = false;
	}

	glutTimerFunc(DELAY, Update, 0);

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
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("OpenGL Scene");

	glewInit();
	InitGL();
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutTimerFunc(DELAY, Update, 0);

	glutMainLoop();

	return 0;
}
