/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 16:40:48 by kaye              #+#    #+#             */
/*   Updated: 2021/05/16 19:48:28 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

/* ************************************************************************** */
/*                                                                            */
/*                                 MANTADORY                                  */
/*                                                                            */
/* ************************************************************************** */

/*
** FT_STRLEN
*/
int 	ft_strlen_test(const char *src)
{
	size_t my;
	size_t rl;

	if (!src)
	{
		printf("\033[1;33msrc can't be NULL\033[0m\n");
		return (1);
	}
	my = ft_strlen(src);
	rl = strlen(src);
	if (my != rl)
	{
		printf("\033[1;31m❌  Result of ft_strlen : [%zu] and strlen : [%zu] are not equal\033[0m\n", my, rl);
		return (0);
	}
	printf("\033[1;32m✅  ft_strlen PASS\033[0m\n");
	return (1);
}

int	ft_strlen_multi_test(void)
{
	if (!ft_strlen_test(""))
	{
		printf("\n");
		return (0);
	}
	if (!ft_strlen_test("a simple test"))
	{
		printf("\n");
		return (0);
	}
	if (!ft_strlen_test("test\nwith\tsome\vno\fprintable\rcaracter"))
	{
		printf("\n");
		return (0);
	}
	if (!ft_strlen_test("test with end of string\0this message does not include"))
	{
		printf("\n");
		return (0);
	}
	printf("\n");
	return (1);
}

/*
** FT_STRCPY
*/
int 	ft_strcpy_test(char *dst, const char *src, int size)
{
	char *my;
	char *rl;

	if (!dst || !src)
	{
		printf("\033[1;33mdst and src can't be NULL\033[0m\n");
		return (1);
	}
	bzero(dst, size);
	my = ft_strcpy(dst, src);
	bzero(dst, size);
	rl = strcpy(dst, src);
	if (strcmp(my, rl) != 0)
	{
		printf("\033[1;31m❌  Result of ft_strcpy : [%s] and strcpy : [%s] are not equal\033[0m\n", my, rl);
		return (0);
	}
	printf("\033[1;32m✅  ft_strcpy PASS\033[0m\n");
	return (1);
}

int	ft_strcpy_multi_test(void)
{
	char dst[100];

	if (!ft_strcpy_test(dst, "", 100))
	{
		printf("\n");
		return (0);
	}
	if (!ft_strcpy_test(dst, "a simple test", 100))
	{
		printf("\n");
		return (0);
	}
	if (!ft_strcpy_test(dst, "test\nwith\tsome\vno\fprintable\rcaracter", 100))
	{
		printf("\n");
		return (0);
	}
	if (!ft_strcpy_test(dst, "test with end of string\0this message does not include", 100))
	{
		printf("\n");
		return (0);
	}
	printf("\n");
	return (1);
}

/*
** FT_STRCMP
*/
int 	ft_strcmp_test(char *s1, char *s2)
{
	int my;
	int rl;

	if (!s1 || !s2)
	{
		printf("\033[1;33ms1 & s2 can't be NULL\033[0m\n");
		return (1);
	}
	my = ft_strcmp(s1, s2);
	rl = strcmp(s1, s2);
	if (my != rl)
	{
		printf("\033[1;31m❌  Result of ft_strcmp : [%d] and strcmp : [%d] are not equal\033[0m\n", my, rl);
		return (0);
	}
	printf("\033[1;32m✅  ft_strcmp PASS\033[0m\n");
	return (1);
}

int	ft_strcmp_multi_test(void)
{
	if (!ft_strcmp_test("", ""))
	{
		printf("\n");
		return (0);
	}
	if (!ft_strcmp_test("test", ""))
	{
		printf("\n");
		return (0);
	}
	if (!ft_strcmp_test("", "test"))
	{
		printf("\n");
		return (0);
	}
	if (!ft_strcmp_test("test", "test"))
	{
		printf("\n");
		return (0);
	}
	if (!ft_strcmp_test("ABC", "abc"))
	{
		printf("\n");
		return (0);
	}
	if (!ft_strcmp_test("abb", "abc"))
	{
		printf("\n");
		return (0);
	}
	if (!ft_strcmp_test("no\nprintable", "no\tprintable"))
	{
		printf("\n");
		return (0);
	}
	if (!ft_strcmp_test("no\nprintable2", "no\0printable2"))
	{
		printf("\n");
		return (0);
	}
	printf("\n");
	return (1);
}

