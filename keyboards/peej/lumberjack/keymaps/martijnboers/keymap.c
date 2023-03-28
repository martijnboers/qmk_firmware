/* Copyright 2020 Paul James
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#define _BASE    0
#define _POKER   1
#define _PROGRAM 2
#define _SELECT  3
#define _EXTRA   4

#define PROG   MO(_PROGRAM)
#define POKER  MO(_POKER)
#define EXTR   MO(_EXTRA)

#define PRESS(keycode) register_code16(keycode)
#define RELEASE(keycode) unregister_code16(keycode)

void TAP(uint16_t keycode) {
    PRESS(keycode);
    RELEASE(keycode);
}

void CTRL(uint16_t keycode) {
  PRESS(KC_LCTL);
  TAP(keycode);
  RELEASE(KC_LCTL);
}

void dance_flsh_finished(tap_dance_state_t *state, void *user_data) {
  layer_on(_SELECT);
  if (state->count == 1) {
    PRESS(KC_LCTL);
    PRESS(KC_LSFT);
  } else {
    PRESS(KC_LCTL);
  }
}

void dance_flsh_reset(tap_dance_state_t *state, void *user_data) {
  layer_off(_SELECT);
  if (state->count == 1) {
    RELEASE(KC_LSFT);
    RELEASE(KC_LCTL);
  } else {
    RELEASE(KC_LCTL);
  }
}

enum {
  LAYER_SWITCH = 0
};

tap_dance_action_t tap_dance_actions[] = {
    [LAYER_SWITCH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_flsh_finished, dance_flsh_reset)
};

enum custom_keycodes {
  HEADP = SAFE_RANGE,
  C_THUMB,
  C_HOME,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Poker |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ctrl |  os  | mod3  | alt  |  program   |    space    | os   | $    | print| ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_BASE] = LAYOUT_ortho_5x12( \
  KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_BSPC, \
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_BSLS, \
  POKER,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_ENT, \
  SC_LSPO,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, SC_RSPC, \
  KC_LCTL,  EXTR,    EXTR,    KC_LALT, PROG,    PROG,    KC_SPC,  KC_SPC,  KC_LGUI, C_THUMB,KC_PSCR, KC_LCTL
),


[_POKER] = LAYOUT_ortho_5x12( \
  KC_CAPS, _______,          _______, _______, _______,  _______,   _______,   _______,   _______,   PUSH_2_TALK, _______,   KC_DEL, \
  _______, KC_MPRV,          KC_MPLY, KC_MNXT, KC_F5,    N_TAB,     KC_PAUSE,  T_PREV,    KC_UP,     T_NEXT,      KC_ENT,    W_QUIT, \
  _______, TD(LAYER_SWITCH), KC_VOLD, KC_VOLU, KC_MUTE,  _______,   KC_HOME,   KC_LEFT,   KC_DOWN,   KC_RGHT,     KC_BSPC,   KC_DEL, \
  _______, _______,          _______, COPY,    PASTE,    _______,   KC_END,    _______,   E_BACK,    E_FORWARD,   ALL,       C_HOME, \
  _______, _______,          _______, _______, _______,  _______,   KC_SPC,    _______,    _______,   _______,    _______,   _______
),

[_PROGRAM] = LAYOUT_ortho_5x12( \
  KC_F12,    KC_F1,   KC_F2,   KC_F3,              KC_F4,             KC_F5,    KC_F6,     KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11, \
  SWITCH,    KC_GRV,  KC_DLR,  KC_TILD,            KC_ASTERISK,       TERMINAL, _______,   _______,  KC_LBRC,  KC_RBRC, _______,  _______, \
  _______,   KC_PLUS, KC_UNDS, KC_MINS,            KC_EQL,            OSDOWN,   OSUP,      KC_DQUO,  KC_LCBR,  KC_RCBR, KC_QUOT,  _______, \
  KC_LSFT,   _______, _______, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP,  _______,  _______,   _______,  _______,  _______, _______,  _______, \
  _______,   _______, _______, _______,            _______,           _______,  _______,   _______,  _______,  _______, _______,  _______
),

[_SELECT] = LAYOUT_ortho_5x12( \
  _______,   _______,  _______,   _______, _______, _______, _______, _______, _______,  _______,  _______, _______, \
  _______,   _______,  KC_W,      _______, _______, KC_T,    _______, _______, KC_UP,    _______,  _______, _______, \
  _______,   _______,  _______,   _______, KC_F,    _______, _______, KC_LEFT, KC_DOWN,  KC_RIGHT, KC_BSPC, _______, \
  _______,   _______,  _______,   KC_C,    KC_V,    _______, _______, _______, _______,  _______,  _______, _______, \
  _______,   _______,  _______,   _______, _______, _______, _______, _______, _______,  _______,  _______, _______
),

[_EXTRA] = LAYOUT_ortho_5x12( \
  _______,   QK_BOOT,        EE_CLR,       _______,          _______,   _______,   _______,   KC_MINS, KC_EQL,  _______, _______, _______, \
  _______,   _______,        _______,      _______,          _______,   _______,   _______,   KC_7,    KC_8,    KC_9,    _______, _______, \
  _______,   _______,        _______,      _______,          _______,   _______,   HEADP,     KC_4,    KC_5,    KC_6,    KC_DEL,  _______, \
  _______,   _______,        _______,      _______,          _______,   _______,   _______,   KC_1,    KC_2,    KC_3,    _______, _______, \
  _______,   _______,        _______,      _______,          _______,   _______,   _______,   _______, KC_0,    KC_0,    KC_0,    _______
)

};

void keyboard_pre_init_user() {
    writePin(LED1, true);
    writePin(LED2, true);
}

void keyboard_post_init_user() {
    writePin(LED1, false);
    writePin(LED2, false);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(LED2, !led_state.caps_lock);
    }
    return res;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  writePin(LED1, record->event.pressed);

  switch (keycode) {
    case HEADP:
      if (record->event.pressed) {
        SEND_STRING("TODO");
      }

      break;

    case C_HOME:
      if (record->event.pressed) {
        SEND_STRING("~/");
      }

      break;

    case C_THUMB:
      if (record->event.pressed) {
        SEND_STRING(":+1:");
      }

      break;

  }
  return true;
};
