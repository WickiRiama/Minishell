/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:22:05 by mriant            #+#    #+#             */
/*   Updated: 2022/09/14 16:54:36 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*get_next_line(int fd)
{
	long int	ret;
	char		*buf;
	static char	*tail[256];
	char		*line;

	if (ft_check_fd(fd, tail) == 1)
		return (NULL);
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	tail[fd] = ft_strjoin_free(tail[fd], "\0");
	line = ft_strdup(tail[fd]);
	ret = ft_readline(fd, &buf, &line);
	if (ret < 0 || !buf)
	{
		ft_clean_gnl(buf, tail[fd], line);
		return (NULL);
	}
	ft_setline(&line, &tail[fd]);
	if (ret == 0 && !tail[fd] && line[0] == '\0')
	{
		free(line);
		line = NULL;
	}
	free(buf);
	return (line);
}
/*
int	main(void)
{
	int		fd1;
	int		fd2;

	fd1 = open("test_file", O_RDONLY);
	fd2 = open("test_file_2", O_RDONLY);
	char	*str = get_next_line(fd1);
	printf("fd1 :%s", str);
	free(str);
	while (str)
	{
		str = get_next_line(0);
		printf("input : %s", str);
		free(str);
		str = get_next_line(fd2);
		printf("fd2 : %s", str);
		free(str);
		str = get_next_line(fd1);
		printf("fd1 : %s", str);
		free (str);
	}
	close (fd1);
	close (fd2);
}*/
