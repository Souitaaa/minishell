/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tbi3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:10:02 by csouita           #+#    #+#             */
/*   Updated: 2024/10/22 19:27:34 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include<stdio.h>
#include<stdarg.h>
#include<unistd.h>


int ft_putchar(int c)
{
    write(1,&c,1);
    return 1;
}
int ft_putstr(char *str)
{
    int i = 0;
    if (!str)
    {
        ft_putstr("(null)");
        return 6;
    }
    while (str[i])
    {
        ft_putchar(str[i]);
        i++;
    }
    return i;
}
int ft_putnbr(int nbr)
{
    int len = 0;
    if (nbr == -2147483648)
    {
        ft_putstr("-2147483648");
        return 11;
    }
    if (nbr < 0)
    {
        len = len + ft_putchar('-');
        nbr = -nbr;   
    }
    if (nbr > 9)
    {
        len = len + ft_putnbr(nbr / 10);
    }
    len = len + ft_putchar(nbr % 10 + 48);
    return len;
}
int ft_puthexa(int nbr)
{
    char str[16] = "0123456789abcdef";
    unsigned int len = 0;
    unsigned int nb = (unsigned int)nbr;
    if (nb > 16)
    {
        len = len + ft_puthexa( nb / 16);
    }
    len = len + ft_putchar(str[nb % 16]);
    return len ;
}
int check_type(char c, va_list arg)
{
    int count = 0;
    if (c == 's')
        count = ft_putstr(va_arg(arg,char *));
    else if (c == 'd')
        count = ft_putnbr(va_arg(arg,int));
    else if (c == 'x')
        count = ft_puthexa(va_arg(arg,int));
    return count;
}
int ft_printf(const char *f, ... )
{
    va_list arg;
    va_start(arg,f);
    int i = 0;
    int len = 0;

    while (f[i])
    {
        if (f[i] == '%' && f[i+1] == '\0')
            return -1;
        else if (f[i] == '%' && (f[i+1] == 's' || f[i+1] == 'd' || f[i+1] == 'x'))
            len = len + check_type(f[++i],arg);
        else 
            len = len + ft_putchar(f[i]);
        i++;   
    }
    va_end(arg);
    return len;
}
int main()
{
    printf("hello [%s] [%d]years old ,love [%x]\n","mohamed",23, 22);
    ft_printf("hello [%s] [%d]years old ,love [%x]\n","mohamed",23, 22);
    // printf("hello");
    printf("%d\n",printf("hello word "));
    ft_printf("%d ",printf("hello word "));
    return 0;
}