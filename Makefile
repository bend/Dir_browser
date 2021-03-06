CFLAGS+=-Wall -Werror -ansi -pedantic -g -std=gnu99
LDFLAGS+=
EXEC=browsed
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
	
.PHONY: clean mrproper

clean:
	@rm $(OBJECTS)

mrproper:
	@rm $(EXEC)

install:
	@cp $(EXEC) /bin
