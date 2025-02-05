#include <GLEW/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

const char* vertexShaderSource = R"(
    #version 330 core
	layout (location = 0) in vec3 position;
	out vec3 fragCoord;
	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;

	void main()
	{
		gl_Position = projection * view * model * vec4(position, 1.0);
		fragCoord = position;
	}
)";

const char* fragmentShaderSource = R"(
    #version 330 core
	in vec3 fragCoord;
	out vec4 color;

	void main()
	{
		if (fragCoord.y > -0.45 && fragCoord.y < -0.15)
			color = vec4(1.0, 0, 0, 1.0);
		else if (fragCoord.y >= -0.15 && fragCoord.y < 0.15)
			color = vec4(0, 0, 1, 1.0);
		else
			color = vec4(1, 1, 1, 1.0);
	}

)";

GLuint vertexShader, fragmentShader, shaderProgram;
GLuint vbo;
GLint modelLoc, viewLoc, projectionLoc;

void init() {

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

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	float vertices[] = {
		-0.75f, 0.45f, 0.0f,
		-0.75f, -0.45f, 0.0f,
		0.75f, -0.45f, 0.0f,
		0.75f, 0.45f, 0.0f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");
}

void Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);
	glutPostRedisplay();
}

void display() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glm::mat4 model = glm::mat4(1.0f);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

	glUseProgram(shaderProgram);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glDrawArrays(GL_QUADS, 0, 4);

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Флаг");

	glEnable(GL_DEPTH);
	glewInit();
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(Reshape);
	glutMainLoop();

	return 0;
}