#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#ifndef USE_ALLOCATOR
  #include "allocator.c"
#endif

typedef struct IntList {
  size_t capacity;
  size_t length;
  int * buffer;
} IntList;

IntList * create_ilist(size_t capacity){
  IntList * l = alloc(sizeof(IntList));
  l->capacity = capacity;
  l->length = 0;
  l->buffer = alloc(sizeof(int) * capacity);
  return l;
}

int ilist_get(IntList * l, size_t index){
  assert(index < l->length && index >= 0);
  return l->buffer[index];
}

void ilist_add(IntList * l, int num){
  assert(l->length < l->capacity);
  l->buffer[l->length] = num;
  l->length++;
}

void ilist_set(IntList * l, int num, size_t index){
  assert(index < l->length && index >= 0);
  l->buffer[index] = num;
}

void ilist_remove(IntList * l, size_t index){
  assert(index < l->length && index >= 0);
  int len = l->length - 1 - index;
  if(len > 0) {
    memcpy(&l->buffer[index], &l->buffer[index + 1], len * sizeof(int));
  }
  l->length--;
}

IntList * ilist_clone(IntList * l){
  IntList * c = alloc(sizeof(IntList));
  memcpy(c, l, sizeof(IntList));
  c->buffer = alloc(sizeof(int) * l->capacity);
  memcpy(c->buffer, l->buffer, sizeof(int) * l->capacity);
  return c;
}

void ilist_print(IntList * l){
  printf("[");
  for(int i=0; i < l->length; i++){
    if(i > 0) printf(", ");
    printf("%d", l->buffer[i]);
  }
  printf("]\n");
}
