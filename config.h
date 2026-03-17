#pragma once

// =============================================================
//  REPLICAZERON 24K - config.h
//  Azeron Cyborg 2 replica - Blue Pill STM32F103
//  24 teclas con PINES DIRECTOS (sin matriz)
// =============================================================

// --- MATRIZ: 1 fila, 24 columnas (pines directos) ---
#define MATRIX_ROWS 1
#define MATRIX_COLS 24

// --- PINES DIRECTOS para las 24 teclas ---
// Pines ocupados (NO usar para teclas):
//   PA6  -> Joystick X
//   PA7  -> Joystick Y
//   PA8  -> Click joystick
//   PC13 -> LED 1
//   PC14 -> Macro switch
//   PB15 -> LED 2
//
// Distribución por dedos (igual que Azeron Cyborg 2):
//   Índice  (T1-T5):  PA0, PA1, PA2, PA3, PA4
//   Medio   (T6-T9):  PA5, PA9, PA10, PA11
//   Anular  (T10-T13):PB0, PB1, PB2, PB3
//   Meñique (T14-T17):PB4, PB5, PB6, PB7
//   Pulgar  (T18-T22):PB8, PB9, PB10, PB11, PB12
//   Palma   (T23-T24):PB13, PB14
//
#define DIRECT_PINS { \
    { A0, A1, A2, A3, A4, \
      A5, A9, A10, A11,   \
      B0, B1, B2, B3,     \
      B4, B5, B6, B7,     \
      B8, B9, B10, B11, B12, \
      B13, B14 }          \
}


// --- JOYSTICK ANALÓGICO (thumbstick) ---
#define ANALOG_JOYSTICK_X_AXIS_PIN      PAL_LINE(GPIOA, 6)
#define ANALOG_JOYSTICK_Y_AXIS_PIN      PAL_LINE(GPIOA, 7)
#define ANALOG_JOYSTICK_CLICK_PIN       PAL_LINE(GPIOA, 8)
#define ANALOG_JOYSTICK_AXES_COUNT      2
#define ANALOG_JOYSTICK_SPEED_MAX       2
#define ANALOG_JOYSTICK_SPEED_REGULATOR 20
#define ANALOG_JOYSTICK_READ_INTERVAL   10
#define ANALOG_JOYSTICK_AXIS_MIN        0
#define ANALOG_JOYSTICK_AXIS_MAX        1023
#define ANALOG_JOYSTICK_CENTER_DEADZONE 50

// --- PIN MACRO SWITCH ---
#define MACRO_SWITCH_PIN PAL_LINE(GPIOC, 14)

// --- PINES LEDs indicadores ---
#define LED_1_PIN PAL_LINE(GPIOC, 13)
#define LED_2_PIN PAL_LINE(GPIOB, 15)

// --- JOYSTICK QMK ---
#define JOYSTICK_AXES_COUNT   2
#define JOYSTICK_BUTTON_COUNT 1

// --- USB ---
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x4276
#define DEVICE_VER   0x0001
#define MANUFACTURER "Carlos4276"
#define PRODUCT      "Replicazeron 24k"

// --- COMPORTAMIENTO ---
#define DEBOUNCE     5
#define TAPPING_TERM 200

// --- ADC ---
#define ADC_RESOLUTION 10

// --- Pull-up en todos los pines de teclas ---
#define MATRIX_IO_DELAY 30
#define PLATFORM_SUPPORTS_HARDWARE_DEBOUNCE
