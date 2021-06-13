#include "buff.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Buff new_buff() {
  Buff b = malloc(sizeof(struct buff_s));
  b->bytes = malloc(512);
  b->size = 0;
  b->capacity = 512;
  return b;
}

void resize(Buff b) {
  unsigned new_capacity = 2 * b->capacity;
  b->bytes = realloc(b->bytes, new_capacity);
  b->capacity = new_capacity;
}

void buff_addb(Buff b, char c) {
  if (b->size >= b->capacity)
    resize(b);
  b->bytes[b->size] = c;
  b->size++;
}

void buff_addn(Buff b, const char *s, unsigned n) {
  if (b->size + n >= b->capacity)
    resize(b);
  memcpy(b->bytes + b->size, s, n);
  b->size++;
}

void del_buff(Buff *b) {
  free((*b)->bytes);
  free(*b);
  *b = NULL;
}