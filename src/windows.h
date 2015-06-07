#pragma once
#ifndef WINDOWS_H
#define WINDOWS_H

#include "types.h"
#include <CoreFoundation/CoreFoundation.h>

#if defined(_MSC_VER)
	#include "ms_stdbool.h"
#else
	#include <stdbool.h>
#endif

#ifdef __cplusplus
extern "C" 
{
#endif

struct _WindowDescription {
	uint16_t *name; //kCGWindowName
	uint32_t id; //kCGWindowNumber
	uint32_t pid; //kCGWindowOwnerPID
};

typedef struct _WindowDescription WindowDescription;
typedef WindowDescription *WindowDescriptionRef;

struct WindowDescriptionList {
	uint16_t count;
	WindowDescriptionRef* items;
};

typedef struct WindowDescriptionList WindowDescriptionList;

/* Creates new WindowDescription with the given values.
 *  * Follows the Create Rule (caller is responsible for destroy()'ing object). */
WindowDescriptionRef createWindowDescription(uint32_t id, uint16_t *name, uint32_t pid);

void destroyWindowDescription(WindowDescriptionRef window);

/* Returns the current windows */
WindowDescriptionList* getWindowList(void);

/* Convenience function that returns whether the given point is in the bounds
 * of the main screen. */
#ifdef __cplusplus
}
#endif

#endif /* WINDOWS_H */
