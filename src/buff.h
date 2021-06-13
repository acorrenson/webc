#ifndef BUFF_H
#define BUFF_H

struct buff_s {
  char *bytes;
  unsigned size;
  unsigned capacity;
};

typedef struct buff_s *Buff;

/**
 * @brief Allocate a new (empty) buffer
 *
 * @return Buff
 */
Buff new_buff();

/**
 * @brief Add a byte at the end of a buffer
 *
 */
void buff_addb(Buff, char);

/**
 * @brief Add n bytes at the end of a buffer
 *
 */
void buff_addn(Buff, const char *, unsigned);

/**
 * @brief Deallocate a buffer & nullify its underlying pointer
 *
 */
void del_buff(Buff *);

#endif