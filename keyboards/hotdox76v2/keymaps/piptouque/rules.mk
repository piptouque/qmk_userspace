# Having a file like this allows you to override Makefile definitions
# for your own particular keymap

SPLIT_KEYBOARD = yes
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
CAPS_WORD_ENABLE = yes
# auto shift increases firmware size by around 3Mo(!)
# we don't want it any way because of Vim (hjkl).
AUTO_SHIFT_ENABLE = no
#
TAP_DANCE_ENABLE = yes
# SWAP_HANDS_ENABLE = yes

# Optimisation / firmware size reduction
LTO_ENABLE_ = yes
CONSOLE_ENABLE = no
COMMAND_ENABLE   = no  # Commands for debug and configuration
AVR_USE_MINIMAL_PRINTF = yes
MUSIC_ENABLE = no
