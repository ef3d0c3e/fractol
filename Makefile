NAME   := fractol
CC     := gcc
CFLAGS := -Wall -Wextra -ggdb -Og -g3 -fsanitize=address -fopenmp
IFLAGS := -Iminilibx-linux
LFLAGS := -L/usr/lib -lX11 -lXext -lm

SOURCES := \
src/fractol.c \
src/ui.c \
src/matrix.c \
src/vector.c \
src/draw_buffer.c \
src/controls_keyboard.c \
src/controls_mouse.c \
src/kernels/mandel_ext_de.c \
src/viewport.c \
src/viewport_linear.c \
src/kernel.c

OBJECTS := $(addprefix objs/,$(SOURCES:.c=.o))

objs/%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) ./minilibx-linux/libmlx_Linux.a $(LFLAGS)

./minilibx-linux/libmlx_Linux.a:
	$(MAKE) -C minilibx-linux

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
