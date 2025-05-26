#include<stdio.h>

//MinHeap
int minHeap[100];
int dataCount = 1;

int getParentIndex(int index)
{
	return index/2;
}

int getLeftIndex(int index)
{
	return index*2;
}

int getRightIndex(int index)
{
	return index*2 +1;
}

void viewHeap()
{
	if(dataCount<=1)
	{
		printf("Your Heap is Empty. Insert more data!\n\n");
	}
	else
	{
		for(int i=1; i<dataCount; i++)
		{
			printf("Heap[%2d] = %d\n", i, minHeap[i]);
		}
		puts("");
	}
}

void swapValue(int parentIndex, int currIndex)
{
	int temp = minHeap[parentIndex];
	minHeap[parentIndex] = minHeap[currIndex];
	minHeap[currIndex] = temp;
}

void HeapUp(int index)
{
	if(index <=1 ) return; //kondisinya kosong
	
	int parentIndex = getParentIndex(index);
	//masih memenuhi kondisi min-heap
	if(minHeap[parentIndex] <= minHeap[index]) return;
	
	//kalo nggk sesuai kondisi min-heap
	swapValue(parentIndex,index);
	//pengecekan kondisi secara rekursif
	HeapUp(parentIndex);
}

void HeapDown(int index)
{
	if(index >= dataCount) return;//ketika kondisinya kosong
	
	int smallest = index;//parent
	int leftValue = getLeftIndex(index);//left child
	int rightValue = getRightIndex(index);//right child
	
	if(minHeap[leftValue] < minHeap[smallest] && leftValue < dataCount)
		smallest = leftValue;
	
	if(minHeap[rightValue] < minHeap[smallest] && rightValue < dataCount)
		smallest = rightValue;
	
	//masih memenuhi kriteria min-heap
	if(smallest == index) return;
	
//	//pengecekan kondisi secara rekursif
//	HeapDown(smallest);

// swap if the current index not the smallest
	 if(smallest != index) {
        swapValue(index, smallest);
        HeapDown(smallest);
    }
}

void push(int input)
{
	minHeap[dataCount] = input;
	HeapUp(dataCount);
	dataCount++;
}

// deletion always start in root/ smallest
int pop()
{
	if(dataCount <=1) printf("Heap is empty!");
	
	int removed = minHeap[1];
	swapValue(1, dataCount-1);
	dataCount--;
	HeapDown(1);
	return removed;
}

void createMenu()
{
	printf("1. Insert\n");
	printf("2. Delete\n");
	printf("3. Exit\n");
}

int main()
{
	int input = -1, num;
	do
	{
		printf("Data:\n",dataCount);
		viewHeap();
		createMenu();
		
		do
		{
			printf("input your choice: ");
			scanf("%d", &input); getchar();
		} while(input < 1 || input > 3);
	
		switch(input)
		{
			case 1: printf("What data should be inputted into the heap?\n");
				scanf("%d", &num);getchar();
				push(num);
				printf("%d has been inputted into the heap\n\n", num);
				getchar();
				break;
			case 2: if(dataCount<=1)
				{
					printf("Your heap is empty. Insert more data!\n\n");
				}
				else
				{
					printf("%d has been deleted\n\n", pop());
				}
				getchar();
				break;
		}
	}while (input!=3);
	
	//return 0;
}

