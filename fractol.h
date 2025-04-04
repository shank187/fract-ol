#ifndef FRACTOL_H
# define FRACTOL_H

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include "MLX42/MLX42.h"
#include <math.h>
#include <stdio.h>

#define EPSILON 1e-9  // Small threshold to avoid floating-point errors

typedef struct s_complex
{
	double real;
	double imaginary;
} t_complex;


typedef struct s_fractol
{
	void		*mlx;        // Connection to MiniLibX
	mlx_image_t	*img;        // Image instance
	char color_mode;
	/*** Fractal Type & Parameters ***/
	int			fractal_type;   // 0 = Mandelbrot, 1 = Julia, 2 = Other
	int			max_iter;       // Maximum iterations for fractal calculations
	double  	zoom;           // Zoom factor
	double  	move_x;         // Horizontal movement
	double  	move_y;         // Vertical movement
	int			height;
	int			width;

	/*** Complex Plane ***/
	double		min_real;       // Minimum real part of complex plane
	double		max_real;       // Maximum real part
	double		min_imag;       // Minimum imaginary part
	double		max_imag;       // Maximum imaginary part

	/*** Julia Set Parameter (If Julia is Selected) ***/
	t_complex	c_julia;
	/*** Color Management ***/
	int			color;          // RGBA color value for rendering
	int			color_shift;    // Allows changing colors dynamically

}   t_fractol;



typedef struct s_3d {
    double  h;
    double  dx;
    double  dy;
    int     clr;
}           t_3d;

size_t	ft_strlen(const char *s);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
double	ft_atof(char *s);
int		is_valid_float(char *s);
t_complex complex_add(t_complex num1, t_complex num2);
t_complex complex_square(t_complex num);
int fractal_suite(t_complex value, t_fractol *fractol);
t_complex pixel_to_complex(int x, int y, t_fractol *fractol);


#endif
