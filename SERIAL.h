#ifndef SERIAL_H
#define SERIAL_H

void serial_init();
void serial_receive();
void serial_in();
void serial_out_sub();
void serial_out();
u16 serial_ver_info();
u16 serial_exist();
s16 serial_in_frag();

#endif
