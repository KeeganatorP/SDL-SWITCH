#include "SDL_config.h"

#include <sys/time.h>
#include <switch.h>
#include <sys/select.h>


#include "SDL_thread.h"
#include "SDL_timer.h"
#include "SDL_error.h"
#include "../SDL_timer_c.h"

static bool started = false;

static Uint64 start = 0;

Uint64 SDL_GetPerformanceCounter(void)
{
    return svcGetSystemTick();
}

Uint64 SDL_GetPerformanceFrequency(void)
{
    return 19200000;
}

void SDL_TicksInit(void)
{
    if (started) {
        return;
    }

    start = SDL_GetPerformanceCounter();
    started = true;
}

void SDL_StartTicks (void) {
	SDL_TicksInit();
}

void SDL_TicksQuit(void)
{
    started = false;
}

Uint32 SDL_GetTicks(void)
{
    if (!started) {
        SDL_TicksInit();
    }

    return (Uint32) ((SDL_GetPerformanceCounter() - start) * 1000 / SDL_GetPerformanceFrequency());
}

void SDL_Delay(Uint32 ms)
{
    svcSleepThread((Uint64) ms * 1000000);
}

int SDL_SYS_TimerInit (void) {
	return 0;
}

void SDL_SYS_TimerQuit (void) {
}

int SDL_SYS_StartTimer (void) {
	SDL_SetError ("Timers not implemented on Switch");

	return -1;
}

void SDL_SYS_StopTimer (void) {
}

/*static struct timeval start;

void SDL_StartTicks (void) {
	gettimeofday (&start, NULL);
} // done

Uint32 SDL_GetTicks (void) {
	Uint32 ticks;
	struct timeval now;

	gettimeofday (&now, NULL);
	ticks = (now.tv_sec - start.tv_sec) * 1000 + (now.tv_usec - start.tv_usec) / 1000;

	return (ticks);
}

void SDL_Delay (Uint32 ms) {
		svcSleepThread((Uint64)ms * 1000000);
}

int SDL_SYS_TimerInit (void) {
	return 0;
}

void SDL_SYS_TimerQuit (void) {
}

int SDL_SYS_StartTimer (void) {
	SDL_SetError ("Timers not implemented on Switch");

	return -1;
}

void SDL_SYS_StopTimer (void) {
}
*/