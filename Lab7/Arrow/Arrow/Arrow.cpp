#include <GLEW/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace std;


const char* vertexShaderSource = R"(
	#version 330 core
	layout (location = 0) in vec2 position;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;

	void main() {
	  gl_Position = view * model * vec4(position, 0.0, 1.0);
	}

)";

const char* geometryShaderSource = R"(
	#version 330 core
	layout (lines) in;
	layout (line_strip, max_vertices = 6) out;

	uniform vec2 screenSize;

	void main() {
	  vec2 start = gl_in[0].gl_Position.xy;
	  vec2 end = gl_in[1].gl_Position.xy;

	  float length = distance(start, end);

	  vec2 direction = normalize(end - start);

	  vec2 tip = end;

	  vec2 side1 = tip - direction * length  *  0.1f - direction * length  * 0.05f  * vec2(sin(radians(60.0f)), -cos(radians(30.0f)));
	  vec2 side2 = tip - direction * length * 0.1f - direction * length  * 0.05f  * vec2(-sin(radians(60.0f)), cos(radians(30.0f)));

	  gl_Position = vec4(side1, 0.0, 1.0); EmitVertex();
	  gl_Position = vec4(tip, 0.0, 1.0); EmitVertex();
	  gl_Position = vec4(side2, 0.0, 1.0); EmitVertex();
	  EndPrimitive();

	  gl_Position = vec4(start, 0.0, 1.0); EmitVertex();
	  gl_Position = vec4(end, 0.0, 1.0); EmitVertex();
	  EndPrimitive();
	}
)";

//убрать искажение.

const char* fragmentShaderSource = R"(
    #version 330 core
	out vec4 FragColor;

	void main() {
	  FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	}
)";

int WIDTH = 800;
int HEIGHT = 600;
GLuint program;
GLint modelLoc, viewLoc, projectionLoc;

GLuint createShader(GLenum shaderType, const char* source) {
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "Error compiling shader: " << infoLog << std::endl;
	}

	return shader;
}

GLuint createProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader) {
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, geometryShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cerr << "Error linking program: " << infoLog << std::endl;
	}

	return program;
}

void InitGL() {


	GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint geometryShader = createShader(GL_GEOMETRY_SHADER, geometryShaderSource);
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	program = createProgram(vertexShader, geometryShader, fragmentShader);

	modelLoc = glGetUniformLocation(program, "model");
	viewLoc = glGetUniformLocation(program, "view");
	projectionLoc = glGetUniformLocation(program, "projection");
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	// Создание линии
	GLfloat vertices[] = {
	  -0.5f, -0.5f,
	  0.5f, 0.5f
	};
	glUseProgram(program);

	glm::mat4 model = glm::mat4(1.0f);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

	// Загрузка данных вершин
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);

	// Рисование линии
	glDrawArrays(GL_LINES, 0, 2);

	glDisableVertexAttribArray(0);
	glUseProgram(0);

	glutSwapBuffers();
}

void Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("OpenGL Scene");

	glewInit();
	InitGL();

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);

	glutMainLoop();

	return 0;
}
