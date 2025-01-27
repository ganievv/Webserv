NAME				:= webserv

CXX					:= c++
FLAGS				:= -g -Wall -Wextra -Werror -std=c++98

INCDIRS				:= -I./includes/

#directories of source files
VPATH				:= srcs/main srcs/http_server

#source files
SRCS_MAIN			:= main.cpp
SRCS_HTTP_SERVER	:= 
#...

SRCS				:= $(SRCS_MAIN) $(SRCS_HTTP_SERVER) \

BUILDDIR			:= ./build
ODIR				:= $(BUILDDIR)/obj
DDIR				:= $(BUILDDIR)/deps
OBJS				:= $(patsubst %.cpp,$(ODIR)/%.o,$(SRCS))
DEPFILES			:= $(patsubst %.cpp,$(DDIR)/%.d,$(SRCS))
DEPFLAGS			=  -MMD -MP -MF $(DDIR)/$*.d

all: $(BUILDDIR) $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME)

$(ODIR)/%.o: %.cpp
	$(CXX) $(FLAGS) $(INCDIRS) $(DEPFLAGS) -c -o $@ $<

$(BUILDDIR):
	@mkdir -p $(BUILDDIR) $(ODIR) $(DDIR)

clean:
	rm -f $(OBJS) $(DEPFILES)

fclean: clean
	rm -f $(NAME)
	rm -rf $(BUILDDIR)

re: fclean all

-include $(DEPFILES)

.PHONY: all clean fclean re
