#ifndef LOADMODEL_H
#define LOADMODEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
// 包含glad来获取所有的必须OpenGL头文件
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<bits/stdc++.h>
using namespace std;

class Loader{
public:
	vector<vector<GLfloat>> vSets;//存放顶点(x,y,z)坐标
	vector<vector<vector<GLint>>> fSets;//存放面的三个顶点索引
	vector<vector<GLfloat>> vtSets;
	vector<vector<GLfloat>> vnSets;

	Loader(string path){
		vSets=vector<vector<GLfloat>>();
		fSets=vector<vector<vector<GLint>>>();
		vtSets=vector<vector<GLfloat>>();
		vnSets=vector<vector<GLfloat>>();

		ifstream file(path);
		string line;

		while(getline(file,line)){
			if(line.substr(0,2)=="v "){
				vector<GLfloat> point=vector<GLfloat>(3);

				istringstream stream(line.substr(2));
				for(int i=0;i<3;i++)stream>>point[i];

				vSets.push_back(point);
			}
			else if(line.substr(0,1)=="f"){
				vector<vector<GLint>> x=vector<vector<GLint>>(3);
				vector<GLint> y=vector<GLint>(3,0);
				x[0]=x[1]=x[2]=y;

				istringstream stream(line.substr(2));
				
				for(int j=0;j<3;j++){
					string s;stream>>s;
					int cur=0;
					for(auto i:s)
						if(i=='/')x[j][cur++]--;
						else x[j][cur]=x[j][cur]*10+i-'0';
					x[j][cur]--;
				}

				fSets.push_back(x);
			}
			else if(line.substr(0,2)=="vt"){
				vector<GLfloat> point=vector<GLfloat>(2);

				istringstream stream(line.substr(3));
				for(int i=0;i<2;i++)stream>>point[i];

				vtSets.push_back(point);
			}
			else if(line.substr(0,2)=="vn"){
				vector<GLfloat> point=vector<GLfloat>(3);

				istringstream stream(line.substr(3));
				for(int i=0;i<3;i++)stream>>point[i];

				vnSets.push_back(point);
			}
			else{
				;;// to be fixed
			}
		}

		file.close();
	}
};

#endif