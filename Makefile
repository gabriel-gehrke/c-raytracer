CC = gcc -lm -g -O3 -W -Wall -Wextra -std=c99

%.o: %.c
	$(CC) -c $<

main: float3.o color.o primitive.o ray.o raycaster.o sphere.o camera.o main.o
	$(CC) -o $@ $^ -lm

clean:
	rm -f main *.o

all: main
