
// MinUnit (http://www.jera.com/techinfo/jtns/jtn002.html#Source_Code)
#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                               if (message) return message; } while (0)
extern int tests_run;

#include <stdio.h>
#include <string.h>

#include "parse_transaction.h"
#include "constants.h"
#include "context.h"

// Temporary area to sore stuff and reuse the same memory
tmpContext_t tmp_ctx;
uiContext_t ui_context;

int tests_run = 0;

static int parse_hex(char *output_buffer, size_t output_length, const char *hex_str) {
    for (int i = 0; i < output_length; i++) {
        if (hex_str[i * 2] == 0) {
            return i;
        }
        if (hex_str[i * 2 + 1] == 0) {
            return -1;
        }
        sscanf(&hex_str[i * 2], "%2hhx", &output_buffer[i]);
    }
    return -1;
}

#define PARSE_HEX(output_array, hex_str) parse_hex(output_array, sizeof(output_array) / sizeof(output_array[0]), hex_str)

static char *test_parse_transfer_1()
{
    tmp_ctx.signing_context.buffer_used = PARSE_HEX(tmp_ctx.signing_context.buffer,
        "18000000746573742d636f6e6e6563742d6c65646765722e746573740072068e029a9809c7f2da79c8a274743ff5f7edce24d648bd13e97f7093a03132040000000000000002000000766750dc6e47ddccb2421f27dec206d5ea4694422a1c2fc35ca8c2e3638a02aacf4b0100000003000040bd8b5b936b6c00000000000000");
    int active_flow = parse_transaction(); 
    mu_assert("parses action", strcmp(ui_context.line1, "transfer") == 0);
    mu_assert("parses receiver", strcmp(ui_context.line2, "vg") == 0);
    mu_assert("parses signer", strcmp(ui_context.line3, "test-connect-ledger.test") == 0);
    mu_assert("parses amount", strcmp(ui_context.amount, "0.002") == 0);
    mu_assert("line 4 empty", strcmp(ui_context.line4, "") == 0);
    mu_assert("line 5 empty", strcmp(ui_context.line5, "") == 0);
    mu_assert("uses transfer flow", active_flow == SIGN_FLOW_TRANSFER);
    return 0;
}

static char *test_parse_transfer_2()
{
    tmp_ctx.signing_context.buffer_used = PARSE_HEX(tmp_ctx.signing_context.buffer,
        "17000000746573742d70722d3531372d6c65646765722e746573740072068e029a9809c7f2da79c8a274743ff5f7edce24d648bd13e97f7093a0313201000000000000000200000076674241eecd753a851429e4b415eb139dda037f705960200aa7a946bf24469b646e0100000003000000a1edccce1bc2d3000000000000");
    int active_flow = parse_transaction(); 
    mu_assert("parses action", strcmp(ui_context.line1, "transfer") == 0);
    mu_assert("parses receiver", strcmp(ui_context.line2, "vg") == 0);
    mu_assert("parses signer", strcmp(ui_context.line3, "test-pr-517-ledger.test") == 0);
    mu_assert("parses amount", strcmp(ui_context.amount, "1") == 0);
    mu_assert("line 4 empty", strcmp(ui_context.line4, "") == 0);
    mu_assert("line 5 empty", strcmp(ui_context.line5, "") == 0);
    mu_assert("uses transfer flow", active_flow == SIGN_FLOW_TRANSFER);
    return 0;
}

static char *all_tests()
{
    mu_run_test(test_parse_transfer_1);
    mu_run_test(test_parse_transfer_2);
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
