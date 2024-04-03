#include "malloc.h"


static void		_info(block_t *b) {
	// [addr]
	ft_putstr_fd("["S_GREEN, STDOUT_FILENO);
	ft_putaddr_fd((void *)b, STDOUT_FILENO);
	ft_putstr_fd(S_NONE"]", STDOUT_FILENO);
	ft_putstr_fd("["S_GREEN, STDOUT_FILENO);
	ft_putstr_fd(b->zone == TINY ? "TINY" : b->zone == SMALL ? "SMALL" : "LARGE", STDOUT_FILENO);
	ft_putstr_fd(S_NONE"]", STDOUT_FILENO);
	ft_putstr_fd("["S_GREEN, STDOUT_FILENO);
	ft_putstr_fd(b->alloc_status == IS_FREE ? "F" : "A", STDOUT_FILENO);
	ft_putstr_fd(S_NONE"]", STDOUT_FILENO);

	// [real size]
	ft_putstr_fd("[r: "S_GREEN, STDOUT_FILENO);
	ft_putnbr_fd(b->size, STDOUT_FILENO, 10);
	ft_putstr_fd(S_NONE" b]", STDOUT_FILENO);

	// [virtual size]
	ft_putstr_fd("[v: "S_GREEN, STDOUT_FILENO);
	ft_putnbr_fd(b->size >= 32 ? b->size - BLOCK_SIZE : b->size, STDOUT_FILENO, 10);
	ft_putstr_fd(S_NONE" b]", STDOUT_FILENO);
}

static void		_info_mode(size_t* tml, size_t* tral, size_t* tval) {
    ft_putstr_fd("Info Mode:\n", STDOUT_FILENO);
	for (block_t *b = g_first_block; b != NULL; b = b->next) {
		*tml += b->size;
		if (b->alloc_status == IS_ALLOCATED) {
			*tral += b->size;
			*tval += b->size >= 32 ? b->size - BLOCK_SIZE : b->size;
		}
		_info(b);
		if (b->next || b->alloc_status == IS_ALLOCATED) {
			ft_putstr_fd("[va: "S_GREEN, STDOUT_FILENO);
			ft_putaddr_fd((void *)b + BLOCK_SIZE, STDOUT_FILENO);
			ft_putstr_fd(S_NONE"]\n", STDOUT_FILENO);
		}
		else
			ft_putstr_fd("\n", STDOUT_FILENO);
		if (b->next && b->zone != b->next->zone)
			ft_putstr_fd("---\n", STDOUT_FILENO);
	}
}

static void		_bar_mode(void) {
	size_t	alloc_count = 0;
	size_t	free_count = 0;

	ft_putstr_fd("\nBar Mode:\n["S_GREEN, STDOUT_FILENO);
	ft_putstr_fd(g_first_block->zone == TINY ? "TINY" : g_first_block->zone == SMALL ? "SMALL" : "LARGE", STDOUT_FILENO);
	ft_putstr_fd(S_NONE"]: [", STDOUT_FILENO);
	for (block_t *b = g_first_block; b != NULL; b = b->next) {
		if (b->alloc_status == IS_FREE) {
			ft_putstr_fd(S_GREEN"F"S_NONE, STDOUT_FILENO);
			++free_count;
		}
		else {
			ft_putstr_fd(S_RED"A"S_NONE, STDOUT_FILENO);
			++alloc_count;
		}
		if (b->next)
			ft_putstr_fd(" ", STDOUT_FILENO);
		if (b->next && b->zone != b->next->zone) {
			ft_putstr_fd("]\n["S_GREEN, STDOUT_FILENO);
			ft_putstr_fd(b->next->zone == TINY ? "TINY" : b->next->zone == SMALL ? "SMALL" : "LARGE", STDOUT_FILENO);
			ft_putstr_fd(S_NONE"]: [", STDOUT_FILENO);
		}
	}
	ft_putstr_fd(S_NONE"]\n\n", STDOUT_FILENO);

}

static void		_print_total(const char *msg, size_t total) {
	ft_putstr_fd(msg, STDOUT_FILENO);
	ft_putstr_fd(S_GREEN, STDOUT_FILENO);
	ft_putnbr_fd(total, STDOUT_FILENO, 0);
	ft_putstr_fd(S_NONE, STDOUT_FILENO);
	ft_putstr_fd(" bytes\n", STDOUT_FILENO);
}

void			_show_alloc_mem_info(void) {
    ft_putstr_fd(S_CYAN"\n--- Memory info ---\n"S_NONE, STDOUT_FILENO);
	if (g_first_block == NULL) {
		ft_putstr_fd(S_YELLOW"No blocks allocate!\n"S_NONE, STDOUT_FILENO);
		return;
	}

	size_t  total_malloc_len = 0;
	size_t  total_r_allocated_len = 0;
	size_t  total_v_allocated_len = 0;

	_info_mode(&total_malloc_len, &total_r_allocated_len, &total_v_allocated_len);
	_bar_mode();

	_print_total("Total allocate bytes (real):    ", total_r_allocated_len);
	_print_total("Total allocate bytes (virtual): ", total_v_allocated_len);
	_print_total("Total malloc len:               ", total_malloc_len);
}


void		show_alloc_mem_info(void) {
	pthread_mutex_lock(&g_memory_mutex);
	_show_alloc_mem_info();
	pthread_mutex_unlock(&g_memory_mutex);
}