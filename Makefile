CC = gcc -g -O3 -W -Wall -std=c99 -lm -mfpu=neon

%.o: %.c
	$(CC) -c $<

main: float3.o color.o primitive.o ray.o sphere.o camera.o main.o
	$(CC) $^ -o $@ -std=c99 -lm

clean:
	rm -f main *.o

all: main
