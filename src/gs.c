#include "utils.h"
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int umax(unsigned int a, unsigned int b) {
  return a < b ? b : a;
}

void gs_init(gs_t *gs) {
  assert(gs != NULL);
  gs->str = malloc(1);
  gs->str[0] = '\0';
  gs->len = 1;
  gs->cap = 1;
}

void gs_cleanup(gs_t *gs) {
  assert(gs_check(gs) == 0);
  free(gs->str);
}

void gs_append_f(gs_t *gs, const char *format, ...) {
  assert(gs_check(gs) == 0);
  va_list ap_1, ap_2;
  va_start(ap_1, format);
  va_copy(ap_2, ap_1);
  unsigned int available_len = gs->cap - gs->len;
  unsigned int requested_len =
      vsnprintf(&gs->str[gs->len - 1], available_len, format, ap_1);
  va_end(ap_1);
  if (requested_len >= available_len) {
    unsigned int len_wanted = gs->len + requested_len;
    if (len_wanted > gs->cap) {
      unsigned int next_step_cap =
          ((float)gs->cap + WEBC_GS_GROWTH_ADD) * WEBC_GS_GROWTH_FACTOR;
      unsigned int new_cap_wanted = umax(len_wanted, next_step_cap);
      char *new_str = realloc(gs->str, new_cap_wanted);
      assert(new_str != NULL);
      gs->str = new_str;
      gs->cap = new_cap_wanted;
    }
    vsprintf(&gs->str[gs->len - 1], format, ap_2);
  }
  va_end(ap_2);
  gs->len += requested_len;
}

int gs_check(const gs_t *gs) {
  if (gs == NULL || gs->str == NULL || gs->len > gs->cap || gs->cap == 0) {
    return -1;
  }
  return 0;
}
