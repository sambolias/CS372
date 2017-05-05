#include "chain.h"
#include <iostream>
using std::cout;
#include <iomanip>
using std::setw;

////////Base/////////

Clock::Clock()
{
	_next = 0;
}
	
void Clock::handle()
{
	_next->handle();
}

void Clock::start()
{
	while(true)
	{
		if(_nsHandle.getTick())
		{
			printTime();
		}

		handle();
	}
}

void Clock::printTime()
{
	cout<<setw(2)<<_hrHandle.getTime()<<":"<<setw(2)<<_minHandle.getTime()<<":"
	<<setw(2)<<_secHandle.getTime()<<"."<<_msHandle.getTime()/100<<"\n";
}

unsigned int Clock::getTime()
{
	return _time;
}

bool Clock::getTick()
{
	return _tick;
}

///////Handles///////

SmallClockHand::SmallClockHand(unsigned int interval, Clock *next)
{
	_next = next;
	_interval=interval;
}

void SmallClockHand::handle()
{
	static double time=0;
	time+=nsPerIter;

	static int msCounter=0;
	const int msPerTick=100;

	if(time >= _interval)
	{
		time=0;
		msCounter++;
		if(msCounter >= msPerTick)
		{
			_tick=true;
			msCounter=0;
		}
		Clock::handle();
	}
	else _tick=false;
}

ClockHand::ClockHand(unsigned int interval, Clock *next)
{
	_next = next;
	_interval=interval;
}

void ClockHand::handle()
{
	_time++;
	if(_time >= _interval)
	{
		_time=0;		
		Clock::handle();
	}
}

//Global Handler objects for clockhands

SmallClockHand _nsHandle(1000000, &_msHandle);
ClockHand _msHandle(1000, &_secHandle);
ClockHand _secHandle(60, &_minHandle);
ClockHand _minHandle(60, &_hrHandle);
ClockHand _hrHandle(24, &_nsHandle);	

////////Main//////////

int main()
{
	cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
		<<"! Warning: this program never ends!\n"
		<<"! press ctrl^c to exit            !\n"
		<<"! press enter to start clock      !\n"
		<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";

	while(std::cin.get() != 10);

	//If I had more time maybe some proxy to deal with the handlers
	//instead of this confusing call
	_nsHandle.start();

	return 0;
}