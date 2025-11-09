#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define BLOCK_SIZE 512
#define NUM_BLOCKS 5000
#define MAX_BLOCKS_PER_FILE 100
#define NAME_LEN 50
#define LINE_LEN 2048


int getNumberOfBlocks(){
    char input[50];
    while(1){
        printf("Enter initial number of blocks:");
        fgets(input, sizeof(input), stdin);
        int valid = 1;
        for(int i=0; input[i]!='\0'; i++){
            if(input[i]=='\n' ){
                input[i]='\0';
                break;
            }
        
        }
        for (int i = 0; input[i] != '\0';i++){
            if(!isdigit(input[i])){
                printf("Entered value is not a number. Please enter a valid number.\n");
                valid = 0;
                break;
            }
        }
        if(valid==1){
            if(atoi(input)<1 || atoi(input)>5000){
                printf("Number must be in range between 0 and 100. Please try again.\n");
            }
            else{
                return atoi(input);
            }
        }
    }
    
}



int isValidDirName(char name[]) {
    // must start with a letter
    if (!((name[0] >= 'A' && name[0] <= 'Z') ||
          (name[0] >= 'a' && name[0] <= 'z'))) {
        return 0;
    }
    // only letters, digits, _ or -
    for (int i = 0; name[i] != '\0'; i++) {
        if (!((name[i] >= 'A' && name[i] <= 'Z') ||
              (name[i] >= 'a' && name[i] <= 'z') ||
              (name[i] >= '0' && name[i] <= '9') ||
              name[i] == '_' ||
              name[i] == '-')) {
            return 0;
        }
    }
    return 1;
}

int isValidFileName(char name[]) {
    // must start with a letter
    if (!((name[0] >= 'A' && name[0] <= 'Z') ||
          (name[0] >= 'a' && name[0] <= 'z'))) {
        return 0;
    }
    // letters, digits, _, -, .
    for (int i = 0; name[i] != '\0'; i++) {
        if (!((name[i] >= 'A' && name[i] <= 'Z') ||
              (name[i] >= 'a' && name[i] <= 'z') ||
              (name[i] >= '0' && name[i] <= '9') ||
              name[i] == '_' ||
              name[i] == '-' ||
              name[i] == '.')) {
            return 0;
        }
    }
    return 1;
}



typedef struct FreeBlockManagement {
    int index;
    struct FreeBlockManagement *next;
    struct FreeBlockManagement *prev;
} FreeBlockDLL;

typedef struct DirectoriesManagement {
    int isDirectory;
    char name[NAME_LEN];
    int blockPointers[MAX_BLOCKS_PER_FILE];
    int blockCount;
    int contentSize;
    struct DirectoriesManagement *parent;
    struct DirectoriesManagement *child;
    struct DirectoriesManagement *prev;
    struct DirectoriesManagement *next;
} DirectoryCLL;

FreeBlockDLL *freeHead = NULL;
FreeBlockDLL *freeTail = NULL;
int freeCount = 0;
char *virtualDisk = NULL;

FreeBlockDLL *createFreeNode(int idx) {
    FreeBlockDLL *n = malloc(sizeof(FreeBlockDLL));
    if (!n) { perror("malloc"); exit(1); }
    n->index = idx;
    n->next = n->prev = NULL;
    return n;
}

void initFreeList() {
    freeHead = createFreeNode(1);
    freeTail = freeHead;
    freeCount = 1;
    for (int i = 2; i <= NUM_BLOCKS; ++i) {
        FreeBlockDLL *n = createFreeNode(i);
        freeTail->next = n;
        n->prev = freeTail;
        freeTail = n;
        freeCount++;
    }
}

int popFreeBlock() {
    if (!freeHead) return -1;
    int idx = freeHead->index;
    FreeBlockDLL *tmp = freeHead;
    freeHead = freeHead->next;
    if (freeHead) freeHead->prev = NULL;
    else freeTail = NULL;
    free(tmp);
    freeCount--;
    return idx;
}

