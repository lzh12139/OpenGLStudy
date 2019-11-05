#include<bits/stdc++.h>

#define GLEW_STATIC
#include "Shader.h"
#include "LoadModel.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const int WindowWidth=800;
const int WindowHeight=600;

struct status{
	bool click;
	float prex,prey;
}cur;

void processInput(GLFWwindow *window,float &x,float &y/*,status &cur*/){
	//if(glfwGetMouseButton(window,)==GLFW_PRESS)
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

float vertices[5000010];
float color[]={
	1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,
};
void draw(GLFWwindow* window){
	glEnable(GL_DEPTH_TEST);

	Loader mymodel("miku.obj");

	pair<float,float> l=make_pair(1e9,1e9),r=make_pair(-1e9,-1e9);
	for(auto i:mymodel.fSets)
		for(int j=0;j<3;j++){
			l.first=min(l.first,mymodel.vtSets[i[j][1]][0]);
			r.first=max(r.first,mymodel.vtSets[i[j][1]][0]);

			l.second=min(l.second,mymodel.vtSets[i[j][1]][1]);
			r.second=max(r.second,mymodel.vtSets[i[j][1]][1]);
		}
	float nextx=r.first-l.first,nexty=r.second-l.second;

	for(int i=0;i<(int)mymodel.fSets.size();i++){
		for(int j=0;j<3;j++){
			for(int k=0;k<3;k++)
				vertices[24*i+8*j+k]=mymodel.vSets[mymodel.fSets[i][j][0]][k]*0.1;
			for(int k=3;k<6;k++)
				//if(rand()&1)vertices[24*i+8*j+k]=color[k-3];
				//else 
				vertices[24*i+8*j+k]=
					mymodel.vnSets[mymodel.fSets[i][j][2]][k-3]*0.5+0.5;

			vertices[24*i+8*j+6]=
				(mymodel.vtSets[mymodel.fSets[i][j][1]][0]-l.first)/nextx;
			vertices[24*i+8*j+7]=
				(mymodel.vtSets[mymodel.fSets[i][j][1]][1]-l.second)/nexty;
			/*for(int k=6;k<7;k++)
				vertices[24*i+8*j+k]=mymodel.vtSets[mymodel.fSets[i][j][1]][k-6];*/
		}
	}

	Shader ourShader("vertex_1.vs", "fragment_1.fs");
	ourShader.use();

	// 绑定顶点数组，顶点缓冲
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*24*mymodel.fSets.size(), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	/**
	 * GL_REPEAT			对纹理的默认行为。重复纹理图像。
	 * GL_MIRRORED_REPEAT	和GL_REPEAT一样，但每次重复图片是镜像放置的。
	 * GL_CLAMP_TO_EDGE		纹理坐标会被约束在0到1之间，超出的部分会重复纹理坐标的边缘，产生一种边缘被拉伸的效果。
	 * GL_CLAMP_TO_BORDER	超出的坐标为用户指定的边缘颜色。
	 **/	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/**
	 * GL_NEAREST	邻近过滤
	 * GL_LINEAR	线性过滤
	 **/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 加载并生成纹理
	int width, height, nrChannels;
	unsigned char *data = stbi_load("sea.jpg", &width, &height, &nrChannels, 0);
	if (data){
		/**
		 * 多级纹理的级别
		 * 历史遗留问题
		 */
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else printf("Failed to load texture \n");
	
	stbi_image_free(data);

	//ourShader.use();

	float x=-75.0f,y=-3.0f;

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
		view=glm::translate(view, glm::vec3(0.0f, -1.0f, y));
		projection=glm::perspective(glm::radians(45.0f),(float)WindowWidth/(float)WindowHeight,0.1f,100.0f);

		unsigned int modelLoc=glGetUniformLocation(ourShader.ID,"model");
		unsigned int viewLoc =glGetUniformLocation(ourShader.ID,"view");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

		ourShader.setMat4("projection",projection);

		glBindTexture(GL_TEXTURE_2D,texture);
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