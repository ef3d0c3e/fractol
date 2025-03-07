NAME   := fractol
CC     := gcc
CFLAGS := -Wall -Wextra -std=c99 -ggdb -fsanitize=address -fopenmp -pedantic
#CFLAGS := -Wall -Wextra -std=c99 -fopenmp -O3 -Ofast -ffast-math -pedantic
IFLAGS := -I./minilibx-linux -I./libs/ft_printf/includes/ -I./src
LFLAGS := -L/usr/lib -lX11 -lXext -lm
LIB_MLX := ./minilibx-linux/libmlx_Linux.a
LIB_PRINTF := ./libs/ft_printf/libftprintf.a


SOURCES := \
src/main.c \
src/app/fractol.c \
src/app/zparam.c \
src/app/render.c \
src/app/viewport/viewport.c \
src/app/viewport/viewport_fragment.c \
src/app/viewport/viewport_linear.c \
src/app/move.c \
src/app/bar.c \
src/app/selector.c \
src/util/vector.c \
src/util/pos.c \
src/util/realloc.c \
src/util/math.c \
src/util/strcmp.c \
src/util/memcpy.c \
src/util/matrix.c \
src/kernel/kernels/mandel_electric.c \
src/kernel/kernels/burning_ship_de.c \
src/kernel/kernels/burning_ship_exp.c \
src/kernel/kernels/mandel_arg.c \
src/kernel/kernels/mandel_exp.c \
src/kernel/kernels/mandel_de.c \
src/kernel/kernels/julia_arg.c \
src/kernel/kernels/ui_debug.c \
src/kernel/kernels/mandel_landing_arg.c \
src/kernel/kernels/fatou.c \
src/kernel/kernels/julia_exp.c \
src/kernel/kernels/mandel_smooth_it.c \
src/kernel/gradient.c \
src/kernel/gradient_randomize.c \
src/kernel/color.c \
src/kernel/post_processing.c \
src/kernel/post_processing_sobel.c \
src/kernel/post_processing_gauss.c \
src/kernel/post_processing_bicubic.c \
src/kernel/kernel.c \
src/ui/event_util.c \
src/ui/draw_queue.c \
src/ui/image.c \
src/ui/draw.c \
src/ui/event_keyboard.c \
src/ui/event.c \
src/ui/ui.c \
src/ui/event_mouse.c

OBJECTS := $(addprefix objs/,$(SOURCES:.c=.o))

objs/%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJECTS) $(LIB_MLX) $(LIB_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIB_MLX) $(LIB_PRINTF) $(LFLAGS)

$(LIB_MLX):
	$(MAKE) -C minilibx-linux

$(LIB_PRINTF):
	$(MAKE) -C ./libs/ft_printf

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
