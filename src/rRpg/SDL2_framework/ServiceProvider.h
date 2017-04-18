#ifndef __ServiceProvider__
#define __ServiceProvider__

#include "UserActions.h"

class ServiceProvider {
	public:
	static UserActions* getUserActions();
	static int setUserActions(const char* mappingFile);
	static void clean();
};

#endif
