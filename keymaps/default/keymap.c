// =============================================================
//  REPLICAZERON 24K - keymap.c
//  Azeron Cyborg 2 replica - Blue Pill STM32F103
//
//  Capa 0 (JOYSTICK): joystick mueve el mouse + 24 teclas
//  Capa 1 (WASD):     joystick -> W/A/S/D (hold en T24/PB14)
//                     Mouse sigue activo en modo WASD
//  LED_1 (PC13): encendido cuando WASD está activo
// =============================================================

#include QMK_KEYBOARD_H
#include "analog.h"
#include "pointing_device.h"

// --- Capas ---
enum layers {
    LAYER_JOYSTICK = 0,
    LAYER_WASD     = 1
};

// --- Configuración del joystick ---
#define JOY_DEADZONE    50    // Zona muerta central
#define JOY_WASD_THRESH 200   // Umbral para disparar WASD
#define JOY_CENTER      512   // Centro ADC 10-bit
#define JOY_MOUSE_DIV   6     // Divisor velocidad mouse

// --- Estado WASD (evita repetición de teclas) ---
static bool key_w = false;
static bool key_a = false;
static bool key_s = false;
static bool key_d = false;

// =============================================================
//  KEYMAPS
// =============================================================
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // ---------------------------------------------------------
    //  CAPA 0 - Modo joystick analógico (mouse)
    // ---------------------------------------------------------
    [LAYER_JOYSTICK] = LAYOUT_direct(
        // Índice  T1     T2     T3     T4     T5
                   KC_Q,  KC_E,  KC_R,  KC_F,  KC_V,
        // Medio   T6     T7     T8     T9
                   KC_1,  KC_2,  KC_3,  KC_4,
        // Anular  T10    T11    T12    T13
                   KC_Z,  KC_X,  KC_C,  KC_LSFT,
        // Meñique T14    T15    T16    T17
                   KC_LCTL, KC_TAB, KC_CAPS, KC_G,
        // Pulgar  T18    T19    T20    T21    T22
                   KC_SPC, KC_LALT, KC_5, KC_6, KC_7,
        // Palma   T23    T24
                   KC_ESC, TG(LAYER_WASD)
    ),

    // ---------------------------------------------------------
    //  CAPA 1 - Modo WASD (hold T24)
    //  Joystick -> W/A/S/D | Mouse sigue activo
    //  LED_1 encendido en esta capa
    // ---------------------------------------------------------
    [LAYER_WASD] = LAYOUT_direct(
        // Índice  T1     T2     T3     T4     T5
                   KC_Q,  KC_E,  KC_R,  KC_F,  KC_V,
        // Medio   T6     T7     T8     T9
                   KC_1,  KC_2,  KC_3,  KC_4,
        // Anular  T10    T11    T12    T13
                   KC_Z,  KC_X,  KC_C,  KC_LSFT,
        // Meñique T14    T15    T16    T17
                   KC_LCTL, KC_TAB, KC_CAPS, KC_G,
        // Pulgar  T18    T19    T20    T21    T22
                   KC_SPC, KC_LALT, KC_5, KC_6, KC_7,
        // Palma   T23    T24
                   KC_ESC, _______
    )
};

// =============================================================
//  LED - Indicador de capa activa
//  PC13 en Blue Pill usa lógica INVERTIDA (LOW = encendido)
// =============================================================
layer_state_t layer_state_set_user(layer_state_t state) {
    if (get_highest_layer(state) == LAYER_WASD) {
        writePinLow(C13);   // Encender LED_1 (modo WASD activo)
    } else {
        writePinHigh(C13);  // Apagar LED_1
    }
    return state;
}

// =============================================================
//  INICIALIZACIÓN
// =============================================================
void keyboard_post_init_user(void) {
    // LED_1 como salida, apagado al inicio
    setPinOutput(C13);
    writePinHigh(C13);

    // LED_2 como salida, disponible para uso futuro
    setPinOutput(B15);
    writePinHigh(B15);
}

// =============================================================
//  BUCLE PRINCIPAL - Joystick analógico
//  Se ejecuta en cada ciclo del firmware
// =============================================================
void housekeeping_task_user(void) {
    // Leer ejes analógicos (rango 0-1023)
    int16_t x = (int16_t)analogReadPin(A6) - JOY_CENTER;
    int16_t y = (int16_t)analogReadPin(A7) - JOY_CENTER;

    bool wasd_mode = (get_highest_layer(layer_state) == LAYER_WASD);

    if (wasd_mode) {
        // -----------------------------------------------------
        //  MODO WASD: joystick dispara teclas W/A/S/D
        // -----------------------------------------------------

        // Eje Y negativo = W (adelante) / positivo = S (atrás)
        if (y < -JOY_WASD_THRESH) {
            if (!key_w) { register_code(KC_W); key_w = true; }
            if (key_s)  { unregister_code(KC_S); key_s = false; }
        } else if (y > JOY_WASD_THRESH) {
            if (!key_s) { register_code(KC_S); key_s = true; }
            if (key_w)  { unregister_code(KC_W); key_w = false; }
        } else {
            if (key_w) { unregister_code(KC_W); key_w = false; }
            if (key_s) { unregister_code(KC_S); key_s = false; }
        }

        // Eje X negativo = A (izquierda) / positivo = D (derecha)
        if (x < -JOY_WASD_THRESH) {
            if (!key_a) { register_code(KC_A); key_a = true; }
            if (key_d)  { unregister_code(KC_D); key_d = false; }
        } else if (x > JOY_WASD_THRESH) {
            if (!key_d) { register_code(KC_D); key_d = true; }
            if (key_a)  { unregister_code(KC_A); key_a = false; }
        } else {
            if (key_a) { unregister_code(KC_A); key_a = false; }
            if (key_d) { unregister_code(KC_D); key_d = false; }
        }

    } else {
        // -----------------------------------------------------
        //  MODO JOYSTICK: joystick mueve el cursor del mouse
        // -----------------------------------------------------

        // Soltar WASD si se cambia de capa mientras están activas
        if (key_w) { unregister_code(KC_W); key_w = false; }
        if (key_a) { unregister_code(KC_A); key_a = false; }
        if (key_s) { unregister_code(KC_S); key_s = false; }
        if (key_d) { unregister_code(KC_D); key_d = false; }

        // Aplicar deadzone central
        if (x > -JOY_DEADZONE && x < JOY_DEADZONE) x = 0;
        if (y > -JOY_DEADZONE && y < JOY_DEADZONE) y = 0;

        if (x != 0 || y != 0) {
            report_mouse_t mouse = pointing_device_get_report();
            mouse.x = (int8_t)(x / JOY_MOUSE_DIV);
            mouse.y = (int8_t)(y / JOY_MOUSE_DIV);
            pointing_device_set_report(mouse);
            pointing_device_send();
        }
    }
}

// =============================================================
//  PROCESAMIENTO DE TECLAS
// =============================================================
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}
