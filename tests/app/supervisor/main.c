// Want to keep the call sequence history for 17 function calls
#define FFF_CALL_HISTORY_LEN 17

#include <zephyr/fff.h>

/*
 * Can only be declared once within the scope
 * of the entire test binary build.
 */
DEFINE_FFF_GLOBALS;
