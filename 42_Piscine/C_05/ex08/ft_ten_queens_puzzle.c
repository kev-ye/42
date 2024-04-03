#include <unistd.h>
#include <stdio.h>

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

int ft_abs(int nb) 
{
    return ((nb < 0)? -nb : nb);
}

int     check(int queen[10], int x)
{
    int i;

    i = 0;
    while (i < x)
    {
        if (queen[i] == queen[x] || ft_abs(queen[i] - queen[x]) == x - i)
            return (0);
        i++;
    }
    return (1);
}

void    solve(int queen[10], int x, int *max)
{
    int i;

    i = -1;
    while (++i < 10)
    {
        queen[x] = i;
        if (check(queen, x) == 1)
        {
            if (x == 9)
            {
                x = 0;
                while (x < 10)
                    ft_putchar(queen[x++] + '0');
                ft_putchar('\n');
                (*max)++;
                return ;
            }
            else
                solve(queen, x + 1, max);
        }
    }
}

int ft_ten_queens_puzzle(void)
{
    int queen[10];
    int max;

    max = 0;
    solve(queen, 0, &max);
    return (max);
}

int main()
{
    printf("%d\n",ft_ten_queens_puzzle());
    return (0);
}