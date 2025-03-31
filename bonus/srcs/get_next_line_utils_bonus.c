/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:20:40 by yabukirento       #+#    #+#             */
/*   Updated: 2024/07/20 15:39:21 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	pc;

	i = 0;
	pc = c;
	while (s[i])
	{
		if (s[i] == pc)
		{
			return ((char *)(s + i));
		}
		i++;
	}
	if (s[i] == pc)
		return ((char *)(s + i));
	return ((void *)0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ans;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	ans = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!ans)
		return (NULL);
	ft_strlcpy(ans, s1, len_s1 + 1);
	ft_strlcpy(ans + len_s1, s2, len_s2 + 1);
	return (ans);
}

char	*ft_strdup(const char *src)
{
	int		i;
	int		len;
	char	*dest;

	len = 0;
	while (src[len])
		len++;
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
