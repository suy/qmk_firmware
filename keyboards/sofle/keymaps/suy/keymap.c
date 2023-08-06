#include QMK_KEYBOARD_H

enum sofle_layers {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    KC_PRVWD = SAFE_RANGE,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND,
    KC_DLINE
};


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
 *            | LCTR | LGUI | LAlt |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
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

// One shot modifiers.
#define OSMC   OSM(MOD_LCTL)
#define OSMS   OSM(MOD_LSFT)
#define OSMA   OSM(MOD_LALT)
#define OSMG   OSM(MOD_LGUI)
#define OSMR   OSM(MOD_RSFT)

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
                    OSMC,    OSMG,    OSMA,    LOWERL,  KC_ENT,  KC_SPC,  RAISEL,  KC_RCTL, KC_RALT, KC_RGUI
),


/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F12 |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |                    |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   4  |   5  |-------.    ,-------| LEFT | DOWN |  UP  | RIGHT|   [  |   ]  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |   6  |   7  |   8  |   9  |   0  |-------|    |-------|   {  |   }  |   \  |   +  |   -  |   =  |
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
#define DUAL_LB RGUI_T(KC_LBRC)

[_LOWER] = LAYOUT(
  KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  _______, DUAL_1,  DUAL_2,  DUAL_3,  DUAL_4,  KC_5,                      KC_LEFT, DUAL_CD, DUAL_CU, DUAL_CR, DUAL_LB, KC_RBRC,
  _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, _______, KC_LCBR, KC_RCBR, KC_BSLS, KC_PLUS, KC_MINS, KC_EQUAL,
                    _______, _______, _______, _______, _______, KC_UNDS, _______, _______, _______, _______
),


/* RAISE
 * ,----------------------------------------.                     ,-----------------------------------------.
 * |      |MoAcc0|MoAcc1|MoAcc2|      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | Ins  |Mnu/Ap| Pscr |      |                    |WhLeft|WhDown| WhUp |WhRght|TappUp|      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |Mouse3|Mouse2|Mouse1|CpsWrd|-------.    ,-------|MsLeft|MsDown| MsUp |MsRght|TappPr|      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      | Undo |  Cut | Copy | Paste|      |-------|    |-------| Home |PgDown| PgUp | End  |TappDo|      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |LOWER | /       /       \      \  |RAISE |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *             `----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT(
  _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, XXXXXXX, KC_INS,  KC_APP,  KC_PSCR, XXXXXXX,                   KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, DT_UP,   _______,
  _______, _______, KC_BTN3, KC_BTN2, KC_BTN1, CW_TOGG,                   KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, DT_PRNT, XXXXXXX,
  _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PASTE,XXXXXXX, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  DT_DOWN, _______,
                    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),


/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | BOOT |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |MACWIN|      |      |      |-------.    ,-------|      | VOLDO| MUTE | VOLUP|      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | PREV | PLAY | NEXT |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |LOWER | /       /       \      \  |RAISE |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *             `----------------------------------'           '------''---------------------------'
 */
[_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, CG_TOGG, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
                    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  )
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
    [_ADJUST]  = { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______) }
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
    switch (get_highest_layer(layer_state)) {
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
    } else { // Needed to clear the previous caps word message
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
    }
    return true;
}

