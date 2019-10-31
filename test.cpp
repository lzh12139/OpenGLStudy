#include<bits/stdc++.h>

#define GLEW_STATIC
#include "Shader.h"

const int WindowWidth=1440;
const int WindowHeight=810;

void processInput(GLFWwindow *window,float &y,float &x){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
		x-=1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
		x+=1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
		y-=1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
		y+=1.0f;
	}
}

void init() {
	glfwInit();//初始化
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//配置GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//配置GLFW
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void draw(GLFWwindow* window){
    float vertices[] = {
0.500000,0.500000,0.500000,0.000000,0.000000,1.000000,
0.500000,-0.500000,0.500000,0.000000,0.000000,1.000000,
-0.500000,-0.500000,0.500000,0.000000,0.000000,1.000000,        
0.500000,0.500000,0.500000,0.000000,0.000000,1.000000,
-0.500000,0.500000,0.500000,0.000000,0.000000,1.000000,
-0.500000,-0.500000,0.500000,0.000000,0.000000,1.000000,        
0.500000,0.500000,-0.500000,0.000000,0.000000,1.000000,
0.500000,-0.500000,-0.500000,0.000000,0.000000,1.000000,        
-0.500000,-0.500000,-0.500000,0.000000,0.000000,1.000000,       
0.500000,0.500000,-0.500000,0.000000,0.000000,1.000000,
-0.500000,0.500000,-0.500000,0.000000,0.000000,1.000000,        
-0.500000,-0.500000,-0.500000,0.000000,0.000000,1.000000,       
0.500000,0.500000,0.500000,0.000000,0.000000,1.000000,
0.500000,-0.500000,0.500000,0.000000,0.000000,1.000000,
0.500000,0.500000,-0.500000,0.000000,0.000000,1.000000,
0.500000,0.500000,-0.500000,0.000000,0.000000,1.000000,
0.500000,-0.500000,-0.500000,0.000000,0.000000,1.000000,        
0.500000,-0.500000,0.500000,0.000000,0.000000,1.000000,
0.500000,-0.500000,0.500000,0.000000,0.000000,1.000000,
-0.500000,-0.500000,0.500000,0.000000,0.000000,1.000000,        
0.500000,-0.500000,-0.500000,0.000000,0.000000,1.000000,        
0.500000,-0.500000,-0.500000,0.000000,0.000000,1.000000,        
-0.500000,-0.500000,-0.500000,0.000000,0.000000,1.000000,       
-0.500000,-0.500000,0.500000,0.000000,0.000000,1.000000,        
-0.500000,-0.500000,0.500000,0.000000,0.000000,1.000000,        
-0.500000,0.500000,0.500000,0.000000,0.000000,1.000000,
-0.500000,-0.500000,-0.500000,0.000000,0.000000,1.000000,       
-0.500000,-0.500000,-0.500000,0.000000,0.000000,1.000000,       
-0.500000,0.500000,-0.500000,0.000000,0.000000,1.000000,        
-0.500000,0.500000,0.500000,0.000000,0.000000,1.000000,
-0.500000,0.500000,0.500000,0.000000,0.000000,1.000000,
0.500000,0.500000,0.500000,0.000000,0.000000,1.000000,
-0.500000,0.500000,-0.500000,0.000000,0.000000,1.000000,        
-0.500000,0.500000,-0.500000,0.000000,0.000000,1.000000,        
0.500000,0.500000,-0.500000,0.000000,0.000000,1.000000,
0.500000,0.500000,-0.500000,0.000000,0.000000,1.000000,
    };

    glEnable(GL_DEPTH_TEST);

	//编译着色器
	Shader ourShader("vertex_1.vs", "fragment_1.fs");//编译着色器
	ourShader.use();//使用着色器

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);//生成顶点数组对象
	glGenBuffers(1, &VBO);//生成顶点缓冲区
	
	glBindVertexArray(VAO);// 绑定顶点数组对象

	glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定顶点缓冲区
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//设置缓冲区中的数据

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// 设置对缓冲区访问的步长为3以及相位为0，告诉着色器，这个数据输入到着色器的第一个(索引为0)输入变量，数据的长度是3个float

    glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	ourShader.use();
	//ourShader.setInt("texture1",0);
	//ourShader.setInt("texture2",1);
	float x=-75.0f,y=10.0f;

	while (!glfwWindowShouldClose(window)) {
		processInput(window,x,y);
		//std::cout<<x<<" "<<y<<"\n";

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.use();

		glm::mat4 model			=glm::mat4(1.0f);
		glm::mat4 view 			=glm::mat4(1.0f);
		glm::mat4 projection	=glm::mat4(1.0f);

		model=glm::rotate(model, glm::radians(x), glm::vec3(y, 0.0f, 0.0f));
		view=glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
		projection=glm::perspective(glm::radians(45.0f),(float)WindowWidth/(float)WindowHeight,0.1f,100.0f);

		unsigned int modelLoc=glGetUniformLocation(ourShader.ID,"model");
		unsigned int viewLoc =glGetUniformLocation(ourShader.ID,"view");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

		ourShader.setMat4("projection",projection);

		glBindVertexArray(VAO);//绑定顶点数组对象
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

int main() {
	init();

	GLFWwindow* window = glfwCreateWindow(WindowWidth, WindowHeight, "Test", nullptr, nullptr);
	if (window == nullptr) {
        printf("Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD");
		return -1;
	}

	draw(window);
	glfwTerminate();
}