#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define FNV_PRIME_32 16777619u
#define FNV_OFFSET_BASIS_32 2166136261u
#define TABLE_SIZE 13

typedef struct Bucket
{
    struct Bucket *next;
    char *key;
    int value;

} Bucket;

// https://softwareengineering.stackexchange.com/questions/49550/which-hashing-algorithm-is-best-for-uniqueness-and-speed
static uint32_t fnv1a_32(const void *data, size_t len)
{
    uint32_t hash = FNV_OFFSET_BASIS_32;
    const unsigned char *bytes = (const unsigned char *)data;

    for (size_t i = 0; i < len; i++)
    {
        hash ^= bytes[i];
        hash *= FNV_PRIME_32;
    }
    printf("Hash: %u (0x%X)\n", hash, hash);

    return hash;
}

static int get_index(const char *key)
{

    uint32_t hash = fnv1a_32(key, strlen(key));
    return hash % TABLE_SIZE;
}

Bucket *get(Bucket *hash_table, const char *key)
{
    int index = get_index(key);
    Bucket *bucket = &hash_table[index];

    while (bucket != NULL)
    {
        if (bucket->key && strcmp(bucket->key, key) == 0)
            return bucket;
        bucket = bucket->next;
    }

    printf("Not able to find bucket! \n");
    return NULL;
}

void save(Bucket *hash_table, char *key, int value)
{
    int index = get_index(key);
    Bucket *current = &hash_table[index];

    if (current->key == NULL)
    {
        current->value = value;
        current->key = strdup(key);
        current->next = NULL;
        return;
    }

    while (current->next != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            printf("There is already an item with this key. Updating value... \n");
            current->value = value;
            return;
        }
        current = current->next;
    }

    if (strcmp(current->key, key) == 0)
    {
        printf("There is already an item with this key. Updating value... \n");
        current->value = value;
        return;
    }

    Bucket *newBucket = malloc(sizeof(Bucket));

    if (!newBucket)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    newBucket->value = value;
    char *key_copy = strdup(key);
    if (!key_copy)
    {
        fprintf(stderr, "Memory allocation failed for key\n");
        free(newBucket);
        exit(EXIT_FAILURE);
    }
    newBucket->key = key_copy;
    newBucket->key = strdup(key);
    newBucket->next = NULL;
    current->next = newBucket;
}

Bucket *initialize_hash_table()
{
    Bucket *hash_table = malloc(TABLE_SIZE * sizeof(Bucket));

    if (hash_table == NULL)
    {
        printf("Not able to initialize hash table. \n");
        return NULL;
    }

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i].next = NULL;
        hash_table[i].key = NULL;
    }

    return hash_table;
}

void destroy_hash_table(Bucket *hash_table)
{
    printf("Destroying hash table. \n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Bucket *current = hash_table[i].next;

        while (current != NULL)
        {
            Bucket *next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
    }

    free(hash_table);
    hash_table = NULL;
}

int main()
{
    Bucket *hash_table = initialize_hash_table();

    int index = get_index("test");
    int index2 = get_index("test4");
    printf("%d", index);
    printf("%d", index2);

    save(hash_table, "I", 1);
    save(hash_table, "I", 10);
    save(hash_table, "I", 15);
    save(hash_table, "V", 5);

    // keys with same index to test
    save(hash_table, "test", 101);
    save(hash_table, "test4", 104);
    Bucket *I = get(hash_table, "I");
    Bucket *V = get(hash_table, "V");
    Bucket *test = get(hash_table, "test");
    Bucket *test4 = get(hash_table, "test4");

    printf("I: %d \n", I->value);
    printf("V: %d \n", V->value);
    printf("test: %d \n", test->value);
    printf("test4: %d \n", test4->value);

    destroy_hash_table(hash_table);
    return 0;
}