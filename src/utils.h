
#ifndef WEBC_UTILS_HEADER
#define WEBC_UTILS_HEADER

/* Growable string. */
struct gs_t
{
	unsigned int len; /* Including the null terminator. */
	unsigned int cap;
	char* str;
};
typedef struct gs_t gs_t;

/* Initializes the given uninitialized growable string to an empty string. */
void gs_init(gs_t* gs);

/* Cleans up the given growable string, leaving garbage values. */
void gs_cleanup(gs_t* gs);

/* Appends the printf-formatted arguments to the given growable string. */
void gs_append_f(gs_t* gs, const char* format, ...);

/* Growable string use example:
 *   gs_t gs;
 *   gs_init(&gs);
 *   gs_append_f(&gs,
 *     "Roses are %s\nViolets are %s\n"
 *     "We program in %c\nAnd so should %s\n",
 *     "red", "blue", 'C', "you");
 *   fputs(stdout, gs.str);
 *   gs_cleanup(&gs);
 * To really avoid use-after-free:
 *   gs = (gs_t){0};
 * Check:
 *   assert(gs_check(&gs) == 0); */

/* Checks the given growable string for memory corruptions,
 * returns -1 if an inconsistency is detected,
 * returns 0 if it seems ok. */
int gs_check(const gs_t* gs);

#ifndef WEBC_GS_GROWTH_ADD
/* See the gs_append_f implementation. */
#define WEBC_GS_GROWTH_ADD (2.3f)
#endif
#ifndef WEBC_GS_GROWTH_FACTOR
/* See the gs_append_f implementation. */
#define WEBC_GS_GROWTH_FACTOR (1.6f)
#endif

#endif /* WEBC_UTILS_HEADER */
