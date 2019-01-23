/*
 Name:		LaserTagGun.h
 Created:	11/8/2018 11:17:16 PM
 Author:	Josh
*/

#ifndef LaserTagGun_h
#define LaserTagGun_h

#include "Arduino.h"
//"C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\Arduino.h"

class LaserTagGun
{
public:

	// must call these to set up your gun
	LaserTagGun(int id);
	void setupData(); // if using custom settings call after setting varables
	void setTriggerPin(int pin, bool checkState);
	void setHitPin(int pin, bool checkState);
	void setReloadPin(int pin, bool checkState);
	void setIrOutPin(int pin);


	// run only if using default settings.
	void update();

	// default way of handleing damage
	void handleDamage(int damageRecived);

	// use when customizeing your gun
	void Fire();
	int* Recive();

	// use to setup a custom gun
	void setTeam(int teamId);
	void setDamage(int damage);
	void setHealth(float health);
	void setMaxHealth(float maxHealth);
	void setAmmo(int ammo);
	void setMaxAmmo(int maxAmmo);
	void setShield(float shield);
	void setMaxShield(float maxShield);
	void setShieldRecharge(float rate);
	void setShieldRechargeDelay(float delayT);

	int getTeam();
	int getDamage();
	int getHealth();
	int getMaxHealth();
	int getAmmo();
	int getMaxAmmo();
	int getShield();
	int getMaxShield();

	// handy functions for handleing data
	int* convertIntToBinary(int num);
	int convertToInt(int* data, int low, int high);
	int* appendData(int* a, int* b);

private:
	int maxAmmo = 30;
	int ammo = 30;
	float maxShield = 100;
	float shield = 100;
	float shieldRecharge = 10;
	float shieldRechargeDelay = 5;
	float maxHealth = 100;
	float health = 100;
	bool triggerCheckState = LOW;
	int triggerPin;
	bool hitCheckState = LOW;
	int hitPin;
	bool reloadCheckState = LOW;
	int reloadPin;
	int irOutPin;
	int dataLength;
	int IrFequency = 57000;
	int IrPulse = 600;
	int damage = 25;
	int id;
	int team = 0;
	int* inputData;
	int* outputData;
	int lastHit = 0;
	int lastShot = 0;
	int lastCharge = 0;
	int lastReload = 0;



};


#endif

