#include "../unmap_all.h"  // for ClearUnmapAllWindowsState, InitUnmapAllWin...

#include <X11/Xlib.h>  // for XCloseDisplay, XGrabServer, XOpenDisplay
#include <stdio.h>     // for NULL, fprintf, stderr

int main(int argc, char **unused_argv) {
  (void)unused_argv;
  Display *display = XOpenDisplay(NULL);
  if (display == NULL) {
    fprintf(stderr, "Could not connect to $DISPLAY.\n");
    return 1;
  }
  UnmapAllWindowsState state;
  XGrabServer(display);
  // Without argument: remap application windows; with argument: remap all
  // toplevel windows.
  InitUnmapAllWindowsState(&state, display, DefaultRootWindow(display), NULL, 0,
                           NULL, NULL, argc > 1);
  UnmapAllWindows(&state, NULL, NULL);
  RemapAllWindows(&state);
  XUngrabServer(display);
  ClearUnmapAllWindowsState(&state);
  XCloseDisplay(display);
  return 0;
}
