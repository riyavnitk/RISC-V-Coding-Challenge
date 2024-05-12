CC = gcc
CFLAGS = -pthread
TARGET = solution
SCRIPT = app_control.sh

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $@ $<

run: $(TARGET)
	./$(SCRIPT) $(DURATION) 

clean:
	rm -f $(TARGET)

