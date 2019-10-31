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

    Loader(string path){
        vSets=vector<vector<GLfloat>>();
        fSets=vector<vector<vector<GLint>>>();
        vtSets=vector<vector<GLfloat>>();

        ifstream file(path);
        string line;

        while(getline(file,line)){
            if(line.substr(0,2)=="v "){
                vector<GLfloat> point=vector<GLfloat>(3);
                GLfloat x,y,z;

                istringstream stream(line.substr(2));
                stream>>x;stream>>y;stream>>z;

                point[0]=x,point[1]=y,point[2]=z;
                vSets.push_back(point);
            }
            else if(line.substr(0,1)=="f"){
                vector<vector<GLint>> x=vector<vector<GLint>>(3);
                vector<GLint> y=vector<GLint>(2,0);
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
                GLfloat x,y;

                istringstream stream(line.substr(3));
                stream>>x;stream>>y;

                point[0]=x,point[1]=y;
                vtSets.push_back(point);
            }
            else{
                ;;// to be fixed
            }
        }

        file.close();
    }
};

#endif