
// MinUnit (http://www.jera.com/techinfo/jtns/jtn002.html#Source_Code)
#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                               if (message) return message; } while (0)
extern int tests_run;

#include <stdio.h>

#include "parse_transaction.h"
#include "constants.h"
#include "context.h"

// Temporary area to sore stuff and reuse the same memory
tmpContext_t tmp_ctx;
uiContext_t ui_context;

int tests_run = 0;

static char *test_parse_transaction()
{
    // TODO: setup
    int active_flow = parse_transaction(); 
    mu_assert("uses generic flow", active_flow == SIGN_FLOW_GENERIC);
    return 0;
}

static char *all_tests()
{
    mu_run_test(test_parse_transaction);
    return 0;
}

int main(int argc, char **argv)
{
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
