/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_calcul.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:52:58 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/04 17:58:33 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
