#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 26
#define INITIAL_SIZE 26
#define LOAD_FACTOR_THRESHOLD 0.7


struct node {
    char data[100];
    struct node *next;
} *hashTable[SIZE], *curr;

int count = 0;

// Hash function using mid-square method
int hashMidSquare(const char *inputString) {
    int numericValue = 0;
    int inputLength = strlen(inputString);

    for (int i = 0; i < 3 && i < inputLength; i++) {
        numericValue = numericValue * 100 + (unsigned char)inputString[i];
    }

    long long squaredValue = (long long)numericValue * numericValue;
    char squaredString[21];
    snprintf(squaredString, sizeof(squaredString), "%lld", squaredValue);

    int squaredLength = strlen(squaredString);
    int middleIndex = squaredLength / 2 - 1;
    char middleDigits[4] = "000";

    if (middleIndex >= 0 && middleIndex + 2 < squaredLength) {
        strncpy(middleDigits, squaredString + middleIndex, 3);
        middleDigits[3] = '\0';
    }
    return atoi(middleDigits) % SIZE;
}

// Hash function using division method
int hashDivision(char data[]) {
    char firstChar = data[0];
    return tolower(firstChar) - 'a';
}

// Hash function using folding method
int hashFolding(const char *data) {
    int hashValue = 0;
    int length = strlen(data);
    int segmentSize = 2; // Size of each segment

    // Process the string in segments
    for (int i = 0; i < length; i += segmentSize) {
        int segmentSum = 0;

        // Sum the ASCII values of the characters in the segment
        for (int j = 0; j < segmentSize && (i + j) < length; j++) {
            segmentSum += (unsigned char)data[i + j];
        }

        // Add the segment sum to the hash value
        hashValue += segmentSum;
    }

    // Return the hash value modulo the size of the hash table
    return hashValue % SIZE;
}

// Hash function using digit extraction method
int hashDigitExtraction(const char *data) {
    int num = 0;
    for (int i = 0; i < 3 && data[i] != '\0'; i++) {
        num = num * 100 + data[i];
    }

    long long square = (long long)num * num;
    char squareStr[21];
    sprintf(squareStr, "%lld", square);

    int len = strlen(squareStr);
    if (len < 5) return num % SIZE; // If the square result is too short

    int extraction = (squareStr[len - 5] - '0') * 100 +
                     (squareStr[len - 3] - '0') * 10 +
                     (squareStr[len - 1] - '0');

    return extraction % SIZE;
}

// Hash function using rotating method
int hashRotating(const char *data) {
    int hash = 0;
    for (int i = 0; data[i] != '\0'; i++) {
        hash = (hash << 4) ^ (hash >> 28) ^ (unsigned char)data[i];
    }
    return abs(hash) % SIZE;
}

