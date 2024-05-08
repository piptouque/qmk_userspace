/* Bepo layout for ergodox EZ by Nicolas CARPi (deltablot.com) */
#include QMK_KEYBOARD_H
#include "keymap_bepo.h"
#include "keymap_french.h"

// Layers
// Have to be available to space cadet / mod-tap
#define L_BASE  0 // default layer
#define L_BEPO  1
#define L_SYMB  2
#define L_NAV_L 3  // function / navigation / mouse layer -- left hand only
#define L_NAV_R 4  // function / navigation / mouse layer -- right hand only
#define L_MNTC  5


/// Taken from: https://docs.qmk.fm/#/feature_tap_dance?id=example-6
// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

typedef struct {
    uint16_t t_key;
    uint16_t dt_key;
} dt_user_data_t;

typedef struct {
    uint16_t key;
    uint16_t mod;
} th_user_data_t;

enum {
    SPC_ENT,
    BSPC_DEL
    // add any other tap dance keys to this enum
};

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(tap_dance_state_t *state, void *user_data);
void ql_reset(tap_dance_state_t *state, void *user_data);

#ifdef SWAP_HANDS_ENABLE
__attribute__((weak))
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    /* Left hand, matrix positions */
    {{0,  6}, {1,  6}, {2,  6}, {3,  6}, {4,  6}, {5,  6}, {6, 6}},
    {{0,  7}, {1,  7}, {2,  7}, {3,  7}, {4,  7}, {5,  7}, {6,  7}},
    {{0,  8}, {1,  8}, {2,  8}, {3,  8}, {4,  8}, {5,  8}, {6,  8}},
    {{0,  9}, {1,  9}, {2,  9}, {3,  9}, {4,  9}, {5,  9}, {6,  9}},
    {{0, 10}, {1, 10}, {2, 10}, {3, 10}, {4, 10}, {5, 10},  {6, 10}},
    {{0, 11}, {1, 11}, {2, 11}, {3, 11}, {4, 11}, {5, 11},  {6, 11}},

    /* Right hand, matrix positions */
    {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5}},
    {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}},
    {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}},
    {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}},
    {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}},
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}}
};
#endif



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: default layer
 *
 * df is for temporary stuff and mo is for toggle (momentary)
 */
[L_BASE] = LAYOUT_ergodox(

/* Left hand */
KC_NO,    KC_NO,    KC_NO,    KC_TRNS,    KC_TRNS,    KC_NO,    KC_NO,
KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,
MO(L_NAV_L),    KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,
KC_TAB,    KC_NO,  KC_NO,   KC_NO,  KC_NO, KC_NO,    KC_NO,
KC_LGUI,    KC_LCTL,   KC_LALT,  KC_LSFT, SH_T(KC_ESC),
                            MO(L_SYMB),  OSL(L_MNTC),
                                TO(L_BEPO),
                        TD(SPC_ENT),    TD(BSPC_DEL),  KC_RALT,

/* Right hand */
        KC_NO,    KC_NO,    KC_TRNS,    KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,    KC_NO,  KC_NO,  KC_NO,    KC_NO,   KC_NO,   KC_NO,
            KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,   MO(L_NAV_R),
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_TAB,
                SH_T(KC_ESC),  KC_RSFT,  KC_LALT,  KC_RCTL,    KC_RGUI,
OSL(L_MNTC),  MO(L_SYMB),
KC_NO,
KC_RALT,  TD(BSPC_DEL),  TD(SPC_ENT)),
[L_BEPO] = LAYOUT_ergodox(

/* Left hand */
BP_DLR,  BP_DQUO,  BP_LDAQ,  BP_RDAQ,  BP_LPRN,  BP_RPRN,  BP_PERC,
KC_TRNS, BP_B,   BP_EACU,    BP_P,   BP_O,   BP_EGRV, BP_W,
KC_TRNS,   BP_A,   BP_U,   BP_I,   BP_E,   BP_COMM,
KC_TRNS,    BP_AGRV,  BP_Y,   BP_X,   BP_DOT,   BP_K,   BP_CCED,
KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,
                            KC_TRNS,  KC_TRNS,
                                KC_TRNS,
                        KC_TRNS,   KC_TRNS,  KC_TRNS,

/* Right hand */
                BP_ECIR, BP_AT,    BP_PLUS, BP_MINS, BP_SLSH,  BP_ASTR, BP_EQL,
        BP_Z,  BP_DCIR,  BP_V,   BP_D,   BP_L,   BP_J,   KC_TRNS,
            BP_C,   BP_T,   BP_S,   BP_R,   BP_N,   KC_TRNS,
        BP_M, BP_QUOT,  BP_Q,   BP_G,   BP_H,   BP_F,   KC_TRNS,
                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
KC_TRNS, KC_TRNS,
KC_TRNS,
KC_TRNS, KC_TRNS,  KC_TRNS),

[L_SYMB] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,KC_TRNS,  KC_F10,  KC_F11,  KC_F12,  KC_TRNS,  KC_TRNS,
       KC_TRNS,KC_TRNS,KC_F7,  KC_F8,KC_F9,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_F4, KC_F5,KC_F6,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_F1,KC_F2,KC_F3,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,   FR_7,   FR_8,    FR_9,    KC_TRNS, KC_TRNS,
                KC_TRNS, FR_4,   FR_5,    FR_6,    KC_TRNS, KC_TRNS,
       KC_TRNS, FR_0, FR_1,   FR_2,    FR_3,    KC_TRNS, KC_TRNS,
                         KC_TRNS,KC_TRNS, KC_TRNS,    KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
