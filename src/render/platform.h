// Header that contains the platform-specific rendering code.
// Implementations are in the platform/ subdir.

namespace platform
{

	typedef void *PLATFORM_WINDOW_REF;

	// initialise the platform
	void InitPlatform();

	// Creates a window with the specified width and height.
	// Title may be omitted.
	PLATFORM_WINDOW_REF CreatePlatformWindow(int width, int height, const char *title="Platforrmer");

	// Updates events, and returns true if the window should close
	bool PollPlatformWindow(PLATFORM_WINDOW_REF window);

	// Presents the window to the forefront.
	void PresentPlatformWindow(PLATFORM_WINDOW_REF window);

	// Cleans up everything.
	void TerminatePlatform();

}