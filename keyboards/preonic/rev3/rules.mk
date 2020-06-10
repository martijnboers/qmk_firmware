# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes      # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes         # Console for debug
COMMAND_ENABLE = yes       # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
WS2812_DRIVER = bitbang
API_SYSEX_ENABLE = no

# Do not enable RGB_MATRIX_ENABLE together with RGBLIGHT_ENABLE
RGB_MATRIX_ENABLE = no

ENCODER_ENABLE = yes
DIP_SWITCH_ENABLE = no

DYNAMIC_MACRO_ENABLE = yes
WPM_ENABLE = no
TAP_DANCE_ENABLE=yes

LAYOUTS = ortho_5x12
