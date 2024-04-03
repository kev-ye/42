#include "malloc.h"


static void	_show_alloc_mem_leak(void) {
	block_t*	curr_zone = g_first_block;
	block_t*	next_zone = NULL;

	size_t		v_total = 0;
	size_t		r_total = 0;
	size_t		index = 0;

	ft_putstr_fd(S_PURPLE"\n--- Memory leaks ---\n"S_NONE, STDOUT_FILENO);
	if (g_first_block == NULL) {
		ft_putstr_fd(S_YELLOW"No blocks allocate!\n"S_NONE, STDOUT_FILENO);
		return;
	}

	while (curr_zone) {
		next_zone = get_next_zone(curr_zone);
		for (block_t *b = curr_zone; b != NULL; b = b->next) {
			if (b->alloc_status == IS_ALLOCATED) {
				v_total += b->size >= 32 ? b->size - BLOCK_SIZE : b->size;
				r_total += b->size;
				++index;
				ft_putstr_fd("Leak #"S_RED, STDOUT_FILENO);
				ft_putnbr_fd(index, STDOUT_FILENO, 10);
				ft_putstr_fd(S_NONE": ["S_YELLOW, STDOUT_FILENO);
				ft_putaddr_fd((void *)b + BLOCK_SIZE, STDOUT_FILENO);
				ft_putstr_fd(S_NONE"]["S_YELLOW, STDOUT_FILENO);
				ft_putnbr_fd(b->size >= 32 ? b->size - BLOCK_SIZE : b->size, STDOUT_FILENO, 10);
				ft_putstr_fd(S_NONE" b]\n", STDOUT_FILENO);
			}
			if (b->next && b->next == next_zone)
				break;
		}
		curr_zone = next_zone;
	}
	ft_putstr_fd("\nVirtual bytes leaked Total: ["S_YELLOW, STDOUT_FILENO);
	ft_putnbr_fd(v_total, STDOUT_FILENO, 0);
	ft_putstr_fd(S_NONE"] bytes\n", STDOUT_FILENO);

	ft_putstr_fd("Real bytes leaked Total:    ["S_YELLOW, STDOUT_FILENO);
	ft_putnbr_fd(r_total, STDOUT_FILENO, 0);
	ft_putstr_fd(S_NONE"] bytes\n", STDOUT_FILENO);
}

void		show_alloc_mem_leak() {
	pthread_mutex_lock(&g_memory_mutex);
	_show_alloc_mem_leak();
	pthread_mutex_unlock(&g_memory_mutex);
}
