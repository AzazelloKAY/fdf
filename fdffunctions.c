/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdffunctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akokoshk <akokoshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 19:43:40 by akokoshk          #+#    #+#             */
/*   Updated: 2018/01/16 20:10:30 by akokoshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			ft_zextr(t_map *map)
{
	t_counters	t;

	ft_bzero(&t, sizeof(t_counters));
	t.x = map->ln[0].ver[0].z;
	t.y = map->ln[0].ver[0].z;
	while (t.i < map->lnum)
	{
		t.j = 0;
		while (t.j < map->ln[t.i].num)
		{
			t.ver = &(map->ln[t.i].ver[t.j]);
			t.x = (t.x > t.ver->z) ? t.ver->z : t.x;
			t.y = (t.y < t.ver->z) ? t.ver->z : t.y;
			t.j++;
		}
		t.i++;
	}
	return (t.y - t.x);
}

char		*ft_skip_wspace(char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	return (str);
}

void		ft_imgput(t_env *mx, int l, int v, uint32_t colr)
{
	l -= mx->tr.min_y;
	v -= mx->tr.min_x;
	((uint32_t*)mx->img.str)[((mx->img.v * l) + v)] = colr;
}

int			ft_cmpdlt(int a, int b)
{
	return ((a > b) ? (a - b) : (b - a));
}

int			ft_atoibase(char *str, int base)
{
	int	res;
	int	neg;

	res = 0;
	if (str == NULL || base <= 0)
		return (0);
	str = ft_skip_wspace(str);
	neg = (*str == '-') ? -1 : 1;
	str = ((*str == '+') || (*str == '-')) ? (str + 1) : str;
	if (ft_strlen(str) > 2 && base == 16 &&
		str[0] == '0' && (ft_toupper(str[1]) == 'X'))
		str = &str[2];
	while (*str)
	{
		if (ft_isdigit(*str) && (*str - '0') < base)
			res = (res * base) + (*str - '0');
		else if (ft_isalpha(*str) && (ft_toupper(*str) - 'A' + 10) < base)
			res = (res * base) + (ft_toupper(*str) - 'A' + 10);
		else
			break ;
		str++;
	}
	return (res * neg);
}
