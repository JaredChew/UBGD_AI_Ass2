#include "window.h"

int Window::width;
int Window::height;
int Window::windowRatio;

int Window::renderWidth;
int Window::renderHeight;
int Window::renderRatio;
int Window::renderQuality;

Window::Window(const int& width, const int& height, const std::string &title, GLFWmonitor* const monitor, GLFWwindow* const share) {

	wnd = glfwCreateWindow(width, height, title.c_str(), monitor, share);

	this->width = width;
	this->height = height;

	this->windowRatio = width / height;

	setRenderQuality(100);

	this->title = title;

	this->monitor = monitor;
	this->share = share;

	vsync = false;
	displayFps = false;

	renderQuality = 100;

	fpsLimit = 0.0;
	totalFrames = 0.0;

	targetDeltaTime = 0;
	currentTime = 0;

	deltaTime = std::chrono::duration<long double, std::nano>(0.0);

	timeElapsed = std::chrono::duration<long double, std::nano>(0.0);

	timeElapsedContinuous = std::chrono::duration<long double, std::nano>(0.0);

	// Hook window resize.
	glfwSetWindowSizeCallback(wnd, onWindowResized);

	tock = std::chrono::high_resolution_clock::now();
	tick = std::chrono::high_resolution_clock::now();

}

Window::~Window() {

	glfwDestroyWindow(wnd);

}

void Window::recordTime() {

	deltaTime = tock - tick;

	timeElapsed += deltaTime;

	timeElapsedContinuous += deltaTime;

}

void Window::limitFps() {

	std::chrono::steady_clock::time_point tock2;

	while (currentTime < targetDeltaTime) {

		if (targetDeltaTime - currentTime > MINIMUM_SLEEP_TIME) { //1000000.0

			std::chrono::duration<double, std::nano> deltaTargetCurrent(0.7 * (targetDeltaTime - currentTime));
			std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTargetCurrent));

		}

		tock2 = std::chrono::high_resolution_clock::now();
		currentTime = std::chrono::duration<long double, std::nano>(tock2 - tock).count();

	}

	//printf("currentTime: %f | targetDeltaTime: %f", currentTime, targetDeltaTime);

}

void Window::fpsCounter() {

	currentTime = deltaTime.count();

	if (fpsLimit > 0.0) { limitFps(); }

	totalFrames = 1000000000.0 / currentTime;

	if (displayFps) {
		sprintf(dynamicTitle, "%s | FPS: %f", title.c_str(), totalFrames);
		glfwSetWindowTitle(wnd, dynamicTitle);
		//printf("\nFrames: %f\n\n", totalFrames);
	}

}

void Window::onWindowResized(GLFWwindow* window, int widthResize, int heightResize) {

	if (heightResize == 0) heightResize = 1;						// Prevent A Divide By Zero By making Height Equal One

	width = widthResize;
	height = heightResize;

	windowRatio = width / height;

	renderWidth = width * (renderQuality / 100);
	renderHeight = height * (renderQuality / 100);

	renderRatio = renderWidth / renderHeight;

	glViewport(0, 0, width, height);					// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	//gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix

}

bool Window::successfulCreation() {
	return !wnd ? false : true;
}

void Window::update() {

	tock = std::chrono::high_resolution_clock::now();

	recordTime();
	fpsCounter();

	tick = std::chrono::high_resolution_clock::now(); //tock;

}

void Window::setVsync(const bool& vsync) {

	this->vsync = vsync;

	glfwSwapInterval(vsync);

}

void Window::setFpsLimit(const double& fpsLimit) {

	this->fpsLimit = fpsLimit;

	targetDeltaTime = 1000000000.0 / fpsLimit;

}

void Window::setDisplayFps(const bool& displayFps) {
	this->displayFps = displayFps;
}

void Window::setRenderQuality(const int& renderQuality) {

	this->renderQuality = renderQuality;

	if (this->renderQuality <= 0) { this->renderQuality = 1; }

	renderWidth = width * (renderQuality / 100);
	renderHeight = height* (renderQuality / 100);

	renderRatio = renderWidth / renderHeight;

}

int Window::getWidth() {
	return width;
}

int Window::getHeight() {
	return height;
}

int Window::getWindowRatio() {
	return windowRatio;
}

int Window::getRenderWidth() {
	return renderWidth;
}

int Window::getRenderHeight() {
	return renderHeight;
}

int Window::getRenderRatio() {
	return renderRatio;
}

long double Window::getDeltaTime() {
	return deltaTime.count();
}

long double Window::getTimeElapsed() {
	return timeElapsed.count();
}

long double Window::getContinuousTimeElapsed() {
	return timeElapsedContinuous.count();
}

GLFWwindow *Window::getWindow() const {
	return wnd;
}