NAME        = webserv
CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98 -MMD -MP -I$(INCL_DIR)

SRCS_DIR    = srcs
INCL_DIR    = includes
BUILD_DIR   = build


CGI_FILES     = CGI.cpp
HTTP_FILES    = Request.cpp Response.cpp
NETWORK_FILES = Client.cpp Server.cpp
PARSING_FILES = HelpersParsing.cpp HostFormat.cpp ParseLocation.cpp ParseServer.cpp UltimateParsing.cpp

SRCS = srcs/main.cpp \
       $(addprefix $(SRCS_DIR)/cgi/, $(CGI_FILES)) \
       $(addprefix $(SRCS_DIR)/http/, $(HTTP_FILES)) \
       $(addprefix $(SRCS_DIR)/network/, $(NETWORK_FILES)) \
	   $(addprefix $(SRCS_DIR)/parsing/, $(PARSING_FILES))

OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.cpp=.o))
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "✅ $(NAME) compilé avec succès !"

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "🔹 Compiling: $<"

-include $(DEPS)

clean:
	@rm -rf $(BUILD_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re