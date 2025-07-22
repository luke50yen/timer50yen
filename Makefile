# Makefile for timer50yen
PREFIX ?= /usr
CXX = g++
CXXFLAGS = -O2 -Wall
TARGET = timer50yen
SRC = timer50yen.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

install: $(TARGET)
	install -d $(DESTDIR)$(PREFIX)/bin
	install -d $(DESTDIR)$(PREFIX)/share/timer50yen
	install -m 755 $(TARGET) $(DESTDIR)$(PREFIX)/bin/$(TARGET)
	install -m 644 alarm.mp3 $(DESTDIR)$(PREFIX)/share/timer50yen/alarm.mp3
	ln -sf $(TARGET) $(DESTDIR)$(PREFIX)/bin/t50

uninstall:
	rm -f $(PREFIX)/bin/$(TARGET)
	rm -f $(PREFIX)/bin/t50
	rm -f $(PREFIX)/share/timer50yen/alarm.mp3
	rmdir $(PREFIX)/share/timer50yen

clean:
	rm -f $(TARGET)