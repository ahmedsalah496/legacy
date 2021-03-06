#include <stdint.h>

#ifdef AVR
	#include <util/delay.h>
#endif

#include <string.h>
#include <stdlib.h>
#include "gui_lib/gui.h"
#include "touchscreen.h"
#include "menu_browser.h"
#include "netvar/netvar.h"
#include "lap_button.h"
#include "lap_slider.h"


#define BUTTON_WIDTH  46
#define BUTTON_HEIGHT 54

#define V_SLIDER_WIDTH  46
#define V_SLIDER_HEIGHT 200

#define H_SLIDER_WIDTH  200
#define H_SLIDER_HEIGHT 46


typedef struct {
	gui_container_t *main_container;
	//gui_container_t *element_container;
	uint8_t *dir_data;
	uint8_t *dir_position;
} menu_browser_state_t;

menu_browser_state_t state;

void parse_dir_to_main_container(uint8_t *dir_data) {

	gui_container_delete_all_childs(state.main_container);

	gui_container_t *akt_container = state.main_container;

	gui_container_t *container_stack[10];
	uint8_t stack_pointer = 0;

	uint8_t b;

	while ((b = *dir_data++) != 0) {
		switch (b) {
			case V_CONTAINER: {
				gui_container_t *c = new_gui_container();
				c->orientation = ORIENTATION_VERTICAL;
				container_stack[stack_pointer++] = akt_container;
				akt_container = c;
			} break;
			case H_CONTAINER: {
				gui_container_t *c = new_gui_container();
				c->orientation = ORIENTATION_HORIZONTAL;
				container_stack[stack_pointer++] = akt_container;
				akt_container = c;
			} break;
			case END_CONTAINER: {
				gui_container_t *new_container = akt_container;
				akt_container = container_stack[--stack_pointer];
				gui_container_add(akt_container, (gui_element_t *) new_container);
			} break;
			case GUI_BUTTON: {
				gui_button_t *b = new_gui_button();
				b->box.w = BUTTON_WIDTH;
				b->box.h = BUTTON_HEIGHT;
				b->text = (char *) dir_data;
				dir_data += strlen((char *) dir_data) + 1;
				gui_container_add(akt_container, (gui_element_t *) b);
			} break;
			case CAN_BUTTON: {
				char *txt = (char *) dir_data;
				dir_data += strlen(txt) + 1;
				uint16_t idx = *(uint16_t*)dir_data;
				dir_data += 2;
				uint8_t sidx = *(uint8_t *) dir_data;
				dir_data += 1;
				lap_button_t *b = new_lap_button(idx, sidx);
				b->text = txt; 
				b->box.w = BUTTON_WIDTH;
				b->box.h = BUTTON_HEIGHT;
				gui_container_add(akt_container, (gui_element_t *) b);
			} break;
			case CAN_V_SLIDER: {
				char *txt = (char *) dir_data;
				dir_data += strlen(txt) + 1;
				uint16_t idx = *(uint16_t *) dir_data;
				dir_data += 2;
				uint8_t sidx = *(uint8_t *) dir_data;
				dir_data += 1;
				lap_slider_t *b = new_lap_slider(idx, sidx);
				b->text = txt;
				b->box.w = V_SLIDER_WIDTH;
				b->box.h = V_SLIDER_HEIGHT;
				b->orientation = ORIENTATION_VERTICAL;
				b->min_value = 0;
				b->max_value = 255;
				b->value = 30;
				gui_container_add(akt_container, (gui_element_t *) b);
			} break;
			case CAN_H_SLIDER: {
				char *txt = (char *) dir_data;
				dir_data += strlen(txt) + 1;
				uint16_t idx = *(uint16_t *) dir_data;
				dir_data += 2;
				uint8_t sidx = *(uint8_t *) dir_data;
				dir_data += 1;
				lap_slider_t *b = new_lap_slider(idx, sidx);
				b->text = txt;
				b->box.w = H_SLIDER_WIDTH;
				b->box.h = H_SLIDER_HEIGHT;
				b->orientation = ORIENTATION_HORIZONTAL;
				b->min_value = 0;
				b->max_value = 255;
				b->value = 30;
				gui_container_add(akt_container, (gui_element_t *) b);
			} break;
			case V_SLIDER: {
				gui_slider_t *b = new_gui_slider();
				b->box.w = V_SLIDER_WIDTH;
				b->box.h = V_SLIDER_HEIGHT;
				b->text = (char *) dir_data;
				dir_data += strlen((char *) dir_data) + 1;
				gui_container_add(akt_container,(gui_element_t *) b);
				b->min_value = 0;
				b->max_value = 255;
				b->value = 30;
			} break;
			case H_SLIDER: {
				gui_slider_t *b = new_gui_slider();
				b->orientation = ORIENTATION_HORIZONTAL;
				b->box.w = 80;
				b->box.h = 32;
				b->text = (char *) dir_data;
				dir_data += strlen((char *) dir_data) + 1;
				gui_container_add(akt_container,(gui_element_t *) b);
				b->min_value = 0;
				b->max_value = 255;
				b->value = 30;
			} break;
		}
	}
}


void menu_browser_set_dir(uint8_t *dir_data) {
	state.dir_data = dir_data;
	parse_dir_to_main_container(dir_data);
}

void menu_browser_init() {
	state.main_container = new_gui_container();
	state.main_container->box.y = 32;
	state.main_container->box.w = 320;
	state.main_container->box.h = 210;
}


void menu_browser_draw() {
	state.main_container->draw( (gui_element_t *) state.main_container, 0);
}


void menu_browser_touch_handler(touch_event_t t) {
	if (state.main_container) {
		state.main_container->touch_handler((gui_element_t *) state.main_container, t);
	}
}
