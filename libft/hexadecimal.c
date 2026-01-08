/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexadecimal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:10:51 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/08 18:41:40 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_hex_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 16;
		len++;
	}
	return (len);
}

char	*ft_int_to_hex(int n)
{
	char	*str;
	char	*base;

	base = "0123456789ABCDEF";
	str = (char *)malloc(sizeof(char) * 3);
	if (!str)
		return (NULL);
	str[0] = base[(n / 16) % 16];
	str[1] = base[n % 16];
	str[2] = '\0';
	return (str);
}

