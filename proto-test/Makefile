# the compiler: gcc for C program, define as g++ for C++
CC = gcc
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
# $(shell pkg-config --libs 'libprotobuf-c >= 1.0.0')
CFLAGS  = -g -Wall 
LFLAGS  = $(shell pkg-config --libs 'libprotobuf-c >= 1.0.0')
# the build target executable:
TARGET = test
DEPS = test-proto3.pb-c.h message.pb-c.h
SOURCES = test-proto3.pb-c.c message.pb-c.c

all: $(TARGET)


%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<



$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c  $(SOURCES)  $(LFLAGS)


clean:
	$(RM) $(TARGET)

proto: $(TARGET)
	$(shell protoc --c_out=. -I. test-proto3.proto)
	$(shell protoc --c_out=. -I. message.proto)

run:
	$(shell ./test)

