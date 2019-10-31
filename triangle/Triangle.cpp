#include<bits/stdc++.h>
#define GLEW_STATIC
#include "Shader.h"

using namespace std;
const int WindowWidth=800;
const int WindowHeight=600;

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void init() {
	glfwInit();//初始化
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//配置GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//配置GLFW
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void drawTriangle(GLFWwindow* window){
	float Triangle[] = {
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
	};

	//编译着色器
	Shader ourShader("vertex_1.vs", "fragment_1.fs");//编译着色器
	ourShader.use();//使用着色器
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);//生成顶点数组对象
	glGenBuffers(1, &VBO);//生成顶点缓冲区
	
	glBindVertexArray(VAO);// 绑定顶点数组对象
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定顶点缓冲区
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle, GL_STATIC_DRAW);//设置缓冲区中的数据
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// 设置对缓冲区访问的步长为3以及相位为0，告诉着色器，这个数据输入到着色器的第一个(索引为0)输入变量，数据的长度是3个float
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//画三角形
		//ourShader.use();
		glBindVertexArray(VAO);//绑定顶点数组对象
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

int main() {
	/*glewExperimental = GL_TRUE;
	if (glewInit()!=GLEW_OK)
	{
		cout << "failed to initalize GLEW" << endl;
		return -1;
	}*/

	init();

	GLFWwindow* window = glfwCreateWindow(WindowWidth, WindowHeight, "Test", nullptr, nullptr);
	if (window == nullptr) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
    /*glfwSetFramebufferSizeCallback(window,
		[](GLFWwindow* window, int width, int height){
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	});*/

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//glClearColor(0,1,0,1.0);
	/*while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 1.0f, 0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}*/
	drawTriangle(window);
	glfwTerminate();
}