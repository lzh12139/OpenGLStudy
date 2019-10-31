#include<bits/stdc++.h>

#define GLEW_STATIC
#include "Shader.h"

#include "LoadModel.h"

/*#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>*/

const int WindowWidth=800;
const int WindowHeight=600;

void processInput(GLFWwindow *window,float &x,float &y){
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
		y-=0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
		y+=0.1f;
	}
}

float vertices[18*69473];
float color[]={
	0.5f,0.5f,0.5f,
	0.0f,1.0f,0.0f,
};
void draw(GLFWwindow* window){
	glEnable(GL_DEPTH_TEST);

	Loader mymodel("bunny.obj");
	
	//float *vertices=new float[18*mymodel.fSets.size()];
	for(int i=0;i<mymodel.fSets.size();i++){
		for(int j=0;j<3;j++){
			for(int k=0;k<3;k++)
				vertices[18*i+j*6+k]=mymodel.vSets[mymodel.fSets[i][j]][k]*0.01;
			for(int k=3;k<6;k++)
				if(rand()&1)vertices[18*i+j*6+k]=color[k-3];
				else vertices[18*i+j*6+k]=color[k];
		}
	}
	/*printf("%d\n",mymodel.fSets.size());
	for(int i=0;i<mymodel.fSets.size()*3;i++){
		for(int o=0;o<6;o++)printf("%lf,",vertices[i*6+o]);
		printf("\n");
	}*/

	Shader ourShader("vertex_1.vs", "fragment_1.fs");
	ourShader.use();

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	ourShader.use();

	float x=-75.0f,y=-10.0f;

	while (!glfwWindowShouldClose(window)) {
		processInput(window,x,y);
		//std::cout<<x<<" "<<y<<"\n";

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.use();

		glm::mat4 model			=glm::mat4(1.0f);
		glm::mat4 view 			=glm::mat4(1.0f);
		glm::mat4 projection	=glm::mat4(1.0f);

		model=glm::rotate(model, glm::radians(x), glm::vec3(0.0f, 1.0f, 0.0f));
		view=glm::translate(view, glm::vec3(0.0f, 0.0f, y));
		projection=glm::perspective(glm::radians(45.0f),(float)WindowWidth/(float)WindowHeight,0.1f,100.0f);

		unsigned int modelLoc=glGetUniformLocation(ourShader.ID,"model");
		unsigned int viewLoc =glGetUniformLocation(ourShader.ID,"view");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

		ourShader.setMat4("projection",projection);

		glBindVertexArray(VAO);//绑定顶点数组对象
		glDrawArrays(GL_TRIANGLES, 0, mymodel.fSets.size()*3);

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
		printf("failed to initalize GLEW" << endl;
		return -1;
	}*/

	glfwInit();//初始化
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//配置GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//配置GLFW
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//

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
	//glClearColor(0,1,0,1.0);
	/*while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 1.0f, 0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}*/
	draw(window);
	glfwTerminate();
}