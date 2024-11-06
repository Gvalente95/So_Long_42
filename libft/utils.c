/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:30:10 by gvalente          #+#    #+#             */
/*   Updated: 2024/10/23 14:15:25 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	return ((int)write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	len;
	int	res;

	res = 1;
	if (str == NULL)
		return (ft_putstr("(null)"));
	len = 0;
	while (str[len])
		if (ft_putchar(str[len++]) == -1)
			return (-1);
	return (len);
}

int	ft_strlen(const char *src)
{
	int	i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

char	*ft_strdup(const char	*s1)
{
	char	*dst;
	int		i;
	int		len;

	len = ft_strlen(s1);
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	ft_putptr(void *ptr)
{
	uintptr_t	address;
	char		buffer[16];
	int			i;
	int			count;

	if (!ptr)
		return (ft_putstr("0x0"));
	address = (uintptr_t)ptr;
	count = ft_putstr("0x");
	if (count == -1)
		return (-1);
	i = 0;
	while (address)
	{
		buffer[i++] = HEXDIGITS_MIN[address % 16];
		address /= 16;
	}
	while (i--)
	{
		if (ft_putchar(buffer[i]) == -1)
			return (-1);
		count++;
	}
	return (count);
}
