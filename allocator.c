#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define USE_ALLOCATOR
#ifndef GLOBAL_STORAGE_SIZE
  #define GLOBAL_STORAGE_SIZE (1024 * 1024)
#endif

typedef struct Arena {
  unsigned char * buffer;
  size_t buffer_length;
  size_t offset;
} Arena;

Arena global_storage;

int init_storage(size_t size){
  global_storage.offset = 0;
  global_storage.buffer = malloc(size);
  if(global_storage.buffer == NULL){
    printf("Failed to allocate memory for the arena");
    return 1;
  }
  global_storage.buffer_length = size;
  return 0;
}

void reset_storage(){
  memset(global_storage.buffer, 0, global_storage.offset);
  global_storage.offset = 0;
}

void free_storage(){
  free(global_storage.buffer);
}

void * alloc(size_t size){
  assert(global_storage.offset + size <= global_storage.buffer_length);
  void * ptr = &global_storage.buffer[global_storage.offset];
  global_storage.offset += size;
  return ptr;
}

void __attribute__ ((constructor)) start_allocator(){
  init_storage(GLOBAL_STORAGE_SIZE);
}

void __attribute__ ((destructor)) free_allocator(){
  free_storage();
}


