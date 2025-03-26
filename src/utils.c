/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:07:18 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/25 18:01:19 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void ft_bzero (void *s, size_t n)
{
    unsigned char *ptr;
    size_t i;

    ptr = (unsigned char *)s;
    i = 0;
    while (i < n)
    {
        ptr[i] = '\0';
        i++;
    }   
}

void *ft_calloc(size_t nmemb, size_t size)
{
    void *ptr;

    ptr = malloc(nmemb * size);
    if (ptr == NULL)
        return (NULL);
    ft_bzero(ptr, (nmemb * size));
    return (ptr);
}

int ft_putstr(char *str)
{
    size_t i;
    int ret;

    i = 0;
    if (str == NULL)
        return (-1);
    while (str[i])
     i++;
    ret = write(1, str, i);
    return (ret);
}

int ft_putchar(unsigned char c)
{
    int ret;

    ret = write(1, &c, 1);
    return (ret);
}

int ft_putnbr(int n)
{
    int ret;
    if ( n == -2147483648)
     ret = write(1, "-2147483648", 11);
    else if (n < 0)
    {
        n = n * -1;
        ret = ft_putchar('-');
        ft_putnbr(n);
    }
    else if (n > 9)
    {
        ft_putnbr(n / 10);
        ret = ft_putchar(n % 10 + '0');
    }
    else
        ret = ft_putchar(n + '0');
    return (ret);  
}