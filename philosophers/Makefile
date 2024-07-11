cc		= gcc
CFLAGS  = -Wall -Werror -Wextra -Iinclude

SRCDIR = src
SOURCES := $(shell find $(SRCDIR) -name '*.c')  
OBJECTS := $(SOURCES:.c=.o)

philosophers: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS) 

all: philosophers

p: all
	./philosophers
	
clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -rf philosophers

re: fclean all
