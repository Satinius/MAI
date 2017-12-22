#include "stdafx.h"
#include "TAllocationBlock.h"

TAllocationBlock::TAllocationBlock(size_t size, size_t count) : size(size), count(count)
{
	usedBlocks = (char*)malloc(size* count);
	freeBlocks = (void**)malloc(sizeof(void*)*count);

	for (size_t i = 0; i < count; ++i)
		freeBlocks[i] = usedBlocks + i * size;
	freeCount = count;
}

void * TAllocationBlock::allocate()
{
	void *result = nullptr;
	
	if (freeCount > 0) {
		result = freeBlocks[freeCount - 1];
		freeCount--;
	}
	else {
		std::cout << "TAllocationBlock: No memory exception" << std::endl;
	}
	return result;
}

void TAllocationBlock:: deallocate(void * pointer)
{
	freeBlocks[freeCount] = pointer;
	freeCount++;
}

bool TAllocationBlock::hasFreeBlocks()
{
	return freeCount > 0;
}

TAllocationBlock::~TAllocationBlock()
{
	if (freeCount < count)
		std::cout << "Memory leak?" << std::endl;
	else
		std::cout << "Memory freed" << std::endl;
	delete freeBlocks;
	delete usedBlocks;
}

