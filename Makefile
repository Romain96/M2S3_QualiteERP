

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
EXEC = parser

CC = g++

CFLAGS = -g
LDFLAGS =

all : $(EXEC)

%.o : %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

$(EXEC) : $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(EXEC) *~ ./src/*.o