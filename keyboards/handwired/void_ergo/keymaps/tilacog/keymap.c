#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _SYMBOL,
    _FUN,
    _NUMPAD
};

// Layer access
#define ENT_NMP LT(_NUMPAD, KC_ENT)
#define ENT_FUN LT(_FUN, KC_ENT)
#define SPC_SYM LT(_SYMBOL, KC_SPC)

// Home row mods - left
#define HR_LGI LGUI_T(KC_A)
#define HR_LAL LALT_T(KC_S)
#define HR_LSH LSFT_T(KC_H)
#define HR_LCT LCTL_T(KC_T)

// Home row mods - right
#define HR_RCT LCTL_T(KC_N)
#define HR_RSH LSFT_T(KC_E)
#define HR_RAL LALT_T(KC_O)
#define HR_RGI LGUI_T(KC_I)

// Alt-gr mod tap
#define LALTGR RALT_T(KC_C)
#define RALTGR RALT_T(KC_L)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_5(
        QK_GESC,  KC_Q  ,  KC_D  , KC_R   , KC_W   , KC_B   ,         KC_J   , KC_F   ,  KC_U   , KC_P  , KC_SCLN, _______,
        KC_BSPC,  HR_LGI,  HR_LAL, HR_LSH , HR_LCT , KC_G   ,         KC_Y   , HR_RCT ,  HR_RSH , HR_RAL, HR_RGI , KC_QUOTE,
        _______,  KC_Z  ,  KC_X  , KC_M   , LALTGR , KC_V   ,         KC_K   , RALTGR ,  KC_COMM, KC_DOT, KC_SLSH, _______,
                    OSM(MOD_HYPR), KC_TAB , ENT_FUN, SPC_SYM,         SPC_SYM, ENT_NMP,  KC_PGUP, KC_PGDN

    ),

    [_SYMBOL] = LAYOUT_split_3x6_5(
        _______, _______, KC_BSLS, S(KC_3), S(KC_BSLS), _______,       _______ , S(KC_1)    , S(KC_4), S(KC_5)   , _______, _______,
        _______, KC_PAST, KC_PSLS, S(KC_2), KC_PEQL,    _______,       _______ , S(KC_MINS) , S(KC_9), S(KC_LBRC), KC_LBRC, _______,
        _______, KC_PPLS, KC_PMNS, S(KC_6), S(KC_7),    _______,       KC_GRAVE, S(KC_GRAVE), S(KC_0), S(KC_RBRC), KC_RBRC, _______,
                          _______, _______, _______,    _______,       _______ , _______    , _______, _______
    ),

    [_FUN] = LAYOUT_split_3x6_5(
        _______, _______, KC_PGDN, KC_UP  , KC_PGUP , _______,         KC_F12 , KC_F7  , KC_F8  , KC_F9  , _______, KC_CAPS,
        KC_DEL , _______, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TAB ,         KC_F11 , KC_F4  , KC_F5  , KC_F6  , _______, KC_PSCR,
        _______, _______, KC_HOME, _______, KC_END  , _______,         KC_F10 , KC_F1  , KC_F2  , KC_F3  , _______, KC_INS ,
                          _______, _______, _______ , _______,         _______, _______, _______, _______
    ),

    [_NUMPAD] = LAYOUT_split_3x6_5(
        _______, _______, _______, _______, _______, _______,          KC_PCMM, KC_7   , KC_8   , KC_9   , _______, _______,
        _______, _______, _______, _______, _______, _______,          KC_PDOT, KC_4   , KC_5   , KC_6   , _______, _______,
        _______, _______, _______, _______, _______, _______,          KC_0   , KC_1   , KC_2   , KC_3   , _______, _______,
                          _______, _______, _______, _______,          _______, _______, KC_0   , KC_0
    )

    /*
    [_NEXT] = LAYOUT_split_3x6_5(
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, _______,          _______, _______, _______, _______
    )
    */
};


/*
 * ROTARY ENCODER
 */

#if defined(ENCODER_MAP_ENABLE)
#define VOLUME ENCODER_CCW_CW(KC_VOLD, KC_VOLU)
#define MOUSE_WHEEL ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE]   = {VOLUME, MOUSE_WHEEL},
    [_SYMBOL] = {VOLUME, MOUSE_WHEEL},
    [_NUMPAD] = {VOLUME, MOUSE_WHEEL},
    [_FUN]    = {VOLUME, MOUSE_WHEEL}
};
#endif
