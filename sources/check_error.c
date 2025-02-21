/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:10:01 by tsaby             #+#    #+#             */
/*   Updated: 2025/01/21 15:49:15 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_map(t_gamestruct *solong)
{
	int	i;
	int	j;

	i = 0;
	if (!solong->map || !solong->map[0])
		free_exit(solong);
	solong->wmap = ft_strlen(solong->map[0]) - 1;
	while (i < solong->hmap)
	{
		j = 0;
		while (j < solong->wmap)
		{
			if (solong->map[i][j] != 'P' && solong->map[i][j] != '1'
				&& solong->map[i][j] != '0' && solong->map[i][j] != 'C'
				&& solong->map[i][j] != 'E' && solong->map[i][j] != '\n')
			{
				write(2, "Forbidden character is detected\n", 32);
				free_exit(solong);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	check_countmap(t_gamestruct *solong)
{
	int	i;
	int	j;

	i = 0;
	while (i < solong->hmap)
	{
		j = 0;
		while (j < solong->wmap)
		{
			if (solong->map[i][j] == 'P')
			{
				solong->pcount++;
				solong->pos_x = i;
				solong->pos_y = j;
			}
			if (solong->map[i][j] == 'C')
				solong->ccount++;
			if (solong->map[i][j] == 'E')
				solong->ecount++;
			j++;
		}
		i++;
	}
	return (1);
}

static int	check_bordermap(t_gamestruct *solong)
{
	int	i;
	int	j;

	i = 0;
	while (i < solong->hmap)
	{
		j = 0;
		while (j < solong->wmap)
		{
			if (solong->map[0][j] != '1' || solong->map[solong->hmap
				- 1][j] != '1' || solong->map[i][0] != '1'
				|| solong->map[i][solong->wmap - 1] != '1')
			{
				write(2, "Border of the map must be wall\n", 31);
				free_exit(solong);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	check_rectangle(t_gamestruct *solong)
{
	int	i;

	i = 0;
	solong->wmap = ft_strlen(solong->map[0]) - 1;
	while (i < solong->hmap)
	{
		if (ft_strlen(solong->map[i]) - 1 != (unsigned long)solong->wmap)
		{
			write(2, "Error ! Map is not rectangle", 28);
			free_exit(solong);
		}
		i++;
	}
	return (1);
}

void	check_errors(t_gamestruct *solong)
{
	check_map(solong);
	check_countmap(solong);
	if (solong->pcount != 1 || solong->ccount < 1 || solong->ecount != 1)
	{
		write(2, "Wrong count of player,collectible or exit\n", 42);
		free_exit(solong);
	}
	check_rectangle(solong);
	check_bordermap(solong);
	check_path(solong);
}