void pushFreeBlock(int idx) {
    FreeBlockDLL *n = createFreeNode(idx);
    if (!freeTail) {
        freeHead = freeTail = n;
    } else {
        freeTail->next = n;
        n->prev = freeTail;
        freeTail = n;
    }
    freeCount++;
}

DirectoryCLL* CreateDirectoryOrFile(char val[], int isDir) {
    DirectoryCLL* node = (DirectoryCLL*)malloc(sizeof(DirectoryCLL));
    strcpy(node->name, val);
    node->isDirectory = isDir;
    node->blockCount = 0;
    node->contentSize = 0;
    for (int i = 0; i < 10; i++) {
        node->blockPointers[i] = -1;
    }
    node->parent = NULL;
    node->child = NULL;
    node->prev = NULL;
    node->next = NULL;
    return node;
}


DirectoryCLL *findChild(DirectoryCLL *current, const char *name) {
    if (!current || !current->child) return NULL;
    DirectoryCLL *head = current->child;
    DirectoryCLL *t = head;
    do {
        if (strcmp(t->name, name) == 0) return t;
        t = t->next;
    } while (t != head);
    return NULL;
}

void insertChild(DirectoryCLL *current, DirectoryCLL *node) {
    if (!current->child) {
        current->child = node;
        node->next = node->prev = node;
    } else {
        DirectoryCLL *head = current->child;
        DirectoryCLL *tail = head->prev;
        tail->next = node;
        node->prev = tail;
        node->next = head;
        head->prev = node;
    }
    node->parent = current;
}

void removeChildNode(DirectoryCLL *node) {
    DirectoryCLL *parent = node->parent;
    if (!parent) return;
    DirectoryCLL *head = parent->child;
    if (!head) return;
    if (node->next == node) {
        parent->child = NULL;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        if (head == node) parent->child = node->next;
    }
    node->next = node->prev = node->parent = NULL;
}

char *blockPtr(int blockIndex) {
    if (blockIndex < 1 || blockIndex > NUM_BLOCKS) return NULL;
    return virtualDisk + (size_t)(blockIndex - 1) * BLOCK_SIZE;
}

void mkdirCmd(DirectoryCLL **current, char val[]) {
    if (strlen(val) == 0) { printf("mkdir: missing name\n"); return; }
    if (findChild(*current, val)) { printf("Name already exists in current directory.\n"); return; }
   if (!isValidDirName(val)) {
    printf("Invalid directory name: must start with a letter and contain only letters, digits, _ or -\n");
    return;
}

    DirectoryCLL *newDir = CreateDirectoryOrFile(val, 1);
    insertChild(*current, newDir);
    printf("Directory '%s' created inside '%s'.\n", val, (*current)->name);
}

void createCmd(DirectoryCLL **current, char val[]) {
    if (strlen(val) == 0) { printf("create: missing name\n"); return; }
    if (findChild(*current, val)) { printf("Name already exists in current directory.\n"); return; }
   if (!isValidFileName(val)) {
    printf("Invalid file name: must start with a letter and can contain letters, digits, _, -, or .\n");
    return;
}

    DirectoryCLL *newFile = CreateDirectoryOrFile(val, 0);
    insertChild(*current, newFile);
    printf("File '%s' created successfully inside '%s'.\n", val, (*current)->name);
}

