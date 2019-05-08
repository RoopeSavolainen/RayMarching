#define GL_GLEXT_PROTOTYPES
#include "shader.h"

#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glext.h>

shader load_shader(const char** src_vert, const char **src_frag) {
    
    shader s;
    s.frag_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(s.frag_id, 1, src_frag, NULL);
    glCompileShader(s.frag_id);

    GLint error = 0;
    glGetShaderiv(s.frag_id, GL_COMPILE_STATUS, &error);
    if(error == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(s.frag_id, GL_INFO_LOG_LENGTH, &maxLength);

        char* error = malloc(maxLength);
        glGetShaderInfoLog(s.frag_id, maxLength, &maxLength, error);
        printf("%s\n", error);

        exit(1);
    }

    s.vert_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(s.vert_id, 1, src_vert, NULL);
    glCompileShader(s.vert_id);

    glGetShaderiv(s.vert_id, GL_COMPILE_STATUS, &error);
    if(error == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(s.vert_id, GL_INFO_LOG_LENGTH, &maxLength);

        char* error = malloc(maxLength);
        glGetShaderInfoLog(s.vert_id, maxLength, &maxLength, error);
        printf("%s\n", error);

        exit(1);
    }

    s.prog_id = glCreateProgram();
    glAttachShader(s.prog_id, s.vert_id);
    glAttachShader(s.prog_id, s.frag_id);
    glLinkProgram(s.prog_id);

    glGetProgramiv(s.prog_id, GL_LINK_STATUS, (int *)&error);
    if (error == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(s.prog_id, GL_INFO_LOG_LENGTH, &maxLength);

        char* error = malloc(maxLength);
        glGetProgramInfoLog(s.prog_id, maxLength, &maxLength,error);
        printf("%s\n", error);

        exit(1);
    }
    return s;
}
