#include QMK_KEYBOARD_H

enum sofle_layers {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
    _MOUSE,
};

enum custom_keycodes {
    KC_PRVWD = SAFE_RANGE,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND,
    KC_DLINE,
    KC_MOCK,
};

static bool mock_case = false;
static bool mock_last_shifted = false;

// Setting a specific layer with TO, to make a layer "stick", and to allow to
// return back to the base layer, like Miryoku does.
#define TOBASE DF(_BASE)
#define TOLOWR DF(_LOWER)
#define TORAIS DF(_RAISE)
#define TOADJU DF(_ADJUST)
#define TOMOUS DF(_MOUSE)


// One shot modifiers.
#define OSMC   OSM(MOD_LCTL)
#define OSMS   OSM(MOD_LSFT)
#define OSMA   OSM(MOD_LALT)
#define OSMG   OSM(MOD_LGUI)
#define OSMR   OSM(MOD_RSFT)
#define OSMAG  OSM(MOD_RALT)


// Some shortcuts for modified function keys or numbers, which are nice to have
// here in the Sofle, but not essential, so I won't have them on the Planck.
#define CT_F1  LCTL(KC_F1)
#define CT_F2  LCTL(KC_F2)
#define CT_F3  LCTL(KC_F3)
#define CT_F4  LCTL(KC_F4)
#define CT_F5  LCTL(KC_F5)
#define CT_F6  LCTL(KC_F6)
#define CT_F7  LCTL(KC_F7)
#define CT_F8  LCTL(KC_F8)
#define CT_F9  LCTL(KC_F9)
#define CT_F10 LCTL(KC_F10)
#define CT_F11 LCTL(KC_F11)
#define CT_F12 LCTL(KC_F12)

#define OS_1  LGUI(KC_1)
#define OS_2  LGUI(KC_2)
#define OS_3  LGUI(KC_3)
#define OS_4  LGUI(KC_4)
#define OS_5  LGUI(KC_5)
#define OS_6  LGUI(KC_6)
#define OS_7  LGUI(KC_7)
#define OS_8  LGUI(KC_8)
#define OS_9  LGUI(KC_9)
#define OS_0  LGUI(KC_0)


// Tap Dance ///////////////////////////////////////////////////////////////////

// The kind of tap dances that we are normally going to use. Just tap and hold,
// one or two times at best. Like in ZSA's Oryx.
typedef enum {
    UNKNOWN_KIND,
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // I think this is when two taps are not fast enough
    MORE_TAPS
} td_kind_t;

// The function that decides the type of TD based on the state. Taken from Oryx.
td_kind_t td_decide_kind(tap_dance_state_t* state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed)
            return SINGLE_TAP;
        else
            return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted)
            return DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return DOUBLE_HOLD;
        else
            return DOUBLE_TAP;
    }
    return MORE_TAPS;
}

typedef struct {
    bool is_press_action;
    td_kind_t kind;
} td_tap_t;

// The "list" of tap dances in the keymap.
enum {
    ENTER_LAYER,
};

// Definitions to be used later in the keymap.
#define TD_ENTR TD(ENTER_LAYER)

// The live state of each tap dance. Needs to be grown if more are added.
static td_tap_t td_state[0];


void on_td_for_enter_or_mouse(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code16(KC_ENTER);
        tap_code16(KC_ENTER);
        tap_code16(KC_ENTER);
    }
    if (state->count > 3) {
        tap_code16(KC_ENTER);
    }
}

void on_td_for_enter_or_mouse_finished(tap_dance_state_t *state, void *user_data) {
    td_state[ENTER_LAYER].kind = td_decide_kind(state);
    switch (td_state[ENTER_LAYER].kind) {
        case SINGLE_TAP: register_code16(KC_ENTER); break;
        case DOUBLE_TAP: register_code16(KC_ENTER); register_code16(KC_ENTER); break;
        case DOUBLE_HOLD: layer_on(_MOUSE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_ENTER); register_code16(KC_ENTER); break;
        default: break;
    }
}

