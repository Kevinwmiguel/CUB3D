/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:28:56 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/08 15:29:01 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int	start;
	int	end;
	char	*res;
	int	i;

	if (!s1 || !set)
		return (NULL);

	start = 0;
	while (s1[start] && is_set(s1[start], set))
		start++;

	end = 0;
	while (s1[end])
		end++;
	end--;

	while (end >= start && is_set(s1[end], set))
		end--;

	res = malloc(end - start + 2);
	if (!res)
		return (NULL);

	i = 0;
	while (start <= end)
		res[i++] = s1[start++];
	res[i] = '\0';
	return (res);
}
