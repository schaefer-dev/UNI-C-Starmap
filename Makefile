.PHONY: all clean

all: stars test_write test_transform test_read

stars: star.o main.o image.o
	$(CC) -o $@ $^

test_write: test_write.o image.o
	$(CC) -o $@ $^

test_transform: test_transform.o image.o star.o
	$(CC) -o $@ $^

test_read: test_read.o image.o star.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -O0 -g -Wall -pedantic --std=c99 -o $@ -c $<

clean:
	rm -f *.o *.pbm stars test_write test_read test_transform
