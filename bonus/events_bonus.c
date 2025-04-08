/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:29:47 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/08 18:45:32 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	zoom_at_center(t_fractol *f, double zoom_factor)
{
	double	center_real;
	double	center_imag;
	double	width;
	double	height;

	center_real = (f->min_real + f->max_real) / 2.0;
	center_imag = (f->min_imag + f->max_imag) / 2.0;
	width = (f->max_real - f->min_real) * zoom_factor;
	height = (f->max_imag - f->min_imag) * zoom_factor;
	f->min_real = center_real - width / 2.0;
	f->max_real = center_real + width / 2.0;
	f->min_imag = center_imag - height / 2.0;
	f->max_imag = center_imag + height / 2.0;
}

void	handle_moves(mlx_key_data_t key, t_fractol *f)
{
	if (key.key == MLX_KEY_UP)
	{
		f->min_imag -= (f->max_imag - f->min_imag) * 0.04;
		f->max_imag -= (f->max_imag - f->min_imag) * 0.04;
	}
	else if (key.key == MLX_KEY_DOWN)
	{
		f->min_imag += (f->max_imag - f->min_imag) * 0.04;
		f->max_imag += (f->max_imag - f->min_imag) * 0.04;
	}
	else if (key.key == MLX_KEY_LEFT)
	{
		f->min_real -= (f->max_real - f->min_real) * 0.04;
		f->max_real -= (f->max_real - f->min_real) * 0.04;
	}
	else if (key.key == MLX_KEY_RIGHT)
	{
		f->min_real += (f->max_real - f->min_real) * 0.04;
		f->max_real += (f->max_real - f->min_real) * 0.04;
	}
	else if (key.key == MLX_KEY_C && f->color_shift < 32)
		f->color_shift += 1;
	else if (key.key == MLX_KEY_C && f->color_shift >= 32)
		f->color_shift = 0;
	else if (key.key == MLX_KEY_ESCAPE)
		ft_clean(f, "GOODBYE\n");
}

void	key_hook(mlx_key_data_t key, void *param)
{
	t_fractol	*f;

	f = (t_fractol *)param;
	if (key.key == MLX_KEY_P && f->max_iter < 400)
		f->max_iter += 10;
	else if (key.key == MLX_KEY_O && f->max_iter > 20)
		f->max_iter -= 10;
	else if (key.key == MLX_KEY_KP_ADD)
		zoom_at_center(f, 1.0 / 1.1);
	else if (key.key == MLX_KEY_KP_SUBTRACT)
		zoom_at_center(f, 1.1);
	else if (key.key == MLX_KEY_R && f->step < 2)
		(f->step)++;
	else if (key.key == MLX_KEY_E && f->step > 1)
		(f->step)--;
	else if (key.key == MLX_KEY_W && f->c_julia.rel < MAX_VALUE)
		f->c_julia.rel += INCREMENT;
	else if (key.key == MLX_KEY_S && f->c_julia.rel > MIN_VALUE)
		f->c_julia.rel -= INCREMENT;
	else if (key.key == MLX_KEY_D && f->c_julia.img < MAX_VALUE)
		f->c_julia.img += INCREMENT;
	else if (key.key == MLX_KEY_A && f->c_julia.img > MIN_VALUE)
		f->c_julia.img -= INCREMENT;
	handle_moves(key, f);
	render_fractal(f);
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fractol	*f;

	f = (t_fractol *)param;
	if (ydelta < 0)
		zoom_at_center(f, 1.1);
	else if (ydelta > 0)
		zoom_at_center(f, 1.0 / 1.1);
	render_fractal(f);
}
