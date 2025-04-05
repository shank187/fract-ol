/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:29:47 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/05 15:01:08 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


// For zooming (e.g., with arrow keys or +/− keys)
void	key_hook(mlx_key_data_t key, void *param)
{
	t_fractol	*f;
	double		step;

	f = (t_fractol *)param;
	step = 0.1 * f->zoom;
	if (key.key == MLX_KEY_UP)
		f->move_y -= step;
	else if (key.key == MLX_KEY_DOWN)
		f->move_y += step;
	else if (key.key == MLX_KEY_LEFT)
		f->move_x -= step;
	else if (key.key == MLX_KEY_RIGHT)
		f->move_x += step;
	else if (key.key == MLX_KEY_KP_ADD)
		f->zoom *= 1.1;
	else if (key.key == MLX_KEY_MINUS)
		f->zoom /= 1.1;
	render_fractal(f);
}

void scroll_hook(double xdelta, double ydelta, void *param)
{
    t_fractol   *f;

    if(!xdelta)
        xdelta=1;
    f = (t_fractol *) param;
    if (ydelta < 0)
        f->zoom *= 1.1;
    else if (ydelta > 0) 
        f->zoom /= 1.1;

    render_fractal(f); 
}
