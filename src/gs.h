#ifndef WEBC_GS_HEADER
#define WEBC_GS_HEADER

struct gs_t {
  unsigned int len; /* Including the null terminator. */
  unsigned int cap;
  char *str;
};

/**
 * @brief Growable strings
 *
 */
typedef struct gs_t gs_t;

/**
 * @brief Initializes the given uninitialized growable string to an empty
 * string.
 *
 */
void gs_init(gs_t *gs);

/**
 * @brief Cleans up the given growable string, leaving garbage values.
 *
 * @param gs
 */
void gs_cleanup(gs_t *gs);

/**
 * @brief Appends the printf-formatted arguments to the given growable string.
 *
 * @param gs
 * @param format
 * @param ...
 */
void gs_append_f(gs_t *gs, const char *format, ...);

/* Growable string use example:
 *   gs_t gs;
 *   gs_init(&gs);
 *   gs_append_f(&gs,
 *     "Roses are %s\nViolets are %s\n"
 *     "We program in %c\nAnd so should %s\n",
 *     "red", "blue", 'C', "you");
 *   fputs(gs.str, stdout);
 *   gs_cleanup(&gs);
 * To really avoid use-after-free:
 *   gs = (gs_t){0};
 * Check:
 *   assert(gs_check(&gs) == 0); */

/**
 * @brief Checks the given growable string for memory corruptions,
 * returns -1 if an inconsistency is detected,
 * returns 0 if it seems ok.
 *
 * @param gs
 * @return int
 */
int gs_check(const gs_t *gs);

#ifndef WEBC_GS_GROWTH_ADD
/** @brief Fine-tuned constant (1) used ind append_f */
#define WEBC_GS_GROWTH_ADD (2.3f)
#endif
#ifndef WEBC_GS_GROWTH_FACTOR
/** @brief Fine-tuned constant (2) used ind append_f */
#define WEBC_GS_GROWTH_FACTOR (1.6f)
#endif

#endif /* WEBC_GS_HEADER */
