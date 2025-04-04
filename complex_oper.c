/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_oper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:53:37 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/04 14:34:01 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex complex_add(t_complex num1, t_complex num2)
{
	t_complex result;
	result.real = num1.real + num2.real;
	result.imaginary = num1.imaginary + num2.imaginary;
	return(result);
}

t_complex complex_square(t_complex z)
{
    t_complex result;
    long double real_part = (long double)z.real * (long double)z.real;
    long double imag_part = (long double)z.imaginary * (long double)z.imaginary;
    result.real = (double)(real_part - imag_part);
    result.imaginary = (double)(2.0 * (long double)z.real * (long double)z.imaginary);
    return result;
}
