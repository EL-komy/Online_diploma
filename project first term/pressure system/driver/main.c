#include <stdint.h>
#include <stdio.h>

#include "driver.h"
#include "p_alarm.h"
#include "p_sensor.h"


int main ()
{
	int p_val,threshold=20;
	GPIO_INITIALIZATION();
	while (1)
	{
		p_val= read_sensor();
		if(p_val>threshold)
		{
		    alarm_tern_on();
		    Delay(200);
		    alarm_tern_off();
		    Delay(200);
		}
		else
		{
			alarm_tern_off();
		}
		Delay(2000);
	}

}
