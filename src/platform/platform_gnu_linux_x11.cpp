module platform; // We don't export as platform.cpp already exports it

// Use these definitions if and only if we're on GNU + Linux
#ifdef PLATFORM_GNU_LINUX_X11
import <iostream>;
import <cstdlib>;
import <cstring>;

#include <X11/Xlib.h>

namespace engine::platform
{
struct InternalState
{
  Display *display;
  int screen;
  Window window;
  GC graphics_context;
};

// Rutic X11 window
bool
init (PlatformState *platform_state, const char *window_name, int x, int y,
      int w, int h)
{
  platform_state->internal_state = malloc (sizeof (InternalState));
  InternalState *state = (InternalState *)platform_state->internal_state;

  state->display = XOpenDisplay (NULL);
  if (state->display == NULL)
    {
      std::cerr << "Failed to open X11 display\n";
      return false;
    }

  state->screen = DefaultScreen (state->display);

  // For testing
  unsigned long black = BlackPixel (state->display, state->screen),
                white = WhitePixel (state->display, state->screen);

  state->window = XCreateSimpleWindow (state->display,
                                       DefaultRootWindow (state->display), x,
                                       y, w, h, 5, white, black);

  XStoreName (state->display, state->window, window_name);

  XSelectInput (state->display, state->window, ExposureMask | KeyPressMask);
  XMapWindow (state->display, state->window);

  state->graphics_context = XCreateGC (state->display, state->window, 0, 0);

  XSetForeground (state->display, state->graphics_context,
                  WhitePixel (state->display, state->screen));

  return true;
}

void
shutdown (PlatformState *platform_state)
{
  InternalState *state = (InternalState *)platform_state->internal_state;

  XCloseDisplay (state->display);
  XFreeGC (state->display, state->graphics_context);
  XDestroyWindow (state->display, state->window);
  free (state);
}

bool
update (PlatformState *platform_state)
{
  InternalState *state = (InternalState *)platform_state->internal_state;

  const char *msg = "Hello, World!";

  bool running = true;
  XEvent e;
  while (XPending (state->display) > 0)
    {
      XNextEvent (state->display, &e);

      // Placeholder rendering event
      if (e.type == Expose)
        {
          XFillRectangle (state->display, state->window,
                          state->graphics_context, 20, 20, 10, 10);
          XDrawString (state->display, state->window, state->graphics_context,
                       10, 50, msg, strlen (msg));
        }

      // Close uppon any key press
      if (e.type == KeyPress)
        {
          running = false;
        }
    }

  return running;
}
}

#endif