#include<stdio.h>

// MaxHeap
int maxHeap[100];
int dataCount = 1; // Index starts at 1

int getParentIndex(int index) {
    return index / 2;
}

int getLeftIndex(int index) {
    return index * 2;
}

int getRightIndex(int index) {
    return index * 2 + 1;
}

void viewHeap() {
    if (dataCount <= 1) {
        printf("Your Heap is Empty. Insert more data!\n\n");
    } else {
        for (int i = 1; i < dataCount; i++) {
            printf("Heap[%2d] = %d\n", i, maxHeap[i]);
        }
        puts("");
    }
}

void swapValue(int index1, int index2) {
    int temp = maxHeap[index1];
    maxHeap[index1] = maxHeap[index2];
    maxHeap[index2] = temp;
}

void HeapUp(int index) {
    if (index <= 1) printf("Heap is empty!"); // heap is empty
    
    int parentIndex = getParentIndex(index);
    
    if (maxHeap[parentIndex] >= maxHeap[index]) return;
    
    swapValue(parentIndex, index);
    HeapUp(parentIndex);
}

void HeapDown(int index) {
    int largest = index;
    int leftChild = getLeftIndex(index);
    int rightChild = getRightIndex(index);
    
    if (leftChild < dataCount && maxHeap[leftChild] > maxHeap[largest])
        largest = leftChild;
    
    if (rightChild < dataCount && maxHeap[rightChild] > maxHeap[largest])
        largest = rightChild;
    
    // swap if largest is not the current index
    if (largest != index) {
        swapValue(index, largest);
        HeapDown(largest);
    }
}

void push(int input) {
    maxHeap[dataCount] = input;
    HeapUp(dataCount);
    dataCount++;
}

// deletion always start in root/ largest
int pop() {
    if (dataCount <= 1) return -1; // Heap is empty
    
    int removed = maxHeap[1];
    dataCount--;
    maxHeap[1] = maxHeap[dataCount]; // move last element to root
    HeapDown(1);
    return removed;
}

void createMenu() {
    printf("1. Insert\n");
    printf("2. Delete\n");
    printf("3. Exit\n");
}

int main() {
    int input = -1, num;
    do {
        printf("Data Count: %d\n", dataCount - 1);
        viewHeap();
        createMenu();
        
        do {
            printf("Input your choice: ");
            scanf("%d", &input); 
            getchar();
        } while (input < 1 || input > 3);
    
        switch (input) {
            case 1: 
                printf("What data should be inserted into the heap?\n");
                scanf("%d", &num); 
                getchar();
                push(num);
                printf("%d has been inserted into the heap\n\n", num);
                getchar();
                break;
            case 2: 
                if (dataCount <= 1) {
                    printf("Your heap is empty. Insert more data!\n\n");
                } else {
                    printf("%d (the largest value) has been removed\n\n", pop());
                }
                getchar();
                break;
        }
    } while (input != 3);
    
//    return 0;
}
