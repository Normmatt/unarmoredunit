# Copyright (C) 1999-2000 Qute Corporation. All rights reserved.
#
# makefile for samples/hello
#	$Id: $

.SUFFIXES: .bin .obj .p86 .a86 .d86 .c

CRT0=crt0.obj

CFLAGS=-I.\lsic86ws\include -L.\lsic86ws\lib
DEFINES=
MODEL=p

.c.obj:
	lcc86 -cv -m$(MODEL) -c $(CFLAGS) $(DEFINES) -o $@ $<

.c.a86:
	lcc86 -cv -m$(MODEL) -SC $(CFLAGS) $(DEFINES) -o $@ $<

.a86.obj:
	r86 $(AFLAGS) -o $@ $<

.bin.obj:
	python bin2d86.py $*.bin
	r86 $(AFLAGS) -o $*.obj $*.d86

default:	all

clean:
	$(RM) *.a86
	$(RM) *.d86
	$(RM) *.obj
	$(RM) *.exe
	$(RM) armoredunit.hex
	$(RM) armoredunit.bin

all:	clean crt0.obj armoredunit.hex armoredunit.bin

crt0.obj:	crt0.p86
	cpp -o crt0.a86 $<
	r86 -o $@ crt0.a86

armoredunit.hex:	SWANMAIN.obj \
					DFONT_char_adr.obj \
					SPRINTF.obj \
					SYSTEM.obj \
					PAD.obj \
					MEMORY.obj \
					select.obj \
					WORK.obj \
					ASM.obj \
					SERIAL.obj \
					IP_MES.obj \
					DEBUG.obj \
					CONSOLE.obj \
					TITLE.obj \
					FILLSAIL.obj \
					SAMMYL.obj \
					SH_FONT.obj \
					KEYBOARD.obj \
					LOGO.obj \
					m_game.obj \
					m_sub.obj \
					G_CONFIG.obj \
					func_tbl.obj \
					m_weapon.obj \
					m_cpu2p.obj \
					menu.obj \
					G_MENU.obj \
					G_ENG.obj \
					G_GAME.obj \
					G_TURN.obj \
					G_HP.obj \
					G_FUNC.obj \
					G_SPACE.obj \
					G_AU1.obj \
					G_AU2.obj \
					G_AU3.obj \
					G_TITLE.obj \
					unisel.obj \
					G_UNISE2.obj \
					G_STGSEL.obj \
					stagesel.obj \
					tuneup.obj \
					G_TUNEUP.obj \
					story.obj \
					G_STORY.obj \
					G_FACE.obj \
					G_02.obj \
					G_04.obj \
					PUT_TEXT.obj \
					SOUND_CODE.obj \
					ending.obj \
					flash.obj \
					RAND.obj \
					SWAN_L_C.obj \
					LMUL.obj \
					STRING.obj \
					GENERAL.obj \
					MAINMAP.obj
	lcc86 -a$(CRT0) -m$(MODEL) -k "-Fh -T 0 -TDATA 10000 -TSAVE_DATA 11E00 -TTEXT 80000 -T_GHOST_DATA 9F000 -TRESET FFFF0 -TFAR_DATA A0000 -TFAR_DATA2 B0000 -TFAR_DATA3 C0000 -TFAR_DATA4 D0000 -TFAR_DATA5 E0000 -TFAR_DATA6 F0000 -TFAR_DATA7 F0000 -TFAR_DATA8 F0000 -TFAR_DATA9 F0000" -k-M -o $@ $#

armoredunit.bin: armoredunit.hex
	hex2bin -s 0000 -l 100000 -p FF armoredunit.hex

#Why does codegen chagne if we go straight to obj without making the .a86 for these
SWANMAIN.a86:  SWANMAIN.c
SYSTEM.a86:  SYSTEM.c
