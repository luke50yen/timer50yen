# Makefile for timer50yen

CXX = g++
CXXFLAGS = -O2 -Wall
TARGET = timer50yen
SRC = timer.cpp

all: $(TARGET)

$(TARGET): $(SRC)
    $(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

install: $(TARGET)
    install -m 755 $(TARGET) /usr/local/bin/$(TARGET)

uninstall:
    rm -f /usr/local/bin/$(TARGET)

clean:
    rm -f $(TARGET)