// collision
// Function to insert data into hash table using chaining
void pushBack(int hashKey, char data[]) {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    strcpy(newNode->data, data);
    newNode->next = NULL;

    if (hashTable[hashKey] == NULL) {
        hashTable[hashKey] = newNode;
    } else {
        curr = hashTable[hashKey];
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
}

// Chaining-based hash table input
void input_hash_chaining_division() {
    char data[100];
    for (int i = 0; i < SIZE; i++) {
        hashTable[i] = NULL;
    }

    while (1) {
        printf("Input Data (type 'exit' to stop): ");
        fgets(data, sizeof(data), stdin);
        data[strcspn(data, "\n")] = '\0';

        if (strcasecmp(data, "exit") == 0) break;

        int hashKey = hashDivision(data);
        pushBack(hashKey, data);
    }
}

// Function to view hash table contents
void viewHashTable() {
    for (int i = 0; i < SIZE; i++) {
        if (hashTable[i] != NULL) {
            printf("HASH TABLE INDEX [%d]: ", i);
            curr = hashTable[i];

            while (curr != NULL) {
                printf("%s -> ", curr->data);
                curr = curr->next;
            }
            printf("NULL\n");
        }
    }
}

// Free allocated memory in hash table
void freeHashTable() {
    for (int i = 0; i < SIZE; i++) {
        curr = hashTable[i];
        while (curr != NULL) {
            struct node *temp = curr;
            curr = curr->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

// Function to insert data using linear probing
void input_linearprobing_division(char data[]) {
    int key = hashDivision(data);

    if (count == SIZE) {
        printf("Table is full\n");
        return;
    }

    // Find next available slot
    while (hashTable[key] != NULL) {
        key = (key + 1) % SIZE;
    }

    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    strcpy(newNode->data, data);
    newNode->next = NULL;
    
    hashTable[key] = newNode;
    count++;
}

// Struct for rehashing method
typedef struct Entry {
    char *key;
    int value;
    struct Entry *next;
} Entry;

typedef struct {
    int size;
    int count;
    Entry **table;
} HashTable;

void createHashTable(HashTable *hashTable) {
    hashTable->size = INITIAL_SIZE;
    hashTable->count = 0;
    hashTable->table = malloc(INITIAL_SIZE * sizeof(Entry*));
    if (!hashTable->table) {
        printf("Memory allocation failed!\n");
        return;
    }
    for (int i = 0; i < INITIAL_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
}

void insert_rehash_division(node *hashTable, char *key, int value) {
    if ((float)(hashTable->count + 1) / hashTable->size > LOAD_FACTOR_THRESHOLD) {
        insert_rehash_division(hashTable);
    }
    int index = hashDivision(key) % hashTable->SIZE;
    Entry *newEntry = (Entry*)malloc(sizeof(Entry));
    if (!newEntry) {
        printf("Memory allocation failed!\n");
        return;
    }
    newEntry->key = strdup(key);
    if (!newEntry->key) {
        free(newEntry);
        printf("Memory allocation failed!\n");
        return;
    }
    newEntry->value = value;
    newEntry->next = hashTable->table[index];
    hashTable->table[index] = newEntry;
    hashTable->count++;
}

void freeHashTableRehash(HashTable *hashTable) {
    for (int i = 0; i < hashTable->SIZE; i++) {
        Entry *entry = hashTable->table[i];
        while (entry != NULL) {
            Entry *temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp);
        }
    }
    free(hashTable->table);
}

void menu_hashfunction() {
    printf("=========== HASH TABLES =========\n");
    printf("+++++++ HASH FUNCTION ++++++++\n");
    printf("1. Mid-square\n");
    printf("2. Division\n");
    printf("3. Folding\n");
    printf("4. Digit Extraction\n");
    printf("5. Rotating Hash\n");
    printf("Your input: ");
}

void menu_collisionhandling() {
    printf("+++++++ COLLISION HANDLING ++++++\n");
    printf("6. Linear Probing\n");
    printf("7. Rehashing\n");
    printf("8. Chaining\n");
    printf("Your input: ");
}

int main() {
    int input, collision;

    menu_hashfunction();
    scanf("%d", &input);
    getchar();

    switch (input) {
    	case 1: //Mid-square
    		break;
    	
        case 2:  // Division Hashing
            menu_collisionhandling();
            scanf("%d", &collision);
            getchar();
            
           if (collision == 6) {
            input_hash_chaining_division();
        } else if (collision == 7) {
            char data[100];
            printf("Enter data: ");
            fgets(data, sizeof(data), stdin);
            data[strcspn(data, "\n")] = '\0';
            input_linearprobing_division(data);
        } else if (collision == 8) {
            insert_rehash_division(&rehashTable, "example", 1);
        }
            viewHashTable();
            freeHashTable();
            freeHashTableRehash(&rehashTable);
            break;
            
        case 3: //Folding
        	break;
        	
        case 4: //Digit Extraction
        	break;
        	
        case 5: //Rotating
        	break;

        default:
            printf("==== Thank you for using this program ====\n");
            break;
    }
    return 0;
}
