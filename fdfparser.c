/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdfparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akokoshk <akokoshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 19:36:19 by akokoshk          #+#    #+#             */
/*   Updated: 2018/01/16 22:01:13 by akokoshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		ft_putver(t_ver *v, char *c, t_counters t, int lnum)
{
	if (*c != ',')
	{
		v->z = t.y;
		v->colr = (t.y != 0) ? 0xFFFFFF : 0;
	}
	else
		v->colr = (t.y == 0) ? 0xFFFFFF : t.y;
	v->x = t.j;
	v->y = lnum;
}

static int		ft_parseln(char *str, t_mapln *line, int lnum)
{
	t_counters	t;

	ft_bzero(&t, sizeof(t_counters));
	while (*str)
	{
		str = ft_skip_wspace(str);
		if (*str == ',' && str[t.i] == ',')
			return (0);
		if (str[t.i] == ',' || str[t.i] == ' ' || str[t.i] == 0)
		{
			t.x = (*str != ',') ? 10 : 16;
			t.y = ft_atoibase(str + (ft_isdigit(*str) ? 0 : 1), t.x);
			ft_putver(&(line->ver[t.j]), str, t, lnum);
			t.j += (str[t.i] == ' ') ? 1 : 0;
			str = &str[t.i];
			t.i = 0;
		}
		t.i++;
	}
	return (1);
}

static t_mapln	*ft_linealloc(t_mapln *mapln, int i, int j)
{
	t_mapln *res;
	size_t	size;

	size = sizeof(t_mapln);
	if (!(res = ft_memrealloc(mapln, size * i, size)))
		return (NULL);
	if (!(res[i].ver = ft_memalloc(sizeof(t_ver) * j)))
		return (NULL);
	res[i].num = j;
	return (res);
}

t_map			*ft_mapread(char *file)
{
	char		*ln;
	t_map		*map;
	t_counters	t;

	ft_bzero(&t, sizeof(t_counters));
	if ((t.y = open(file, O_RDONLY)) <= 0)
		return (NULL);
	if (!(map = ft_memalloc(sizeof(t_map))))
		return (NULL);
	t.i = 0;
	while ((t.x = get_next_line(t.y, &ln)) > 0)
	{
		t.j = ft_wordsnum(ln, ' ');
		map->ln = ft_linealloc(map->ln, t.i, t.j);
		map->vnum = (map->vnum < t.j) ? t.j : map->vnum;
		if (t.j == 0 || !map->ln || !ft_parseln(ln, &(map->ln[t.i]), t.i))
			return (NULL);
		t.i++;
		ft_strdel(&ln);
	}
	ft_strdel(&ln);
	((t.y > 0) ? close(t.y) : 0);
	map->lnum = t.i;
	return ((t.x < 0) ? NULL : map);
}
