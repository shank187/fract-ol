/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 03:19:36 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/05 16:27:49 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


void fill_fractol(t_fractol *fractol, int who, char **av)
{
    if (who == 1)
        fractol->c_julia = (t_complex){ft_atof(av[2]), ft_atof(av[3])};
    else
        fractol->c_julia = (t_complex){0.0, 0.0};
    fractol->height = 700;
    fractol->width = 700;
    fractol->mlx = mlx_init(fractol->width, fractol->height, av[1], 0);
    fractol->img = mlx_new_image(fractol->mlx, fractol->width, fractol->height);
    fractol->fractal_type = who;
    fractol->max_iter = 200;
    fractol->zoom = 1;
    fractol->move_x = 0;
    fractol->move_y = 0;
	fractol->min_real = -2.0;
	fractol->max_real = 2.0;
	fractol->min_imag = -2.0;
	fractol->max_imag = 2.0;
}

static int get_color(int iteration, int max_iter)
{
    if (iteration == -1)
        return 0x000000;
    
    double t = (double)iteration / max_iter;
    int r = (int)(9 * (1 - t) * t * t * t * 255);
    int g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
    int b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);

    return (r << 16) | (g << 8) | b;
}

int fractal_suite(t_complex value, t_fractol *fractol)
{
    t_complex last;
    t_complex z;
    int i;
    int iteration;

    last.imaginary = 0; 
    last.real = 0; 
    if (fractol->fractal_type)
        last = value;
    iteration = fractol->max_iter;
    i = 0;
    while (i < iteration)
    {
        if (!(fractol->fractal_type))
            z = complex_add(complex_square(last), value);
        else
            z = complex_add(complex_square(last), fractol->c_julia);
		if ((z.real * z.real + z.imaginary * z.imaginary) > (4.0 + EPSILON))
            return i;
        last = z;
        i++;
    }
    return -1;
}

t_complex pixel_to_complex(int x, int y, t_fractol *f) {
    t_complex c;
    double scale_x = (f->max_real - f->min_real) / (double)f->width;
    double scale_y = (f->max_imag - f->min_imag) / (double)f->height;

    c.real = f->min_real + (x) * scale_x * f->zoom + f->move_x;
    c.imaginary = f->min_imag + (y) * scale_y * f->zoom + f->move_y;

    return c;
}


void render_fractal(t_fractol *f)
{
    int x, y, iteration;
    t_complex c;

    x = -1;
    while (++x < f->width)
    {
        y = -1;
        while (++y < f->height)
        {
            c = pixel_to_complex(x, y, f);
            iteration = fractal_suite(c, f);
            int color = get_color(iteration, f->max_iter);            
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
    render_fractal(f);
    mlx_key_hook(f -> mlx, &key_hook, f);
	mlx_scroll_hook(f->mlx, &scroll_hook, f);
    mlx_loop(f->mlx);
    mlx_terminate(f->mlx);
    return (0);
}

