#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <glew.h>
#include <glfw3.h>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <assert.h> 

class CShaderManager
{
public:
	/*Singleton setup*/
	static CShaderManager& GetInstance();
	CShaderManager(CShaderManager const&) = delete;
	void operator=(CShaderManager const&) = delete;
	~CShaderManager();

	/*Core Functions*/
	GLuint loadShaders(const char * _vertexShader, const char * _fragmentShader);
	void AddShader(GLuint _shader, std::string _key);

	/*Accessor Functions*/
	GLuint GetShaderByString(std::string _name);
	

private:
	CShaderManager();
	std::map<std::string, GLuint> m_Shadermap;
	
};
#endif