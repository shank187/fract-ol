/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:29:47 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/06 18:15:07 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void zoom_at_center(t_fractol *f, double zoom_factor)
{
	double center_real = (f->min_real + f->max_real) / 2.0;
	double center_imag = (f->min_imag + f->max_imag) / 2.0;
	double width = (f->max_real - f->min_real) * zoom_factor;
	double height = (f->max_imag - f->min_imag) * zoom_factor;

	f->min_real = center_real - width / 2.0;
	f->max_real = center_real + width / 2.0;
	f->min_imag = center_imag - height / 2.0;
	f->max_imag = center_imag + height / 2.0;
}

// For zooming (e.g., with arrow keys or +/− keys)
void	key_hook(mlx_key_data_t key, void *param)
{
	t_fractol	*f = (t_fractol *)param;
	double		range_x = f->max_real - f->min_real;
	double		range_y = f->max_imag - f->min_imag;

	if (key.key == MLX_KEY_UP)
	{
		f->min_imag -= range_y * 0.04;
		f->max_imag -= range_y * 0.04;
	}
	else if (key.key == MLX_KEY_DOWN)
	{
		f->min_imag += range_y * 0.04;
		f->max_imag += range_y * 0.04;
	}
	else if (key.key == MLX_KEY_LEFT)
	{
		f->min_real -= range_x * 0.04;
		f->max_real -= range_x * 0.04;
	}
	else if (key.key == MLX_KEY_RIGHT)
	{
		f->min_real += range_x * 0.04;
		f->max_real += range_x * 0.04;
	}
	else if (key.key == MLX_KEY_P)
		f->max_iter += 10;
	else if (key.key == MLX_KEY_O)
		f->max_iter -= 10;
	render_fractal(f);
}


void scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fractol *f = (t_fractol *)param;
	if (ydelta < 0)
		zoom_at_center(f, 1.1);       // zoom out
	else if (ydelta > 0)
		zoom_at_center(f, 1.0 / 1.1); // zoom in
	render_fractal(f);
}

