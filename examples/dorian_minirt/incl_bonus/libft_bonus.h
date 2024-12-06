/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:22:53 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/25 10:22:53 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_BONUS_H
# define LIBFT_BONUS_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define MY_INT_MAX 2147483647
# define MY_INT_MIN -2147483648

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_range
{
	float	min;
	float	max;
}			t_range;

int		ft_atoi(const char *str);
float	ft_atof(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar(char c);
void	ft_putendl(char *s);
void	ft_putnbr(int n);
void	ft_putstr(char *s);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	**ft_split2(char const *s);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strcmp(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_get_word(const char *str);
int		ft_tolower(int c);
void	ft_tolower2(char *c);
void	ft_toupper2(char *c);
void	ft_strlower(char *s);
void	ft_strupper(char *s);
int		ft_toupper(int c);
int		ft_isupper(int c);
int		ft_islower(int c);
int		ft_empty_str(char *str);
int		ft_lenbase(int n, int base);

// linked list
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
// ft_printf
int		ft_printf(const char *input, ...);
int		ft_putchar_c(int c);
int		ft_putstr_c(char *s);
int		ft_putnbr_c(int n);
int		ft_putunbr_c(unsigned int n);
void	ft_strrev(char *str);
size_t	ft_len16(unsigned long long n);
char	*ft_dec_hexstr(unsigned long n);
int		ft_puthex_c(unsigned int n, int c);
int		ft_putptr_c(unsigned long long ptr);
int		return_null(void);
// ft_printf_fd
int		ft_printf_fd(int fd, const char *input, ...);
int		ft_putchar_c2(int c, int fd);
int		ft_putstr_c2(char *s, int fd);
int		ft_putnbr_c2(int n, int fd);
int		ft_putunbr_c2(unsigned int n, int fd);
int		ft_puthex_c2(unsigned int n, int c, int fd);
int		ft_putptr_c2(unsigned long long ptr, int fd);
int		return_null2(int fd);
// get_next_line
char	*get_next_line(int fd, int clear);
//MISC
long	ft_max(long a, long b);
long	ft_min(long a, long b);
float	ft_frac(float a);
int		ft_sign(float a);
double	ft_powerf(double x, int exp);
float	ft_scale(float value, t_range range_old, t_range range_new);
void	ft_free(void *ptr);
void	*ft_free_array(char ***array, size_t elements);
void	*ft_free_anyarray(void ***array, size_t elements);
size_t	ft_count_elements(char **array);

#endif
