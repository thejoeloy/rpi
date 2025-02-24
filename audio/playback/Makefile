CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lasound

TARGET = playback
SRC = playback.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

