#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memallocator.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 1)
    // Дескриптор
    typedef struct descriptor_t {
        int blockSize;
        struct descriptor_t* next;
    } descriptor_t;
#pragma pack(pop)

    // макрос для блока, блок состоит из blockSize, next, data, blockSize
#define BLOCK_INFO_SIZE (int)(sizeof(descriptor_t) + sizeof(int))

// переменная для данных памяти
    static struct {
        void* memBlock;      // начало блока
        descriptor_t
            * startList,        // начало списка
            * endList,          // конец списка
            * beforeLastAlloc;  // элемент списка, чтобы начать искать блок для выделения
        int totalSize;       // размер блока
    } s_memInfo;

#define SUCCESS 1
#define FAIL 0

   
    int meminit(void* pMemory, int size) {
        descriptor_t descriptor;

        if (size < memgetminimumsize() || pMemory == NULL)
            return FAIL;

        s_memInfo.beforeLastAlloc = s_memInfo.startList = (descriptor_t*)pMemory;
        s_memInfo.memBlock = pMemory;
        s_memInfo.endList = (descriptor_t*)((char*)pMemory + BLOCK_INFO_SIZE);
        s_memInfo.totalSize = size;

        descriptor.blockSize = 0;
        descriptor.next = (descriptor_t*)((char*)pMemory + BLOCK_INFO_SIZE);
        memcpy(pMemory, &descriptor, sizeof(descriptor));
        *(int*)(s_memInfo.startList + 1) = 0;

        descriptor.blockSize = size - 2 * BLOCK_INFO_SIZE;
        descriptor.next = (descriptor_t*)pMemory;
        memcpy((char*)pMemory + BLOCK_INFO_SIZE, &descriptor, sizeof(descriptor));
        memset((char*)pMemory + BLOCK_INFO_SIZE + sizeof(descriptor), 0, size - 2 * BLOCK_INFO_SIZE);
        *(int*)((char*)pMemory + size - sizeof(int)) = descriptor.blockSize;

        return SUCCESS;
    }

 
    void memdone() {
        int size;

        if (s_memInfo.memBlock == NULL)
            return;

        size = s_memInfo.startList->blockSize + s_memInfo.startList->next->blockSize + 2 * BLOCK_INFO_SIZE;
#ifdef PRINT_LEAKS
        if (size != s_memInfo.totalSize)
            fprintf(stderr, "Memory leaks");
#endif /* PRINT_LEAKS */

        memset(s_memInfo.memBlock, 0, s_memInfo.totalSize);
        memset(&s_memInfo, 0, sizeof(s_memInfo));
    }


    void* memalloc(int size) {
        descriptor_t* beforeNewAlloc, * newAlloc;

        if (s_memInfo.memBlock == NULL)
            return NULL;

        if (size <= 0)
            return NULL;

        beforeNewAlloc = s_memInfo.beforeLastAlloc;
        newAlloc = beforeNewAlloc->next;

        while (newAlloc->blockSize < size) {
            beforeNewAlloc = newAlloc;
            newAlloc = newAlloc->next;

            if (beforeNewAlloc == s_memInfo.beforeLastAlloc)
                return NULL;
        }
        s_memInfo.beforeLastAlloc = beforeNewAlloc;

        if (newAlloc->blockSize > size + BLOCK_INFO_SIZE) {
            descriptor_t* splitedBlock = (descriptor_t*)((char*)newAlloc + size + BLOCK_INFO_SIZE);

            if (s_memInfo.startList == newAlloc)
                s_memInfo.startList = splitedBlock;
            if (s_memInfo.endList == newAlloc)
                s_memInfo.endList = splitedBlock;

            beforeNewAlloc->next = splitedBlock;
            splitedBlock->blockSize = newAlloc->blockSize - BLOCK_INFO_SIZE - size;
            splitedBlock->next = newAlloc->next;
            *((int*)((char*)newAlloc + sizeof(descriptor_t) + newAlloc->blockSize)) = splitedBlock->blockSize;

            newAlloc->next = NULL;
            newAlloc->blockSize = -size;
            *((int*)splitedBlock - 1) = -size;

            return newAlloc + 1;
        }

        if (s_memInfo.startList == newAlloc)
            s_memInfo.startList = newAlloc->next;
        if (s_memInfo.endList == newAlloc)
            s_memInfo.endList = beforeNewAlloc;

        beforeNewAlloc->next = newAlloc->next;
        
        newAlloc->next = NULL;
        newAlloc->blockSize = -newAlloc->blockSize;
        *((int*)((char*)newAlloc + sizeof(descriptor_t) - newAlloc->blockSize)) = newAlloc->blockSize;
        return newAlloc + 1;
    }

    // Free memory previously allocated by memalloc
    void memfree(void* p) {
        descriptor_t* blockDescr;

        if ((char*)p < (char*)s_memInfo.memBlock + BLOCK_INFO_SIZE ||
            (char*)p >(char*)s_memInfo.memBlock + s_memInfo.totalSize - sizeof(int))
            return;

        blockDescr = (descriptor_t*)p - 1;

        if (blockDescr->blockSize > 0)
            return;

        if ((char*)p - (char*)s_memInfo.memBlock - blockDescr->blockSize + (int)sizeof(int) < s_memInfo.totalSize &&
            ((descriptor_t*)((char*)p - blockDescr->blockSize + sizeof(int)))->blockSize > 0) {
            descriptor_t
                * prev = s_memInfo.endList,
                * next = s_memInfo.startList,
                * realNext = (descriptor_t*)((char*)p + sizeof(int) - blockDescr->blockSize);

            
            do {
                prev = next;
                next = next->next;
            } while (next != realNext);
            prev->next = next->next;
            blockDescr->blockSize -= next->blockSize + BLOCK_INFO_SIZE;
            
            if (s_memInfo.endList == next)
                s_memInfo.endList = prev;
            if (s_memInfo.startList == next)
                s_memInfo.startList = next->next;
            if (s_memInfo.beforeLastAlloc == next)
                s_memInfo.beforeLastAlloc = next->next;
        }
        
        if (*(int*)((char*)p - BLOCK_INFO_SIZE) > 0) {
            
            descriptor_t* descr = (descriptor_t*)((char*)p - sizeof(descriptor_t) - BLOCK_INFO_SIZE - *(int*)((char*)p - BLOCK_INFO_SIZE));
            descr->blockSize -= blockDescr->blockSize - BLOCK_INFO_SIZE;
            *((int*)((char*)p - blockDescr->blockSize)) = descr->blockSize;
            memset(descr + 1, 0, descr->blockSize);
            return;
        }

        
        blockDescr->next = s_memInfo.startList;
        blockDescr->blockSize = -blockDescr->blockSize;
        *(int*)((char*)blockDescr + blockDescr->blockSize + sizeof(descriptor_t)) = blockDescr->blockSize;
        memset(blockDescr + 1, 0, blockDescr->blockSize);
        s_memInfo.endList->next = blockDescr;
        s_memInfo.startList = blockDescr;
    }

    int memgetminimumsize() {
        return 2 * BLOCK_INFO_SIZE;
    }

    int memgetblocksize() {
        return BLOCK_INFO_SIZE;
    }

#ifdef __cplusplus
}
#endif

