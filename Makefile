NAME   := fractol
CC     := gcc
CFLAGS := -Wall -Wextra -ggdb -fsanitize=address -fopenmp
#CFLAGS := -Wall -Wextra -fopenmp -fsanitize=address -O3 -Ofast -ffast-math
IFLAGS := -Iminilibx-linux -Isrc
LFLAGS := -L/usr/lib -lX11 -lXext -lm

SOURCES := \
src/main.c \
src/app/fractol.c \
src/app/render.c \
src/app/viewport/viewport.c \
src/app/viewport/viewport_fragment.c \
src/app/viewport/viewport_linear.c \
src/app/move.c \
src/app/selector.c \
src/app/zparam.c \
src/app/bar.c \
src/util/vector.c \
src/util/pos.c \
src/util/realloc.c \
src/util/strcmp.c \
src/util/math.c \
src/util/memcpy.c \
src/util/matrix.c \
src/kernel/kernels/mandel_electric.c \
src/kernel/kernels/julia_exp.c \
src/kernel/kernels/julia_arg.c \
src/kernel/kernels/mandel_exp.c \
src/kernel/kernels/mandel_exp_pt.c \
src/kernel/kernels/burning_ship.c \
src/kernel/kernels/mandel_de.c \
src/kernel/kernels/mandel_landing_arg.c \
src/kernel/kernels/mandel_arg.c \
src/kernel/kernels/mandel_smooth_it.c \
src/kernel/gradient.c \
src/kernel/color.c \
src/kernel/post_processing.c \
src/kernel/kernel.c \
src/ui/draw_queue.c \
src/ui/image.c \
src/ui/draw.c \
src/ui/event_keyboard.c \
src/ui/event.c \
src/ui/event_util.c \
src/ui/ui.c \
src/ui/event_mouse.c

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
