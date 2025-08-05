#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define FNV_PRIME_32 16777619u
#define FNV_OFFSET_BASIS_32 2166136261u
#define TABLE_SIZE 13
#define MAX_INPUT_SIZE 25

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

Bucket *create_roman_to_int_dict()
{
    Bucket *hash_table = initialize_hash_table();

    save(hash_table, "I", 1);
    save(hash_table, "V", 5);
    save(hash_table, "X", 10);
    save(hash_table, "L", 50);
    save(hash_table, "C", 100);
    save(hash_table, "D", 500);
    save(hash_table, "M", 1000);

    return hash_table;
}

int validate_sequence(Bucket *current, Bucket *next)
{
    // edge case: IIIII, VVVVVV, só pode no max 3 seguidos

    if (current == NULL || next == NULL)
    {

        printf("You inserted an invalid roman number. \n");
        return 0;
    }

    if (current->value < next->value)
    {

        if (strcmp(current->key, "I") == 0)
        {
            if (strcmp(next->key, "V") == 0 || strcmp(next->key, "X") == 0)
            {
                return 1;
            }
        }
        else if (strcmp(current->key, "X") == 0)
        {
            if (strcmp(next->key, "L") == 0 || strcmp(next->key, "C") == 0)
            {
                return 1;
            }
        }
        else if (strcmp(current->key, "C") == 0)
        {
            if (strcmp(next->key, "D") == 0 || strcmp(next->key, "M") == 0)
            {
                return 1;
            }
        }

        return 0;
    }

    return 1;
}

int romanToInt(char *s, Bucket *dict)
{
    char *aux = s;
    unsigned int result = 0;
    while (*aux != '\0')
    {
        char current_key[2] = {*aux, '\0'};
        Bucket *current_bucket = get(dict, current_key);
        char *next = aux + 1;

        Bucket *next_bucket = NULL;
        if (*next != '\0')
        {
            char next_key[2] = {*next, '\0'};
            next_bucket = get(dict, next_key);
        }

        int is_valid_sequence = current_bucket != NULL && next_bucket == NULL ? 1 : validate_sequence(current_bucket, next_bucket);

        if (!is_valid_sequence)
        {
            return -1;
        }

        if (next_bucket != NULL && current_bucket->value < next_bucket->value)
        {
            result = result + (next_bucket->value - current_bucket->value);
            aux = aux + 2;
        }
        else
        {
            result = result + current_bucket->value;
            aux++;
        }
    }

    return result;
}

int main()
{
    Bucket *roman_to_int_dict = create_roman_to_int_dict();

    char roman_number_input[MAX_INPUT_SIZE];

    printf("Input your roman number: \n");
    fgets(roman_number_input, MAX_INPUT_SIZE, stdin);
    roman_number_input[strcspn(roman_number_input, "\n")] = '\0';

    char *aux = roman_number_input;

    unsigned int result = romanToInt(aux, roman_to_int_dict);

    printf("Result: %d \n", result);

    destroy_hash_table(roman_to_int_dict);
    return 0;
}