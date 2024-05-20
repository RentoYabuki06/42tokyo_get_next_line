/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:05:04 by yabukirento       #+#    #+#             */
/*   Updated: 2024/05/20 13:17:10 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*allocate_and_init_buffer(void)
{
	char	*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	return (buffer);
}

static char	*read_loop(int fd, char *saved, char *buffer)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = 1;
	while (!ft_strchr(saved, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			if (saved)
				free(saved);
			return (NULL);
		}
		if (saved[0] == '\0' && buffer[0] == '\0')
		{
			free(buffer);
			if (saved)
				free(saved);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = saved;
		saved = ft_strjoin(saved, buffer);
		if (!saved)
		{
			free(buffer);
			free(temp);
			return (NULL);
		}
		if (bytes_read == 0 && saved[0] == '\0') // Check if nothing was added
		{
			free(saved);
			saved = NULL;
			free(temp);
			break;
		}
		free(temp);
	}
	return (saved);
}

static char	*read_to_newline(int fd, char *saved)
{
	char	*buffer;

	buffer = allocate_and_init_buffer();
	if (!buffer)
		return (NULL);
	if (!saved)
	{
		saved = ft_strdup("");
		if (!saved)
		{
			if (buffer)
				free(buffer);
			return (NULL);
		}
	}
	saved = read_loop(fd, saved, buffer);
	if (buffer)
		free(buffer);
	return (saved);
}

static char	*extract_line(char **saved)
{
	char	*line;
	char	*new_saved;
	size_t	len;

	len = 0;
	if (!*saved || !**saved)
		return (NULL);
	while ((*saved)[len] && (*saved)[len] != '\n')
		len++;
	if ((*saved)[len] == '\n')
		len++;
	line = (char *)malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, *saved, len + 1);
	line[len] = '\0';
	new_saved = ft_strdup(*saved + len);
	if (!new_saved)
	{
		if (line)
			free(line);
		return (NULL);
	}
	if (*saved)
		free(*saved);
	*saved = new_saved;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (saved)
		{
			free(saved);
			saved = NULL;
		}
		return (NULL);
	}
	saved = read_to_newline(fd, saved);
	if (!saved || *saved == '\0')
		return (NULL);
	line = extract_line(&saved);
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
