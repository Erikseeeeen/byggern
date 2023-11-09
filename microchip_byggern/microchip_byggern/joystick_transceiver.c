
#include "joystick_transceiver.h"

void joystick_loop(input_t input, int current_menu)
{
	can_message msg;
	msg.id = 0;
	msg.data_length = 4;
	
	msg.data[0] = input.slider_2;
	msg.data[1] = input.joystick_x;
	msg.data[2] = input.button_left;
	msg.data[3] = current_menu;
	
	//printf("Joystick x: %8d y: %8d                                                ", input.joystick_x, input.joystick_y);
	//printf("Button   l: %8d r: %8d                                                ", input.button_left, input.button_right);
	//printf("Slider   1: %8d 2: %8d                                                ", input.slider_1, input.slider_2);
	
	can_message_send(msg);
}
