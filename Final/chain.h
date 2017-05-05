// Sam Erie
// CS 372
// Hartman
// Final
// 5/4/17
// Clock Demonstration to showcase Chain of Responsibility
// Had trouble coming up with toy program, I think this fits design pattern 
// Kind of a stretch but way more entertaining than doing something by random number

#pragma once

//Average NanoSeconds per Iteration, set specific to machine
//to make clock semi-accurate
//did manage to align with stopwatch on my phone
const double nsPerIter = 4.3;

//circular dependancies
//if this were a bigger project I would have
//made some sort of proxy wrapper for the handlers
class SmallClockHand;
class ClockHand;
//these are made just above main in chain.cpp
extern SmallClockHand _nsHandle;
extern ClockHand _msHandle;
extern ClockHand _secHandle;
extern ClockHand _minHandle;
extern ClockHand _hrHandle;

//This is the base
class Clock
{
protected:
	Clock * _next;

	unsigned int _time=0,
				 _interval=0;
	bool _tick=true;

	void printTime();
	unsigned int getTime();
	bool getTick();

public:

	virtual ~Clock()=default;
	Clock();

	virtual void handle();
	void start();

};

//Clockhands are the handlers
class SmallClockHand: public Clock
{
public:
	SmallClockHand(unsigned int interval, Clock *next);
	void handle() override;
};

class ClockHand: public Clock
{
public:
	ClockHand(unsigned int interval, Clock *next);
	void handle() override;
};
