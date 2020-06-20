#include "sign_transaction.h"
#include "os.h"
#include "ux.h"
#include "utils.h"
#include "main.h"

//////////////////////////////////////////////////////////////////////

UX_STEP_NOCB(
    sign_flow_intro_step,
    bnnn_paging,
    {
        .title = "Confirm",
        .text = ui_context.line1,
    });

UX_STEP_NOCB(
    sign_flow_receiver_step,
    bnnn_paging,
    {
        .title = "To",
        .text = ui_context.line2,
    });

UX_STEP_NOCB(
    sign_flow_signer_step,
    bnnn_paging,
    {
        .title = "From",
        .text = ui_context.line3,
    });

UX_STEP_VALID(
    sign_flow_approve_step,
    pb,
    send_response(set_result_sign(), true),
    {
        &C_icon_validate_14,
        "Approve",
    });

UX_STEP_VALID(
    sign_flow_reject_step,
    pb,
    send_response(0, false),
    {
        &C_icon_crossmark,
        "Reject",
    });

UX_FLOW(
    ux_display_sign_flow,
    &sign_flow_intro_step,
    &sign_flow_receiver_step,
    &sign_flow_signer_step,
    &sign_flow_approve_step,
    &sign_flow_reject_step);

void sign_ux_flow_init() {
    ux_flow_init(0, ux_display_sign_flow, NULL);
}

void handle_sign_transaction(uint8_t p1, uint8_t p2, uint8_t *input_buffer, uint16_t input_length, volatile unsigned int *flags, volatile unsigned int *tx) {
    UNUSED(input_length);
    UNUSED(p2);

    // TODO: Should clear context on first chunk?
    // init_context();

    // TODO: Move handling command here from main.c
    sign_ux_flow_init();
    *flags |= IO_ASYNCH_REPLY;
}
