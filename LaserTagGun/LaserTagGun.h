/*
 Name:		LaserTagGun.h
 Created:	11/8/2018 11:17:16 PM
 Author:	Josh
*/

#ifndef LaserTagGun_h
#define LaserTagGun_h

#include "arduino.h"

class LaserTagGun
{
public:
	LaserTagGun();
	void Fire(bool *data, int size);
	bool* Recive();
private:



};


#endif

