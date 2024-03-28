# Copyright (C) 1999-2000 Qute Corporation. All rights reserved.
#
# makefile for samples/hello
#	$Id: $

CRT0=crt0.obj

CFLAGS=-I.\lsic86ws\include -L.\lsic86ws\lib
DEFINES=
MODEL=p

.obj.bin:
	lcc86 -m$(MODEL) -a$(CRT0) -k-M -o $*.bin $^

.c.obj:
	lcc86 -cv -m$(MODEL) -c $(CFLAGS) $(DEFINES) -o $@ $<

.c.a86:
	lcc86 -cv -m$(MODEL) -SC $(CFLAGS) $(DEFINES) -o $@ $<

default:	all

clean:
	$(RM) *.a86
	$(RM) *.obj
	$(RM) *.exe
	$(RM) *.bin

all:	clean crt0.obj armoredunit.hex armoredunit.bin

crt0.obj:	crt0.p86
	cpp -o crt0.a86 $<
	r86 -o $@ crt0.a86
	
DFONT_char_adr.obj:	DFONT_char_adr.p86
	cpp -o DFONT_char_adr.a86 $<
	r86 -o $@ DFONT_char_adr.a86
	
RAND.obj:	RAND.p86
	cpp -o RAND.a86 $<
	r86 -o $@ RAND.a86
	
LMUL.obj:	LMUL.p86
	cpp -o LMUL.a86 $<
	r86 -o $@ LMUL.a86
	
SOUND_CODE.obj:	SOUND_CODE.p86
	cpp -o SOUND_CODE.a86 $<
	r86 -o $@ SOUND_CODE.a86
	
MAINMAP.obj:	MAINMAP.p86
	cpp -o MAINMAP.a86 $<
	r86 -o $@ MAINMAP.a86

#armoredunit.bin:	SWANMAIN.obj DFONT_char_adr.obj SPRINTF.obj SYSTEM.obj PAD.obj MEMORY.obj select.obj ASM.obj SERIAL.obj IP_MES.obj DEBUG.obj CONSOLE.obj TITLE.obj LOGO.obj m_game.obj m_sub.obj m_weapon.obj m_cpu2p.obj menu.obj unisel.obj stagesel.obj tuneup.obj story.obj PUT_TEXT.obj SOUND_CODE.obj ending.obj flash.obj _GENETEXT.obj SWAN_L_C.obj _KNOTEXT.obj STRING.obj GENERAL.obj
#armoredunit.bin:	SWANMAIN.obj DFONT_char_adr.obj SPRINTF.obj SYSTEM.obj PAD.obj MEMORY.obj select.obj ASM.obj SERIAL.obj IP_MES.obj DEBUG.obj CONSOLE.obj TITLE.obj LOGO.obj m_game.obj m_sub.obj m_weapon.obj m_cpu2p.obj menu.obj unisel.obj stagesel.obj tuneup.obj story.obj PUT_TEXT.obj SOUND_CODE.obj ending.obj flash.obj RAND.obj SWAN_L_C.obj LMUL.obj
#armoredunit.bin:	SWANMAIN.obj DFONT_char_adr.obj SPRINTF.obj SYSTEM.obj SOUND_CODE.obj
#	lld -Fc $(LFLAGS) $(LLD_OPTS) -M -o $@ $(CRT0) snake.obj moveswan.obj -ldoslib
#	lcc86 -a$(CRT0) -m$(MODEL) -k "-Fc -TIRAM 0 -TDATA 10000 -TSAVE_DATA 11E00 -T 80000 -TRESETVEC FFFFF" -k-M -o $@ $#
#	lcc86 -a$(CRT0) -m$(MODEL) -k "-Fc -T 0 -TDATA 10000 -TSAVE_DATA 11E00 -TTEXT 80000 -T_GHOST_DATA 9F000 -TFAR_DATA A0000 -TFAR_DATA2 B0000 -TFAR_DATA3 C0000 -TFAR_DATA4 D0000 -TFAR_DATA5 E0000 -TFAR_DATA6 F0000 -TRESET FFFF0 -TFAR_DATA7 F0000 -TFAR_DATA8 F0000 -TFAR_DATA9 F0000" -k-M -o $@ $#
#	lcc86 -a$(CRT0) -m$(MODEL) -k "-Fc -T 0 -TDATA 10000" -k-M -o $@ $#

