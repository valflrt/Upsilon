# You can override those settings on the command line

PLATFORM ?= device
DEBUG ?= 0

HOME_DISPLAY_EXTERNALS ?= 1
EPSILON_VERSION ?= 15.5.0
OMEGA_VERSION ?= 2.0.2
UPSILON_VERSION ?= 1.0.1-dev
OMEGA_USERNAME ?= valflrt
OMEGA_STATE ?= dev
# reader has been removed: to re-add it don't forget to add reader to apps/home/apps_layout.csv
EPSILON_APPS ?= calculation graph rpn code statistics probability solver atomic sequence regression mandelbrot settings external
SUBMODULES_APPS = atomic rpn
EPSILON_I18N ?= en fr nl pt it de es hu
EPSILON_COUNTRIES ?= WW CA DE ES FR GB IT NL PT US
EPSILON_GETOPT ?= 0
ESCHER_LOG_EVENTS_BINARY ?= 0
THEME_NAME ?= val_cursed_night_light
THEME_REPO ?= local
INCLUDE_ULAB ?= 1