/*
** FT_WRITE
*/
int 	ft_write_test(int fd, char *buf, int nbyte)
{
	int my;
	int rl;
	int my_errno;
	int rl_errno;

	errno = 0;
	my = ft_write(fd, buf, nbyte);
	my_errno = errno;
	errno = 0;
	rl = write(fd, buf, nbyte);
	rl_errno = errno;
	if (my != rl || my_errno != rl_errno)
	{
		printf("\033[1;31m❌  Result of ft_write : [%d] errno : [%d] and write : [%d] errno : [%d]are not equal\033[0m\n", my, my_errno, rl, rl_errno);
		return (0);
	}
	printf("\033[1;32m✅  ft_write PASS\033[0m\n");
	return (1);
}

int	ft_write_multi_test(void)
{
	printf("\033[1;33mNormal print test :\033[0m\n");
	if (!ft_write_test(STDERR_FILENO, "test", 4))
	{
		printf("\n");
		return (0);
	}
	printf("\033[1;33mErrno test :\033[0m\n");
	if (!ft_write_test(STDERR_FILENO, "test" , -1))
	{
		printf("\n");
		return (0);
	}
	printf("\n");
	return (1);
}

/*
** FT_READ
*/
int 	ft_read_test(int fd1, int fd2, char *buf1, char *buf2, int nbyte)
{
	int my;
	int rl;
	int my_errno;
	int rl_errno;

	if (buf1 && buf2)
	{
		bzero(buf1, nbyte);
		bzero(buf2, nbyte);
	}
	errno = 0;
	my = ft_read(fd1, buf1, nbyte);
	buf1[nbyte] = '\0';
	my_errno = errno;
	errno = 0;
	rl = read(fd2, buf2, nbyte);
	buf2[nbyte] = '\0';
	rl_errno = errno;
	if (my != rl || my_errno != rl_errno || ((buf1 && buf2) && strcmp(buf1, buf2) != 0))
	{
		printf("\033[1;31m❌  Result of ft_read : [%d] and read : [%d] are not equal\033[0m\n", my, rl);
		return (0);
	}
	printf("\033[1;32m✅  ft_read PASS\033[0m\n");
	return (1);
}

