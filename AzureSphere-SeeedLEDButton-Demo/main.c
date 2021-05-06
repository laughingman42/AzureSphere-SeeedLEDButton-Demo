// This minimal Azure Sphere app prints "High Level Application" to the debug
// console and exits with status 0.
#include "hw/seeed_mt3620_mdb.h"

#include <applibs/log.h>
#include <stdbool.h>

#include <Sensors/GroveLEDButton.h>
#include <Common/Delay.h>


int main(void)
{
	Log_Debug("LED Button Application starting\n");

	void* btn = GroveLEDButton_Init(SEEED_MT3620_MDB_J1_PIN9_GPIO30, SEEED_MT3620_MDB_J1_PIN3_GPIO6);
	GPIO_Value_Type btn_sta, last_btn_sta;
	last_btn_sta = GroveLEDButton_GetBtnState(btn);

	int btncounter = 0;

	// Main loop
	while (true) {
		btn_sta = GroveLEDButton_GetBtnState(btn);

		if (btn_sta != last_btn_sta) {
			if (btn_sta == 0) {
				GroveLEDButton_LedOn(btn);
				Log_Debug("Button pressed.\n");
			}
			else {
				GroveLEDButton_LedOff(btn);
				Log_Debug("Button released.\n");
			}
			btncounter = btncounter + 1;
			Log_Debug("Counter: %d\n", btncounter);
		}
		last_btn_sta = btn_sta;

		usleep(1);
	}

	Log_Debug("Application exiting\n");
	return 0;
}
