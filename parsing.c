/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:43:12 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/02 17:32:08 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int is_valid_float(char *s)
{
	int i;
	int np;
	int valid;

	i = 0;
	np = 0;
	valid = 0;
	while(s[i])
	{
		if((s[i] < '0' || s[i] > '9') && s[i] != '.')
			return(0);
		else if(s[i] == '.' && !np)
			np = 1;
		else if (s[i] >= '0'  && s[i] <= '9')
			valid = 1;
		else
			return(0);
		i++;
	}
	return(valid);
}