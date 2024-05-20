/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:05:44 by yabukirento       #+#    #+#             */
/*   Updated: 2024/05/20 11:49:09 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (destsize == 0)
		return (src_len);
	while (i < destsize - 1 && *src != '\0')
	{
		*dest = *src;
		dest ++;
		src ++;
		i++;
	}
	*dest = '\0';
	return (src_len);
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

	if (!s1 || !s2)
		return (NULL);
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
	if (dest == NULL)
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
