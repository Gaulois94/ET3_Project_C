CC=gcc
CFLAGS=-W -Wall -I include
LDFLAGS= -lexpat -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm
EXEC=MarioLike
SRC= $(wildcard src/*.c src/*/*.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

MarioLike: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf src/*.o src/*/*.o

mrproper: clean
	rm -rf $(EXEC)
