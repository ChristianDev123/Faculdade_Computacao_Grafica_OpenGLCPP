#include <iostream>
#include <GL/glew.h>
#include <GLFW//glfw3.h>

using namespace std;

const GLint WIDTH = 800, HEIGHT = 600;
GLuint VAO,VBO,shaderProgram; 
// VAO = espaço para alocação de itens
// VBO = item/dado a ser alocado

static const char* vertexShader = "					\n\
	#version 330									\n\
													\n\
	layout(location=0) in vec2 pos;					\n\
													\n\
	void main(){									\n\
		gl_position = vec4(pos.x,pos.y, 0.0, 1.0)	\n\
	}												\n\
"; //posionamento de x e y na tela (forma de transferencia de dados: layout)

static const char* fragmentShader = "				\n\
	#version 330									\n\
													\n\
	uniform in vec3 colorArr;						\n\
													\n\
	void main(){									\n\
		color = vec4(colorArr, 1.0)					\n\
	}												\n\
"; //mudança de caracteristicas dado um ponto (forma de transferencia de dados: uniform)


void createTriangle() {
	GLfloat vertices[] = {
		0.0f, 1.0f, //v1
		-1.0f, -1.0f, //v2
		1.0f, -1.0f //v3
	};
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0); //location
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}

void addTriangle(GLuint program, const char* shaderCode, GLenum type_program) {
	GLuint _shader = glCreateShader(type_program);
	const GLchar* glCharCode[1];
	glCharCode[0] = shaderCode;
	glShaderSource(_shader, 1, glCharCode,NULL);
	glCompileShader(_shader);
	glAttachShader(program, _shader);
}

void addProgram() {
	shaderProgram = glCreateProgram();
	if (!shaderProgram) {
		cout << "Erro ao criar o programa!";
		return; 
	}
	addTriangle(shaderProgram, vertexShader, GL_VERTEX_SHADER);
	addTriangle(shaderProgram, fragmentShader, GL_FRAGMENT_SHADER);
	glLinkProgram(shaderProgram);
}

int main() {
	// inicando GLFW
	if (!glfwInit()) {
		cout << "Erro: GLFW não foi iniciado";
		glfwTerminate();
		return -1;
	}

	// set nas coisas obrigatórias para subir uma janela
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // versão máxima permitida 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // versão mínima
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // somente as funções core
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // qual a precisão de ponto flutuante que vamos usar, precisão da placa

	// criação de janela 
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Window", NULL, NULL);
	if (!window) {
		cout << "Erro: Não foi possível criar a janela";
		glfwTerminate();
		return -1;
	}

	// guardando o tamanho real da minha tela 
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(window); // tornando essa janela como principal

	//iniciando o Glew
	glewExperimental = GLU_TRUE;
	if (glewInit() != GLEW_OK) {
		cout << "Erro: não foi possível iniciar o glew";
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, bufferWidth, bufferHeight);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}