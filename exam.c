/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exam.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:46:54 by csouita           #+#    #+#             */
/*   Updated: 2024/10/22 20:01:04 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>



int ft_putchar_exam(int c)
{
    write(1,&c, 1);
    return 1;
}

int ft_putstr_exam(char *str)
{
    int i = 0 ;
    if(!str)
    {
        ft_putstr_exam("(null)");
        return 6;
    }
    while(str[i])
    {
        ft_putchar_exam(str[i]);
        i++;
    }
    return i ;
}

int ft_putnbr_exam(int c)
{
    int len = 0;

    if (c == -2147483648)
    {
        ft_putstr_exam("-2147483648");
        return 11;
    }
    if (c < 0)
    {
        len = len + ft_putchar_exam('-');
        c = -c;
    }
    if (c > 9)
        len = len + ft_putnbr_exam(c / 10);
    len = len + ft_putchar_exam(c % 10 + 48);
    return len ; 
}

int ft_putnbr_hex(int c )
{
    char str[16] = "0123456789abcdef";
    unsigned int len = 0 ;
    unsigned int nbr = (unsigned int)c;
    if (nbr > 16)
        len = len + ft_putnbr_hex(nbr / 16);
    len = len + ft_putchar_exam(str[nbr % 16]);
    return len;
}

int type_check(char c , va_list arg)
{
    int len = 0;
    if(c == 's')
        len = ft_putstr_exam(va_arg(arg, char *));
    else if(c == 'd')
        len = ft_putnbr_exam(va_arg(arg,int));
    else if( c == 'x')
        len = ft_putnbr_hex(va_arg(arg,int));
    return len;
}


int ft_printf(const char *f, ... )
{
    va_list arg ;
    va_start(arg,f);

    int len = 0;
    int i = 0;
    while(f[i])
    { 
        if (f[i] == '%' && f[i + 1] == '\0')
            return -1;
        else if (f[i] == '%' && (f[i + 1] == 's' || f[i + 1] == 'd' || f[i + 1] == 'x'))
            len = len + type_check(f[++i],arg);
        else 
            len = len + ft_putchar_exam(f[i]);
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