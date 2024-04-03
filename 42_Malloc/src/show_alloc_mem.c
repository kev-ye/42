#include "malloc.h"


static void	_show_alloc_mem(void) {
	if (g_first_block == NULL)
		return;

	const char	*zone_name[] = {"TINY", "SMALL", "LARGE"};
	size_t		total = 0;

	ft_putstr_fd(zone_name[g_first_block->zone], STDOUT_FILENO);
	ft_putstr_fd(" : ", STDOUT_FILENO);
	ft_putaddr_fd(g_first_block, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	for (block_t *b = g_first_block; b != NULL; b = b->next) {
		if (b->alloc_status == IS_ALLOCATED) {
			size_t	vsize_count = b->size >= BLOCK_SIZE ? b->size - BLOCK_SIZE : b->size;
			ft_putaddr_fd((void *)b + BLOCK_SIZE, STDOUT_FILENO);
			ft_putstr_fd(" - ", STDOUT_FILENO);
			ft_putaddr_fd((void *)b + b->size, STDOUT_FILENO);
			ft_putstr_fd(" : ", STDOUT_FILENO);
			ft_putnbr_fd(vsize_count, STDOUT_FILENO, 0);
			ft_putstr_fd(" bytes\n", STDOUT_FILENO);
			total += vsize_count;
		}
		if (b->next && b->zone != b->next->zone) {
			ft_putstr_fd(zone_name[b->next->zone], STDOUT_FILENO);
			ft_putstr_fd(" : ", STDOUT_FILENO);
			ft_putaddr_fd(b, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
	}
	ft_putstr_fd("Total : ", STDOUT_FILENO);
	ft_putnbr_fd(total, STDOUT_FILENO, 0);
	ft_putstr_fd(" bytes\n", STDOUT_FILENO);
}

void		show_alloc_mem(void) {
	pthread_mutex_lock(&g_memory_mutex);
	_show_alloc_mem();
	pthread_mutex_unlock(&g_memory_mutex);
}
