# Hey Emacs, this is a -*- makefile -*-
#----------------------------------------------------------------------------
# $Id: Makefile 27 2013-02-16 21:19:12Z pjean $
# On command line:
#
# make all = Make software.
#
# make clean = Clean out built project files.
#
# make rebuild = rebuilt project.
#
# make coff = Convert ELF to AVR COFF.
#
# make extcoff = Convert ELF to AVR Extended COFF.
#
# make program = Download the hex file to the device, using avrdude.
#                Please customize the avrdude settings below first!
#
# make debug = Start either simulavr or avarice as specified for debugging,
#              with avr-gdb or avr-insight as the front end for debugging.
#
# make filename.s = Just compile filename.c into the assembler code only.
#
# make filename.i = Create a preprocessed source file for use in submitting
#                   bug reports to the GCC project.

# Nom du fichier cible (sans extension).
TARGET = BootloaderDFU

# Chemin relatif du répertoire racine du projet de l'utilisateur
PROJECT_TOPDIR = ../../..

# Normalement le MCU est défini dans board.mk Il est possible de le modifier
# dans le cas où le modèle implanté (cas des cartes avec support) ne correspond
# pas.
# MCU = atmega32

# Normalement F_CPU est définie dans board.mk ... Il est possible de la modifier
# dans le cas où la fréquence n'est pas fixée par un quartz (horloge interne...)
# F_CPU = 8000000

# Facteur de division de l'horloge, par défaut 1, peut être mis à 2
F_DIV = 1

#----------------------------------------------------------------------------
#                               ~~~~AVRIO~~~~
# Chemin relatif du répertoire racine d'AVRIO
# AVRIO_TOPDIR = $(PROJECT_TOPDIR)/../avrio

# Nom de la carte cible (voir le fichier board/board.mk pour la liste)
# Si BOARD est vide, il faut un fichier board.mk pour définir les propriétés de
# la carte dans le répertoire où se trouve ce Makefile !
BOARD = USBKEY

# Configuration de AvrIO
# -------------------------------
AVRIO_CONFIG = 

# Valide le noyau multitâche temps réel AVRX (sous forme de bibliothèque)
AVRX = OFF
#                               ~~~~AVRIO~~~~
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
#                               ~~~~LUFA~~~~
LUFA_ENABLE = YES
LUFA_BOARD  = BOARD_$(BOARD)

# Chemin relatif du répertoire racine de LUFA
# LUFA_TOPDIR  = $(AVRIO_TOPDIR)/src/lufa

# You must define F_USB to the frequency of the unprescaled USB controller clock
F_USB        = $(F_CPU)*$(F_DIV)

# Configuration de LUFA
# -------------------------------
LUFA_CONFIG  = USE_LUFA_CONFIG_HEADER
LUFA_CONFIG += BOOT_START_ADDR=$(BOOT_START_OFFSET)

LUFA_SRC = $(LUFA_SRC_USB)

# Specific Bootloader configuration---------------------------------------------
# Flash size and bootloader section sizes of the target, in KB. These must
# match the target's total FLASH size and the bootloader size set in the
# device's fuses.
FLASH_SIZE_KB         = 128
BOOT_SECTION_SIZE_KB  = 4

# Bootloader address calculation formulas (requires the "bc" unix utility)
# Do not modify these macros, but rather modify the depedant values above.
BOOT_START_OFFSET     = 0x$(shell echo "obase=16; ($(FLASH_SIZE_KB) - $(BOOT_SECTION_SIZE_KB)) * 1024" | bc)
BOOT_SEC_OFFSET       = 0x$(shell echo "obase=16; (($(FLASH_SIZE_KB) * 1024) - $(strip $(1)))" | bc)

# Bootloader linker section flags for relocating the API table sections to
# known FLASH addresses - these should not normally be user-edited.
BOOT_SECTION_LD_FLAG  = -Wl,--section-start=.apitable_$(strip $(1))=$(call BOOT_SEC_OFFSET, $(3)) -Wl,--undefined=BootloaderAPI_$(strip $(2))
BOOT_API_LD_FLAGS     = $(call BOOT_SECTION_LD_FLAG, trampolines, Trampolines, 96)
BOOT_API_LD_FLAGS    += $(call BOOT_SECTION_LD_FLAG, jumptable,   JumpTable,   32)
BOOT_API_LD_FLAGS    += $(call BOOT_SECTION_LD_FLAG, signatures,  Signatures,  8)

