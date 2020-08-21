#include "svcapplication.h"

//-----------------------------------
int main(int argc, char *argv[])
{
	CHECK_FORK(argc, argv);
	AskuSvcApplication app(argc, argv);
	return app.exec();
}

//-----------------------------------
