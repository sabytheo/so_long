/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:18:47 by tsaby             #+#    #+#             */
/*   Updated: 2025/01/21 13:13:57 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	copy_line(t_gamestruct *solong, char *line)
{
	char	**temp;
	int		i;

	if (!line)
		return (0);
	i = 0;
	solong->hmap++;
	temp = (char **)malloc(sizeof(char *) * (solong->hmap + 1));
	if (!temp)
	{
		free(line);
		free_exit(solong);
	}
	temp[solong->hmap] = NULL;
	while (i < solong->hmap - 1)
	{
		temp[i] = solong->map[i];
		i++;
	}
	temp[i] = line;
	if (solong->map)
		free(solong->map);
	solong->map = temp;
	return (1);
}

int	open_map(t_gamestruct *solong, char **argv)
{
	char	*line;

	solong->fd = open(argv[1], O_RDONLY);
	if (solong->fd < 0)
		return (0);
	while (1)
	{
		line = get_next_line(solong->fd);
		if (!copy_line(solong, line))
			break ;
	}
	close(solong->fd);
	return (1);
}
