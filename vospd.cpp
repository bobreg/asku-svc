#include "../common/logger.h"
#include "../common/module.h"
#include "vospd.h"

// ------------------------------------------------------------------
VOSPD::VOSPD(QObject * parent) : VOSPD_THREAD(parent)
{
}

// ------------------------------------------------------------------
VOSPD::~VOSPD()
{
}

// ------------------------------------------------------------------
void VOSPD::onChangedMain(bool on)
{
	emit sigSetMain(on);
}

// ------------------------------------------------------------------
void VOSPD::onChangedAzimuthSource(quint32 channel)
{
	emit sigChangedAzimuthSource(channel);
}

// ------------------------------------------------------------------
