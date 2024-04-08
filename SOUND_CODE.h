#ifndef SOUND_CODE_H
#define SOUND_CODE_H

void bgmreq(u8 val);
void sereq(u8 val);

void SOUND_INIT();
void SDREQ();
void SOUND();
void VOREQ();
void VOICE();
void CHECK_VOICE();
void CHECK_SE();

#endif
