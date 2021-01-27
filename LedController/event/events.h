#ifndef EVENTS_H
#define EVENTS_H

typedef enum
{
	evButtonIrqId = 1,
	evButtonPressedId,
	evButtonReleasedId,
	tmDebounceId,
	evButtonLongPressedId,
	evButtonShortPressedId,
	tmOnLedId,
	tmOffLedId

} EventIds;

#endif // EVENTS_H
