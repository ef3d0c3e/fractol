# Fractol -- Fractal explorer program

![Fractol in action](./docs/mandel_arg.png)

## Defining new fractals

You can add a new fractal by creating the following file: `src/kernel/kernels/my_fractal.c`.

**Template**
```c
// Iteration code
static inline t_color	iter(double complex c, const t_closure *data)
{
	int				i;
	double			m;
	double complex	dz;
	double complex	z;

	dz = 0;
	z = 0;
	i = 0;
	while (i < data->max_it)
	{
        // Derivative
        dz = 3 * z * z * dz + c;
        // Main function Z(n+1) = Z(n)^3 + c
        z = z * z * z + c;
        m = cabs(z);
        if (m > 1e8) // c is outside the set, color it...
        {
            m = 2 * log2(m) * m / cabs(dz);
            // Plot from gradienbt
            return (gradient_get(&data->settings->gradient, log10(m)));
        }
		++i;
	}
	return ((t_color){0x000000});
}

// Render callback, called when the user asks for rendering
static inline void
	render(
			struct s_fragment_data *data,
			const t_kernel_settings *settings,
			const int max_it
			)
{
	struct s_kernel_closure	closure;

	closure.view = data->viewport;
	closure.settings = settings;
	closure.max_it = max_it;
    // Call iteration code for each pixel
	viewport_fragment(data, (t_color (*)(double _Complex, void *))iter,
		&closure);
}

// Initialization function of your fractal.
// if `settings` is NULL, do not initialize anything!
const t_kernel	*my_fractal(t_kernel_settings *settings)
{
    // Red/Green/Blue gradient
	static const struct s_gr_color	colors[] = {
	{{0xFF0000}, 1.0}, {{0x00FF00}, 1.0}, {{0x0000FF}, 1.0}};
	static const t_kernel			kernel = {
		.name = "My custom fractal",
		.render = render,
		.default_viewport = {{-1.5, 1.5, -1.0, 1.0}}, // Viewable area, can be changed according to window's sizes
		.default_mat = {{1, 0, 0, 1}}, // Transformation
		.flags = USE_GRADIENT, // Flag because we use the gradient
		.default_color = {0x000000}, // Background color
	};

	if (settings)
		settings->gradient
			= gradient_new(colors, sizeof(colors) / sizeof(colors[0]));
	return (&kernel);
}
```

Don't forget to add your file to the kernel list in `./src/kernel/kernel.c` and to the makefile.
![Example custom kernel](./docs/custom.png)
