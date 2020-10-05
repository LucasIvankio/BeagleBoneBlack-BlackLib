#include <iostream>
#include "BlackGPIO.h"
#include "BlackTime.h"

using namespace BlackLib;
using namespace std;

int main(void) {

	BlackGPIO PINx(GPIO_51, output, SecureMode);
	BlackTime myTime(8,12,40);

	myTime.start();
	BlackTimeElapsed et = myTime.restart();
	int lastSec, currentSec;
	lastSec = et.second;
	PINx.setValue(high);
	for (;;) {
		et = myTime.elapsed();
		currentSec = et.second;
		if (currentSec != lastSec) {
			lastSec = currentSec;
			PINx.toggleValue();
			cout << "elapsed second :" << et.second << endl;
		}
	}
}