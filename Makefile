CC = gcc -O3 -W -Wall -std=c99 -lm

%.o: %.c
	$(CC) -c $<

main: float3.o color.o primitive.o ray.o sphere.o camera.o main.o
	$(CC) $^ -o $@

clean:
	rm -f main *.o

all: main
