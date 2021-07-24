#include"p_sensor.h"

int read_sensor()
{
	int p_val;
	p_val= getPressureVal();
	return p_val;
}