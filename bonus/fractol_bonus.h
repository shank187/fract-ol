/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:56:34 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/09 14:58:40 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_BONUS_H
# define FRACTOL_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h> 
# include <math.h>
# include <MLX42/MLX42.h>

# define MIN_VALUE -2.0
# define MAX_VALUE 2.0
# define INCREMENT 0.01
# define WRONG_ARG \
	"Usage: ./fractol <mandelbrot|julia> [real] [imag]\n"
# define WRONG_FLOAT \
	"Invalid Float number for JULIA set\n"
# define DBL_MAX 1.7976931348623157e+308

typedef struct s_complex
{
	double	rel;
	double	img;
}	t_complex;

typedef struct s_fractol
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	char		color_mode;
	int			fractal_type;
	int			max_iter;
	int			height;
	int			width;
	int			step;
	double		min_real;
	double		max_real;
	double		min_imag;
	double		max_imag;
	int			co_shift;
	char		**argv;
	t_complex	c_julia;
}	t_fractol;

typedef struct s_rend
{
	int		x;
	int		y;
	double	scale_x;
	double	scale_y;
}	t_rend;

typedef struct s_color
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;
	uint32_t	color;
}	t_color;

size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_putstr_fd(char *s, int fd);
double		ft_atof(char *s);
int			is_valid_float(char *s);
void		reset_fractal(t_fractol *f, int who, char **av);
void		render_fractal(t_fractol *f);
void		key_hook(mlx_key_data_t keydata, void *param);
void		scroll_hook(double xdelta, double ydelta, void *param);
void		ft_clean(t_fractol *f, char *s);
t_complex	calcul_func(t_fractol *f, t_complex *last, t_complex point);
void		fractal_suite(t_complex point, t_fractol *f, int x, int y);

#endif
