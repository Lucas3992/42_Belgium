/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:39:27 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/11/21 14:16:00 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 19
# elif BUFFER_SIZE > 1000000
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# elif BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_isalpha(int c);
int		ft_isascii(int i);
int		ft_isdigit(int i);
int		ft_isprint(int i);
char	*ft_itoa(int n);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstnew(void *content);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, char *s2);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_strchr(const char *s, int c);
char	*ft_strstr(char *str, char *to_find);
int		ft_isalnum(int c);
char	*ft_strchr2(const char *s, int c);
char	*ft_strdup_gnl(const char *s);
size_t	ft_strlen_gnl(const char *c);
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len);
char	*ft_join_gnl(char *s1, char *s2, int bytes_read);
char	*cleanfree_gnl(char **toclean);
char	*get_next_line(int fd);

#endif