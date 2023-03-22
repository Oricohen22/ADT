#include "AdptArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;

};

PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_,PRINT_FUNC  printFunc_)
{
	PAdptArray pArr = (PAdptArray)malloc(sizeof(struct AdptArray_));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc_;
	pArr->copyFunc = copyFunc_;
    pArr->printFunc = printFunc_; 
	return pArr;
}


Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
	PElement* newpElemArr;
	if (pArr == NULL)
		return FAIL;

	if (idx >= pArr->ArrSize)
	{
		
    // Extend Array
		if ((newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL)
			return FAIL;
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
		free(pArr->pElemArr);
		pArr->pElemArr = newpElemArr;
	}

	if (pArr->pElemArr[idx]!= NULL){
	pArr->delFunc((pArr->pElemArr)[idx]);
    }
    (pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);
	// Update Array Size
	pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
	return SUCCESS;
}

void DeleteAdptArray(PAdptArray pArr)
{
	int i;
	if (pArr == NULL)
		return;
	for(i = 0; i < pArr->ArrSize; ++i)
	{
        if (pArr->pElemArr[i]!= NULL)
		pArr->delFunc((pArr->pElemArr)[i]);
	}
	free(pArr->pElemArr);
	free(pArr);}


PElement GetAdptArrayAt(PAdptArray Parray, int index)
{
    if (Parray == NULL)
    return NULL;

    if (index >= Parray->ArrSize)
    return NULL;

    if(Parray->pElemArr[index]==NULL)
    return NULL;

    return Parray->copyFunc(Parray->pElemArr[index]);
}


int GetAdptArraySize(PAdptArray Parray)
{
    //check if the array are initiallized
    if(Parray== NULL)
    return -1;

    return Parray->ArrSize;
}

void PrintDB(PAdptArray Parray)
{
for (int i = 0; i < Parray->ArrSize; i++)
{
    if (Parray->pElemArr[i] != NULL)
    Parray->printFunc(Parray->pElemArr[i]);

}

}

