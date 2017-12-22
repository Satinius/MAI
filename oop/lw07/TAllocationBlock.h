#pragma once
#include <cstdlib>
#include <iostream>

class TAllocationBlock
{
public:
	TAllocationBlock(size_t size, size_t count);
	void *allocate();
	void deallocate(void *pointer);
	bool hasFreeBlocks();

	~TAllocationBlock();

private:
	size_t size;
	size_t count;

	char * usedBlocks;
	void ** freeBlocks;

	size_t freeCount;
};

