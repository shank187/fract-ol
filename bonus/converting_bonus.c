/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:41:21 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/08 18:33:56 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

t_complex	calcul_func(t_fractol *f, t_complex *last, t_complex point)
{
	t_complex	z;
	t_complex	s;

	if (!f->fractal_type)
	{
		s.rel = (last->rel * last -> rel) - (last->img * last->img);
		s.img = 2.0 * last->rel * last->img;
		z.rel = s.rel + point.rel;
		z.img = s.img + point.img;
	}
	else
	{
		s.rel = (last->rel * last -> rel) - (last->img * last->img);
		s.img = 2.0 * last->rel * last->img;
		z.rel = s.rel + f->c_julia.rel;
		z.img = s.img + f->c_julia.img;
	}
	*last = z;
	return (z);
}

int	is_valid_float(char *s)
{
	int	i;
	int	np;
	int	valid;

	i = 0;
	np = 0;
	valid = 0;
	while (s[i])
	{
		if ((s[i] < '0' || s[i] > '9') && s[i] != '.')
			return (0);
		else if (s[i] == '.' && !np)
			np = 1;
		else if (s[i] >= '0' && s[i] <= '9')
			valid = 1;
		else
			return (0);
		i++;
	}
	return (valid);
}

static void	ft_get_sign(double *s, long *i, const char *str)
{
	*s = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*s = -1;
		(*i)++;
	}
}

double	fractional_part(char *s, int i)
{
	double	part;
	double	n;

	part = 10.00;
	n = 0.00;
	while (s[i] >= '0' && s[i] <= '9')
	{
		n += (s[i] - '0') / part;
		part *= 10;
		i++;
	}
	return (n);
}

double	ft_atof(char *s)
{
	double	sign;
	double	t;
	double	oldt;
	long	i;

	i = 0;
	t = 0;
	ft_get_sign(&sign, &i, s);
	if (!is_valid_float(&s[i]))
		return (ft_clean(NULL, "Invalid float !\n"), 0);
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (t > (DBL_MAX - (s[i] - '0')) / 10)
			ft_clean(NULL, "overflow !!\n");
		t = (t * 10) + (s[i++] - '0');
		oldt = t;
	}
	if (s[i] == '.')
		t += fractional_part(s, ++i);
	return (sign * t);
}
