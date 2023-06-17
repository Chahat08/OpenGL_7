//#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>

class Shader
{
	// program ID
	unsigned int ID = 0;

	// utility function for shader compilation or linking logging errors
	void logError(unsigned int shaderId, std::string typeOfShader, std::string process, char* infoLog);

public:
	// constructor
	Shader(std::string vertexPath, std::string fragmentPath);

	// get program ID
	unsigned int getID();

	// activate the shader
	void use();

	// set uniforms
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};


#endif