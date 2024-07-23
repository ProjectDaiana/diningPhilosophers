# cc		= cc
# CFLAGS  = -Wall -Werror -Wextra -Iinclude

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g -fsanitize=address -fsanitize=undefined
LDFLAGS = -fsanitize=address -fsanitize=undefined

NAME = philosophers
SRCDIR = src
SOURCES := $(shell find $(SRCDIR) -name '*.c')  
OBJECTS := $(SOURCES:.c=.o)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS) 

all: $(NAME)

p: all
	./$(NAME)
	
clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
