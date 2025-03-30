#include QMK_KEYBOARD_H

enum layer_number {
  _IRIDESCENCE = 0,
  _QWERTY,
  _QWERTY_EXTRA,
  _UNUSED,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * ,-----------------------------------------.                   ,-----------------------------------------.
 * | Strt | Left | Rght |      | DelB |   !  |                   |  ?   | FocF |      | Down |  Up  | End  |
 * |------+------+------+------+------+------|                   |------+------+------+------+------+------|
 * | CDic |  G   |  D   |  B   |   V  | Alt2 |                   | Alt2 |  L   |  C   |  M   |  P   | VDic |
 * |------+------+------+------+------+------|                   |------+------+------+------+------+------|
 * | Alt1 |  A   |  E   |  O   |   I  |   U  |-------.   ,-------|  H   |  R   |  S   |  N   |  T   | Alt1 |
 * |------+------+------+------+------+------|   No  |   |  Yes  |------+------+------+------+------+------|
 * |  ,   |  F   |  '   |  Q   |   Y  |   W  |-------|   |-------|  Z   |  J   |  X   | Eng  |  K   |   .  |
 * `-----------------------------------------/       /    \      \-----------------------------------------'
 *                   | Lock | Sys  | Ctl  | / VSpc  /      \ HSpc \  |  Ctl |  Sys | LyrR |
 *                   |      |      |      |/       /        \      \ |      |      |      |
 *                   `----------------------------'          '------''--------------------'
 */

[_IRIDESCENCE] = LAYOUT(
  KC_HOME, KC_LEFT, KC_RGHT, KC_2,    KC_BSPC, KC_3,
  KC_4,    KC_TAB,  KC_5,    KC_DOWN, KC_UP,   KC_END,

  KC_6,           KC_G, KC_D, KC_B, KC_V, LALT_T(KC_NUM),
  RALT_T(KC_NUM), KC_L, KC_C, KC_M, KC_P, KC_7,

  LSFT_T(KC_CAPS), KC_A, KC_E, KC_O, KC_I, KC_U,
  KC_H,            KC_R, KC_S, KC_N, KC_T, RSFT_T(KC_CAPS),

  KC_8,    KC_F, KC_0, KC_Q, KC_Y, KC_W, KC_ESC,
  KC_PENT, KC_Z, KC_J, KC_X, KC_1, KC_K, KC_9,

  QK_LOCK, KC_LGUI, KC_LCTL, KC_ENT,
  KC_SPC,  KC_RCTL, KC_RGUI, TO(_QWERTY)
),
[_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                        KC_LALT, KC_LGUI, XXXXXXX, KC_SPC, KC_ENT, XXXXXXX, KC_BSPC,
  TO(_QWERTY_EXTRA)
),
[_QWERTY_EXTRA] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                       XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   _______, _______,  KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                             _______, _______, _______,  _______, _______,  _______, _______,
  TO(_IRIDESCENCE)
),
[_UNUSED] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _QWERTY, _QWERTY_EXTRA, _UNUSED);
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
