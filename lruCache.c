#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int capacity;

int validSize() {
    while(1) {
        char size[10];
        printf("Enter cache size (1-1000): ");
        fgets(size, sizeof(size), stdin);
        for(int i = 0; size[i] != '\0'; i++) {
            if(size[i] == '\n') {
                size[i] = '\0';
                break;
            }
        }
        int valid = 1;
        for(int i = 0; size[i] != '\0'; i++) {
            if(!isdigit(size[i])) valid = 0;
        }
        if(!valid){
            printf("Invalid size. Please try again.\n");
            continue;
        }
       
        int v = atoi(size);
        if(v > 0 && v <= 1000) {
            return v;
        }
        else{
            printf("Invalid size. Please try again.\n");
            continue;
        }
         
    }
}

int validChoice() {
    while(1) {
        char choice[10];
        printf("Enter the valid choice: ");
        fgets(choice, sizeof(choice), stdin);
        for(int i = 0; choice[i] != '\0'; i++) {
            if(choice[i] == '\n') {
                choice[i] = '\0';
                break;
            }
        }
        int valid = 1;
        for(int i = 0; choice[i] != '\0'; i++) {
            if(!isdigit(choice[i])) valid = 0;
        }
        if(!valid){
            printf("Invalid choice. Please try again.\n");
            continue;
        }
       
        int v = atoi(choice);
        if(v > 0 && v <= 5) {
            return v;
        }
        else{
            printf("Invalid choice. Please try again.\n");
            continue;
        }
         
    }
}

int validKey() {
    while(1) {
        char key[50];
        printf("Enter key (non-negative integer): ");
        fgets(key, sizeof(key), stdin);
        for(int i = 0; key[i] != '\0'; i++) {
            if(key[i] == '\n') {
                key[i] = '\0';
                break;
            }
        }
        int valid = 1;
        for(int i = 0; key[i] != '\0'; i++) {
            if(!isdigit(key[i])){
                valid = 0;
                break;

            } 
        }
        if(!valid){
            printf("Invalid key. Please try again.\n");
            continue;
        } 
        int v = atoi(key);
        if(v >= 0){
            return v;
        } 
        else{
            printf("Invalid key. Please try again.\n");
            continue;
        }
         
    }
}

void validValue(char value[]) {
    while(1) {
        char input[100];
        printf("Enter value (non-empty string up to 100 chars): ");
        fgets(input, sizeof(input), stdin);
        for(int i = 0; input[i] != '\0'; i++) {
            if(input[i] == '\n') {
                input[i] = '\0';
                break;
            }
        }
        if(input[0] == '-') {
            printf("Invalid value. Please try again.\n");
            continue;
        }
        if(isdigit(input[0])) {
            printf("Invalid value. Please try again.\n");
            continue;
        }
        int len = strlen(input);
        if(len > 0 && len <= 100) {
            strcpy(value, input);
            return;
        }
        else{
            printf("Invalid value. Please try again.\n");
            continue;
        }
        
    }
}

typedef struct Node {
    int key;
    char value[100];
    struct Node* prev;
    struct Node* next;
    struct Node* hashNext;
} Node;

typedef struct {
    Node** bucket;
    int total;
    Node* head;
    Node* tail;
} LRUCache;

int hashFunction(int key) {
    return key % capacity;
}

void initCache(LRUCache* cache) {
    cache->bucket = malloc(capacity * sizeof(Node*));
    for(int i = 0; i < capacity; i++) cache->bucket[i] = NULL;
    cache->total = 0;
    cache->head = NULL;
    cache->tail = NULL;
}

void moveToFront(LRUCache* cache, Node* node) {
    if(cache->head == node) return;
    if(node->prev) node->prev->next = node->next;
    if(node->next) node->next->prev = node->prev;
    if(cache->tail == node) cache->tail = node->prev;
    node->prev = NULL;
    node->next = cache->head;
    if(cache->head) cache->head->prev = node;
    cache->head = node;
    if(cache->tail == NULL) cache->tail = node;
}

void removeTail(LRUCache* cache) {
    Node* d = cache->tail;
    if(d == NULL) return;
    int idx = hashFunction(d->key);
    Node* t = cache->bucket[idx];
    Node* p = NULL;
    while(t) {
        if(t == d) {
            if(p == NULL) cache->bucket[idx] = t->hashNext;
            else p->hashNext = t->hashNext;
            break;
        }
        p = t;
        t = t->hashNext;
    }
    if(d->prev) d->prev->next = NULL;
    cache->tail = d->prev;
    if(cache->head == d) cache->head = NULL;
    free(d);
    cache->total--;
}

void put(LRUCache* cache, int key, char value[]) {
    int idx = hashFunction(key);
    Node* t = cache->bucket[idx];
    while(t) {
        if(t->key == key) {
            strcpy(t->value, value);
            moveToFront(cache, t);
            return;
        }
        t = t->hashNext;
    }
    if(cache->total == capacity) removeTail(cache);
    Node* n = malloc(sizeof(Node));
    n->key = key;
    strcpy(n->value, value);
    n->prev = NULL;
    n->next = cache->head;
    if(cache->head) cache->head->prev = n;
    cache->head = n;
    if(cache->tail == NULL) cache->tail = n;
    n->hashNext = cache->bucket[idx];
    cache->bucket[idx] = n;
    cache->total++;
    printf("Inserted (%d,%s)\n", key, value);
}

char* get(LRUCache* cache, int key) {
    int idx = hashFunction(key);
    Node* t = cache->bucket[idx];
    while(t) {
        if(t->key == key) {
            moveToFront(cache, t);
            printf("the value of the key is: ");
            return t->value;
        }
        t = t->hashNext;
    }
    return "key is not present";
}

void display(LRUCache* cache) {
    Node* t = cache->head;
    if(t == NULL) {
        printf("Cache is empty\n");
        return;
    }
    while(t) {
        printf("The key and value pair is:(%d,%s) ", t->key, t->value);
        printf("\n");
        t = t->next;
    }
    printf("\n");
}

int main() {
    capacity = validSize();
    LRUCache cache;
    initCache(&cache);
    while(1) {
        
        printf("1. Put\n2. Get\n3. Display\n4. Exit\n ");
        int c = validChoice();
       
        
        if(c == 1) {
            int k = validKey();
            char v[100];
            validValue(v);
            put(&cache, k, v);
        } else if(c == 2) {
            int k = validKey();
            char* r = get(&cache, k);
            if(r) printf("%s\n", r);
            else printf("NULL\n");
        } else if(c == 3) {
            display(&cache);
        } else if(c == 4) {
            printf("Exiting the program\n");
            exit(0);
        }
    }
    return 0;
}
