#include "windows.h"
#include "os.h"
#include <stdio.h>

#if defined(IS_MACOSX)
	#include <ApplicationServices/ApplicationServices.h>
	#include <CoreFoundation/CoreFoundation.h>
#elif defined(USE_X11)
	#include <X11/Xlib.h>
	#include "xdisplay.h"
#endif

WindowDescriptionRef createWindowDescription(uint32_t id, uint16_t *name, uint32_t pid)
{
	WindowDescriptionRef window = malloc(sizeof(WindowDescription));
	if (window == NULL) return NULL;

	window->id = id;
	window->name = name;
	window->pid = pid;

	return window;
}

void destroyWindowDescription(WindowDescriptionRef window)
{
	if (window->name != NULL) {
		free(window->name);
		window->name = NULL;
	}
	free(window);
}

WindowDescriptionList* getWindowList(void)
{
#if defined(IS_MACOSX)
	CFArrayRef windows = CGWindowListCopyWindowInfo(kCGWindowListExcludeDesktopElements, kCGNullWindowID);
	uint16_t count = CFArrayGetCount(windows);
	WindowDescriptionRef* descriptions = calloc(count, sizeof(WindowDescriptionRef*));
	WindowDescriptionRef* description = descriptions;

	for (int i=0; i<count; i++) {
		CFDictionaryRef item = CFArrayGetValueAtIndex(windows, i);
		int id = 0, pid = 0;
		CFNumberGetValue(CFDictionaryGetValue(item, kCGWindowNumber), kCFNumberIntType, &id);
		CFNumberGetValue(CFDictionaryGetValue(item, kCGWindowOwnerPID), kCFNumberIntType, &pid);

		CFStringRef nameString = CFDictionaryGetValue(item, kCGWindowName);

		if (nameString != NULL) {
			const UniChar* name = CFStringGetCharactersPtr(nameString);
			*description = createWindowDescription(id, name, pid);
		} else {
			*description = createWindowDescription(id, NULL, pid);
		}
		description++;
	}

	WindowDescriptionList* list = malloc(sizeof(WindowDescriptionList*));
	list->count = count;
	list->items = descriptions;
	return list;
#elif defined(USE_X11)
	return NULL;
#elif defined(IS_WINDOWS)
	return NULL;
#endif
}

