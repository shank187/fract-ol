/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sstring_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 03:20:17 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/08 19:58:48 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	ft_clean(t_fractol *f, const char *s)
{
	if (s)
		perror(s);
	// if (f->mlx)
	// 	mlx_close_window(f->mlx);
	// if (f->img)
		// mlx_delete_image(f->mlx, f->img);
	mlx_terminate(f->mlx);
	exit(0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			j;
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	j = 0;
	while ((us1[j] && us2[j]) && us1[j] == us2[j] && j < n - 1 && n)
		j++;
	if (us1[j] < us2[j] && n)
		return (-1);
	if (us1[j] > us2[j] && n)
		return (1);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
