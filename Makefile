OBJS = countdown.o
CC = g++
CFLAGS = -std=c++14
SRC = src
NAME = countdown

all :
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)/countdown.cpp

clean:
	rm $(NAME)
