# Colors
GREEN=\033[0;32m
YELLOW=\033[0;33m
NC=\033[0m

# Target and Compiler Settings
NAME        := philo
CC          := cc
CFLAGS      := -Wextra -Wall -Werror
PFLAGS      := -pthread
# Source Files
SRCS        := srcs/main.c srcs/utils.c srcs/initialize.c srcs/dinner_cycle.c\
					srcs/philo_routine.c srcs/monitor_routine.c srcs/thread_utils.c
OBJS_PATH   := ./objs
OBJS        := $(patsubst srcs/%.c,$(OBJS_PATH)/%.o,$(SRCS))
INCLUDE := include

# Targets
all: $(OBJS_PATH) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(PFLAGS) $(INCLUDES) $(OBJS) $(LINCLUDES) -o $@
	@echo "${GREEN}Compilation completed.${NC}"

$(OBJS_PATH)/%.o: ./srcs/%.c $(INCLUDE)/philosopher.h | $(OBJS_PATH)
	@echo "${YELLOW}Compiling $<.${NC}"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)

clean:
	@rm -rf $(OBJS_PATH)
	@echo "${YELLOW}Cleaning objects.${NC}"

fclean: clean
	@rm -f $(NAME)
	@echo "${YELLOW}Cleaning executables.${NC}"

re: fclean all

.PHONY: all clean fclean re
