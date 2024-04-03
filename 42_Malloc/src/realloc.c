#include "malloc.h"


static void*	_realloc(void *ptr, size_t size) {
	if (ptr == NULL)
		return (_malloc(size));

	block_t*	free_block = NULL;
	block_t*	old_block = GET_META(ptr);
	size_t		align_size = ALIGN(size);
	void*		new_ptr = NULL;

	if (old_block->alloc_status == IS_FREE) {
		ft_putstr_fd(S_YELLOW"realloc()"S_NONE": called on a free block\n", STDERR_FILENO);
		return NULL;
	}

	if (old_block->size == align_size + BLOCK_SIZE)
		return ptr;


	if (old_block->size > align_size + BLOCK_SIZE) {
		split_block(old_block, align_size);
		free_block = old_block->next;
		merge_free_block(free_block);
		return ptr;
	}

	if (old_block->next &&
			old_block->next->alloc_status == IS_FREE &&
			old_block->next->size + old_block->size >= align_size + BLOCK_SIZE &&
			old_block->next->zone == old_block->zone) {
		old_block->alloc_status = IS_FREE;
		merge_free_block(old_block);
		split_block(old_block, align_size);
		return ptr;
	}
	else {
		if ((new_ptr = _malloc(size)) == NULL)
			return NULL;
		ft_memcpy(new_ptr, ptr, old_block->size - BLOCK_SIZE);
		_free(ptr);
		return new_ptr;
	}
	return ptr;
}

void*			realloc(void *ptr, size_t size) {
	if (DEBUG) {
		ft_putstr_fd("\n-- "S_CYAN"realloc()"S_NONE" called: ", STDOUT_FILENO);
		ft_putstr_fd("["S_GREEN, STDOUT_FILENO);
		ft_putnbr_fd(size, STDOUT_FILENO, 0);
		ft_putstr_fd(S_NONE" bytes]", STDOUT_FILENO);
		ft_putstr_fd("["S_GREEN, STDOUT_FILENO);
		ft_putaddr_fd(ptr, STDOUT_FILENO);
		ft_putstr_fd(S_NONE"]", STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}

	void	*new_ptr = NULL;

	pthread_mutex_lock(&g_memory_mutex);
	new_ptr = _realloc(ptr, size);
	pthread_mutex_unlock(&g_memory_mutex);

	return (new_ptr);
}