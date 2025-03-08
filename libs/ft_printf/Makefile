NAME   := libftprintf
CC     := gcc
CFLAGS := -Wall -Wextra -Werror -pedantic-errors -O2
IFLAGS := -Iincludes

SOURCES := \
		src/arg_parser.c \
		src/args.c \
		src/args_char.c \
		src/args_hex.c \
		src/args_int.c \
		src/args_ptr.c \
		src/args_string.c \
		src/args_unsigned.c \
		src/printf.c \
		src/util.c
OBJECTS := $(addprefix objs/,$(SOURCES:.c=.o))

objs/%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $@

$(NAME).a: $(OBJECTS)
	$(AR) rcs $(NAME).a $(OBJECTS)

$(NAME)-shared.so:
	$(CC) $(IFLAGS) $(CFLAGS) $(SOURCES) -shared -o $(NAME)-shared.so

.PHONY: all
all: $(NAME).a $(NAME)-shared.so

.PHONY: clean
clean:
	$(RM) $(OBJECTS)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME).a
	$(RM) $(NAME)-shared.so

.PHONY: re
re: fclean all
