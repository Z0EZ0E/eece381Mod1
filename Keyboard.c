#include <stdio.h>
#include "altera_up_avalon_ps2.h"
#include "altera_up_ps2_keyboard.h"

#define KEYBOARD_UP 0x75
#define KEYBOARD_DOWN 0x72
#define KEYBOARD_ENTER 0x5A

alt_up_ps2_dev *ps2;
KB_CODE_TYPE decode;
char ascii;
int keyboard_init = 1;

alt_u8 getKeyboard(){
	alt_u8 data;

	if (keyboard_init == 1){
	
		ps2 = alt_up_ps2_open_dev("/dev/ps2_0");
		
		alt_up_ps2_init(ps2); //initialize device
		if(ps2->device_type == PS2_KEYBOARD){
			printf("keyboard connected\n");
		}
		else if(ps2->device_type  == PS2_MOUSE ){
			printf("connected to mouse\n");
		}
		else if(ps2->device_type  == PS2_UNKNOWN){
			printf("unknown device\n");
		}
		else
			printf("Not connected\n");


		alt_up_ps2_clear_fifo(ps2); //clear buffer
		set_keyboard_rate(ps2, 0x00);
		keyboard_init = 0; //initialize device once per reset
	}
	decode_scancode(ps2, &decode, &data, &ascii);
	return data;
}

int main()
{


	unsigned int i=90000;

	while(1){
		if( i > 0)//keyboard read delay
			i--;
		else{
		
			//Read into keyboard
			alt_u8 data = getKeyboard();


			if (data == KEYBOARD_DOWN){
				printf("DOWN 0\n");
			}
			if (ascii != NULL){
				printf("%c\n",ascii);
			}
			if (data == KEYBOARD_ENTER){
				printf("Enter\n");
			}

			i = 90000;
		}
	}

	return 0;
}
