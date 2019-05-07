PACKAGES = glew glib-2.0 gtk+-3.0
CFLAGS = `pkg-config --cflags $(PACKAGES)` -I./inc -Wall -Wextra -pedantic
LDFLAGS = `pkg-config --libs $(PACKAGES)`

OBJS = $(addprefix obj/, $(addsuffix .o, \
	main ))

OUT = demo

all:    $(OUT)


obj/%.o: src/%.c inc/shader.h
	@mkdir -p obj; \
	gcc -c $< $(CFLAGS) -o $@

$(OUT):   inc/shader.h $(OBJS)
	gcc $(OBJS) $(LDFLAGS) -o $@

inc/shader.h:	shaders/*
	./gen_shaders.sh

clean:	
	@rm -f main main.o shader.h
