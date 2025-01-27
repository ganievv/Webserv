NAME				:= webserv

CXX					:= c++
FLAGS				:= -g -Wall -Wextra -Werror -std=c++17

INCDIRS				:= -I./include/

#directories of source files
VPATH				:= 

#source files
SRCS_MAIN			:= 
SRCS_CONFIG_FILE	:= 
#...

SRCS				:= $(SRCS_MAIN) $(SRCS_CONFIG_FILE) \

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
