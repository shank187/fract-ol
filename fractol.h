#ifndef FRACTOL_H
# define FRACTOL_H

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include "MLX42/MLX42.h"

typedef struct s_fractol
{
    /*** MiniLibX Window & Image ***/
    void    *mlx;        // Connection to MiniLibX
 

    /*** Fractal Type & Parameters ***/
    int     fractal_type;   // 0 = Mandelbrot, 1 = Julia, 2 = Other
    int     max_iter;       // Maximum iterations for fractal calculations
    double  zoom;           // Zoom factor
    double  move_x;         // Horizontal movement
    double  move_y;         // Vertical movement

    /*** Complex Plane ***/
    double  min_real;       // Minimum real part of complex plane
    double  max_real;       // Maximum real part
    double  min_imag;       // Minimum imaginary part
    double  max_imag;       // Maximum imaginary part

    /*** Julia Set Parameter (If Julia is Selected) ***/
    double  julia_real;     // Real part of Julia's C constant
    double  julia_imag;     // Imaginary part of Julia's C constant

    /*** Color Management ***/
    int     color;          // RGBA color value for rendering
    int     color_shift;    // Allows changing colors dynamically

}   t_fractol;
typedef struct s_complex
{
	double natural;
	int imaginary;
} t_complex;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
double	ft_atof(char *s);
int		is_valid_float(char *s);


#endif