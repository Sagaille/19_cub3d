/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 16:25:53 by ldavids           #+#    #+#             */
/*   Updated: 2020/10/10 23:48:54 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void ft_int_to_hex(unsigned long n, char *outbuf)
{

    int i = 12;
    int j = 0;

    while (i > 6)
	{
        outbuf[i] = "0123456789abcdef"[n % 16];
        i--;
        n = n/16;
    }

    while( ++i < 13){
       outbuf[j++] = outbuf[i];
    }

    outbuf[j] = 0;
    /*printf("outbuf = %s\n", outbuf);*/

}

int two_hex_to_int(char *temp)
{
    int j;
    int a;
    
    j = 0;
    a = 0;
    while (temp[a] == '0')
    a++;
    /*printf("tempstrlen = %i\n", strlen(temp));
    printf("a = %i\n", a);*/
        if ((a % 2) == 0)
        {
		if (temp[a] >= '0' && temp[a] <= '9')
		j = ((temp[a] - 48) * ((16^1) - 1));
		if (temp[a] >= 'a' && temp[a] <= 'f')
		j = ((temp[a] - 97 + 10) * ((16^1) - 1));
	if (temp[a + 1] >= '0' && temp[a + 1] <= '9')
	j = j + (temp[a + 1] - 48);
	if (temp[a + 1] >= 'a' && temp[a + 1] <= 'f')
	j = j + (temp[a + 1] - 97 + 10);
    /*printf("j = %i\n", j);*/
    return (j);
    }
    if ((a % 2) == 1)
        {
        if (temp[a] >= '0' && temp[a] <= '9')
	j = j + (temp[a] - 48);
	if (temp[a] >= 'a' && temp[a] <= 'f')
	j = j + (temp[a] - 97 + 10);
    }
    /*printf("j = %i\n", j);*/
return (j);
}

/*int main ()
{
char test[6];
prntnum(10500, test);    
printf("int = %i\n", hex_to_int(test));
char *temp2 = "d10";   
printf("int = %i\n", hex_to_int(temp2));
char *temp3 = "0d";
printf("int = %i\n", hex_to_int(temp3));
	
}*/