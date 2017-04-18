#include "ServiceProvider.h"

static UserActions* s_userActions;

UserActions* ServiceProvider::getUserActions() {
	return s_userActions;
}

int ServiceProvider::setUserActions(const char* mappingFile) {
	delete s_userActions;
	s_userActions = new UserActions();
	return s_userActions->setActionsFromFile(mappingFile);
}

void ServiceProvider::clean() {
	free(s_userActions);
	s_userActions = 0;
}
