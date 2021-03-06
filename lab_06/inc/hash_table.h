#ifndef hash_table_h
#define hash_table_h

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "element.h"
#include "list.h"

#define MEMORY_ERROR 1
#define LENGTH_ERROR 2
#define OK 0

typedef struct
{
    node_t *head;
    size_t count;
} list_t;

typedef struct hash_table hash_table_t;

typedef size_t (* hash_func_type_t)(elem_t *elem, hash_table_t *table);

struct hash_table {
    list_t *data;
    size_t size;
    double mul_const;
    hash_func_type_t hash_func_type;
    double av_conflicts;
};

hash_table_t * create_hash_table(size_t max_count, hash_func_type_t hash_func);

void read_hash_table(char *filename, hash_table_t *table, void *(*reader)(FILE *f), stat_values_t *stat);

void print_hash_table(FILE *f, hash_table_t *table, void print_elem(FILE *f, const void *elem));

void free_hash_table(hash_table_t **table, void (* free_elem)(void *val));

void delete_hash_table_elem(hash_table_t *table, elem_t *elem, void (* free_elem)(void *val), int (* comp)(const void *lhs, const void *rhs), stat_values_t *stat);

void insert_hash_table_elem(hash_table_t *table, elem_t *value);

hash_table_t * restruct(hash_table_t *table, hash_func_type_t hash_func, size_t new_size);

hash_table_t * reduce_conflicts_by_restruction_ht(hash_table_t *table, double av_max);

size_t hash_func_sum(elem_t *elem, hash_table_t *table);

size_t hash_func_mul(elem_t *elem, hash_table_t *table);

size_t hash_func_xor(elem_t *elem, hash_table_t *table);
#endif