void on_td_for_enter_or_mouse_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (td_state[ENTER_LAYER].kind) {
        case SINGLE_TAP: unregister_code16(KC_ENTER); break;
        case DOUBLE_TAP: unregister_code16(KC_ENTER); break;
        case DOUBLE_HOLD: layer_off(_MOUSE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_ENTER); break;
        default: break;
    }
    td_state[ENTER_LAYER].kind = UNKNOWN_KIND;
}

tap_dance_action_t tap_dance_actions[] = {
    [ENTER_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(on_td_for_enter_or_mouse,
            on_td_for_enter_or_mouse_finished, on_td_for_enter_or_mouse_reset)
};



// Tap Dance End ///////////////////////////////////////////////////////////////


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LCTR | LGUI | LAlt |LOWER | /Enter  /       \Space \  |RAISE | OSM  | LEFT | RGHT |
 *            |      |      |      |      |/       /         \      \ |      |AltGr |      |      |
 *             `----------------------------------'           '------''---------------------------'
 */

// Home row modifier keys with dual function.
#define DUAL_A LGUI_T(KC_A)
#define DUAL_S LALT_T(KC_S)
#define DUAL_D LCTL_T(KC_D)
#define DUAL_F LSFT_T(KC_F)

#define DUAL_J RSFT_T(KC_J)
#define DUAL_K RCTL_T(KC_K)
#define DUAL_L LALT_T(KC_L)
#define DUAL__ RGUI_T(KC_SCLN)

// One shot layers (unused, as they get stuck on a hold, and one has to be
// forced to press a key or wait for the timeout if holds it accidentally).
#define OSLOW  OSL(_LOWER)
#define OSRAI  OSL(_RAISE)

// Layer change with Tap Toggle. Keeps active only while you hold it (like MO),
// but can be locked as active if tapping it TAPPING_TOGGLE times (default=5).
#define LOWERL TT(_LOWER)
#define RAISEL TT(_RAISE)

[_BASE] = LAYOUT(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_ESC,  DUAL_A,  DUAL_S,  DUAL_D,  DUAL_F,  KC_G,                      KC_H,    DUAL_J,  DUAL_K,  DUAL_L,  DUAL__,  KC_QUOT,
  OSMS,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE, XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, OSMR,
                    OSMC,    OSMG,    OSMA,    LOWERL,  TD_ENTR, KC_SPC,  RAISEL,  OSMAG,   KC_LEFT, KC_RGHT
),


/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F12 |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |                    |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |-------.    ,-------|   <  |   -  |   +  |   >  |   [  |   ]  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |   6  |   7  |   8  |   9  |   0  |-------|    |-------|   {  |   }  |   ,  |   .  |   \  |   =  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |LOWER | /       /       \   _  \  |RAISE |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *             `----------------------------------'           '------''---------------------------'
 */

// Home row modifier keys with dual function.
#define DUAL_1 LGUI_T(KC_1)
#define DUAL_2 LALT_T(KC_2)
#define DUAL_3 LCTL_T(KC_3)
#define DUAL_4 LSFT_T(KC_4)

#define DUAL_CD RSFT_T(KC_DOWN)
#define DUAL_CU RCTL_T(KC_UP)
#define DUAL_CR LALT_T(KC_RGHT)
#define DUAL_LB RGUI_T(KC_LBRC)  // The only one used of this block after last changes

[_LOWER] = LAYOUT(
  KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  KC_GRV,  DUAL_1,  DUAL_2,  DUAL_3,  DUAL_4,  KC_5,                      KC_LT,   KC_MINS, KC_PLUS, KC_GT,   DUAL_LB, KC_RBRC,
  _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, _______, KC_LCBR, KC_RCBR, _______, _______, KC_BSLS, KC_EQUAL,
                    _______, _______, _______, _______, _______, KC_UNDS, _______, _______, _______, _______
),


/* RAISE
 * ,----------------------------------------.                     ,-----------------------------------------.
 * | CF12 | CF1  | CF2  | CF3  | CF4  | CF5  |                    | CF6  | CF7  | CF8  | CF9  | CF10 | CF11 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    | Home |PgDown| PgUp | End  |TappUp| DEL  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |ToBase|  OS  |  Alt | Ctrl | Shift|OSMAG |-------.    ,-------| LEFT | DOWN |  UP  | RIGHT|TappPr|ToBase|
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |ToThis|      |      |      |      |      |-------|    |-------|CLEFT |CDOWN | CUP  |CRIGHT|TappDo|ToThis|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |LOWER | /       /       \      \  |RAISE | PLAY | VOL- | VOL+ |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *             `----------------------------------'           '------''---------------------------'
 */

#define CT_LEFT LCTL(KC_LEFT)
#define CT_DOWN LCTL(KC_DOWN)
#define CT_UP   LCTL(KC_UP)
#define CT_RGHT LCTL(KC_RGHT)

[_RAISE] = LAYOUT(
  CT_F12,  CT_F1,   CT_F2,   CT_F3,   CT_F4,   CT_F5,                     CT_F6,   CT_F7,   CT_F8,   CT_F9,   CT_F10,  CT_F11,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  DT_UP,   KC_DEL,
  TOBASE,  KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, OSMAG,                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, DT_PRNT, TOBASE,
  TORAIS,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, CT_LEFT, CT_DOWN, CT_UP,   CT_RGHT, DT_DOWN, TORAIS,
                    _______, _______, _______, _______, _______, _______, _______, KC_MPLY, KC_VOLD, KC_VOLU
),


/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  W1  |  W2  |  W3  |  W4  |  W5  |                    |  W6  |  W7  |  W8  |  W9  |  W0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F12 |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |ToBase| Ins  |Mnu/Ap| Pscr |CpsWrd|CpsLck|-------.    ,-------| PREV | VOL- | VOL+ | NEXT | PLAY | MUTE |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |ToThis|      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |LOWER | /       /       \      \  |RAISE |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *             `----------------------------------'           '------''---------------------------'
 */
[_ADJUST] = LAYOUT(
  XXXXXXX, OS_1,    OS_2,    OS_3,    OS_4,    OS_5,                      OS_6,    OS_7,    OS_8,    OS_9,    OS_0,    XXXXXXX,
  KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  TOBASE,  KC_INS,  KC_APP,  KC_PSCR, CW_TOGG, KC_CAPS,                   KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY, KC_MUTE,
  TOADJU,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MOCK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                    _______, _______, _______, XXXXXXX, _______, _______, XXXXXXX, _______, _______, _______
),

[_MOUSE] = LAYOUT(
  CT_F12,  CT_F1,   CT_F2,   CT_F3,   CT_F4,   CT_F5,                     CT_F6,   CT_F7,   CT_F8,   CT_F9,   CT_F10,  CT_F11,
  _______, XXXXXXX, KC_ACL2, KC_ACL1, KC_ACL0, XXXXXXX,                   KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX, _______,
  _______, XXXXXXX, KC_BTN3, KC_BTN2, KC_BTN1, XXXXXXX,                   KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, TOBASE,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TOMOUS,
                    _______, _______, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX
),
};


layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


// Left encoder works like the dial in the car radio: clockwise is volume up.
// Right encoder work like the PageUp/Down keys placement. Turning "to the
// right" (clockwise) is going forward, so page down, and is also the key to the
// right in some laptop's keyboard, like my Thinkpad.
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]    = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),           ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_LOWER]   = { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______) },
    [_RAISE]   = { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______) },
    [_ADJUST]  = { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______) },
    [_MOUSE]   = { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______) },
};
#endif


#ifdef OLED_ENABLE /////////////////////////////////////////////////////////////
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {
    // TODO: remove eventually. I don't think I'll ever change this mode.
    oled_write_ln_P(PSTR("MODE"), false);
    if (!keymap_config.swap_lctl_lgui) {
        oled_write_ln_P(PSTR("Win"), false);
    } else {
        oled_write_ln_P(PSTR("Mac"), false);
    }

    oled_write_P(PSTR("\n"), false);

    // NB: Lines with 5 characters dont't have a newline, because the text fills
    // the whole line by itself, and the next line would get an extra space.
    oled_write_P(PSTR("LAYER"), false);
    layer_state_t defaultLayer = get_highest_layer(default_layer_state);
    layer_state_t layer = defaultLayer != _BASE ? defaultLayer : get_highest_layer(layer_state);
    switch (layer) {
        case _BASE:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjst"), false);
            break;
        case _MOUSE:
            oled_write_P(PSTR("Mouse"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }

    oled_write_P(PSTR("\n"), false);

    // Print whether a modifier is active and if in one-shot state.
    uint8_t mods = get_mods();
    uint8_t ones = get_oneshot_mods();
    uint8_t both = mods|ones;

    oled_write_P((both & MOD_MASK_SHIFT) ? PSTR("S") : PSTR(" "), false);
    oled_write_P((ones & MOD_MASK_SHIFT) ? PSTR("1") : PSTR(" "), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P((both & MOD_MASK_CTRL) ? PSTR("C") : PSTR(" "), false);
    oled_write_P((ones & MOD_MASK_CTRL) ? PSTR("1") : PSTR(" "), false);
    oled_write_P(PSTR("\n"), false);
    oled_write_P((both & MOD_MASK_GUI) ? PSTR("G") : PSTR(" "), false);
    oled_write_P((ones & MOD_MASK_GUI) ? PSTR("1") : PSTR(" "), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P((both & MOD_MASK_ALT) ? PSTR("A") : PSTR(" "), false);
    oled_write_P((ones & MOD_MASK_ALT) ? PSTR("1") : PSTR(" "), false);

    oled_write_P(PSTR("\n"), false);

    led_t led_usb_state = host_keyboard_led_state();
    if (led_usb_state.caps_lock) {
        oled_write_ln_P(PSTR("CAPS LOCK!"), false);
    } else { // Needed to clear the previous caps lock message
        oled_write_P(PSTR("\n\n"), false);
    }
    if (is_caps_word_on()) {
        oled_write_ln_P(PSTR("CAPS WORD!"), false);
    } else if (mock_case) {
        oled_write_ln_P(PSTR("MoCk cASe!"), false);
    } else { // Needed to clear the previous message
        oled_write_P(PSTR("\n\n"), false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return OLED_ROTATION_180;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
    return false;
}
#endif /////////////////////////////////////////////////////////////////////////


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_PRVWD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                }
            }
            break;
        case KC_NXTWD:
             if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_LSTRT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                     //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_LEND:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            break;
        case KC_DLINE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_BSPC);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_BSPC);
            }
            break;
        case KC_COPY:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_C);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_C);
            }
            return false;
        case KC_PASTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_V);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_V);
            }
            return false;
        case KC_CUT:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_X);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_X);
            }
            return false;
            break;
        case KC_UNDO:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Z);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Z);
            }
            return false;
        case CW_TOGG:
            mock_case = false;
            return true; // Keep processing the key stroke.
        case KC_MOCK:
            if (!record->event.pressed) {
                mock_case = !mock_case;
                caps_word_off();
            }
            return false; // Don't process it any longer
        case KC_A ... KC_Z:
            if (!mock_case)
                break;
            if ((get_mods() & MOD_MASK_CTRL) ||
                (get_mods() & MOD_MASK_ALT)  ||
                (get_mods() & MOD_MASK_GUI))
                break; // prevent any change if modifiers are pressed
            if (record->event.pressed) {
                // One out of 8, toggle the previous case.
                // TODO: the probability doesn't seem very reliable. I still get
                // a lot of repeated keys.
                if ((rand() % 8) > 0) {
                    mock_last_shifted = !mock_last_shifted;
                }
                if (mock_last_shifted)
                    register_code(KC_LSFT);
            } else {
                if (mock_case)
                    unregister_code(KC_LSFT);
            }
            break;
    }
    return true;
}

// This is a copy of the default callback. Changed only for '-'.
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        // Don't shift '-', as it prevents from nicely typing stuff like UTF-8,
        // CONSTANT-1, etc. Also '_' is as easy to press as '-' for me.
        // case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}
