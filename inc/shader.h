#ifndef _SHADER_H_
#define _SHADER_H_

#include <GL/gl.h>

typedef struct {
    GLuint prog_id,
           vert_id,
           frag_id;
} shader;

shader load_shader(const char **, const char **);

#endif
