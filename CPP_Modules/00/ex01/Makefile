NAME = phonebook
CC = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
INCLUDES = -Iincludes

SRC = PhoneBook.cpp add.cpp main.cpp search.cpp getters.cpp setters.cpp

OBJ_DIR = .obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))
MAKEFLAGS += --no-print-directory

all : $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CPPFLAGS) $(INCLUDES) $(OBJ) -o $@
	@echo "phonebook ready"

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Cleaned"

fclean:
	@rm -rf $(NAME) $(OBJ_DIR)
	@echo "Fcleaned"

c: all clean

re: fclean all

.PHONY: clean fclean re all