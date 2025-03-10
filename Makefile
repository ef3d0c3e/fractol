NAME := fractol
CC := gcc
CFLAGS := -Wall -Wextra -pedantic -ggdb -fsanitize=address
IFLAGS := -I./libs/minilibx-linux -I./libs/ft_printf/includes/ -I./src
LFLAGS := -L/usr/lib -lX11 -lXext -lm
LIB_MLX := ./libs/minilibx-linux/libmlx_Linux.a
LIB_PRINTF := ./libs/ft_printf/libftprintf.a

SOURCES := \
src/main.c \
src/args.c \
src/args_parse.c \
src/app/fractol.c \
src/app/zparam.c \
src/app/render.c \
src/app/render_utils.c \
src/app/screenshot.c \
src/app/viewport/viewport.c \
src/app/viewport/viewport_fragment.c \
src/app/viewport/viewport_linear.c \
src/app/move.c \
src/app/ui.c \
src/app/selector.c \
src/util/vector.c \
src/util/murmur3.c \
src/util/realloc.c \
src/util/math.c \
src/util/strcmp.c \
src/util/memcpy.c \
src/util/memcpy_unaligned.c \
src/util/matrix.c \
src/kernel/kernels/mandel_electric.c \
src/kernel/kernels/burning_ship_de.c \
src/kernel/kernels/mandel_orbit.c \
src/kernel/kernels/mandel_tia.c \
src/kernel/kernels/burning_ship_exp.c \
src/kernel/kernels/mandel_arg.c \
src/kernel/kernels/mandel_exp.c \
src/kernel/kernels/mandel_de.c \
src/kernel/kernels/julia_arg.c \
src/kernel/kernels/julia_de.c \
src/kernel/kernels/julia_exp_galaxy.c \
src/kernel/kernels/mandel_exp_galaxy.c \
src/kernel/kernels/ui_debug.c \
src/kernel/kernels/mandel_landing_arg.c \
src/kernel/kernels/fatou.c \
src/kernel/kernels/julia_exp.c \
src/kernel/kernels/mandel_smooth_it.c \
src/kernel/gradient.c \
src/kernel/gradient_randomize.c \
src/kernel/color.c \
src/kernel/color_vec.c \
src/kernel/post_processing.c \
src/kernel/post_processing_sobel.c \
src/kernel/post_processing_gauss.c \
src/kernel/post_processing_bicubic.c \
src/kernel/post_processing_bilinear.c \
src/kernel/kernel.c \
src/ui/event_util.c \
src/ui/draw_queue.c \
src/ui/draw_hash.c \
src/ui/draw.c \
src/ui/event_keyboard.c \
src/ui/event_misc.c \
src/ui/event.c \
src/ui/ui.c \
src/ui/event_mouse.c

OBJECTS := $(addprefix objs/,$(SOURCES:.c=.o))
FRACTOL_DEFS := -include "defs/default.def"
# Flags for optimizations
FLAGS_OPT := -O3 \
	-fopenmp \
	-mtune=native \
	-march=native \
	-fvect-cost-model=dynamic \
	-fsimd-cost-model=dynamic \
	-fstrict-aliasing \
	-funroll-loops \
	-fno-math-errno \
	-funsafe-math-optimizations \
	-fassociative-math \
	-ffinite-math-only \
	-fno-signed-zeros \
	-fno-trapping-math

objs/%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(IFLAGS) $(FRACTOL_DEFS) -c $< -o $@

$(NAME): $(OBJECTS) += objs/ui/draw.o
$(NAME): $(OBJECTS) $(LIB_MLX) $(LIB_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIB_MLX) $(LIB_PRINTF) $(LFLAGS)

.PHONY: bonus
bonus: $(OBJECTS) += objs/ui/draw_bonus.o
bonus: FRACTOL_DEFS := -include "defs/bonus.def"
bonus: CFLAGS += $(FLAGS_OPT) \
	-flto
bonus: $(OBJECTS) $(LIB_MLX) $(LIB_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIB_MLX) $(LIB_PRINTF) $(LFLAGS)

$(NAME)-profile: FRACTOL_DEFS := -include "defs/bonus.def"
$(NAME)-profile: CFLAGS += $(FLAGS_OPT) \
	-pg \
	--coverage \
	-fprofile-arcs \
	-fcondition-coverage \
	-fprofile-generate
$(NAME)-profile: clean $(OBJECTS) $(LIB_MLX) $(LIB_PRINTF)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIB_MLX) $(LIB_PRINTF) $(LFLAGS)

$(NAME)-instrumented: FRACTOL_DEFS := -include "defs/bonus.def"
$(NAME)-instrumented: CFLAGS += $(FLAGS_OPT) \
	-fprofile-use \
	-flto
$(NAME)-instrumented: clean $(OBJECTS) $(LIB_MLX) $(LIB_PRINTF)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIB_MLX) $(LIB_PRINTF) $(LFLAGS)

# minilibx-linux
$(LIB_MLX):
	echo "Building libmlx..."
	cd $(dir $(LIB_MLX)) && ./configure

# ft_printf
$(LIB_PRINTF):
	echo "Building libprintf..."
	$(MAKE) -C $(dir $(LIB_PRINTF))

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	$(RM) $(OBJECTS)
	$(RM) $(BONUS_OBJECTS)

.PHONY: lclean
lclean:
	echo "Cleaning mlx..."
	cd $(dir $(LIB_MLX)) && make clean
	echo "Cleaning printf..."
	cd $(dir $(LIB_PRINTF)) && make fclean

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME)-profile
	$(RM) $(NAME)-instrumented

.PHONY: re
re: fclean all
