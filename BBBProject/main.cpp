#include <iostream>
#include <unistd.h>
#include "BlackGPIO.h"
#include "BlackTime.h"
#include "BlackPWM.h"
#include "BlackADC.h"

using namespace BlackLib;
using namespace std;

int main(void) {

	
	BlackTime myTime(8,12,40);
	BlackPWM myPWM(P9_14);
	BlackGPIO PINx(GPIO_51, output, SecureMode);
	BlackADC myADC(AIN5);

	myPWM.setDutyPercent(0);

	myTime.start();
	BlackTimeElapsed et = myTime.restart();
	int lastSec, currentSec;
	lastSec = et.miliSecond;
	PINx.setValue(low);
	for (;;) {
		et = myTime.elapsed();
		currentSec = et.miliSecond;
		if (currentSec>500) {
			lastSec += currentSec;
			PINx.toggleValue();
			myPWM.setDutyPercent(myADC.getNumericValue() / 18);
			cout << "elapsed milisecond :" << et.miliSecond << endl;
			cout << "PWM duty cycle :" << myPWM.getValue() << endl;
			et = myTime.restart();
		}
		
		//cout << "ADC Value: " << myADC.getNumericValue() << endl;
		//usleep(1000);
	}
}