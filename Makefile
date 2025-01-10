NAME   := fractol
CC     := gcc
CFLAGS := -Wall -Wextra -ggdb -Og -g3
IFLAGS := -Iminilibx-linux
LFLAGS := -L/usr/lib -lX11 -lXext -lz -lm

SOURCES := \
		src/fractol.c \
		src/viewport.c \
		src/controls.c \
		src/kernels/mandel_ext_de.c
OBJECTS := $(addprefix objs/,$(SOURCES:.c=.o))

./minilibx-linux/libmlx_Linux.a:
	cd ./minilibx-linux && make

objs/%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) ./minilibx-linux/libmlx_Linux.a $(LFLAGS)

.PHONY: all
all: $(NAME)


.PHONY: clean
clean:
	$(RM) $(OBJECTS)
	$(RM) $(BONUS_OBJECTS)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
