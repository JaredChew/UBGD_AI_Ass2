#pragma once

#include <thread>
#include <cstdlib> 
#include <chrono>
#include <string>
#include <iostream>

#include <GLFW/glfw3.h>

#define MINIMUM_SLEEP_TIME 10000000.0

#define DYNAMIC_WINDOW_TITLE_SIZE 80

class Window {

private:

	GLFWwindow* wnd;
	GLFWwindow* share;

	GLFWmonitor* monitor;

	static int width;
	static int height;
	static int windowRatio;

	static int renderWidth;
	static int renderHeight;
	static int renderRatio;

	static int renderQuality;

	std::string title;
	char dynamicTitle[DYNAMIC_WINDOW_TITLE_SIZE];

	bool vsync;
	bool displayFps;
	//bool usingDynamicTitle;

	double fpsLimit;

	long double currentTime;
	long double totalFrames;
	long double targetDeltaTime;

	std::chrono::steady_clock::time_point tick;
	std::chrono::steady_clock::time_point tock;

	std::chrono::duration<long double, std::nano> deltaTime;
	std::chrono::duration<long double, std::nano> timeElapsed;
	std::chrono::duration<long double, std::nano> timeElapsedContinuous;

private:

	void recordTime();
	void limitFps();
	void fpsCounter();

	static void onWindowResized(GLFWwindow* window, int width, int height);

public:

	Window(const int &width, const int &height, const std::string &title, GLFWmonitor* const monitor, GLFWwindow* const share);
	~Window();

	bool successfulCreation();

	void update();

	void setVsync(const bool& onOff);
	void setFpsLimit(const double&fpsLimit);
	void setDisplayFps(const bool& displayFps);
	void setRenderQuality(const int& renderQuality);
	//void setDynamicTitle(const bool& dynamicTitle);

	int getWidth();
	int getHeight();
	int getWindowRatio();

	int getRenderWidth();
	int getRenderHeight();
	int getRenderRatio();

	long double getDeltaTime();
	long double getTimeElapsed();
	long double getContinuousTimeElapsed();

	GLFWwindow* getWindow() const;

};