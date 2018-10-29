/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdfmakeres.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akokoshk <akokoshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 19:26:45 by akokoshk          #+#    #+#             */
/*   Updated: 2018/01/16 20:09:44 by akokoshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_scale_vertex(t_ver *res, t_ver *ver, int scale)
{
	res->x = ver->x * scale;
	res->y = ver->y * scale;
	res->z = ver->z * scale;
	res->colr = ver->colr;
}

int			ft_init_res(t_env *mx)
{
	size_t ressize;

	if (mx->res)
		ft_memdel((void*)&(mx->res));
	if (!(mx->res) && mx->map)
	{
		ressize = sizeof(t_ver) * (mx->map->lnum * mx->map->vnum);
		if (!(mx->res = ft_memalloc(ressize)))
			return (0);
	}
	return (1);
}

void		ft_fill_res(t_env *mx)
{
	t_counters	t;

	ft_bzero(&t, sizeof(t_counters));
	while (t.i < mx->map->lnum)
	{
		t.j = 0;
		while (t.j < mx->map->ln[t.i].num)
		{
			t.res = &(mx->res[(t.i * mx->map->vnum) + t.j]);
			t.ver = &(mx->map->ln[t.i].ver[t.j]);
			ft_scale_vertex(t.res, t.ver, mx->tr.scale);
			ft_rotate_vertex(mx, t.res);
			t.j++;
		}
		t.i++;
	}
	ft_perspective(mx);
}

int			ft_put_res_to_img(t_env *mx)
{
	t_counters	t;

	ft_bzero(&t, sizeof(t_counters));
	while (t.i < mx->map->lnum)
	{
		t.j = 0;
		while (t.j < mx->map->ln[t.i].num)
		{
			t.res = &(mx->res[(t.i * mx->map->vnum) + t.j]);
			ft_imgput(mx, t.res->y, t.res->x, t.res->colr);
			t.j++;
		}
		t.i++;
	}
	return (1);
}

void		ft_centering_map(t_map *map)
{
	t_counters	t;
	int			z_mod;

	ft_bzero(&t, sizeof(t_counters));
	t.x = map->vnum / 2;
	t.y = map->lnum / 2;
	z_mod = ft_zextr(map);
	while (t.i < map->lnum)
	{
		t.j = 0;
		while (t.j < map->ln[t.i].num)
		{
			t.ver = &(map->ln[t.i].ver[t.j]);
			t.ver->x -= t.x;
			t.ver->y -= t.y;
			t.ver->z += z_mod;
			t.j++;
		}
		t.i++;
	}
}
