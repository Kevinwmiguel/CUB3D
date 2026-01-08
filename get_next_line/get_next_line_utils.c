/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:25:47 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/08 00:33:16 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*buffer_full_clear(int fd, char **buffer, char *line)
{
	size_t	i;

	if (fd >= 0 && fd < FOPEN_MAX)
	{
		i = 0;
		while (buffer && buffer[fd][i])
			buffer[fd][i++] = '\0';
	}
	if (line)
		free(line);
	return (NULL);
}

int	next_line(char **line, char *buffer)
{
	char	*join;
	int		i;

	join = ft_strjoin2(*line, buffer);
	free(*line);
	if (join == NULL)
		return (-1);
	*line = join;
	i = 0;
	while ((*line)[i] != '\0')
	{
		if ((*line)[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen2(char const *str1)
{
	int	i;

	if (str1 == NULL)
		return (0);
	i = 0;
	while (str1[i] != '\0')
	{
		if (str1[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*ft_strjoin2(char const *str1, char const *str2)
{
	char	*str3;
	int		i;
	int		j;

	str3 = (char *)malloc(ft_strlen2(str1) + ft_strlen2(str2) + 1);
	if (!str3)
		return (str3);
	i = 0;
	j = 0;
	while (str1 != NULL && str1[i] != '\0')
		str3[j++] = str1[i++];
	i = 0;
	while (str2 != NULL && str2[i] != '\0')
	{
		str3[j++] = str2[i++];
		if (str2[i - 1] == '\n')
			break ;
	}
	str3[j] = '\0';
	return (str3);
}

void	buffer_clear(char *buffer)
{
	int	blen;
	int	n_cases;
	int	i;

	blen = 0;
	while (buffer[blen] != '\0')
		blen++;
	n_cases = ft_strlen2(buffer);
	i = 0;
	while (i < blen)
	{
		if (n_cases + i < blen)
		{
			buffer[i] = buffer[n_cases + i];
			buffer[n_cases + i] = '\0';
		}
		else
			buffer[i] = '\0';
		i++;
	}
}
