TARGET = libanimations.a
TOPDIR = ..

include $(TOPDIR)/defaults.mk

SRC = program.c

ifeq ($(ANIMATION_SNAKE),y)
  SRC += snake.c
endif

ifeq ($(ANIMATION_MATRIX),y)
  SRC += matrix.c
endif

ifeq ($(ANIMATION_STONEFLY),y)
  SRC += stonefly.c
endif

ifeq ($(ANIMATION_FLYINGDOTS),y)
  SRC += flyingdots.c
endif

ifeq ($(ANIMATION_GAMEOFLIFE),y)
  SRC += gameoflife.c
endif

ifeq ($(ANIMATION_MHERWEG),y)
  SRC += mherweg.c
endif

ifeq ($(ANIMATION_BREAKOUT),y)
  SRC += breakout_demo.c
endif

ifeq ($(ANIMATION_LTN_ANT),y)
  SRC += ltn_ant.c
endif

ifneq (,$(filter y,$(ANIMATION_PLASMA) $(ANIMATION_PSYCHEDELIC)))
  SRC += fpmath_patterns.c
endif

ifeq ($(ANIMATION_BLACKHOLE),y)
  SRC += blackhole.c
endif

ifeq ($(ANIMATION_SQUARES),y)
  SRC += squares.c
endif

ifeq ($(ANIMATION_TIME),y)
  SRC += borg_time.c
endif

include $(TOPDIR)/rules.mk
