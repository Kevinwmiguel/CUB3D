/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 22:33:10 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/17 23:07:24 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	clean_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\r')
		{
			str[i] = '\0';
			return ;
		}
		i++;
	}
}

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	in_range_0_255(char *str)
{
	int	n;

	n = ft_atoi(str);
	if (n < 0 || n > 255)
		return (0);
	return (1);
}

int	ft_strlen3(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

int	check_rgb_format(char *line)
{
	char	**tmp;
	char	**rgb;
	int		i;

	if (!line || (line[0] != 'F' && line[0] != 'C') || line[1] != ' ')
		return (0);
	tmp = ft_split(line, ' ');
	if (!tmp || !tmp[1] || tmp[2])
		return (ft_free_split(tmp), 0);
	clean_newline(tmp[1]);
	rgb = ft_split(tmp[1], ',');
	ft_free_split(tmp);
	if (!rgb)
		return (0);
	i = ft_strlen3(rgb);
	if (i != 3)
		return (ft_free_split(rgb), 0);
	if (!is_number(rgb[0]) || !is_number(rgb[1]) || !is_number(rgb[2]))
		return (ft_free_split(rgb), 0);
	if (!in_range_0_255(rgb[0]) || !in_range_0_255(rgb[1])
		|| !in_range_0_255(rgb[2]))
		return (ft_free_split(rgb), 0);
	ft_free_split(rgb);
	return (1);
}
