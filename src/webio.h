#ifndef WEBIO_H
#define WEBIO_H

#include "buff.h"

typedef struct Webio_s *Webio;

/**
 * @brief Allocate a new WebIO object
 *
 */
Webio new_webio();

/**
 * @brief Open a WebIO interface
 *
 */
void webio_open(Webio);

/**
 * @brief Write bytes through a WebIO interface (push)
 *
 * @return unsigned Number of effective bytes written
 */
unsigned webio_write(Webio, const char *);

/**
 * @brief Read bytes through a WebIO interface (pull)
 *
 * @return unsigned Number of effective bytes read
 */
unsigned webio_read(Webio, Buff, unsigned);

/**
 * @brief Close a WebIO interface
 *
 */
void webio_close(Webio);

/**
 * @brief Deallocate a WebIO object and nullify its underlying pointer
 *
 */
void del_webio(Webio *);

#endif