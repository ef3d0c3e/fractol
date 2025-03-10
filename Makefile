NAME := fractol
CC := gcc
CFLAGS := -Wall -Wextra -pedantic -ggdb -fsanitize=address
IFLAGS := -I./src
LFLAGS :=  -lm

# Flags for optimizations
FLAGS_OPT := \
	-O3 \
	-mtune=native \
	-march=native \

# Flags for openmp
FLAGS_OMP := $(FLAGS_OPT) \
	-fopenmp
	-fvect-cost-model=dynamic \
	-fsimd-cost-model=dynamic \
	-fstrict-aliasing \
	-fno-math-errno \
	-funsafe-math-optimizations \
	-fassociative-math \
	-ffinite-math-only \
	-fno-signed-zeros \
	-fno-trapping-math

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
	src/ui/event_keyboard.c \
	src/ui/event_misc.c \
	src/ui/event.c \
	src/ui/ui.c \
	src/ui/event_mouse.c

# Sources with a bonus version
BONUS_SOURCES := \
	src/ui/draw_bonus.c

# Objects
OBJECTS := $(addprefix objs/,$(SOURCES:.c=.o))
OBJECTS += $(addprefix objs/,$(BONUS_SOURCES:_bonus.c=.o))
OBJECTS_BONUS := $(addprefix objs/,$(SOURCES:.c=.o))
OBJECTS_BONUS += $(addprefix objs/,$(BONUS_SOURCES:.c=.o))

FRACTOL_DEFS := -include "defs/default.def"
objs/%.o: IFLAGS += -I./libs/ft_printf/includes/ -I./libs/minilibx-linux
objs/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(IFLAGS) $(FRACTOL_DEFS) -c $< -o $@

# Default target
$(NAME): LFLAGS += -L/usr/lib -lX11 -lXext
$(NAME): $(LIB_MLX) $(LIB_PRINTF) $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIB_MLX) $(LIB_PRINTF) $(LFLAGS)

# Bonus target
bonus: LFLAGS += -L/usr/lib -lX11 -lXext
bonus: FRACTOL_DEFS := -include "defs/bonus.def"
bonus: CFLAGS += $(FLAGS_OPT) \
	-flto
bonus: $(LIB_MLX) $(LIB_PRINTF) $(OBJECTS_BONUS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS_BONUS) $(LIB_MLX) $(LIB_PRINTF) $(LFLAGS)

# Openmp optimized target
bonus-omp: LFLAGS += -L/usr/lib -lX11 -lXext
bonus-omp: FRACTOL_DEFS := -include "defs/bonus.def"
bonus-omp: CFLAGS += $(FLAGS_OMP) \
	-flto
bonus-omp: $(LIB_MLX) $(LIB_PRINTF) $(OBJECTS_BONUS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS_BONUS) $(LIB_MLX) $(LIB_PRINTF) $(LFLAGS)

# Target for GCC's profiler
$(NAME)-profile: FRACTOL_DEFS := -include "defs/bonus.def"
$(NAME)-profile: CFLAGS += $(FLAGS_OMP) \
	-pg \
	--coverage \
	-fprofile-arcs \
	-fcondition-coverage \
	-fprofile-generate
$(NAME)-profile: clean $(OBJECTS_BONUS) $(LIB_MLX) $(LIB_PRINTF)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS_BONUS) $(LIB_MLX) $(LIB_PRINTF) $(LFLAGS)

# GCC instrumented target (requires profile)
$(NAME)-instrumented: FRACTOL_DEFS := -include "defs/bonus.def"
$(NAME)-instrumented: CFLAGS += $(FLAGS_OMP) \
	-fprofile-use \
	-flto
$(NAME)-instrumented: clean $(OBJECTS_BONUS) $(LIB_MLX) $(LIB_PRINTF)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS_BONUS) $(LIB_MLX) $(LIB_PRINTF) $(LFLAGS)

# Libraries
# minilibx-linux
LIB_MLX := ./libs/minilibx-linux/libmlx_Linux.a
$(LIB_MLX):
	echo "Building libmlx..."
	cd $(dir $(LIB_MLX)) && ./configure

# ft_printf
LIB_PRINTF := ./libs/ft_printf/libftprintf.a
$(LIB_PRINTF):
	echo "Building libprintf..."
	$(MAKE) -C $(dir $(LIB_PRINTF))

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	$(RM) $(OBJECTS)

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
