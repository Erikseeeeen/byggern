
#ifndef CAN_H_
#define CAN_H_

typedef struct can_message {
	uint16_t id ;
	char data_length ;
	char data [8];
} can_message;

void can_init();
void can_message_send();
char* can_data_receive();
void can_int_vect();



#endif /* CAN_H_ */