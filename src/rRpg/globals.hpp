#ifndef __GLOBALS__
#define __GLOBALS__

#if GCW
const bool FULL_SCREEN = true;
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;
#else
const bool FULL_SCREEN = false;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
#endif
const char * const GAME_DATA_FOLDER = ".rrpg/";

#endif
