/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 03:19:36 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/02 18:30:38 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void insert_infos(t_fractol *fractol, int who, char *av)
{
	if(who == 1)
	{
			
	}
	fractol -> fractal_type = who;
	fractol -> max_iter = 300;
	fractol -> color = 0xFF0000FF;
	fractol -> zoom = 1;
	fractol -> mlx = mlx_init(500, 500, av[2], 0);
	fractol -> move_x = 0;
	fractol -> move_y = 0;
	fractol->min_real = -2.0;
	fractol->max_real = 1.0;
	fractol->min_imag = -1.5;
	fractol->max_imag = 1.5;

}


int main(int ac, char **av)
{
	t_fractol	*fractol;

	if (ac != 2 || ac != 4)
		return (ft_putstr_fd("invalid arguiments", 0), 0);
	else if (ft_strncmp(av[1], "mandelbrot", 13) && ac == 2)
		insert_infos(fractol, 0, av);
	else if (ft_strncmp(av[1], "julia", 13) && ac == 4)
		insert_infos(fractol, 1, av);
	else
		return (ft_putstr_fd("invalid arguiments", 0), 0);
}
