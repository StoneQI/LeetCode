/*
 * @Author: stone
 * @Date: 2019-08-31 20:36:46
 * @LastEditTime: 2019-08-31 21:08:30
 * @LastEditors: stone
 * @Description: 
 */
#include <stdio.h>
int main()
{
    int a[3][4];
    int(*c)[4] = a[1];
    int *d = a+2;
    int f  = a+1;
    int (*e)[4]  = a[0];
    int(*b)[4] = &a[1];
    printf("a");
}