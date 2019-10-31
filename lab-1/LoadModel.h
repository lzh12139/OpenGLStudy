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
    vector<vector<GLint>> fSets;//存放面的三个顶点索引

    Loader(string path){
        vSets=vector<vector<GLfloat>>();
        fSets=vector<vector<GLint>>();

        ifstream file(path);
        string line;

        while(getline(file,line)){
            if(line.substr(0,1)=="v"){
                vector<GLfloat> point=vector<GLfloat>(3);
                GLfloat x,y,z;

                istringstream stream(line.substr(2));
                stream>>x;stream>>y;stream>>z;

                point[0]=x,point[1]=y,point[2]=z;
                vSets.push_back(point);
            }
            else if(line.substr(0,1)=="f"){
                vector<GLint> point=vector<GLint>(3);
                GLint x,y,z;

                istringstream stream(line.substr(2));
                stream>>x;stream>>y;stream>>z;

                point[0]=x-1,point[1]=y-1,point[2]=z-1;
                fSets.push_back(point);
            }
            else{
                ;;// to be fixed
            }
        }

        file.close();
    }
};

#endif