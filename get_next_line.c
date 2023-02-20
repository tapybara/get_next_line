/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuyamatakahito <okuyamatakahito@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 23:44:14 by okuyamataka       #+#    #+#             */
/*   Updated: 2023/02/21 01:18:07 by okuyamataka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*trim_str_by_1stlinebreak(char *backup)
{
	char	*trimed_str;
	int		i;
	int		trim_len;

	i = 0;
	trim_len = 1;
	while (backup[i++] != '\n')
		trim_len++;
	trimed_str = (char *)malloc((trim_len + 1) * sizeof(char));
	if (!trimed_str)
		return (NULL);
	trimed_str[trim_len] = '\0';
	i = 0;
	while (i < trim_len){
		trimed_str[i] = backup[i];
		i++;
	}
	return (trimed_str);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*tmp;
	char		*buf;
	char		*line;
	ssize_t		read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = NULL;
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	read_bytes = 1;
	while (!(ft_strchr(backup, '\n')))
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buf);
			return (NULL);	
		}
		buf[read_bytes] = '\0';
		tmp = ft_strjoin(backup, buf); //結合前のbackupってfree必要じゃない？
		free(backup);
		backup = tmp;
		tmp = NULL;
		if (!read_bytes)
		{
			free(buf);
			if (ft_strlen(backup))
				return (backup);
			else
			{
				free(backup);
				backup = NULL;
				return (NULL);
			}
		}
	}
	free(buf);
	line = trim_str_by_1stlinebreak(backup);
	tmp = ft_strdup(ft_strchr(backup, '\n') + 1);
	free(backup);
	backup = tmp;
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>
// // #include <libc.h>
// // #include "leakdetect.h"
// // #define malloc(s) leak_detelc_malloc(s, __FILE__, __LINE__)
// // #define free leak_detect_free

// int main()
// {
// 	char	*str;
// 	int i;
// 	int fd;

// 	// leak_detect_init();
// 	// fd = open("test.txt", O_RDONLY);
// 	// fd = open("nl.txt", O_RDONLY);
// 	fd = open("41_no_nl", O_RDONLY);
// 	// fd = open("42_no_nl", O_RDONLY);
// 	// fd = open("empty", O_RDONLY);
// 	// fd = open("big_line_no_nl", O_RDONLY);
// 	i = 3;
// 	while(i--)
// 	{
// 		str = get_next_line(fd);
// 		printf("buf=%s", str);
// 		free(str);
// 	}
// 	// printf("buf=%s", get_next_line(fd2));
// 	// printf("buf=%s", get_next_line(fd3));
// 	// printf("buf=%s", get_next_line(fd4));
// 	// leak_detect_check();
//     return 0;
// }

// // __attribute__((destructor))
// // static void destructor() {
// //     system("leaks -q a.out");
// // }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*str;
// 	size_t	s1_len;
// 	size_t	s2_len;
// 	size_t	i;

// 	s1_len = 0;
// 	s2_len = 0;
// 	if (!s1 && !s2)
// 		return (NULL);
// 	if (s1)
// 		s1_len = ft_strlen(s1);
// 	if (s2)
// 		s2_len = ft_strlen(s2);
// 	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (s1_len--)
// 		str[i++] = *s1++;
// 	while (s2_len--)
// 		str[i++] = *s2++;
// 	str[i] = '\0';
// 	return (str);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	const char	*str;

// 	if (!s)
// 		return (NULL);
// 	str = (char *)s;
// 	while (*str != '\0')
// 	{
// 		if (*str == (char)c)
// 			return ((char *)str);
// 		str++;
// 	}
// 	if (c == '\0')
// 		return ((char *)str);
// 	return (NULL);
// }

// char	*ft_strdup(const char *s)
// {
// 	char	*p;
// 	size_t	size;
// 	int		i;

// 	size = ft_strlen(s) + 1;
// 	p = (char *)malloc(size * sizeof(char));
// 	if (p == NULL)
// 		return (p);
// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		p[i] = s[i];
// 		i++;
// 	}
// 	p[i] = '\0';
// 	return (p);
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }
