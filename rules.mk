# =============================================================
#  REPLICAZERON 24K - rules.mk
#  Blue Pill STM32F103 - Pines directos (sin matriz)
# =============================================================

MCU        = STM32F103
BOOTLOADER = stm32duino

# --- PINES DIRECTOS (QMK maneja la matriz internamente) ---
CUSTOM_MATRIX = no

# --- Build Options ---
BOOTMAGIC_ENABLE       = yes      # Bootmagic lite
MOUSEKEY_ENABLE        = yes      # Control del mouse con teclado
EXTRAKEY_ENABLE        = yes      # Audio/media keys
CONSOLE_ENABLE         = no
COMMAND_ENABLE         = no
NKRO_ENABLE            = yes      # N-Key Rollover
BACKLIGHT_ENABLE       = no
RGBLIGHT_ENABLE        = no
AUDIO_ENABLE           = no
JOYSTICK_ENABLE        = yes      # HID Joystick analógico
POINTING_DEVICE_ENABLE = yes      # Para mover el mouse con el joystick

# --- Archivos fuente personalizados ---
SRC += analog.c
