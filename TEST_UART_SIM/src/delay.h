/*
 * delay.h
 *
 *  Created on: Sep 23, 2014
 *      Author: HaDuong
 */

#ifndef DELAY_H_
#define DELAY_H_

#define delay_ms(ms)    {SysCtlDelay(ms * (SysCtlClockGet() / 3000));}
#define delay_us(us)    {SysCtlDelay(us * ((SysCtlClockGet() / 3000)/1000));}
#define delay_s(s)	{SysCtlDelay(s * (SysCtlClockGet() / 3));}

#endif /* DELAY_H_ */
