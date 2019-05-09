printf "#ifndef _SHADERS_H_\n#define _SHADERS_H_\n\n" > inc/shaders.h

minify="shader_minifier.exe --format none -o /dev/stdout"

for f in shaders/*.frag; do
    printf "const char * %s_f = " $(basename $f .frag) >> inc/shaders.h
    ${minify} $f | sed 's/\(.*\)/"\1\\n"/' >> inc/shaders.h
    printf ";\n" >> inc/shaders.h
done

for f in shaders/*.vert; do
    printf "const char * %s_v = " $(basename $f .vert) >> inc/shaders.h
    ${minify} $f | sed 's/\(.*\)/"\1\\n"/' >> inc/shaders.h
    printf ";\n" >> inc/shaders.h
done

printf "#endif\n" >> inc/shaders.h
