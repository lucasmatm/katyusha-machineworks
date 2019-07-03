#include <SCL.h>

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

SCL::SCL(char* vert_shader, char* frag_shader){

    unsigned int vertex_shader;
    unsigned int fragment_shader;

    std::string tmp_vertex;
    std::string tmp_fragment;

    try {
        std::ifstream vertex_file(vert_shader);
        std::stringstream vertex_string;
        vertex_string << vertex_file.rdbuf();
        tmp_vertex = vertex_string.str();
    }catch(std::ifstream::failure e){
        std::cout << "ERROR::SHADER::VERTEX::FILE NOT SUCCESFULY READ" << std::endl;
    }

    try {
        std::ifstream fragment_file(frag_shader);
        std::stringstream fragment_string;
        fragment_string << fragment_file.rdbuf();
        tmp_fragment = fragment_string.str();
    }catch(std::ifstream::failure e){
        std::cout << "ERROR::SHADER::FRAGMENT::FILE NOT SUCCESFULY READ" << std::endl;
    }

    const char* vertex_code = tmp_vertex.c_str();
    const char* fragment_code = tmp_fragment.c_str();

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);


    glShaderSource(vertex_shader, 1, &vertex_code, NULL);
    glShaderSource(fragment_shader, 1, &fragment_code, NULL);

    glCompileShader(vertex_shader);
    glCompileShader(fragment_shader);

    int vertex_success, fragment_success;

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_success);
    if(!vertex_success){
        char infoLog[512];
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION FAILED\n" << infoLog << std::endl;
    }

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragment_success);
    if(!fragment_success){
        char infoLog[512];
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION FAILED\n" << infoLog << std::endl;
    }


    if(vertex_success && fragment_success){

        this->shader_program = glCreateProgram();
        glAttachShader(this->shader_program, vertex_shader);
        glAttachShader(this->shader_program, fragment_shader);
        glLinkProgram(this->shader_program);

        int program_success;

        glGetProgramiv(this->shader_program, GL_LINK_STATUS, &program_success);
        if(!program_success){
            char infoLog[512];
            glGetProgramInfoLog(this->shader_program, 512, NULL, infoLog);
            std::cout << "ERROR::PROGRAM::LINK FAILED\n" << infoLog << std::endl;
        }
    }else{
        std::cout << "ERRO::COMPILING SHADER::PROGRAM NOT LINKED\n" << std::endl;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void SCL::use(){
    glUseProgram(this->shader_program);
}

unsigned int SCL::ID(){
    return this->shader_program;
}

int SCL::getUniform(char* uniform){
    return glGetUniformLocation(this->shader_program, uniform);
}

void SCL::setUniform(char* uniform, int i){
    glUniform1i(glGetUniformLocation(this->shader_program, uniform), i);
}

void SCL::setUniform(char* uniform, float f){
    glUniform1f(glGetUniformLocation(this->shader_program, uniform), f);
}

void SCL::setUniform(char* uniform, unsigned int ui){
    glUniform1ui(glGetUniformLocation(this->shader_program, uniform), ui);
}

void SCL::setUniform(char* uniform, int* iv, unsigned int count){
    switch (count) {
        case 1:
        this->setUniform(uniform, iv[0]);
        break;

        case 2:
        glUniform2i(glGetUniformLocation(this->shader_program, uniform), iv[0],iv[1]);
        break;

        case 3:
        glUniform3i(glGetUniformLocation(this->shader_program, uniform), iv[0],iv[1],iv[2]);
        break;

        case 4:
        glUniform4i(glGetUniformLocation(this->shader_program, uniform), iv[0],iv[1],iv[2],iv[3]);
        break;
    }
}
void SCL::setUniform(char* uniform, float* fv, unsigned int count){
    switch (count) {
        case 1:
        this->setUniform(uniform, fv[0]);
        break;

        case 2:
        glUniform2f(glGetUniformLocation(this->shader_program, uniform), fv[0],fv[1]);
        break;

        case 3:
        glUniform3f(glGetUniformLocation(this->shader_program, uniform), fv[0],fv[1],fv[2]);
        break;

        case 4:
        glUniform4f(glGetUniformLocation(this->shader_program, uniform), fv[0],fv[1],fv[2],fv[3]);
        break;
    }
}
void SCL::setUniform(char* uniform, unsigned int* uiv, unsigned int count){
    switch (count) {
        case 1:
        this->setUniform(uniform, uiv[0]);
        break;

        case 2:
        glUniform2ui(glGetUniformLocation(this->shader_program, uniform), uiv[0],uiv[1]);
        break;

        case 3:
        glUniform3ui(glGetUniformLocation(this->shader_program, uniform), uiv[0],uiv[1],uiv[2]);
        break;

        case 4:
        glUniform4ui(glGetUniformLocation(this->shader_program, uniform), uiv[0],uiv[1],uiv[2],uiv[3]);
        break;
    }
}
