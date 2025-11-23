#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int capacity;

int validSize() {
    while(1) {
        char size[10];
        fgets(size, sizeof(size), stdin);
        for(int i = 0; size[i] != '\0'; i++) {
            if(size[i] == '\n') {
                size[i] = '\0';
                break;
            }
        }
        int ok = 1;
        for(int i = 0; size[i] != '\0'; i++) {
            if(!isdigit(size[i])) ok = 0;
        }
        if(!ok) continue;
        int v = atoi(size);
        if(v > 0 && v <= 1000) return v;
    }
}

int validKey() {
    while(1) {
        char key[50];
        fgets(key, sizeof(key), stdin);
        for(int i = 0; key[i] != '\0'; i++) {
            if(key[i] == '\n') {
                key[i] = '\0';
                break;
            }
        }
        int ok = 1;
        for(int i = 0; key[i] != '\0'; i++) {
            if(!isdigit(key[i])) ok = 0;
        }
        if(!ok) continue;
        int v = atoi(key);
        if(v >= 0) return v;
    }
}

void validValue(char value[]) {
    while(1) {
        char input[100];
        fgets(input, sizeof(input), stdin);
        for(int i = 0; input[i] != '\0'; i++) {
            if(input[i] == '\n') {
                input[i] = '\0';
                break;
            }
        }
        int len = strlen(input);
        if(len > 0 && len <= 100) {
            strcpy(value, input);
            return;
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
}

char* get(LRUCache* cache, int key) {
    int idx = hashFunction(key);
    Node* t = cache->bucket[idx];
    while(t) {
        if(t->key == key) {
            moveToFront(cache, t);
            return t->value;
        }
        t = t->hashNext;
    }
    return NULL;
}

void display(LRUCache* cache) {
    Node* t = cache->head;
    while(t) {
        printf("(%d,%s) ", t->key, t->value);
        t = t->next;
    }
    printf("\n");
}

int main() {
    capacity = validSize();
    LRUCache cache;
    initCache(&cache);
    while(1) {
        int c;
        scanf("%d", &c);
        getchar();
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
            exit(0);
        }
    }
    return 0;
}
