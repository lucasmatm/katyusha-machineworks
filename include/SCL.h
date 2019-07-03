#ifndef _SCL_H_
#define _SCL_H_


class SCL{
private:
    unsigned int shader_program;
public:
    SCL(char* vert_shader, char* frag_shader);
    void use();
    int getUniform(char* uniform);
    unsigned int ID();

    void setUniform(char* uniform, int);
    void setUniform(char* uniform, float);
    void setUniform(char* uniform, unsigned int);

    void setUniform(char* uniform, int*, unsigned int);
    void setUniform(char* uniform, float*, unsigned int);
    void setUniform(char* uniform, unsigned int*, unsigned int);

    // void setUniform(char* uniform, int**, unsigned int);
    // void setUniform(char* uniform, float**, unsigned int);
    // void setUniform(char* uniform, unsigned int**, unsigned int);    

};

#endif
