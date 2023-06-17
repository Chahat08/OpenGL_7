#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(std::string vertexPath, std::string fragmentPath) {

	// reading shaders from file sources

	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);

		std::stringstream vertexShaderStream, fragmentShaderStream;
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cerr << "ERROR: File not read successfully read" << std::endl;
	}

	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSouce = fragmentCode.c_str();

	// compiling shaders
	unsigned int vertexShader, fragmentShader;
	char infoLog[512];

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	logError(vertexShader, "vertex shader", "compile", infoLog);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSouce, NULL);
	glCompileShader(fragmentShader);
	logError(fragmentShader, "fragment shader", "compile", infoLog);

	// linking shaders and creating shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	logError(ID, "shader program", "link", infoLog);

	// deleting shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::logError(unsigned int shaderId, std::string typeOfShader, std::string process, char* infoLog) {
	int success;

	if (process.compare("compile") == 0)
	{
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
			std::cerr << "ERROR: Failed to " << process << " " << typeOfShader << std::endl;
		}
	}
	else {
		glGetShaderiv(shaderId, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderId, 512, NULL, infoLog);
			std::cerr << "ERROR: Failed to " << process << " " << typeOfShader << std::endl;
		}
	}
}

unsigned int Shader::getID() {
	return ID;
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}