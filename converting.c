/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:41:21 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/02 17:32:05 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


static void	ft_get_sign(int *s, long *i, const char *str)
{
	*s = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*s = -1;
		(*i)++;
	}
}

double fractional_part(char *s, int i)
{
	double	part;
	double	n;

	part = 10.00;
	n = 0.00;
	while(s[i] >= '0' && s[i] <= '9')
	{
		n += (s[i] - '0')/part;
		part *= 10;
		i++;
	}
	return(n);
}

double	ft_atof(char *s)
{
	double sign;
	double t;
	double oldt;
	int i;

	if(!is_valid_float(s))
		return(printf("Invalid float !\n"), 0);
	sign = 1.0000;
	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (t > (DBL_MAX - (s[i] - '0')) / 10)
			return(printf("overflow !!\n"), 1);
		t = (t * 10) + (s[i++] - '0');
		oldt = t;
	}
	if(s[i])
		t += fractional_part(s, ++i);
	return(sign * t);
}
