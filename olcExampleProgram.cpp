#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <thread>

#define N_THREADS 12
#define DEEP_ZOOM false

class Example : public olc::PixelGameEngine
{
public:
	double camPos[2] = { 0, 0 };
	double defaultBounds[4] = { -2.5, 1, -1, 1 };
	
	static void threadDrawRow(void* obj, int y, int interval, double xItrVal, double yItrVal, double xLow, double yLow, double invZoom) {
		((Example* )obj)->drawRow(y, interval, xItrVal, yItrVal, xLow, yLow, invZoom);
	}

	void drawRow(int y, int interval, double xItrVal, double yItrVal, double xLow, double yLow, double invZoom) {
		while (y < ScreenHeight()) {
			double y0 = yLow + y * yItrVal;
			for (int x = 0; x < ScreenWidth(); x++) {
				double x0 = xLow + x * xItrVal;
				drawMandelBrotPixel(x, y, x0, y0, invZoom);
			}
			y += interval;
		}
	}

	void drawMandelBrotPixel(int x, int y, double x0, double y0, double invZoom) {
		double a = x0;
		double b = y0;
		double maxItr = 1500;
		int i = 0;
		double divBound = 4;

		while (a * a + b * b <= divBound && i < maxItr) {
			i++;
			double temp = a * a - b * b;
			b = 2 * a * b + y0;
			a = temp + x0;
		}

		double quotient = i / maxItr;

		double r;
		double g;
		double blu;

		if (i == maxItr) {
			r = g = blu = 0;
		}
		else if (quotient > 0.5) {
			r = 1;
			g = quotient * invZoom;
			blu = 1;
		}
		else {
			r = sqrt(quotient);
			g = 0;
			blu = sqrt(quotient);

		}

		Draw(x, y, olc::Pixel(r * 255, g * 255, blu * 255));
	}

	void drawMandlebrot(double camPos[2], double zoom) {
		double invZoom = 1 / zoom;

		double xLow = camPos[0] + defaultBounds[0] * invZoom;
		double xHigh = camPos[0] + defaultBounds[1] * invZoom;
		double yLow = camPos[1] + defaultBounds[2] * invZoom;
		double yHigh = camPos[1] + defaultBounds[3] * invZoom;

		double xItrVal = (xHigh - xLow) / ScreenWidth();
		double yItrVal = (yHigh - yLow) / ScreenHeight();

		//drawRow(0, 1, xItrVal, yItrVal, xLow, yLow);
		std::thread* threads[N_THREADS];
		for (int i = 0; i < N_THREADS; i++) {
			threads[i] = new std::thread(threadDrawRow, this, i, N_THREADS, xItrVal, yItrVal, xLow, yLow, invZoom);
		}

		for (int i = 0; i < N_THREADS; i++) {
			threads[i]->join();
			delete threads[i];
		}
	}

public:
	Example()
	{
		sAppName = "Mandlebrot";
	}

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		static double zoom = 0.25;
		static double camPos[2]{ 0.023323, 0.813299 };
		drawMandlebrot(camPos, zoom);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		static double zoom = 0.25;
		static double camPos[2]{ -1.785940, 0.000344};
		bool lclick = GetMouse(0).bPressed;
		bool rclick = GetMouse(1).bPressed;
		if (DEEP_ZOOM) {
			zoom += fElapsedTime * zoom / 10;
			drawMandlebrot(camPos, zoom);
		}
		if (lclick || rclick) {
			
			if (lclick) {
				double invZoom = 1 / zoom;

				double xLow = camPos[0] + defaultBounds[0] * invZoom;
				double xHigh = camPos[0] + defaultBounds[1] * invZoom;
				double yLow = camPos[1] + defaultBounds[2] * invZoom;
				double yHigh = camPos[1] + defaultBounds[3] * invZoom;

				camPos[0] = xLow + ((xHigh - xLow) * GetMouseX()) / (ScreenWidth());
				camPos[1] = yLow + ((yHigh - yLow) * GetMouseY()) / (ScreenHeight());
				zoom *= 1.1;

			}
			else {
				zoom /= 1.1;
			}
			drawMandlebrot(camPos, zoom);
			printf("%f, %fi\n", camPos[0], camPos[1]);
		}
		// called once per frame
		return true;
	}
};


int main()
{
	Example demo;
	if (demo.Construct(1200, 800, 1, 1))
		demo.Start();

	return 0;
}