int	ft_read_multi_test(void)
{
	char buf_for_read1[BUFF_SIZE + 1];
	char buf_for_read2[BUFF_SIZE + 1];
	int fd1;
	int fd2;

	fd1 = open("./src/ft_read.s", O_RDONLY);
	fd2 = open("./src/ft_read.s", O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
	{
		printf("open failed\n");
		exit(1);
	}
	printf("\033[1;33mNormal print test :\033[0m\n");
	if (!ft_read_test(fd1, fd2, buf_for_read1, buf_for_read2, BUFF_SIZE))
	{
		close(fd1);
		close(fd2);
		printf("\n");
		return (0);
	}
	printf("\033[1;33mErrno test :\033[0m\n");
	if (!ft_read_test(-111, -111, buf_for_read1, buf_for_read2, 0))
	{
		close(fd1);
		close(fd2);
		printf("\n");
		return (0);
	}
	close(fd1);
	close(fd2);
	printf("\n");
	return (1);
}

/*
** FT_STRDUP
*/
int 	ft_strdup_test(char *src)
{
	char *my;
	char *rl;

	if (!src)
	{
		printf("\033[1;33msrc can't be NULL\033[0m\n");
		return (1);
	}
	my = ft_strdup(src);
	rl = strdup(src);
	if (strcmp(my, rl) != 0)
	{
		free(my);
		free(rl);
		printf("\033[1;31m❌  Result of ft_strdup and strdup are not equal\033[0m\n");
		return (0);
	}
	free(my);
	free(rl);
	printf("\033[1;32m✅  ft_strdup PASS\033[0m\n");
	return (1);
}

int	ft_strdup_multi_test(void)
{
	if (!ft_strdup_test(""))
	{
		printf("\n");
		return (0);
	}
	if (!ft_strdup_test("a simple test"))
	{
		printf("\n");
		return (0);
	}
	if (!ft_strdup_test("test\nwith\tsome\vno\fprintable\rcaracter"))
	{
		printf("\n");
		return (0);
	}
	if (!ft_strdup_test("test with end of string\0this message does not include"))
	{
		printf("\n");
		return (0);
	}
	printf("\n");
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                   BONUS                                    */
/*                                                                            */
/* ************************************************************************** */

/*
** FT_LIST_SIZE
*/
int	ft_list_size_test(t_list *list, int size_check)
{
	int size;

	size = 0;
	size = ft_list_size(list);
	if (size != size_check)
	{
		printf("\033[1;31m❌  Result of ft_list_size [%d] with size [%d] check are not equal\033[0m\n", size, size_check);
		return (0);
	}
	printf("\033[1;32m✅  ft_list_size PASS\033[0m\n");
	return (1);
}

void	free_list(t_list *list1,t_list *list2, t_list *list3, t_list *list4, t_list *list5, t_list *list6)
{
	free(list1);
	free(list2);
	free(list3);
	free(list4);
	free(list5);
	free(list6);
}

int	ft_list_size_multi_test(void)
{
	t_list *list;
	t_list *list1 = calloc(1, sizeof(t_list));
    t_list *list2 = calloc(1, sizeof(t_list));
    t_list *list3 = calloc(1, sizeof(t_list));
	t_list *list4 = calloc(1, sizeof(t_list));
	t_list *list5 = calloc(1, sizeof(t_list));
	t_list *list6 = calloc(1, sizeof(t_list));

	list = list1;
	if (!ft_list_size_test(list, 1))
	{
		free_list(list1, list2, list3, list4, list5, list6);
		return (0);
	}
	list1->next = list2;
	list1->next->next = list3;
	if (!ft_list_size_test(list, 3))
	{
		free_list(list1, list2, list3, list4, list5, list6);
		return (0);
	}
	list1->next = list2;
	list1->next->next = list3;
	list1->next->next->next = list4;
	list1->next->next->next->next = list5;
	list1->next->next->next->next->next = list6;
	if (!ft_list_size_test(list, 6))
	{
		free_list(list1, list2, list3, list4, list5, list6);
		printf("\n");
		return (0);
	}
	printf("\n");
	return (1);
}

/*
** FT_LIST_PUSH_FRONT
*/
int	ft_list_push_front_test(t_list *list, int data_check)
{
	if ((int)list->data != data_check)
	{
		printf("\033[1;31m❌  Result of data [%d] with data_check [%d] are not equal\033[0m\n", (int)list->data, data_check);
		return (0);
	}
	printf("\033[1;32m✅  ft_list_push_front PASS\033[0m\n");
	return (1);
}

int	ft_list_push_front_multi_test(void)
{
	t_list *list = NULL;

	ft_list_push_front(&list, (void *)(intptr_t)1);
	if (!ft_list_push_front_test(list, 1))
	{
		free(list);
		printf("\n");
		return (0);
	}
	ft_list_push_front(&list, (void *)(intptr_t)2);
	if (!ft_list_push_front_test(list, 2))
	{
		free(list->next);
		free(list);
		printf("\n");
		return (0);
	}
	ft_list_push_front(&list, (void *)(intptr_t)3);
	if (!ft_list_push_front_test(list, 3))
	{
		free(list->next->next);
		free(list->next);
		free(list);
		printf("\n");
		return (0);
	}
	printf("\n");
	return (1);
}

/*
** MAIN
*/
int main(void)
{
	#if defined (__MANDATORY__)
	int mandatory;
	int check;

	mandatory = 6;
	check = 0;
	printf("\033[1;36mMandatory part :\033[0m\n\n");
	printf("\033[1;35mft_strlen :\033[0m\n");
	check += ft_strlen_multi_test();
	printf("\033[1;35mft_strcpy :\033[0m\n");
	check += ft_strcpy_multi_test();
	printf("\033[1;35mft_strcmp :\033[0m\n");
	check += ft_strcmp_multi_test();
	printf("\033[1;35mft_write :\033[0m\n");
	check += ft_write_multi_test();
	printf("\033[1;35mft_read :\033[0m\n");
	check += ft_read_multi_test();
	printf("\033[1;35mft_strdup :\033[0m\n");
	check += ft_strdup_multi_test();
	if (mandatory != check)
		printf("\033[1;31m❌  Mandatory failed : \033[0m%d / %d\n", check, mandatory);
	else
		printf("\033[1;32m✅  Mandatory PASS : \033[0m%d / %d\n", check, mandatory);
	#endif

	#if defined (__BONUS__)
	int bonus;
	int check_bonus;

	bonus = 2;
	check_bonus = 0;
	printf("\033[1;36mBonus part :\033[0m\n\n");
	printf("\033[1;35mft_list_size :\033[0m\n");
	check_bonus += ft_list_size_multi_test();
	printf("\033[1;35mft_list_push_front :\033[0m\n");
	check_bonus += ft_list_push_front_multi_test();
	if (bonus != check_bonus)
		printf("\033[1;31m❌  Bonus failed : \033[0m%d / %d\n", check_bonus, bonus);
	else
		printf("\033[1;32m✅  Bonus PASS : \033[0m%d / %d\n", check_bonus, bonus);
	#endif
	return (0);
}