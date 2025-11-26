name = phonebook
SRCS = phonebook.cpp
OBJS = $(SRCS:.cpp=.o)
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
all: $(name)
$(name): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(name)
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(name)
re: fclean all
.PHONY: all clean fclean re