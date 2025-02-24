CC = gcc
CFLAGS = -Wall -g
LIBS = -lasound

TARGET = properties
SRC = properties.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)