[L_NAV_L] = LAYOUT_ergodox(
/* Left hand */
KC_NO,    KC_NO,    KC_MS_BTN3,    KC_NO,    KC_NO,    KC_MS_BTN4,    KC_NO,
KC_NO,    KC_NO, KC_MS_BTN1, KC_MS_WH_UP, KC_MS_WH_DOWN, KC_MS_BTN2,  KC_TRNS,
KC_NO,    KC_NO, KC_MS_LEFT, KC_MS_UP, KC_MS_DOWN,  KC_MS_RIGHT,
KC_TRNS,    KC_NO,  KC_CUT,   KC_COPY,  KC_PASTE, KC_UNDO,    KC_TRNS,
KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,
                            KC_TRNS,  KC_TRNS,
                                KC_TRNS,
                        KC_TRNS,    KC_TRNS,  KC_TRNS,

/* Right hand */
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,   KC_NO,   KC_NO,
            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,   KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,
KC_TRNS,  KC_TRNS,
KC_TRNS,
KC_TRNS,  KC_TRNS,  KC_TRNS),

[L_NAV_R] = LAYOUT_ergodox(
/* Left hand */
KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS,    KC_TRNS,
KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,
                            KC_TRNS,  KC_TRNS,
                                KC_TRNS,
                        KC_TRNS,    KC_TRNS,  KC_TRNS,

/* Right hand */
        KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_TRNS,    KC_HOME,  KC_PGDN,  KC_PGUP,    KC_END,   KC_NO,   KC_NO,
            KC_LEFT,  KC_DOWN,  KC_UP,  KC_RIGHT, KC_NO,   KC_NO,
        KC_TRNS,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_TRNS,
                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,
KC_TRNS,  KC_TRNS,
KC_TRNS,
KC_TRNS,  KC_TRNS,  KC_TRNS),

[L_MNTC] = LAYOUT_ergodox(

/* Left hand */
KC_NO,    RGB_TOG,    RGB_MOD,    RGB_HUI,    QK_RBT,    QK_MAKE,    QK_BOOT,
KC_NO,    NK_TOGG, KC_NO, KC_NO, KC_NO, QK_RBT,  KC_TRNS,
KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO,  EH_LEFT,
KC_TRNS,    KC_NO,  KC_NO,   KC_NO,  KC_NO, KC_NO,    KC_TRNS,
KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,
                            KC_TRNS,  KC_TRNS,
                                KC_TRNS,
                        KC_TRNS,    KC_TRNS,  KC_TRNS,

/* Right hand */
        QK_BOOT,    DB_TOGG,    KC_TRNS,    BL_BRTG,   BL_STEP,   BL_TOGG,   KC_NO,
        KC_TRNS,    QK_RBT,  KC_NO,  KC_NO,    KC_NO,   KC_NO,   KC_NO,
            EH_LEFT,  KC_NO,  KC_NO,  KC_NO, KC_NO,   KC_NO,
        KC_TRNS,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_TRNS,
                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,
KC_TRNS,  KC_TRNS,
KC_TRNS,
KC_TRNS,  KC_TRNS,  KC_TRNS),
};

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case BP_A:
        case BP_B:
        case BP_C:
        case BP_D:
        case BP_E:
        case BP_F:
        case BP_G:
        case BP_H:
        case BP_I:
        case BP_J:
        case BP_K:
        case BP_L:
        case BP_M:
        case BP_N:
        case BP_O:
        case BP_P:
        case BP_Q:
        case BP_R:
        case BP_S:
        case BP_T:
        case BP_U:
        case BP_V:
        case BP_W:
        case BP_X:
        case BP_Y:
        case BP_Z:
        case BP_CCED:
        case BP_EGRV:
        case BP_EACU:
        case BP_AGRV:
        // TODO: add bépo keys.
        // or depend on position on the board?
        //case KC_A ... KC_Z:
        //case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;
        // Keycodes that continue Caps Word, without shifting.
        case BP_1 ... BP_0:
        case BP_UNDS:
            return true;
        default:
            return false;  // Deactivate Caps Word.
    }
}

// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        return state->pressed ? TD_SINGLE_HOLD : TD_SINGLE_TAP;
    } else if (state->count == 2) {
        return state->pressed ? TD_DOUBLE_HOLD : TD_DOUBLE_TAP;
    }
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key

static td_tap_t td_tap_state = { .is_press_action = true, .state = TD_NONE } ;


void dt_finished(tap_dance_state_t *state, void *user_data) {
    dt_user_data_t *data = (dt_user_data_t *)user_data;
    td_tap_state.state = cur_dance(state);
    switch (td_tap_state.state) {
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:
            register_code16(data->t_key);
            break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_HOLD:
            register_code16(data->dt_key);
            break;
        default:
            break;
    }
}

void dt_reset(tap_dance_state_t *state, void *user_data) {
    dt_user_data_t *data = (dt_user_data_t *)user_data;
    switch (td_tap_state.state) {
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:
            unregister_code16(data->t_key);
            break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_HOLD:
            unregister_code16(data->dt_key);
            break;
        default:
            break;
    }
}

#define ACTION_TAP_DANCE_DOUBLE_TAP(t_key_, dt_key_) \
    { .fn = {NULL, dt_finished, dt_reset}, .user_data = (void *)&((dt_user_data_t){ .t_key = t_key_, .dt_key = dt_key_}), }


// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [SPC_ENT]   = ACTION_TAP_DANCE_DOUBLE_TAP(KC_SPC, KC_ENT),
    [BSPC_DEL]  = ACTION_TAP_DANCE_DOUBLE_TAP(KC_BSPC, KC_DEL)
};
