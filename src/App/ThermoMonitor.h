/*
 * ThermoMonitor.h
 *
 *  Created on: 2015/03/26
 *      Author: sa
 */

#ifndef THERMOMONITOR_H_
#define THERMOMONITOR_H_

class ThermoMonitor {
	// Singleton pattern definition
private:
	ThermoMonitor();
	ThermoMonitor(const ThermoMonitor& rhs);
	ThermoMonitor& operator=(const ThermoMonitor& rhs);
	virtual ~ThermoMonitor() {}
public:
	static ThermoMonitor* GetInstance() {
		static ThermoMonitor instance;
		return &instance;
	}

	// Class definition
private:
	int getMkTemp();
	void thermoMonitorTask();
public:
	static void thermoMonitorTaskEntry(void* pvParameter);
	static void initThermoMonitor();
};

#endif /* THERMOMONITOR_H_ */
