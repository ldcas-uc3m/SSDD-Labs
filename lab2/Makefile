BIN_FILES = p1 p2 p3 p6 p7 pi pi2

CC = gcc

CPPFLAGS = -I$(INSTALL_PATH)/include -Wall

LDFLAGS = -L$(INSTALL_PATH)/lib/
LDLIBS = -lpthread -lm


all: $(BIN_FILES)
.PHONY : all


p1: p1.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

p2: p2.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

p3: p3.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

p5: p5.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

p6: p6.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

pi: pi.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	
pi2: pi2.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

clean:
	rm -f $(BIN_FILES) *.o

.SUFFIXES:
.PHONY : clean
