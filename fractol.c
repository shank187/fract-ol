/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 03:19:36 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/04 16:01:47 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
void fill_fractol(t_fractol *fractol, int who, char **av)
{
    if (who == 1)
        fractol->c_julia = (t_complex){ft_atof(av[2]), ft_atof(av[3])};
    else
        fractol->c_julia = (t_complex){0.0, 0.0};
    fractol->height = 900;
    fractol->width = 900;
    fractol->mlx = mlx_init(fractol->width, fractol->height, av[1], 0);
    fractol->img = mlx_new_image(fractol->mlx, fractol->width, fractol->height);
    fractol->fractal_type = who;
    fractol->max_iter = 100;
    fractol->zoom = 1;
    fractol->move_x = 0;
    fractol->move_y = 0;
    fractol->min_real = -2.0;
    fractol->max_real = 2.0;
    fractol->min_imag = -2.0;
    fractol->max_imag = 2.0;
}

static int custom_coloring(int iter, int max_iter, double height)
{
    double t = (double)iter / max_iter;
    int r = (int)(9 * (1 - t) * t * t * t * 255);
    int g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
    int b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
    
    int shade = (int)(height * 255) & 255;
    return ((shade << 16) | (g << 8) | b);
}

static t_3d get_height(t_fractol *f, int x, int y) {
    t_3d d;
    d.h = fractal_suite(pixel_to_complex(x, y, f), f);
    d.dx = fractal_suite(pixel_to_complex(x + 1, y, f), f) - d.h;
    d.dy = fractal_suite(pixel_to_complex(x, y + 1, f), f) - d.h;
    return (d);
}

static int calc_light(t_3d d) {
    double dot;
    double lx = 0.7071, ly = 0.7071;
    dot = (d.dx * lx) + (d.dy * ly);
    return ((int)fmax(0, dot * 255));
}


static int	hsv_to_rgb(float h, float s, float v)
{
	float	c = v * s;
	float	x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
	float	m = v - c;
	float	rgb[3];

	if (h >= 0 && h < 60)
		rgb[0] = c, rgb[1] = x, rgb[2] = 0;
	else if (h < 120)
		rgb[0] = x, rgb[1] = c, rgb[2] = 0;
	else if (h < 180)
		rgb[0] = 0, rgb[1] = c, rgb[2] = x;
	else if (h < 240)
		rgb[0] = 0, rgb[1] = x, rgb[2] = c;
	else if (h < 300)
		rgb[0] = x, rgb[1] = 0, rgb[2] = c;
	else
		rgb[0] = c, rgb[1] = 0, rgb[2] = x;

	return (
		(int)((rgb[0] + m) * 255) << 16 |
		(int)((rgb[1] + m) * 255) << 8 |
		(int)((rgb[2] + m) * 255)
	);
}

void render_3d(t_fractol *f) {
    int x, y;
    t_3d d;
    int lum, color;

    for (x = 0; x < f->width; x++) {
        for (y = 0; y < f->height; y++) {
            d = get_height(f, x, y);
            lum = calc_light(d); // Light intensity
            float hue = 40 + (d.h / f->max_iter) * 60;  // Golden-yellow to red
            float saturation = 2;  // Strong colors
            float value = lum / 50.0; // Use light for brightness
            color = hsv_to_rgb(hue, saturation, value);
            mlx_put_pixel(f->img, x, y, color);
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
    render_3d(f);
    mlx_loop(f->mlx);
    mlx_terminate(f->mlx);
    return (0);
}