void writeCmd(DirectoryCLL *current, char val[], char content[]) {
    if (!current) return;
    DirectoryCLL *file = findChild(current, val);
    if (!file || file->isDirectory) { 
        printf("File not found: %s\n", val); 
        return; 
    }

   
    int len = (int)strlen(content);
    if (len >= 2 && content[0] == '"' && content[len - 1] == '"') {
        memmove(content, content + 1, len - 2);
        content[len - 2] = '\0';
        len -= 2;
    }

    
    if (strlen(content) == 0) {
        printf("Error: No content provided for writing.\n");
        return;
    }

    
    for (int i = 0; i < file->blockCount; ++i)
        pushFreeBlock(file->blockPointers[i]);

    file->blockCount = 0;
    file->contentSize = 0;
    
    int written = 0;
    while (written < len && file->blockCount < MAX_BLOCKS_PER_FILE) {
        if (freeHead == NULL) {
            printf("Disk full. Could not write all data.\n");
            break;
        }
        int bidx = popFreeBlock();
        if (bidx == -1) {
            printf("Disk full.\n");
            break;
        }
        file->blockPointers[file->blockCount++] = bidx;
        int remain = len - written;
        int toCopy = (remain > BLOCK_SIZE) ? BLOCK_SIZE : remain;
        char *dest = blockPtr(bidx);
        memcpy(dest, content + written, toCopy);
        if (toCopy < BLOCK_SIZE)
            memset(dest + toCopy, 0, BLOCK_SIZE - toCopy);
        written += toCopy;
    }

    file->contentSize = written;
    printf("Data written successfully (size=%d bytes) to '%s'.\n", written, val);
}

void readCmd(DirectoryCLL *current, char val[]) {
    if (!current) return;
    DirectoryCLL *file = findChild(current, val);
    if (!file || file->isDirectory) { printf("File not found: %s\n", val); return; }
    if (file->blockCount == 0 || file->contentSize == 0) { printf("(empty)\n"); return; }
    int remaining = file->contentSize;
    for (int i = 0; i < file->blockCount && remaining > 0; ++i) {
        int bidx = file->blockPointers[i];
        char *src = blockPtr(bidx);
        int toPrint = (remaining > BLOCK_SIZE) ? BLOCK_SIZE : remaining;
        fwrite(src, 1, toPrint, stdout);
        remaining -= toPrint;
    }
    printf("\n");
}

void deleteCmd(DirectoryCLL **current, char val[]) {
    if (!current || !(*current)) return;
    DirectoryCLL *file = findChild(*current, val);
    if (!file || file->isDirectory) { printf("File not found: %s\n", val); return; }
    for (int i = 0; i < file->blockCount; ++i) pushFreeBlock(file->blockPointers[i]);
    removeChildNode(file);
    free(file);
    printf("File '%s' deleted successfully.\n", val);
}

void rmdirCmd(DirectoryCLL **current, char val[]) {
    if (!current || !(*current)) return;
    DirectoryCLL *dir = findChild(*current, val);
    if (!dir || !dir->isDirectory) { printf("Directory not found: %s\n", val); return; }
    if (dir->child != NULL) { printf("Directory not empty. Remove files first.\n"); return; }
    removeChildNode(dir);
    free(dir);
    printf("Directory '%s' removed successfully.\n", val);
}

void lsCmd(DirectoryCLL *current) {
    if (!current) return;
    if (current->child == NULL) { printf("(empty)\n"); return; }
    DirectoryCLL *head = current->child;
    DirectoryCLL *t = head;
    do {
        if (t->isDirectory) printf("%s/\n", t->name);
        else printf("%s\n", t->name);
        t = t->next;
    } while (t != head);
}

void cdCmd(DirectoryCLL **current, char val[]) {
    if (!current || !(*current)) return;
    if (strcmp(val, "..") == 0) {
        if ((*current)->parent != NULL) {
            *current = (*current)->parent;
            printf("Moved to %s\n", (*current)->name);
        } else {
            printf("Already at root.\n");
        }
        return;
    }
    DirectoryCLL *d = findChild(*current, val);
    if (!d || !d->isDirectory) { printf("Directory not found: %s\n", val); return; }
    *current = d;
    printf("Moved to %s\n", d->name);
}

