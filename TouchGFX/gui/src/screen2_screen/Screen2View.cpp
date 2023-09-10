#include <gui/screen2_screen/Screen2View.hpp>
#include "cmsis_os.h"

extern osMessageQueueId_t Queue1Handle;
Screen2View::Screen2View()
{
	tickCount = 0;
//	tickCount_1 = 0;
}

void Screen2View::setupScreen()
{
	localImageX = presenter->GetImageX();
    Screen2ViewBase::setupScreen();
    lamb.setX(14);
    lamb.setY(0);
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
    presenter->UpdateImageX(localImageX);
}

void Screen2View::handleTickEvent()
{
	Screen2ViewBase::handleTickEvent();

	tickCount++;
	switch (tickCount % 5)
	{
	case 0:
		track0.setVisible(true);
		track4.setVisible(false);
		break;
	case 1:
		track1.setVisible(true);
		track0.setVisible(false);
		break;
	case 2:
		track2.setVisible(true);
		track1.setVisible(false);
		break;
	case 3:
		track3.setVisible(true);
		track2.setVisible(false);
		break;
	case 4:
		track4.setVisible(true);
		track3.setVisible(false);
		break;
	default:
		break;
	}

	lamb.setY(tickCount*2%320);
	lamb.setX(tickCount*2/320%4*60+15);


	uint8_t res = 0;
	uint32_t count = osMessageQueueGetCount(Queue1Handle);
	if(count > 0) {

		osMessageQueueGet(Queue1Handle, &res, NULL, osWaitForever);
		if(res == 'R') {
			int16_t x = image1.getX();
			x += 2;
			if(x > 240) {
				x = 200;
			}
			image1.setX(x);
		}
			if(res == 'L') {
			int16_t x = image1.getX();
			x -= 2;
			if(x < 0) {
				x = 20;
			}
			image1.setX(x);
		}
	}
	invalidate();
}
