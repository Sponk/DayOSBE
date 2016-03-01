#include <malloc.h>
#include <syscall.h>
#include <string.h>
#include <stdio.h>

#ifndef MALLOC_270_H

extern void* sbrk(size_t size);

#define HEADERSIZE sizeof(node_t)

#define BLOCK_HEADER(x) (void*)(((uintptr_t) x) - HEADERSIZE)
#define BLOCK_START(x) (void*)(((uintptr_t) x) + HEADERSIZE)
#define NEXT_BLOCK(x) (void*)((uintptr_t) BLOCK_START(x) + x->size)

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#define MAGIC 0xDEADBEEF

typedef struct NODE
{
	unsigned int free;
	size_t size;
	unsigned int magic;
	struct NODE* next;
} node_t;

static node_t* root = NULL;
uint32_t currentLimit = 0;

node_t* createBlock(node_t* parent, size_t sz)
{
	if (!parent || !sz)
		return NULL;

	parent->next = NEXT_BLOCK(parent);
	
	size_t oldLimit = currentLimit;
	while(((uint32_t)parent->next) + sz >= (currentLimit - HEADERSIZE))
	{
		sbrk(0x1000);
		currentLimit += 0x1000;
	}
	
	/*currentLimit = MAX(currentLimit, ((uintptr_t) parent->next) + sz + HEADERSIZE);*/
	//if(oldLimit != currentLimit)
	//{
		/*currentLimit += 0x1000;
		currentLimit &= ~0xFFF;		
	*///	sbrk(currentLimit - oldLimit);
	//}
	
	parent->next->size = sz;
	parent->next->next = NULL;
	parent->next->free = 1;
	parent->next->magic = MAGIC;
	
	//kprintf("Creating block for memory: 0x%x at 0x%x\n", BLOCK_START(parent->next), parent->next);
	
	return parent->next;
}

void* malloc(size_t size)
{
	node_t* node = root;
	node_t* last = node;
	while(node != NULL)
	{
		if(node->size >= size && node->free == 1)
		{
			node->free = 0;
			return BLOCK_START(node);
		}
		
		last = node;
		node = node->next;
	}
	
	node = createBlock(last, size);
	node->free = 0;
	
	// printf("malloc %d 0x%x\n", size, BLOCK_START(node));

	return BLOCK_START(node);
}

void free(void* addr)
{
	//kprintf("Trying to free: %x\n", addr);
	node_t* node = BLOCK_HEADER(addr);
	//printf("free 0x%x\n", addr);
	
	if(addr == NULL)
		return;
	
	if(node->magic != MAGIC)
	{
		printf("Heap corruption: Magic does not match!\n");
		return;
	}
	
	if(node->free == 1)
	{
		printf("Heap corruption: Double free!\n");
		return;
	}
	
	node->free = 1;
	
	// assert(node->magic == MAGIC);
	
	/*while(node != NULL)
	{
	//	kprintf("Processing: %x which starts at %x\n", node, BLOCK_START(node));
		if(BLOCK_START(node) == addr)
		{
			//kprintf("Freeing memory at: 0x%x\n", addr);
			node->free = 1;
		}
		
		node = node->next;
	}*/
}

void* realloc(void* p, size_t sz)
{
	if(p == NULL)
		return malloc(sz);
	
	if(sz == 0)
	{
		free(p);
		return NULL;
	}
	
	node_t* oldBlock = BLOCK_HEADER(p);
	
	if(oldBlock->magic != MAGIC)
	{
		printf("Block magic does not match!\n");
		return NULL;
	}
	
	void* newmem = malloc(sz);
	
	sz = MIN(oldBlock->size, sz);
	memcpy(newmem, p, sz);
	
	oldBlock->free = 1;
	//free(p);
	
	return newmem;
}

void* calloc(size_t num, size_t bytes)
{
	size_t sz = num * bytes;
	void* mem = malloc(sz);
	if(mem)
		memset(mem, sz, 0);
	
	return mem;
}

void InitHeap()
{
	root = sbrk(0x1000);
	root->size = 0;
	root->next = NULL;
	root->free = 1;
	
	currentLimit = ((uint32_t) root) + 0x1000;
}
#else
void InitHeap()
{

}
#endif
