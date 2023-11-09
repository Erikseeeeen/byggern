#include "menu.h"



const char* menu_items[2][1] = {
	{
		"play"
	},
	{
		"return to menu"
	},
};
const MENU_INFO menu_info[2] = {
	{ .number_of_items=3, .select_jump={1, 1, 1, 0, 0} },
	{ .number_of_items=3, .select_jump={0, 0, 0, 0, 0} }
};

void menu_init()
{
	selected_position = 0;
	current_menu = 0;
	OLED_pos(0, 0);
	OLED_reset();
}
void menu_input_loop(input_t input)
{
	if(input.direction == UP && last_input.direction != UP)
	{
		selected_position = MAX(selected_position-1, 0);
		printf("UP %d", selected_position);
	}
	if(input.direction == DOWN && last_input.direction != DOWN)
	{
		selected_position = MIN(selected_position+1, 2);
		printf("DOWN %d", selected_position);
	}
	
	if(input.button_right && (!last_input.button_right))
	{
		current_menu = menu_info[current_menu].select_jump[selected_position];
		/*can_message msg;
		msg.id = 0;
		msg.data_length = 1;
		
		msg.data[0] = current_menu;
		printf("msg id: %8d data_length: %8d                                                ", msg.id, msg.data_length);
		
		
		//printf("Joystick x: %8d y: %8d                                                ", input.joystick_x, input.joystick_y);
		//printf("Button   l: %8d r: %8d                                                ", input.button_left, input.button_right);
		//printf("Slider   1: %8d 2: %8d                                                ", input.slider_1, input.slider_2);
		
		can_message_send(msg);*/
		
	}
	
	/*printf("Joystick x: %8d y: %8d                                                ", input.joystick_x, input.joystick_y);
	printf("Button   l: %8d r: %8d                                                ", input.button_left, input.button_right);
	printf("Slider   1: %8d 2: %8d                                                ", input.slider_1, input.slider_2);*/
	last_input = input;
}
void menu_draw_loop(input_t input)
{
	//if(input.direction != last_input.direction || input.button_left != last_input.button_left)
	//{
	OLED_reset();
	//}
	
	for(int row = 0; row < 1; row++)
	{
		OLED_pos(10 + row*8, 10);
		OLED_print(menu_items[current_menu][row]);
	}
	OLED_print_arrow(10 + selected_position*8, 0);
}