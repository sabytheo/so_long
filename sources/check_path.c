/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:31:41 by tsaby             #+#    #+#             */
/*   Updated: 2025/01/21 13:12:49 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map_copy(char **map, t_gamestruct *solong)
{
	int	line;

	line = 0;
	while (line < solong->hmap)
		free(map[line++]);
	free(map);
}

static char	**copy_map(t_gamestruct *solong)
{
	int	i;
	int	j;

	solong->map_copy = malloc(solong->hmap * sizeof(char *));
	if (!solong->map_copy)
		return (NULL);
	i = 0;
	while (i < solong->hmap)
	{
		solong->map_copy[i] = malloc((solong->wmap + 1) * sizeof(char));
		if (!solong->map_copy[i])
		{
			free(solong->map_copy);
			return (NULL);
		}
		j = 0;
		while (j < solong->wmap + 1)
		{
			solong->map_copy[i][j] = solong->map[i][j];
			j++;
		}
		i++;
	}
	return (solong->map_copy);
}

void	flood_fill(char **map, int x, int y, t_gamestruct *solong)
{
	if (x < 0 || x >= solong->hmap || y < 0 || y >= solong->wmap)
		return ;
	if (map[x][y] == 'P')
		map[x][y] = '2';
	else if (map[x][y] == 'C' || map[x][y] == '0')
		map[x][y] = '2';
	else
		return ;
	flood_fill(map, x + 1, y, solong);
	flood_fill(map, x - 1, y, solong);
	flood_fill(map, x, y + 1, solong);
	flood_fill(map, x, y - 1, solong);
}

static int	valid_path(t_gamestruct *solong)
{
	int	i;
	int	j;

	i = 0;
	while (i < solong->hmap)
	{
		j = 0;
		while (j < solong->wmap)
		{
			if (solong->map_copy[i][j] == 'C')
				return (0);
			if (solong->map_copy[i][j] == 'E')
			{
				if (solong->map_copy[i + 1][j] != '2' && solong->map_copy[i
					- 1][j] != '2' && solong->map_copy[i][j - 1] != '2'
					&& solong->map_copy[i][j + 1] != '2')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_path(t_gamestruct *solong)
{
	int	player_x;
	int	player_y;

	if (!copy_map(solong))
		free_exit(solong);
	player_x = solong->pos_x;
	player_y = solong->pos_y;
	flood_fill(solong->map_copy, player_x, player_y, solong);
	if (!valid_path(solong))
	{
		write(2, "No path to reach finish exist !\n", 32);
		return (free_map_copy(solong->map_copy, solong), free_exit(solong));
	}
	free_map_copy(solong->map_copy, solong);
	return (1);
}
