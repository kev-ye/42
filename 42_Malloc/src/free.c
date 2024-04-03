#include "malloc.h"


static block_t*	_get_current_block(block_t *block) {
	for (block_t *b = g_first_block; b != NULL; b = b->next) {
		if (b == block)
			return b;
	}
	return NULL;
}

void			_free(void *ptr) {
	if (ptr == NULL)
		return;

	block_t*    b = GET_META(ptr);


	// check if the pointer is valid
	if (_get_current_block(b) == NULL) {
		ft_putstr_fd(S_YELLOW"free():"S_NONE" invalid pointer\n", STDERR_FILENO);
		return;
	}

	// check if the pointer is already free
	if (b->alloc_status == IS_FREE) {
		ft_putstr_fd(S_YELLOW"free():"S_NONE" double free\n"S_NONE, STDERR_FILENO);
		return;
	}

	b->alloc_status = IS_FREE;
	if (b->prev && b->prev->alloc_status == IS_FREE)
		b = merge_free_block(b->prev);
	if (b->next)
		merge_free_block(b);
}

void			free(void *ptr) {
	if (DEBUG) {
		ft_putstr_fd("\n-- "S_CYAN"free()"S_NONE" called: ", STDOUT_FILENO);
		ft_putstr_fd("["S_GREEN, STDOUT_FILENO);
		ft_putaddr_fd(ptr, STDOUT_FILENO);
		ft_putstr_fd(S_NONE"]", STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}

	pthread_mutex_lock(&g_memory_mutex);
	_free(ptr);
	pthread_mutex_unlock(&g_memory_mutex);
}

/*
 * Destructor function that will be called when the program exits
 * It will free all the memory zones that are not used anymore
 */
__attribute__((destructor))
void			dealloc_free_zone() {
	if (DEBUG)
		ft_putstr_fd("\n-- "S_PURPLE"dealloc_free_zone()"S_NONE" called\n", STDOUT_FILENO);

	block_t*	to_dealloc = NULL;
	block_t*	next_zone = NULL;
	block_t*	curr_zone = g_first_block;

	while (curr_zone) {
		next_zone = get_next_zone(curr_zone);
		to_dealloc = curr_zone;
		for (block_t *b = to_dealloc; b != NULL; b = b->next) {
			if (b->alloc_status == IS_ALLOCATED) {
				to_dealloc = NULL;
				break;
			}
			if (b->next && b->next != next_zone)
				break;
		}
	

		if (to_dealloc) {
			if (munmap(to_dealloc, to_dealloc->size) != 0) {
				if (DEBUG)
					ft_putstr_fd(S_RED"Error:"S_NONE" munmap failed\n", STDERR_FILENO);
				return;
			}
			to_dealloc = NULL;
			g_first_block = next_zone;
		}	
		curr_zone = next_zone;
	}

	if (DEBUG)
		_show_alloc_mem_info();
}
