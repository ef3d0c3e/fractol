NAME   := fractol
CC     := clang
#CFLAGS := -Wall -Wextra -ggdb  -fsanitize=address -fopenmp
CFLAGS := -Wall -Wextra -fopenmp -O3 -Ofast -ffast-math
IFLAGS := -Iminilibx-linux -Isrc
LFLAGS := -L/usr/lib -lX11 -lXext -lm

SOURCES := \
src/main.c \
src/app/fractol.c \
src/app/viewport/viewport.c \
src/app/viewport/viewport_linear.c \
src/util/vector.c \
src/util/pos.c \
src/util/realloc.c \
src/util/math.c \
src/util/memcpy.c \
src/util/matrix.c \
src/kernel/kernels/mandel_exp.c \
src/kernel/kernels/mandel_smooth_it.c \
src/kernel/kernels/mandel_de.c \
src/kernel/gradient.c \
src/kernel/color.c \
src/kernel/kernel.c \
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
