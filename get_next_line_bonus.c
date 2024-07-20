/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:19:56 by yabukirento       #+#    #+#             */
/*   Updated: 2024/07/20 15:39:27 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_to_newline(int fd, char *saved, char *buffer)
{
	char	*join_buf;
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		join_buf = ft_strjoin(saved, buffer);
		if (!join_buf)
			return (free(saved), free(buffer), NULL);
		free(saved);
		saved = join_buf;
		if (ft_strchr(saved, '\n'))
			break ;
	}
	free(buffer);
	if (bytes_read < 0 || (bytes_read == 0 && ft_strlen(saved) == 0))
		return (free(saved), NULL);
	return (saved);
}

static char	*extract_line(char *saved, size_t len)
{
	size_t	i;
	char	*line;

	i = 0;
	line = (char *)malloc((len + 2) * sizeof(char));
	if (!line)
		return (free(saved), NULL);
	while (i <= len)
	{
		line[i] = saved[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_shift_pointer(size_t len, char *saved, char *line)
{
	char	*tmp;

	tmp = ft_strdup(saved + len + 1);
	if (!tmp)
		return (free(saved), free(line), NULL);
	free(saved);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*saved[OPEN_MAX];
	char		*line;
	char		*buffer;
	size_t		len;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	if (!saved[fd])
		saved[fd] = ft_strdup("");
	if (!saved[fd])
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	saved[fd] = read_to_newline(fd, saved[fd], buffer);
	if (!saved[fd])
		return (NULL);
	len = 0;
	while (saved[fd][len + 1] && saved[fd][len] != '\n')
		len++;
	line = extract_line(saved[fd], len);
	saved[fd] = ft_shift_pointer(len, saved[fd], line);
	return (line);
}
