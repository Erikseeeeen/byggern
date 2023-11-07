
#include "pwm.h"
#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))


void pwm_init()
{
	// Disable PIO, enable peripheral B
	PIOC->PIO_PDR |= PIO_PDR_P19;
	PIOC->PIO_ABSR |= PIO_ABSR_P19;
	
	// Enable peripheral clock
	PMC->PMC_PCR |= (ID_PWM << PMC_PCR_PID_Pos) | PMC_PCR_DIV_PERIPH_DIV_MCK | PMC_PCR_EN;
	PMC->PMC_PCER1 |= (1 << (ID_PWM-32));
	
	// Disable write protection
	PIOC->PIO_WPMR = 0;
	PWM->PWM_WPCR = 0;
	
	// Enable clock A, divide by 84
	PWM->PWM_CLK = PWM_CLK_DIVA(84) | PWM_CLK_PREA(0);
	
	// Set PWM clock source/prescaler to master clock
	PWM->PWM_CH_NUM[5].PWM_CMR = PWM_CMR_CPRE_CLKA;
	
	// servo period, duty cycle
	servo_period = 20E-3 * F_CPU / 84;
	PWM->PWM_CH_NUM[5].PWM_CPRD = PWM_CPRD_CPRD(servo_period);
	PWM->PWM_CH_NUM[5].PWM_CDTY = PWM_CDTY_CDTY((uint32_t)((float)servo_period * (1 - pos_to_duty(joystick_x))));
	set_servo_duty();
	
	// Set dead time
	//PWM->PWM_CH_NUM[5].PWM_DT = 0;
	
	// Enable PWM
	PWM->PWM_ENA = PWM_ENA_CHID5;
}


void set_servo_duty()
{
	// printf("%d    ",joystick_x);
	PWM->PWM_CH_NUM[5].PWM_CDTY = PWM_CDTY_CDTY((uint32_t)((float)servo_period * (1 - pos_to_duty(joystick_x))));
}

float pos_to_duty(uint8_t pos)
{
	return (float)CLAMP(pos, 0, 255) / 255.0 * 0.05 + 0.05;
}

// Enable PWM clock

