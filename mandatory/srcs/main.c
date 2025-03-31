/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:50:51 by yabukirento       #+#    #+#             */
/*   Updated: 2025/03/31 13:56:43 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

static void	ft_gnl(int fd, char **saved)
{
	char	*line1;
	char	*line2;
	char	*line3;

	line1 = get_next_line(fd, saved);
	line2 = get_next_line(fd, saved);
	line3 = get_next_line(fd, saved);
	printf("line1: [%s]\n", line1);
	printf("line2: [%s]\n", line2);
	printf("line3: [%s]\n", line3);
	free(line1);
	free(line2);
	free(line3);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*saved;

	if (argc != 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return (EXIT_SUCCESS);
	}
	if (argv[1] == NULL || argv[1][0] == '\0')
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return (EXIT_SUCCESS);
	}
	saved = ft_strdup("");
	if (saved == NULL)
	{
		printf("Error: failed to allocate memory\n");
		return (EXIT_SUCCESS);
	}
	fd = open(argv[1], O_RDONLY);
	ft_gnl(fd, &saved);
	free(saved);
	return (EXIT_SUCCESS);
}

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q get_next_line");
}