void pwdCmd(DirectoryCLL *current) {
    if (!current) return;
    char path[LINE_LEN] = "";
    DirectoryCLL *t = current;
    while (t != NULL) {
        char temp[LINE_LEN];
        if (strcmp(t->name, "/") == 0) snprintf(temp, sizeof(temp), "/%s", path);
        else snprintf(temp, sizeof(temp), "/%s%s", t->name, path);
        strncpy(path, temp, sizeof(path)-1);
        path[sizeof(path)-1] = '\0';
        t = t->parent;
        if (t == t->parent) break;
    }
    if (strlen(path) == 0) strcpy(path, "/");
    printf("%s\n", path);
}

void dfCmd() {
    int total = NUM_BLOCKS;
    int freeb = freeCount;
    int used = total - freeb;
    double usage = (double)used / (double)total * 100.0;
    printf("Total Blocks: %d\nUsed Blocks: %d\nFree Blocks: %d\nDisk Usage: %.2f%%\n", total, used, freeb, usage);
}

void freeDirectoryTree(DirectoryCLL *dir) {
    if (!dir) return;

    DirectoryCLL *child = dir->child;
    if (child) {
        DirectoryCLL *start = child;
        do {
            DirectoryCLL *next = child->next;
            child->next = child->prev = child->parent = NULL;
            freeDirectoryTree(child);
            child = next;
        } while (child != start);
    }

    free(dir);
}

void freeFreeBlockList() {
    FreeBlockDLL *f = freeHead;
    while (f) {
        FreeBlockDLL *nx = f->next;
        free(f);
        f = nx;
    }
    freeHead = freeTail = NULL;
    freeCount = 0;
}

void freeVirtualDisk() {
    if (virtualDisk) {
        free(virtualDisk);
        virtualDisk = NULL;
    }
}



int main() {
    virtualDisk = malloc((size_t)NUM_BLOCKS * BLOCK_SIZE);
    if (!virtualDisk) { perror("virtualDisk malloc"); return 1; }
    initFreeList();
    DirectoryCLL *root = CreateDirectoryOrFile("/", 1);
    root->parent = NULL;
    DirectoryCLL *current = root;
    char line[LINE_LEN], cmd[64], arg1[128], arg2[1536];
    printf("Compact VFS - ready. Type 'exit' to quit.\n");
    while (1) {
        printf("%s > ", current->name);
        if (!fgets(line, sizeof(line), stdin)) break;
        line[strcspn(line, "\n")] = '\0';
        cmd[0]=arg1[0]=arg2[0]=0;
        sscanf(line, "%s %s %[^\n]", cmd, arg1, arg2);
        if (strcmp(cmd, "mkdir")==0) {
            mkdirCmd(&current, arg1);
        } else if (strcmp(cmd, "create")==0) {
            createCmd(&current, arg1);
        } 
        else if (strcmp(cmd, "write") == 0) {
            if (strlen(arg1) == 0) {
                printf("Usage: write <filename> <content>\n");
            } else {
                writeCmd(current, arg1, arg2);
            }
        }
        else if (strcmp(cmd, "read")==0) {
            readCmd(current, arg1);
        } else if (strcmp(cmd, "delete")==0) {
            deleteCmd(&current, arg1);
        } else if (strcmp(cmd, "rmdir")==0) {
            rmdirCmd(&current, arg1);
        } else if (strcmp(cmd, "ls")==0) {
            lsCmd(current);
        } else if (strcmp(cmd, "cd")==0) {
            cdCmd(&current, arg1);
        } else if (strcmp(cmd, "pwd")==0) {
            pwdCmd(current);
        } else if (strcmp(cmd, "df")==0) {
            dfCmd();
        } else if (strcmp(cmd, "exit")==0) {
            printf("Exiting. Cleaning up...\n");
            break;
        } else if (strlen(cmd)==0) {
            continue;
        } else {
            printf("Unknown command: %s\n", cmd);
        }
    }
   if (root) {
    freeDirectoryTree(root);
    root = NULL;
}
freeFreeBlockList();
freeVirtualDisk();
printf("Cleanup complete. Bye!\n");
    return 0;
}
