#ifndef SWAN_L_C_H
#define SWAN_L_C_H

#include "types.h"

extern u16 v_blank_cnt_count;
extern u16 v_blank_int_count;
extern u16 h_blank_cnt_count;
extern u16 sr_count;
extern u16 sw_count;
extern u16 int_frag;
extern vu8 int_enable;

void font_load();
void put_sprite();
void pad_in();
void get_cell_no();
void put_cell_no();
void far_strcpy();
void font_put();
void bitmap();
void put_cell_pixel();
void get_bmp_cell_pixel();
void get_cel_no_offset();
void get_cell_pixel_offset();
void memset();
void serial_send_cause();
void key_create_cause();
void casette_int_cause();
void serial_receive_cause();
void display_data_cause();
void v_brank_cnt_cause();
void v_brank_int_cause();
void h_brank_cnt_cause();
void interrupt_init();
void interrupt_main0();
void interrupt_main3();
void interrupt_main5();
void interrupt_main6();
void interrupt_main7();
void e2lib_i_read();

#endif
