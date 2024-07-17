// https://logikara.blog/m5stack-lcd-setting/#mokuji_2
//
#include <M5StickCPlus.h>

float accX		= 0;
float accY		= 0;
float accZ		= 0;
float max_accX	= 0;
float max_accY	= 0;
float max_accZ	= 0;

int g_nAxis		= 0;
#define	AXIS_X		0
#define	AXIS_Y		1
#define	AXIS_Z		2
#define	NUM_AXIS	3

int g_nLoopIdx	= 0;
int	g_nLoopMax	= 10;

#define	DELAY_MS	100

////////////////////////////////////////
//
void setup()
{
	M5.begin();
	M5.Imu.Init();
	M5.Lcd.setRotation(3);
}

////////////////////////////////////////
//
void loop()
{
	M5.update();
	if (M5.BtnA.wasReleased()) {
		g_nAxis++;
		if (g_nAxis >= NUM_AXIS)
			g_nAxis = 0;
		g_nLoopIdx = g_nLoopMax - 1;
	}

	if (M5.BtnB.wasReleased()) {
		if (g_nLoopMax < 10)
			g_nLoopMax += 1;
		else
			g_nLoopMax += 10;

		if (g_nLoopMax > 100)
			g_nLoopMax = 1;
		g_nLoopIdx = g_nLoopMax - 1;
	}

	M5.Imu.getAccelData(&accX, &accY, &accZ);

	if (max_accX < accX)
		max_accX = accX;
	if (max_accY < accY)
		max_accY = accY;
	if (max_accZ < accZ)
		max_accZ = accZ;

	g_nLoopIdx++;
	if (g_nLoopIdx >= g_nLoopMax) {
		g_nLoopIdx = 0;

		switch (g_nAxis) {
			case AXIS_X:
				M5.Lcd.setTextFont(4);
				M5.Lcd.setCursor(10, 00);
				M5.Lcd.printf("X : %d ms   ", g_nLoopMax * DELAY_MS);
				M5.Lcd.setTextFont(8);
				M5.Lcd.setCursor(10, 30);
				M5.Lcd.printf("%04.0f", abs(max_accX * 1000));
				break;
			case AXIS_Y:
				M5.Lcd.setTextFont(4);
				M5.Lcd.setCursor(10, 00);
				M5.Lcd.printf("Y : %d ms   ", g_nLoopMax * DELAY_MS);
				M5.Lcd.setTextFont(8);
				M5.Lcd.setCursor(10, 30);
				M5.Lcd.printf("%04.0f", abs(max_accY * 1000));
				break;
			case AXIS_Z:
				M5.Lcd.setTextFont(4);
				M5.Lcd.setCursor(10, 0);
				M5.Lcd.printf("Z : %d ms   ", g_nLoopMax * DELAY_MS);
				M5.Lcd.setTextFont(8);
				M5.Lcd.setCursor(10, 30);
				M5.Lcd.printf("%04.0f", abs(max_accZ * 1000));
				break;
		}
		max_accX = 0;
		max_accY = 0;
		max_accZ = 0;

	}
	delay(DELAY_MS);
}
