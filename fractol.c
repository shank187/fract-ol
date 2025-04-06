/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 03:19:36 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/06 20:34:41 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


void fill_fractol(t_fractol *fractol, int who, char **av)
{
    fractol->c_julia = (t_complex){0.0, 0.0};
    if (who == 1)
        fractol->c_julia = (t_complex){ft_atof(av[2]), ft_atof(av[3])};
    fractol->height = 700;
    fractol->width = 700;
    fractol->mlx = mlx_init(fractol->width, fractol->height, av[1], 0);
    if (!fractol->mlx) {
        ft_putstr_fd("Failed to initialize mlx\n", 2);
    }    
    fractol->img = mlx_new_image(fractol->mlx, fractol->width, fractol->height);
    if (!fractol->img) {
        ft_putstr_fd("Failed to create image\n", 2);
    }
    fractol->fractal_type = who;
    fractol->max_iter = 100;
	fractol->min_real = -2.0;
	fractol->max_real = 2.0;
	fractol->min_imag = -2.0;
	fractol->max_imag = 2.0;
}

static t_color hsb_to_rgb(double h, double s, double v)
{
    double r, g, b;
    int i;
    double f, p, q, t;
    h -= floor(h); // ensure h is fractional [0..1]
    h *= 6.0;
    i = (int)floor(h);
    f = h - i;
    p = v * (1.0 - s);
    q = v * (1.0 - s * f);
    t = v * (1.0 - s * (1.0 - f));
    if (i == 0) { r = v; g = t; b = p; }
    else if (i == 1) { r = q; g = v; b = p; }
    else if (i == 2) { r = p; g = v; b = t; }
    else if (i == 3) { r = p; g = q; b = v; }
    else if (i == 4) { r = t; g = p; b = v; }
    else { r = v; g = p; b = q; }

    t_color color;
    color.r = (unsigned char)(r * 255.0);
    color.g = (unsigned char)(g * 255.0);
    color.b = (unsigned char)(b * 255.0);
    color.a = 255;
    return color;
}

int	get_color_rgb(int iteration, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iteration == max_iter)
		return (0x000000); // inside the set, return black
	t = (double)iteration / max_iter;
	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return ((r << 16) | (g << 8) | b);
}


int get_color(int i, double real, double imag, t_fractol *f)
{
    if (i >= f->max_iter)
        return 0x000000; // black

    // Smooth iteration
    double mod2 = real * real + imag * imag;
    double smooth_i = i + 1.0 - log2(log2(mod2)) / log2(2.0);
    if (smooth_i < 0.0) smooth_i = 0.0; // safety clamp

    double t = smooth_i / (double)f->max_iter;
    if (t > 1.0) t = 1.0;

    // Hue from blue (0.66) to orange (0.08):
    double hue_start = 0.66;
    double hue_end   = 0.08;
    double hue_range = hue_end - hue_start;
    double hue = hue_start + hue_range * t;
    if (hue < 0) hue += 1.0; 
    if (hue > 1) hue -= 1.0;

    // Full saturation, full brightness
    t_color c = hsb_to_rgb(hue, 1.0, 1.0);
    return ((c.a << 24) | (c.r << 16) | (c.g << 8) | c.b);
}
void fractal_suite(t_complex value, t_fractol *f, int x, int y)
{
    t_complex z = value;
    int i = 0;
    while (i < f->max_iter)
    {
        if (!f->fractal_type)
            z = complex_add(complex_square(z), value);
        else
            z = complex_add(complex_square(z), f->c_julia);
        if ((z.real * z.real + z.imaginary * z.imaginary) > 4.0)
        {
            // int color = get_color(i, z.real, z.imaginary, f);
            int color = get_color_rgb(i, f -> max_iter);
            mlx_put_pixel(f->img, x, y, color);
            return;
        }
        i++;
    }
    // If we get here, point is in the set
    mlx_put_pixel(f->img, x, y, 0x000000);
}


// void	fractal_suite(t_complex value, t_fractol *f, int x, int y)
// {
// 	t_complex	z;
// 	t_complex	last;
// 	int			i;

//     last = value;
// 	i = -1;
// 	while (++i < f->max_iter)
// 	{
// 		if (!f->fractal_type)
// 			z = complex_add(complex_square(last), value);
// 		else
// 			z = complex_add(complex_square(last), f->c_julia);
// 		if ((z.real * z.real + z.imaginary * z.imaginary) > 4.0)
//         {
// 	        coloring(f, x, y, i);
//             return;
//         }
// 		last = z;
// 	}
//     mlx_put_pixel(f->img, x, y, 0x000000);
// }


void render_fractal(t_fractol *f)
{
    t_rend rend;
    t_complex c;

    rend.x = -1;
    ft_memset(f-> img -> pixels, 0, f ->img->width * f -> img->height * sizeof(int32_t));

    rend.x = -1;
    rend.scale_x = (f->max_real - f->min_real) / (double)f->width;
    rend.scale_y = (f->max_imag - f->min_imag) / (double)f->height;
    while (++(rend.x) < f->width)
    {
        rend.y = -1;
        while (++(rend.y) < f->height)
        {
            c.real = f->min_real + (rend.x) * (rend.scale_x);
            c.imaginary = f->min_imag + (rend.y) * (rend.scale_y);;
            fractal_suite(c, f, rend.x, rend.y);
        }
    }
    mlx_image_to_window(f->mlx, f->img, 0, 0);
}


int main(int ac, char **av)
{
    t_fractol fractol;
    t_fractol *f = &fractol;

    if ((ac != 2 && ac != 4) || (!ft_strncmp(av[1], "mandelbrot", 20) && ac != 2) || (!ft_strncmp(av[1], "julia", 20) && ac != 4))
        return (ft_putstr_fd("Usage: ./fractol <mandelbrot|julia> [real] [imag]\n", 2), 1);
    
    fill_fractol(f, !ft_strncmp(av[1], "julia", 20), av);
    render_fractal(f);
    mlx_key_hook(f -> mlx, &key_hook, f);
	mlx_scroll_hook(f->mlx, &scroll_hook, f);
    mlx_loop(f->mlx);
    mlx_terminate(f->mlx);
    return (0);
}

