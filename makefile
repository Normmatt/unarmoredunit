# Copyright (C) 1999-2000 Qute Corporation. All rights reserved.
#
# makefile for samples/hello
#	$Id: $

.SUFFIXES: .bin .char .obj .p86 .a86 .d86 .c

CRT0=crt0.obj

CFLAGS=-I.\lsic86ws\include -L.\lsic86ws\lib
DEFINES=
MODEL=p

#Add -g for line info
.c.obj:
	lcc86 -O -B -cv -m$(MODEL) -c $(CFLAGS) $(DEFINES) -o $@ $<
	obj2asm.exe $@ -c$*.cod

.c.a86:
	lcc86 -O -B -cv -m$(MODEL) -SC $(CFLAGS) $(DEFINES) -o $@ $<

.a86.obj:
	r86 $(AFLAGS) -o $@ $<
	obj2asm.exe $@ -c$*.cod

.char.obj:
	python bin2d86.py $*.char
	r86 $(AFLAGS) -o $*.obj $*.d86

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

all:  crt0.obj armoredunit.hex armoredunit.bin compare

crt0.obj:	crt0.p86
	cpp -o crt0.a86 $<
	r86 -o $@ crt0.a86

OBJS= 	SWANMAIN.obj \
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
		G_06.obj \
		G_08.obj \
		G_10.obj \
		G_12.obj \
		G_14.obj \
		G_16.obj \
		G_18.obj \
		G_20.obj \
		G_01.obj \
		G_03.obj \
		G_05.obj \
		G_07.obj \
		G_09.obj \
		G_11.obj \
		G_13.obj \
		G_15.obj \
		G_17.obj \
		G_19.obj \
		PUT_TEXT.obj \
		SOUND_CODE.obj \
		SOUND_DATA.obj \
		G_EFEC0.obj \
		G_EFEC1.obj \
		G_EFEC21.obj \
		G_EFEC22.obj \
		G_EFEC3.obj \
		G_EFEC41.obj \
		G_EFEC42.obj \
		G_EFEC5.obj \
		G_EFEC61.obj \
		G_EFEC62.obj \
		G_EFEC71.obj \
		G_EFEC72.obj \
		G_EFEC8.obj \
		G_MSG.obj \
		G_FON16H.obj \
		G_FON16L.obj \
		G_ENDING.obj \
		ending.obj \
		flash.obj \
		_GENETEXT.obj \
		SWAN_L_C.obj \
		LMUL.obj \
		STRING.obj \
		GENERAL.obj \
		MAINMAP.obj

armoredunit.hex:	crt0.obj $(OBJS)
	lcc86 -a$(CRT0) -m$(MODEL) -k "-Fh -T 0 -TDATA 10000 -TSAVE_DATA 11E00 -TTEXT 80000 -T_GHOST_DATA 9F000 -TRESET FFFF0 -TFAR_DATA A0000 -TFAR_DATA2 B0000 -TFAR_DATA3 C0000 -TFAR_DATA4 D0000 -TFAR_DATA5 E0000 -TFAR_DATA6 F0000 -TFAR_DATA7 F0000 -TFAR_DATA8 F0000 -TFAR_DATA9 F0000" -k-M -o $@ @objs.txt

armoredunit.bin: armoredunit.hex
	hex2bin -s 0000 -l 100000 -p FF armoredunit.hex

compare:
	sha1sum -c armoredunit.sha1

#Why does codegen chagne if we go straight to obj without making the .a86 for these
SWANMAIN.a86:  SWANMAIN.c
SYSTEM.a86:  SYSTEM.c
CONSOLE.a86:  CONSOLE.c
stagesel.a86:  stagesel.c
SPRINTF.a86:  SPRINTF.c
