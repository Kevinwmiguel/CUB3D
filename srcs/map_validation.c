/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 22:33:10 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/30 15:10:59 by kwillian         ###   ########.fr       */
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

static void	skip_space_chars(char **s)
{
	while (**s == ' ' || **s == '\t')
		(*s)++;
}

static int	parse_rgb_component(char **s)
{
	char	*start;
	int		value;

	if (**s < '0' || **s > '9')
		return (-1);
	start = *s;
	while (**s >= '0' && **s <= '9')
		(*s)++;
	if (*s - start > 3)
		return (-1);
	value = ft_atoi(start);
	if (value < 0 || value > 255)
		return (-1);
	return (value);
}

int	check_rgb_format(char *line)
{
	char	*s;
	int		i;

	if (!line)
		return (0);
	s = line;
	skip_space_chars(&s);
	if (*s != 'F' && *s != 'C')
		return (0);
	s++;
	if (*s != ' ')
		return (0);
	s++;
	skip_space_chars(&s);
	i = 0;
	while (i < 3)
	{
		if (parse_rgb_component(&s) < 0)
			return (0);
		i++;
		skip_space_chars(&s);
		if (i == 3)
			break ;
		if (*s != ',')
			return (0);
		s++;
		skip_space_chars(&s);
	}
	while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r')
		s++;
	return (*s == '\0');
}
