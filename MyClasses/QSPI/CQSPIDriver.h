/*
 * CQSPIDriver.h
 *
 *  Created on: 11 cze 2016
 *      Author: Marcin
 */

#ifndef QSPI_CQSPIDRIVER_H_
#define QSPI_CQSPIDRIVER_H_

#include "stm32f7xx.h"

class CQSPIDriver {
public:
	CQSPIDriver();
	virtual ~CQSPIDriver();

	/* QSPI Info */
	typedef struct {
		uint32_t FlashSize; /*!< Size of the flash */
		uint32_t EraseSectorSize; /*!< Size of sectors for the erase operation */
		uint32_t EraseSectorsNumber; /*!< Number of sectors for the erase operation */
		uint32_t ProgPageSize; /*!< Size of pages for the program operation */
		uint32_t ProgPagesNumber; /*!< Number of pages for the program operation */
	} QSPIInfo;

	/* QSPI Status */
	typedef enum {
		OK = 0, ERROR = 1, BUSY = 2, NOT_SUPPORTED = 4, SUSPENDED = 8
	} QSPIStatus;
	void init(void);
	void memoryMappedMode(void);
	static QSPI_HandleTypeDef* getQspiHandle(void);
private:
	static QSPI_HandleTypeDef m_QSPIHandle;
	QSPIInfo m_info;

	void read(uint8_t* pData, uint32_t ReadAddr, uint32_t Size);
	void write(uint8_t* pData, uint32_t WriteAddr, uint32_t Size);
	void eraseBlock(uint32_t BlockAddress);
	void eraseChip(void);
	QSPIStatus getStatus(void);
	QSPIInfo* getInfo(void);

	void initPins(void);
	void resetMemory(QSPI_HandleTypeDef *hqspi);
	void autoPollingMemReady(QSPI_HandleTypeDef *hqspi, uint32_t Timeout);
	void dummyCyclesCfg(QSPI_HandleTypeDef *hqspi);
	void writeEnable(QSPI_HandleTypeDef *hqspi);
protected:
};

#endif /* QSPI_CQSPIDRIVER_H_ */
