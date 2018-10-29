/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdfperspective.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akokoshk <akokoshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 18:16:43 by akokoshk          #+#    #+#             */
/*   Updated: 2018/01/15 23:16:16 by akokoshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_refresh_zlen(t_env *mx)
{
	t_counters	t;
	int			min;
	int			max;

	ft_bzero(&t, sizeof(t_counters));
	min = 0;
	max = 0;
	while (t.i < mx->map->lnum)
	{
		t.j = 0;
		while (t.j < mx->map->ln[t.i].num)
		{
			t.res = &(mx->res[(t.i * mx->map->vnum) + t.j]);
			min = (t.res->z < min) ? t.res->z : min;
			max = (t.res->z > max) ? t.res->z : max;
			t.j++;
		}
		t.i++;
	}
	mx->tr.z_len = (max - min) / 2;
}

void		ft_perspective(t_env *mx)
{
	t_counters	t;
	double		mod;

	if (mx->needperspect)
	{
		ft_bzero(&t, sizeof(t_counters));
		ft_refresh_zlen(mx);
		while (t.i < mx->map->lnum)
		{
			t.j = 0;
			while (t.j < mx->map->ln[t.i].num)
			{
				t.res = &(mx->res[(t.i * mx->map->vnum) + t.j]);
				mod = t.res->z
				/ ((mx->tr.z_len != 0) ? mx->tr.z_len : t.res->z);
				t.res->x *= mod;
				t.res->y *= mod;
				t.j++;
			}
			t.i++;
		}
	}
}
