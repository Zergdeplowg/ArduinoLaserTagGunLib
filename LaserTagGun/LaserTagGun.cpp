/*
 Name:		LaserTagGun.cpp
 Created:	11/8/2018 11:17:16 PM
 Author:	Josh
 Editor:	http://www.visualmicro.com
*/

#include "LaserTagGun.h"

LaserTagGun::LaserTagGun(int id)
{
	this->id = id;
}

void LaserTagGun::setupData()
{
	outputData = convertIntToBinary(damage);
	dataLength = 8;
	outputData = appendData(outputData, convertIntToBinary(team));
	outputData = appendData(outputData, convertIntToBinary(id));
}

void LaserTagGun::setTriggerPin(int pin, bool checkState)
{
	triggerPin = pin;
	triggerCheckState = checkState;
}

void LaserTagGun::setHitPin(int pin, bool checkState)
{
	hitPin = pin;
	hitCheckState = checkState;
}

void LaserTagGun::setReloadPin(int pin, bool checkState)
{
	reloadPin = pin;
	reloadCheckState = checkState;
}

void LaserTagGun::setIrOutPin(int pin)
{
	irOutPin = pin;
}

void LaserTagGun::update()
{
	if (digitalRead(hitPin) == hitCheckState)
	{
		inputData = Recive();
		if (inputData != NULL)
		{
			handleDamage(convertToInt(inputData, 0, 8));
			lastHit = millis();
		}
	}
	if(digitalRead(triggerPin) == triggerCheckState & millis()-lastShot > 300 & !(ammo <= 0))
	{
		Fire();
		lastShot = millis();
		lastCharge = lastShot + (shieldRechargeDelay * 1000);
		ammo--;
	}
	if(digitalRead(reloadPin) == reloadCheckState & millis() - lastReload > 300)
	{
		ammo = maxAmmo;
		lastReload = millis();
	}


	if(millis()-lastHit > shieldRechargeDelay*1000)
	{
		if(shield < maxShield)
		{
			if (millis() - lastCharge > 0)
			{
				shield += (shieldRecharge / 1000)*(millis() - lastCharge);
				lastCharge = millis();
			}
		}
	}
}

void LaserTagGun::handleDamage(int damageRecived)
{
	shield -= damageRecived;
	if (shield < 0)
	{
		health += shield;
		shield = 0;
	}
}

int * LaserTagGun::appendData(int * a, int * b)
{
	int* nData = new int[dataLength + 8];
	for(int i = 0; i < dataLength; i ++)
		nData[i] = a[i];
	for (int i = 0; i < 8; i++)
		nData[dataLength + i] = b[i];
	dataLength += 8;
	return nData;
}

void LaserTagGun::Fire()
{
	tone(irOutPin, IrFequency);
	delayMicroseconds(IrPulse*2);
	noTone(irOutPin);
	delayMicroseconds(IrPulse*0.83);
	for (int i = 0; i < dataLength; i++)
	{
		if(outputData[i] == 1)
		{
			tone(irOutPin, IrFequency);
			delayMicroseconds(IrPulse*2);
			noTone(irOutPin);
		}
		else
		{
			tone(irOutPin, IrFequency);
			delayMicroseconds(IrPulse);
			noTone(irOutPin);
		}
		delayMicroseconds(IrPulse*0.83);
	}
}

int * LaserTagGun::Recive()
{
	int* data = new int[dataLength];
	int t;
	for (int i = 0; i < dataLength; i++)
	{
		t = pulseIn(hitPin, LOW);
		if (t > 1000)
			data[i] = 1;
		else if (t > 0)
			data[i] = 0;
		else if (t == 0)
		{
			return NULL;
		}
	}
	return data;
}

void LaserTagGun::setTeam(int teamId)
{
	team = teamId;
}

void LaserTagGun::setDamage(int damage)
{
	this->damage = damage;
}

void LaserTagGun::setHealth(float health)
{
	this->health = health;
}

void LaserTagGun::setMaxHealth(float maxHealth)
{
	this->maxHealth = maxHealth;
}

void LaserTagGun::setAmmo(int ammo)
{
	this->ammo = ammo;
}

void LaserTagGun::setMaxAmmo(int maxAmmo)
{
	this->maxAmmo = maxAmmo;
}

void LaserTagGun::setShield(float shield)
{
	this->shield = shield;
}

void LaserTagGun::setMaxShield(float maxShield)
{
	this->maxShield = maxShield;
}

void LaserTagGun::setShieldRecharge(float rate)
{
	shieldRecharge = rate;
}

void LaserTagGun::setShieldRechargeDelay(float delayT)
{
	shieldRechargeDelay = delayT;
}

int LaserTagGun::getTeam()
{
	return team;
}

int LaserTagGun::getDamage()
{
	return damage;
}

int LaserTagGun::getHealth()
{
	return health;
}

int LaserTagGun::getMaxHealth()
{
	return maxHealth;
}

int LaserTagGun::getAmmo()
{
	return ammo;
}

int LaserTagGun::getMaxAmmo()
{
	return maxAmmo;
}

int LaserTagGun::getShield()
{
	return shield;
}

int LaserTagGun::getMaxShield()
{
	return maxShield;
}


int * LaserTagGun::convertIntToBinary(int num)
{
	int *bList = new int[8];
	for(int i = 0; i < 8; i++)
	{
		if (num % 2 == 0)
			bList[i] = 1;
		else
			bList[i] = 0;
		num = num / 2;
		if (num == 0)
			break;
	}
	int* output = new int[8];
	for(int i = 0; i < 8; i++)
	{
		output[i] = bList[7 - i];
	}
	return output;
}

int LaserTagGun::convertToInt(int* data, int low, int high)
{
	int num = 0;
	int multi = 64;
	for (int i = low; i < high; i++)
	{
		if(data[i] == 1)
		{
			num += multi;
		}
		multi = multi / 2;
	}
}