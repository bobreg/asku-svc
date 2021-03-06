#include "../common/logger.h"
#include "../common/module.h"
#include "avt.h"

// ------------------------------------------------------------------
AVT::AVT(QObject * parent) : AVT_THREAD(parent)
{
}

// ------------------------------------------------------------------
AVT::~AVT()
{
}

// ------------------------------------------------------------------
void AVT::onChangedMain(bool on)
{
	emit sigSetMain(on);
}

// ------------------------------------------------------------------
