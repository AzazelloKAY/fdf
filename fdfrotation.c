/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdfrotation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akokoshk <akokoshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 22:10:11 by akokoshk          #+#    #+#             */
/*   Updated: 2018/01/15 23:07:08 by akokoshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	ft_calc_resx(t_env *mx, int x, int y, int z)
{
	double alp;
	double bet;
	double gam;

	alp = mx->tr.x_rad;
	bet = mx->tr.y_rad;
	gam = mx->tr.z_rad;
	return ((((x * cos(bet)) - (((z * cos(alp))
		- (y * sin(alp))) * sin(bet))) * cos(gam))
		+ (((y * cos(alp)) + (z * sin(alp))) * sin(gam)));
}

static double	ft_calc_resy(t_env *mx, int x, int y, int z)
{
	double alp;
	double bet;
	double gam;

	alp = mx->tr.x_rad;
	bet = mx->tr.y_rad;
	gam = mx->tr.z_rad;
	return ((((y * cos(alp)) + (z * sin(alp))) * cos(gam))
		- (((x * cos(bet)) - (((z * cos(alp)) - (y * sin(alp)))
			* sin(bet))) * sin(gam)));
}

static double	ft_calc_resz(t_env *mx, int x, int y, int z)
{
	double alp;
	double bet;
	double gam;

	alp = mx->tr.x_rad;
	bet = mx->tr.y_rad;
	gam = mx->tr.z_rad;
	return ((((z * cos(alp)) - (y * sin(alp))) *
		cos(bet)) + (x * sin(bet)));
}

void			ft_rotate_vertex(t_env *mx, t_ver *res)
{
	int	x;
	int	y;
	int	z;

	x = res->x;
	y = res->y;
	z = res->z;
	res->x = ft_calc_resx(mx, x, y, z);
	res->y = ft_calc_resy(mx, x, y, z);
	res->z = ft_calc_resz(mx, x, y, z);
}

void			ft_calc_radians(t_env *mx)
{
	mx->tr.x_rad = M_PI * mx->tr.x_ang / 180;
	mx->tr.y_rad = M_PI * mx->tr.y_ang / 180;
	mx->tr.z_rad = M_PI * mx->tr.z_ang / 180;
}
