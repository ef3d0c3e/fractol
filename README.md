# Fractol -- Fractal explorer program

![Fractol in action](./docs/mandel_arg.png)

# Navigation

You can navigate using the mouse:
 * Mouse wheel is responsible for zooming
 * Mouse left 'pans' the view

Or you can use the keyboard:
 * Numpad + or - for zooming
 * Arrow keys for moving
*Note: You have to disable the [S]elector in order to use arrow key navigation.*

# Rendering

The program uses two different rendering pipelines according to the value chosen for `downsampling`.

 * **When `downsampling == 1`: [Key = R]**
   - The image is rendered using 1 sample per screen pixel. The image is then displayed without no further processing.\
        *This is the default rendering method, note that some regions may require [upsampling](#render-upsampling) in order to display 'precisely'.*

 * **When `downsampling > 1`: [Key = R]**
    - The image is rendered to a buffer of sizes `(window_width / downsampling, window_height / downsampling)`.
    - The image is then upscaled using bilinear filtering.\
        *Doing so gives good result around 'smooth' regions in the smaller image.\
        However, 'noisy' regions become blurry when upscaled. Edge-detection can help to detect these regions\
        in order to 'fix' their blurryness.*
    - Edges are detected using [Sobel edge detection](https://en.wikipedia.org/wiki/Sobel_operator)
    - Detected edges are propagated to their neighbor pixels in order to create a 'mask' of blurry regions.
    - Each pixel present in the mask is re-sampled from the fractal in order to get a newer accurate reading of their values.\
        *A possible optimization to this method is to re-use the previously computed pixel data from the smaller image*


 * **When using <a name="render-upsampling">upsampling</a> (antialiasing): [Key = U]**
    - Sobel edge-detection is used to detect noisy regions that might need re-computing.
    - A 5x5 gaussian blur is used to 'propagate' noisy pixels to their neighbors.
    - From then, each pixel gets an oversampling weight assigned.\
        *The assigned weights can be visualized using the `Oversampling debug` in the selector ui.*
    - Each pixel is recomputed using `(2 * floor(weight) + 1) ^ 2` samples.\
        *(The original pixel is subdivided into a grid with 1 cell for each sample)*
    - They are then blended into the final pixel value using gaussian sampling.\
        *This upsampling method can save a lot of resources, as most smooth pixel regions would have\
        stayed the same if they had been oversampled. Oversampling only the noisy regions uses.\
        However, expect very noisy images to result in global oversampling of the entire image (long).*

# Building

Fractol requires the following to be installed:
 - `libx11`
 - `libxext`

Then you can run `make` to build the fractol executable. Or `make bonus` for the multithreaded (faster) version.

# Parameters

## Required parameters

The program requires two positional arguments, respectively `WIDTH` and `HEIGHT`.
They must be positive integers between 256 and 4096. These will be the window's default sizes.

**Example**
`./fractol 1280 780 # for a 1280x720 window`

## Additional parameters

The program support the following additional options:
 * [downsampling](#opt-downsampling) *Integer value between 1 and 16*
    This value controls the downscaling factor for when rendering the image.
    Defaults to 1, 

# Defining new fractals

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
            // Plot from gradient
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

# License

This project is licensed under the GNU GPL version 3.
