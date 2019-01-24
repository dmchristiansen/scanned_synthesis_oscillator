/*
 * 
 * Author: Daniel Christiansen (christiansen.daniel@gmail.com)
 *
 *
 *
 */


#ifndef UI_EVENT_QUEUE_H
#define UI_EVENT_QUEUE_H

#include <functional>
#include <stdint.h>

enum EventType {
	CONTROL_BUTTON_PRESS = 0,
	CONTROL_BUTTON_HOLD,
	CONTROL_BUTTON_RELEASE,
	CONTROL_POT,
	CONTROL_SWITCH,
	CONTROL_UPDATE_TIMER
};

struct Event_t {
	EventType control;
	int32_t context;
	uint32_t timestamp;
};

template <size_t queue_size>
class EventQueue {

	private:

		Event_t EventList[queue_size];
		uint8_t read_ptr;
		uint8_t write_ptr;

	public:

		EventQueue() {read_ptr = 0; write_ptr = 0;};
		~EventQueue() {};
		void Init();

		uint8_t addEvent(EventType, int32_t, uint32_t);
		uint8_t doEvent();

		uint8_t eventCount() {return (write_ptr - read_ptr) % queue_size;};
		uint8_t queueFull() {return (read_ptr == ((write_ptr + 1) % queue_size));};
		uint8_t queueEmpty() {return (read_ptr == write_ptr);};

};

template <size_t queue_size> 
uint8_t EventQueue<queue_size>::addEvent(EventType control, int32_t context, uint32_t timestamp) {

	if (queueFull()) return 0;

	// Should this disable interrupts?
	// It should only be called from an interrupt context
	EventList[write_ptr].control = control;
	EventList[write_ptr].context = context;
	EventList[write_ptr].timestamp = timestamp;

	write_ptr = (write_ptr + 1) % queue_size;
		
	return 1;
}

template <size_t queue_size>
uint8_t EventQueue<queue_size>::doEvent() {
	if (queueEmpty()) return 0;

	// This should actually disable interrupts
	// Maybe? 
	Event_t event;
	event.control = EventList[read_ptr].control;
	event.context = EventList[read_ptr].context;
	event.timestamp = EventList[read_ptr].timestamp;

	read_ptr = (read_ptr + 1) % queue_size;

	switch (event.control) {	
		case (CONTROL_BUTTON_PRESS):
			break;
		case (CONTROL_BUTTON_HOLD):
			break;
		case (CONTROL_BUTTON_RELEASE):
			break;
		case (CONTROL_POT):
			break;
		case (CONTROL_SWITCH):
			break;
		case (CONTROL_UPDATE_TIMER):
			break;
	}

	return 1;
}

#endif
