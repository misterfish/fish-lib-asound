# install: libasound2-dev

fish_util_dir = fish-lib-util/fish-util
fish_util_o = $(fish_util_dir)/fish-util.o

#glib_inc_dir = $(shell pkg-config --cflags glib-2.0)

FLAGS_C = -std=c99 -fPIC -lm -lpthread -lasound -I$(fish_util_dir)
FLAGS_SHARED = -fPIC -shared
#FLAGS_SHARED = -shared

all: fish-asound.o libfish-asound.so

fish-asound.o: $(fish_util_o) fish-asound.c fish-asound.h
	gcc $(FLAGS_C) fish-asound.c -c -o fish-asound.o

# deps?
$(fish_util_o): 
	sh -c "cd $(fish_util_dir); make"

# The shared library is not necessary for fish-vol, but it is useful for
# other applications. 
# Also make install is not necessary for fish-vol.
libfish-asound.so: $(fish_util_o) fish-asound.c fish-asound.h
	gcc $(FLAGS_C) $(FLAGS_SHARED) fish-asound.c fish-asound.h  -o libfish-asound.so

install: all
	cp fish-asound.h /usr/local/include
	cp libfish-asound.so /usr/local/lib
	ldconfig


clean: 
	rm -f *.o
	rm -f *.so
	rm -f test
