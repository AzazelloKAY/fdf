/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_brez.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akokoshk <akokoshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 20:01:56 by akokoshk          #+#    #+#             */
/*   Updated: 2018/01/15 22:19:07 by akokoshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_brzcalc(t_env *mx, t_brez *brz)
{
	int			i;
	int			j;
	int			res;
	uint32_t	color;

	i = (brz->axis == 1) ? brz->a->x : brz->a->y;
	j = (brz->axis == 1) ? brz->b->x : brz->b->y;
	if (brz->axis == 1)
		while (i <= j)
		{
			res = brz->a->y + ((i - brz->a->x) * brz->dlt);
			color = brz->colr + (brz->colrstp * (i - brz->a->x));
			ft_imgput(mx, res, i++, color);
		}
	else
		while (i <= j)
		{
			res = brz->a->x + ((i - brz->a->y) * brz->dlt);
			color = brz->colr + (brz->colrstp * (i - brz->a->y));
			ft_imgput(mx, i++, res, color);
		}
}

void		ft_drawbeam(t_env *mx, t_ver *a, t_ver *b)
{
	t_brez		brz;
	int			tdlt;
	uint32_t	tclr;

	brz.axis = (abs(ft_cmpdlt(a->x, b->x))
		> abs(ft_cmpdlt(a->y, b->y))) ? 1 : 2;
	if (brz.axis == 1)
		brz.a = (a->x < b->x) ? a : b;
	if (brz.axis == 1)
		brz.b = (a->x < b->x) ? b : a;
	if (brz.axis == 2)
		brz.a = (a->y < b->y) ? a : b;
	if (brz.axis == 2)
		brz.b = (a->y < b->y) ? b : a;
	brz.dx = brz.b->x - brz.a->x;
	brz.dy = brz.b->y - brz.a->y;
	tdlt = (brz.axis == 1) ? brz.dx : brz.dy;
	tclr = (brz.b->colr != 0) ? brz.b->colr : 0xFFFFFF;
	brz.colr = (brz.a->colr != 0) ? brz.a->colr : 0xFFFFFF;
	brz.colrstp = ft_cmpdlt(brz.colr, tclr);
	brz.colrstp = ((tdlt != 0) ? brz.colrstp / tdlt : 0);
	brz.colrstp *= (brz.colr < tclr) ? 1 : -1;
	if (brz.dx != 0 || brz.dy != 0 || (brz.dlt = 0))
		brz.dlt = (brz.axis == 1) ? brz.dy / brz.dx : brz.dx / brz.dy;
	ft_brzcalc(mx, &brz);
}

int			ft_put_lines_to_img(t_env *mx)
{
	t_counters	t;

	ft_bzero(&t, sizeof(t_counters));
	while (t.i < mx->map->lnum)
	{
		t.j = 0;
		while (t.j < mx->map->ln[t.i].num)
		{
			t.res = &(mx->res[(t.i * mx->map->vnum) + t.j]);
			if (t.j + 1 != mx->map->ln[t.i].num)
				ft_drawbeam(mx,
					&(mx->res[(t.i * mx->map->vnum) + (t.j + 1)]), t.res);
			if (t.i + 1 != mx->map->lnum)
				ft_drawbeam(mx,
					&(mx->res[((t.i + 1) * mx->map->vnum) + t.j]), t.res);
			t.j++;
		}
		t.i++;
	}
	return (1);
}
