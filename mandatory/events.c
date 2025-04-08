/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:29:47 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/08 18:26:19 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

void	key_hook(mlx_key_data_t key, void *param)
{
	t_fractol	*f;

	f = (t_fractol *)param;
	if (key.key == MLX_KEY_ESCAPE)
		ft_clean(f, "GOODBYE\n");
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
