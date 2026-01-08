/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexadecimal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:10:51 by kwillian          #+#    #+#             */
/*   Updated: 2026/01/08 20:47:03 by kwillian         ###   ########.fr       */
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
	// Garante que o número está no range 0-255 para evitar erros
	if (n < 0) n = 0;
	if (n > 255) n = 255;

	str = (char *)malloc(sizeof(char) * 3);
	if (!str)
		return (NULL);

	// Se n = 10 (A):
	// n / 16 = 0 -> base[0] = '0'
	// n % 16 = 10 -> base[10] = 'A'
	// Resultado: "0A"
	str[0] = base[n / 16];
	str[1] = base[n % 16];
	str[2] = '\0';
	return (str);
}


