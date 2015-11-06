/*
 * VoltageMonitor.h
 *
 *  Created on: 2015/03/25
 *      Author: sa
 */

#ifndef VOLTAGEMONITOR_H_
#define VOLTAGEMONITOR_H_

class VoltageMonitor {
	// Singleton pattern definition
private:
	VoltageMonitor();
	VoltageMonitor(const VoltageMonitor& rhs);
	VoltageMonitor& operator=(const VoltageMonitor& rhs);
	virtual ~VoltageMonitor() {}
public:
	static VoltageMonitor* GetInstance() {
		static VoltageMonitor instance;
		return &instance;
	}

	// Class definition
private:
	static const uint32_t MV_ALART_VOLTAGE = 7200; 
	
	uint32_t mvOffset = 500;
	uint32_t VoltageMonitor::getMvVoltage();
	void voltageMonitorTask();
public:
	static void voltageMonitorTaskEntry(void* pvParameters);
	static void initVoltageMonitor();
};

	

#endif /* VOLTAGEMONITOR_H_ */