armoredunit.hex:	SWANMAIN.obj DFONT_char_adr.obj SPRINTF.obj SYSTEM.obj PAD.obj MEMORY.obj select.obj WORK.obj ASM.obj SERIAL.obj IP_MES.obj DEBUG.obj CONSOLE.obj TITLE.obj LOGO.obj m_game.obj m_sub.obj m_weapon.obj m_cpu2p.obj menu.obj unisel.obj stagesel.obj tuneup.obj story.obj PUT_TEXT.obj SOUND_CODE.obj ending.obj flash.obj RAND.obj SWAN_L_C.obj LMUL.obj STRING.obj GENERAL.obj MAINMAP.obj
	lcc86 -a$(CRT0) -m$(MODEL) -k "-Fh -T 0 -TDATA 10000 -TSAVE_DATA 11E00 -TTEXT 80000 -T_GHOST_DATA 9F000 -TFAR_DATA A0000 -TFAR_DATA2 B0000 -TFAR_DATA3 C0000 -TFAR_DATA4 D0000 -TFAR_DATA5 E0000 -TFAR_DATA6 F0000 -TRESET FFFF0 -TFAR_DATA7 F0000 -TFAR_DATA8 F0000 -TFAR_DATA9 F0000" -k-M -o $@ $#

armoredunit.bin: armoredunit.hex
	hex2bin -s 0000 -l 100000 -p FF armoredunit.hex

SWANMAIN.a86:  SWANMAIN.c
SPRINTF.a86:  SPRINTF.c
SYSTEM.a86:  SYSTEM.c
PAD.a86:  PAD.c
MEMORY.a86:  MEMORY.c
select.a86:  select.c
WORK.a86:  WORK.c
ASM.a86:  ASM.c
SERIAL.a86:  SERIAL.c
IP_MES.a86:  IP_MES.c
DEBUG.a86:  DEBUG.c
CONSOLE.a86:  CONSOLE.c
TITLE.a86:  TITLE.c
LOGO.a86:  LOGO.c
m_game.a86:  m_game.c
m_sub.a86:  m_sub.c
m_weapon.a86:  m_weapon.c
m_cpu2p.a86:  m_cpu2p.c
menu.a86:  menu.c
unisel.a86:  unisel.c
stagesel.a86:  stagesel.c
tuneup.a86:  tuneup.c
story.a86:  story.c
PUT_TEXT.a86:  PUT_TEXT.c
ending.a86:  ending.c
flash.a86:  flash.c
_GENETEXT.a86:  _GENETEXT.c
SWAN_L_C.a86:  SWAN_L_C.c
_KNOTEXT.a86:  _KNOTEXT.c
STRING.a86:  STRING.c
GENERAL.a86:  GENERAL.c


SWANMAIN.obj:  SWANMAIN.a86
SPRINTF.obj:  SPRINTF.a86
SYSTEM.obj:  SYSTEM.a86
PAD.obj:  PAD.a86
MEMORY.obj:  MEMORY.a86
select.obj:  select.a86
WORK.obj:  WORK.a86
ASM.obj:  ASM.a86
SERIAL.obj:  SERIAL.a86
IP_MES.obj:  IP_MES.a86
DEBUG.obj:  DEBUG.a86
CONSOLE.obj:  CONSOLE.a86
TITLE.obj:  TITLE.a86
LOGO.obj:  LOGO.a86
m_game.obj:  m_game.a86
m_sub.obj:  m_sub.a86
m_weapon.obj:  m_weapon.a86
m_cpu2p.obj:  m_cpu2p.a86
menu.obj:  menu.a86
unisel.obj:  unisel.a86
stagesel.obj:  stagesel.a86
tuneup.obj:  tuneup.a86
story.obj:  story.a86
PUT_TEXT.obj:  PUT_TEXT.a86
ending.obj:  ending.a86
flash.obj:  flash.a86
_GENETEXT.obj:  _GENETEXT.a86
SWAN_L_C.obj:  SWAN_L_C.a86
_KNOTEXT.obj:  _KNOTEXT.a86
STRING.obj:  STRING.a86
GENERAL.obj:  GENERAL.a86

