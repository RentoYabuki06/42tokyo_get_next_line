/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:05:04 by yabukirento       #+#    #+#             */
/*   Updated: 2024/07/15 19:55:10 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*read_to_newline(int fd, char *saved)
{
	char	*buffer;
	char	*join_buf;
	ssize_t	bytes_read;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			if (saved)
				free(saved);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		// printf("buffer is [%s]\n", buffer);
		join_buf = ft_strjoin(saved, buffer);
		// printf("join_buf is [%s]\n", join_buf);
		if (!join_buf)
			return (free(saved), free(buffer), NULL);
		free(saved);
		saved = join_buf;
		if (ft_strchr(saved, '\n'))
			break ;
	}
	free(buffer); // バッファを解放
	return (saved);
}

static char	*extract_line(char *saved)
{
	char	*line;
	// char	*new_saved;
	size_t	len;

	len = 0;
	if (!saved)
		return (NULL);
	while (saved[len] && saved[len] != '\n')
		len++;
	if (saved[len] == '\n')
		len++;
	line = (char *)malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, saved, len + 1);
	line[len] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!saved)
		saved = ft_strdup("");
	saved = read_to_newline(fd, saved);
	if (!saved)
		return (NULL);
	line = extract_line(saved);
	if (!line && saved)
	{
		free(saved);
		saved = NULL;
	}
	if (line && line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}