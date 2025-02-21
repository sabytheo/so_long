/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycontrol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:32:02 by tsaby             #+#    #+#             */
/*   Updated: 2025/01/21 13:14:43 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	conditional_move(t_gamestruct *solong, int x, int y)
{
	if (solong->map[x][y] == 'E')
	{
		if (solong->ccount != 0)
			return (0);
		ft_printf("You win with %d step !\n", solong->step);
		free_exit(solong);
	}
	if (solong->map[x][y] == '0')
	{
		solong->map[x][y] = 'P';
		solong->pos_x = x;
		solong->pos_y = y;
		solong->step++;
	}
	if (solong->map[x][y] == 'C')
	{
		solong->map[x][y] = 'P';
		solong->pos_x = x;
		solong->pos_y = y;
		solong->step++;
		solong->ccount--;
	}
	if (solong->map[x][y] == '1')
		return (0);
	return (1);
}

static int	move_up_down(t_gamestruct *solong, int keypress)
{
	int	x;
	int	y;
	int	a;

	x = solong->pos_x;
	y = solong->pos_y;
	if (keypress == W)
	{
		x--;
		a = conditional_move(solong, x, y);
		if (!a)
			return (0);
		solong->map[x + 1][y] = '0';
	}
	if (keypress == S)
	{
		x++;
		a = conditional_move(solong, x, y);
		if (!a)
			return (0);
		solong->map[x - 1][y] = '0';
	}
	return (1);
}

static int	move_right_left(t_gamestruct *solong, int keypress)
{
	int	x;
	int	y;
	int	a;

	x = solong->pos_x;
	y = solong->pos_y;
	if (keypress == A)
	{
		y--;
		a = conditional_move(solong, x, y);
		if (!a)
			return (0);
		solong->map[x][y + 1] = '0';
	}
	if (keypress == D)
	{
		y++;
		a = conditional_move(solong, x, y);
		if (!a)
			return (0);
		solong->map[x][y - 1] = '0';
	}
	return (1);
}

int	define_control(int keypress, t_gamestruct *solong)
{
	int	temp;

	temp = -1;
	if (keypress == ESCAPE)
		free_exit(solong);
	if (keypress == A)
		temp = move_right_left(solong, keypress);
	if (keypress == W)
		temp = move_up_down(solong, keypress);
	if (keypress == S)
		temp = move_up_down(solong, keypress);
	if (keypress == D)
		temp = move_right_left(solong, keypress);
	if (temp == 1)
		print_image(solong);
	return (1);
}
