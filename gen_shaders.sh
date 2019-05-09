printf "#ifndef _SHADERS_H_\n#define _SHADERS_H_\n\n" > inc/shaders.h

minify="shader_minifier.exe --format none -o /dev/stdout"

for f in shaders/*; do
    suffix=${f##*.}
    printf "const char * %s_%s = " $(basename $f .${suffix}) ${suffix} >> inc/shaders.h
    ${minify} $f | sed 's/\(.*\)/"\1\\n"/' >> inc/shaders.h
    printf ";\n" >> inc/shaders.h
done

printf "#endif\n" >> inc/shaders.h
