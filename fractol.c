/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 03:19:36 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/08 16:41:08 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	reset_fractal(t_fractol *f, int who, char **av)
{
	f->c_julia = (t_complex){0.0, 0.0};
	if (who == 1)
		f->c_julia = (t_complex){ft_atof(av[2]), ft_atof(av[3])};
	f->height = 700;
	f->width = 700;
	f->img = NULL;
	f->mlx = NULL;
	f->mlx = mlx_init(f->width, f->height, av[1], 0);
	if (!f->mlx)
	{
		ft_clean(NULL, "Failed to initialize mlx\n");
	}
	f->img = mlx_new_image(f->mlx, f->width, f->height);
	if (!f->img)
	{
		ft_clean(f, "Failed to create image\n");
	}
	f->fractal_type = who;
	f->max_iter = 100;
	f->min_real = -2.0;
	f->max_real = 2.0;
	f->min_imag = -2.0;
	f->max_imag = 2.0;
	f->step = 1;
}

void	get_color_rgb(t_fractol *f, int i, int x, int y)
{
	double	t;
	t_color	c;
	int		iy;
	int		ix;

	if (i == f->max_iter)
		c = (t_color){0, 0, 0, 255};
	else
	{
		t = (double)i / f->max_iter;
		c.r = (unsigned int)(9 * (1 - t) * t * t * t * 255);
		c.g = (unsigned int)(15 * (1 - t) * (1 - t) * t * t * 255);
		c.b = (unsigned int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
		c.a = 255;
	}
	c.color = (c.r << 24) | (c.g << 16) | (c.b << 8) | c.a;
	iy = y;
	while (iy < y + f->step && iy < f->height)
	{
		ix = x;
		while (ix < x + f->step && ix < f->width)
			mlx_put_pixel(f->img, ix++, iy, c.color);
		iy++;
	}
}

void	fractal_suite(t_complex point, t_fractol *f, int x, int y)
{
	t_complex	z;
	t_complex	last;
	int			i;

	last = point;
	i = -1;
	while (++i < f->max_iter)
	{
		z = calcul_func(f, &last, point);
		if ((z.rel * z.rel + z.img * z.img) > 4.0)
			return (get_color_rgb(f, i, x, y));
	}
	get_color_rgb(f, f->max_iter, x, y);
}

void	render_fractal(t_fractol *f)
{
	t_rend		rend;
	t_complex	c;

	rend.scale_x = (f->max_real - f->min_real) / (double)f->width;
	rend.scale_y = (f->max_imag - f->min_imag) / (double)f->height;
	rend.x = 0;
	while (rend.x < f->width)
	{
		rend.y = 0;
		while (rend.y < f->height)
		{
			c.rel = f->min_real + rend.x * rend.scale_x;
			c.img = -(f->min_imag + rend.y * rend.scale_y);
			fractal_suite(c, f, rend.x, rend.y);
			rend.y += f->step;
		}
		rend.x += f->step;
	}
	mlx_image_to_window(f->mlx, f->img, 0, 0);
}

// void func (void)
// {system("leaks fractol");}
	// atexit(func);

int	main(int ac, char **av)
{
	t_fractol	fractol;
	t_fractol	*f;

	f = &fractol;
	if ((ac != 2 && ac != 4) || (!ft_strncmp(av[1], "mandelbrot", 20)
			&& ac != 2) || (!ft_strncmp(av[1], "julia", 20) && ac != 4))
		return (ft_putstr_fd(WRONG_ARG, 2), 1);
	reset_fractal(f, !ft_strncmp(av[1], "julia", 20), av);
	render_fractal(f);
	mlx_key_hook(f -> mlx, &key_hook, f);
	mlx_scroll_hook(f->mlx, &scroll_hook, f);
	mlx_loop(f->mlx);
	ft_clean(f, NULL);
	return (0);
}
