/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 22:33:10 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/31 21:52:39 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

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

int	help_lines(char **s)
{
	skip_space_chars(s);
	if (**s != 'F' && **s != 'C')
		return (0);
	(*s)++;
	if (**s != ' ')
		return (0);
	(*s)++;
	skip_space_chars(s);
	return (1);
}

int	check_rgb_format(char *line)
{
	char	*s;
	int		i;

	if (!line)
		return (0);
	s = line;
	if (!help_lines(&s))
		return (0);
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
