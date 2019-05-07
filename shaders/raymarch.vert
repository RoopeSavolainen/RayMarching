#version 330
void main() {
   vec4 x[4];
   x[0] = vec4(-1.0, -1.0, 1.0, 1.0);
   x[1] = vec4( 1.0, -1.0, 1.0, 1.0);
   x[2] = vec4(-1.0,  1.0, 1.0, 1.0);
   x[3] = vec4( 1.0,  1.0, 1.0, 1.0);
   gl_Position = x[gl_VertexID];
}

