all:	libcgmath.so libcgmath.a

libcgmath.a:	vec2f.o vec3f.o vec4f.o mat2f.o mat3f.o mat4f.o
	ar rcs bin/libcgmath.a vec2f.o vec3f.o vec4f.o mat2f.o mat3f.o mat4f.o

libcgmath.so:	vec2f.o vec3f.o vec4f.o mat2f.o mat3f.o mat4f.o
	gcc -fPIC -o bin/libcgmath.so -shared vec2f.o vec3f.o vec4f.o mat2f.o mat3f.o mat4f.o

vec2f.o:	vec2f.c
	gcc -o vec2f.o -c vec2f.c -fPIC

vec3f.o:	vec3f.c
	gcc -o vec3f.o -c vec3f.c -fPIC

vec4f.o:	vec4f.c
	gcc -o vec4f.o -c vec4f.c -fPIC

mat2f.o:	mat2f.c
	gcc -o mat2f.o -c mat2f.c -fPIC

mat3f.o:	mat3f.c
	gcc -o mat3f.o -c mat3f.c -fPIC

mat4f.o:	mat4f.c
	gcc -o mat4f.o -c mat4f.c -fPIC

testlib: 	bin/test/main.c
	gcc -L./bin -I./ bin/test/main.c -lcgmath -Wl,-rpath,'$$ORIGIN' -Wl,-z,origin -o bin/test/main
	cp ./bin/libcgmath.so ./bin/test/libcgmath.so

.PHONY:

clean:
	rm *.o