LDFLAGS += -Wl,--section-start=.text=$(BOOT_START_OFFSET) $(BOOT_API_LD_FLAGS)

#                               ~~~~LUFA~~~~
#----------------------------------------------------------------------------

# Niveau d'optimisation de GCC =  [0, 1, 2, 3, s].
#     0 = pas d'optimisation (pour debug).
#     s = optimisation de la taille du code (pour release).
#     (Note: 3 n'est pas toujours le meilleur niveau. Voir la FAQ avr-libc.)
OPT = s

# Liste des fichiers source C. (Les dépendances sont automatiquement générées.)
# Le chemin d'accès des fichiers sources systèmes a été ajouté au chemin de 
# recherche du compilateur, il n'est donc pas nécessaire de préciser le chemin 
# d'accès complet du fichier mais seulement le nom du projet (avrio, avrx, ...)
SRC  = src/bootloader/$(TARGET).c
SRC += src/bootloader/Descriptors.c src/bootloader/BootloaderAPI.c 

# Liste des fichiers source C++. (Les dépendances sont automatiquement générées.)
# Le chemin d'accès des fichiers sources systèmes a été ajouté au chemin de 
# recherche du compilateur, il n'est donc pas nécessaire de préciser le chemin 
# d'accès complet du fichier mais seulement le nom du projet (avrio, avrx, ...)
CPPSRC =

# Liste des fichiers source assembleur
#   L'extenson doit toujours être .S (en majuscule). En effet, les fichiers .s
#   ne sont pas consédérés comme des fichiers sources mais comme des fichiers
#   générés par le compilateur et seront supprimés lors d'un make clean.
#   Cela est valable aussi sous DOS/Windows (bien que le système d'exploitation
#   ne soit pas sensible à la casse).
ASRC = src/bootloader/BootloaderAPITable.S

# Place -D or -U options here for C sources
CDEFS = 

# Place -D or -U options here for ASM sources
ADEFS = 

# Place -D or -U options here for C++ sources
CPPDEFS = 

# List any extra directories to look for include files here.
#     Each directory must be seperated by a space.
#     Use forward slashes for directory separators.
#     For a directory that has spaces, enclose it in quotes.
EXTRA_INCDIRS = ../Config

#---------------- Library Options ----------------
# List any extra directories to look for libraries here.
#     Each directory must be seperated by a space.
#     Use forward slashes for directory separators.
#     For a directory that has spaces, enclose it in quotes.
EXTRA_LIBDIRS = 

# List any extra libraries here.
#     Each library must be seperated by a space.
EXTRA_LIBS = 

# STANDARD, MIN or FLOAT
PRINTF_VERSION = STANDARD

# STANDARD, MIN or FLOAT
SCANF_VERSION = STANDARD

# ON/OFF
MATH_LIB_ENABLE = ON

#---------------- Programming Options (avrdude) ----------------

# Programming hardware
# Type: avrdude -c ?
# to get a full listing.
#
AVRDUDE_PROGRAMMER = jtag2

# com1 = serial port. Use lpt1 to connect to parallel port.
AVRDUDE_PORT = usb 

# ON/OFF
AVRDUDE_WRITE_EEPROM_ENABLE = OFF

#---------------- Debugging Options ----------------

# Set the DEBUG_UI to either gdb or insight.
# DEBUG_UI = gdb
DEBUG_UI = insight

# Set the debugging back-end to either avarice, simulavr.
DEBUG_BACKEND = avarice
#DEBUG_BACKEND = simulavr

# When using avarice settings for the JTAG
JTAG_DEV = usb

#------------------------------------------------------------------------------
include $(PROJECT_TOPDIR)/msl.mk
include $(AVRIO_TOPDIR)/script/common.mk 
