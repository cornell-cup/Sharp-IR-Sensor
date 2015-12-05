#include <gp2y0a.h>
#include <stdio.h>
#include <stdlib.h>
#include "mraa.hpp"
#include <iostream>
#include <unistd.h>
#include <math.h>



 // Instantiate a GP2Y0A on analog pin A1
	upm::GP2Y0A *volts = new upm::GP2Y0A(1);

// Define global variables for voltage
  double R,A,B,C,D;
  float V;

  int main(int argc, char **argv)
   {

	mraa_gpio_context PIN1 = mraa_gpio_init(13);
	mraa_gpio_dir(PIN1,MRAA_GPIO_OUT);
	mraa_gpio_context PIN2 = mraa_gpio_init(12);
	mraa_gpio_dir(PIN2,MRAA_GPIO_OUT);
	mraa_gpio_context PIN3 = mraa_gpio_init(7);
	mraa_gpio_dir(PIN3,MRAA_GPIO_OUT);

	  while (1)
		{

		 V	= volts->value(4.95,1);
		 sleep(1);


		 // Returns distance in units of cm.
		  A = 0.0082712905;
		  B = 939.57652;
		  C = -3.3978697;
		  D = 17.339222;
		  // Curve fit.
		  R = (A + B * V) / (1 + C * V + D * V * V);

		 printf ("2.Obstacle detected and input voltage is %.2f\t",V);
		 printf ("Distance = %.2f\n",R);

		 if (R<= 25){
			 mraa_gpio_write(PIN1,1);
		 }
		 else if (R>20 && R<=35){
			 mraa_gpio_write(PIN1,1);
			 mraa_gpio_write(PIN2,1);
		 }
		 else if(R>35){
			 mraa_gpio_write(PIN1,1);
			 mraa_gpio_write(PIN2,1);
			 mraa_gpio_write(PIN3,1);
		 }



		}
	  return(0);

   }
