#include "timer.h"

uint32_t (*CTimer::getTickFunc)() = CTimer::defaultGetTickFunc;

/*---CLASS FUNCTIONS-------------------------------------*/
/*-------------------------------------------------------*/
void CTimer::classInit1000(uint32_t (*getterTick1000)())
{
    getTickFunc = getterTick1000;
}

/*-------------------------------------------------------*/
uint32_t CTimer::defaultGetTickFunc()
{
    return 0;
}

/*-------------------------------------------------------*/
uint32_t CTimer::getTick()
{
    return getTickFunc();
}

/*---OBJECT FUNCTIONS------------------------------------*/
/*-------------------------------------------------------*/
CTimer::CTimer(Unit unit)
{
    setCounterUnit(unit);
}

/*-------------------------------------------------------*/
void CTimer::setCounterUnit(Unit unit)
{
    turnOff();
    this->unit = unit;
}

/*-------------------------------------------------------*/
void CTimer::setCounterType(Unit unit)
{
    setCounterUnit(unit);
}

/*-------------------------------------------------------*/
void CTimer::start(uint32_t time)
{
	timState = TS_DOWNCOUNTING;
    startTick = getTick();
    duration = time;
}

/*-------------------------------------------------------*/
void CTimer::startAligned(uint32_t time)
{
    uint32_t timeSinceStart;
    uint32_t totalDuration;

    if (timState == TS_ELAPSED)
    {
        timeSinceStart = _getTimeSinceStart();
        totalDuration = duration + time;

        if (timeSinceStart >= totalDuration)
        {
            //ustawiany czas juz minal
            start(time);
        }
        else
        {
            timState = TS_DOWNCOUNTING;
            startTick += _timerUnits2ticks(duration);    //poprzednia wartosc m_duration
            duration = time;
        }
    }
    else
    {
        start(time);
    }
}

/*-------------------------------------------------------*/
void CTimer::startStrictAligned(uint32_t time)
{
    if (timState == TS_ELAPSED)
    {
        timState = TS_DOWNCOUNTING;
        startTick += _timerUnits2ticks(duration);    //poprzednia wartosc m_duration
        duration = time;
    }
    else
    {
        start(time);
    }
}

/*-------------------------------------------------------*/
void CTimer::changeOverallTime(uint32_t time)
{
    if (_isInDowncounterMode())
    {
        timState = TS_DOWNCOUNTING;
        duration = time;
    }
}

/*-------------------------------------------------------*/
void CTimer::startFreeRun()
{
    timState = TS_FREE_RUN;
    duration = 0;
    startTick = getTick();
}

/*-------------------------------------------------------*/
uint32_t CTimer::getOverallTime()
{
    uint32_t result = 0;

    //nie potrzebny _updateState
    if(_isInDowncounterMode())
    {
        result = duration;
    }
    return result;
}

/*-------------------------------------------------------*/
void CTimer::turnOff()
{
    timState = TS_OFF;
}

/*-------------------------------------------------------*/
bool CTimer::isTurnedOn()
{
    //nie potrzebny _updateState
    return (timState != TS_OFF);
}

/*-------------------------------------------------------*/
bool CTimer::isZero()
{
	bool isZeroFlag = false;

	_updateDowncounter();
	switch(timState)
	{
    case TS_ELAPSED:
    case TS_OFF:
        isZeroFlag = true;
        break;
    case TS_DOWNCOUNTING:
    case TS_FREE_RUN:
        break;
	}
	return isZeroFlag;
}

/*-------------------------------------------------------*/
bool CTimer::isGoingOn()
{
    return !isZero();
}

/*-------------------------------------------------------*/
bool CTimer::isElapsed()
{
    bool elapsedFlag = false;

    _updateDowncounter();
    switch(timState)
    {
    case TS_ELAPSED:
        elapsedFlag = true;
        break;
    case TS_OFF:
    case TS_DOWNCOUNTING:
    case TS_FREE_RUN:
        break;
    }
    return elapsedFlag;
}

/*-------------------------------------------------------*/
uint32_t CTimer::getElapsedTime()
{
    uint32_t elapsedTime;

    elapsedTime = _updateDowncounter();
    switch(timState)
    {
    case TS_DOWNCOUNTING:
        //elapsedTime ma juz wartosc
        break;
    case TS_ELAPSED:
        elapsedTime = duration;
        break;
    case TS_FREE_RUN:
        elapsedTime = _getTimeSinceStart();
        break;
    case TS_OFF:
        //elapsedTime ma juz wartosc
        break;
    }
    return elapsedTime;
}

/*-------------------------------------------------------*/
uint32_t CTimer::getRemainingTime()
{
    uint32_t remainingTime = 0;
    uint32_t elapsedTime;

    elapsedTime = _updateDowncounter();
    switch(timState)
    {
    case TS_DOWNCOUNTING:
        remainingTime = duration - elapsedTime;
        break;
    case TS_ELAPSED:
    case TS_FREE_RUN:
    case TS_OFF:
        //pozostaje wartosc 0
        break;
    }
    return remainingTime;
}

//--------PRIVATE----------------------------------------------------
/*-------------------------------------------------------*/
uint32_t CTimer::_getTimeSinceStart()
{
    uint32_t ticksDuration;
    uint32_t unitsDuration;

    ticksDuration = getTick() - startTick;
    unitsDuration = _ticks2timerUnits(ticksDuration);

    return unitsDuration;
}

/*-------------------------------------------------------*/
uint32_t CTimer::_updateDowncounter()
{
    uint32_t timeSinceStart = 0;

    switch(timState)
    {
    case TS_OFF:
        break;
    case TS_DOWNCOUNTING:
        timeSinceStart = _getTimeSinceStart();
        if (_isTimeElapsed(timeSinceStart))
        {
            timState = TS_ELAPSED;
        }
        break;
    case TS_ELAPSED:
    case TS_FREE_RUN:
        break;
    }

    return timeSinceStart;
}

/*-------------------------------------------------------*/
bool CTimer::_isInDowncounterMode()
{
    bool result = false;

    switch(timState)
    {
    case TS_DOWNCOUNTING:
    case TS_ELAPSED:
        result = true;
        break;
    case TS_FREE_RUN:
    case TS_OFF:
        result = false;
        break;
    }
    return result;
}

/*-------------------------------------------------------*/
bool CTimer::_isTimeElapsed(uint32_t _timeSinceStart)
{
    return _timeSinceStart >= duration;
}

/*-------------------------------------------------------*/
uint32_t CTimer::getFactor1000(Unit unit)
{
    uint32_t factor;

    switch (unit)
    {
        case UNIT_MILISEC:
            //0.001s <-> 0.001s
            factor = 1U;
            break;
        case UNIT_HUNDRETHS_SEC:
            //0.001s <-> 0.01s
            factor = 10U;
            break;
        case UNIT_TENTHS_SEC:
            //0.001s <-> 0.1s
            factor = 100U;
            break;
        case UNIT_SEC:
            //0.001s <-> 1s
            factor = 1000U;
            break;
        case UNIT_MIN:
            //0.001s <-> 1min
            factor = 60000U;
            break;
        case UNIT_HOUR:
            //0.001s <-> 1hour
            factor = 3600000U;
            break;
        default:
            factor = 1U;
            break;
    }
    return factor;
}

/*-------------------------------------------------------*/
uint32_t CTimer::_timerUnits2ticks(uint32_t timerUnits)
{
    return timerUnits * getFactor1000(unit);
}

/*-------------------------------------------------------*/
uint32_t CTimer::_ticks2timerUnits(uint32_t ticks)
{
    return ticks / getFactor1000(unit);
}


