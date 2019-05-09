PACKAGES = glew glib-2.0 gtk+-3.0
CFLAGS = `pkg-config --cflags $(PACKAGES)` -Os -fomit-frame-pointer -c -I./inc -Wall -Wextra -pedantic
LDFLAGS = `pkg-config --libs $(PACKAGES)`

OBJS = $(addprefix obj/, $(addsuffix .o, \
	main shader ))

OUT = demo

all:    $(OUT)_pack

$(OUT)_pack:	$(OUT)
	./pack.sh $(OUT)

obj/%.o: src/%.c inc/shaders.h
	mkdir -p obj; \
	gcc $< $(CFLAGS) -o $@

$(OUT):   inc/shaders.h $(OBJS)
	gcc $(OBJS) $(LDFLAGS) -o $@; strip -s -R .comment -R .gnu.version -R .note.ABI-tag -R .note.gnu.build-id -R .gnu.hash $@

inc/shaders.h:	shaders/*
	./gen_shaders.sh

clean:	
	@rm -f $(OUT) $(OUT)_pack inc/shaders.h obj/*
