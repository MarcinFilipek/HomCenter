/*
 * CQSPIDriver.cpp
 *
 *  Created on: 11 cze 2016
 *      Author: Marcin
 */

#include "CQSPIDriver.h"
#include "n25q128a.h"

QSPI_HandleTypeDef CQSPIDriver::m_QSPIHandle;

CQSPIDriver::CQSPIDriver() {
}

CQSPIDriver::~CQSPIDriver() {
	// TODO Auto-generated destructor stub
}

void CQSPIDriver::init(void){
	m_QSPIHandle.Instance = QUADSPI;
	HAL_QSPI_DeInit(&m_QSPIHandle);
	initPins();

	/* QSPI initialization */
	m_QSPIHandle.Init.ClockPrescaler = 1; /* QSPI freq = 216 MHz/(1+2) = 72 Mhz */
	m_QSPIHandle.Init.FifoThreshold = 4;
	m_QSPIHandle.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
	m_QSPIHandle.Init.FlashSize = POSITION_VAL(N25Q128A_FLASH_SIZE) - 1;
	m_QSPIHandle.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_2_CYCLE;
	m_QSPIHandle.Init.ClockMode = QSPI_CLOCK_MODE_0;
	m_QSPIHandle.Init.FlashID = QSPI_FLASH_ID_1;
	m_QSPIHandle.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
	if (HAL_QSPI_Init(&m_QSPIHandle)!= HAL_OK){
		while(1);
	}
	/* QSPI memory reset */
	resetMemory(&m_QSPIHandle);
	/* Configuration of the dummy cycles on QSPI memory side */
	dummyCyclesCfg(&m_QSPIHandle);
}
void CQSPIDriver::initPins() {
	GPIO_InitTypeDef gpioInitStruct;
	__HAL_RCC_QSPI_CLK_ENABLE()
	;
	__HAL_RCC_QSPI_FORCE_RESET();
	__HAL_RCC_QSPI_RELEASE_RESET();

	/* QSPI CS GPIO pin configuration  */
	gpioInitStruct.Pin = GPIO_PIN_6;
	gpioInitStruct.Mode = GPIO_MODE_AF_PP;
	gpioInitStruct.Pull = GPIO_PULLUP;
	gpioInitStruct.Speed = GPIO_SPEED_HIGH;
	gpioInitStruct.Alternate = GPIO_AF10_QUADSPI;
	HAL_GPIO_Init(GPIOB, &gpioInitStruct);

	/* QSPI CLK GPIO pin configuration  */
	gpioInitStruct.Pin = GPIO_PIN_2;
	gpioInitStruct.Pull = GPIO_NOPULL;
	gpioInitStruct.Alternate = GPIO_AF9_QUADSPI;
	HAL_GPIO_Init(GPIOB, &gpioInitStruct);

	/* QSPI D0 GPIO pin configuration  */
	gpioInitStruct.Pin = GPIO_PIN_11;
	gpioInitStruct.Alternate = GPIO_AF9_QUADSPI;
	HAL_GPIO_Init(GPIOD, &gpioInitStruct);

	/* QSPI D1 GPIO pin configuration  */
	gpioInitStruct.Pin = GPIO_PIN_12;
	gpioInitStruct.Alternate = GPIO_AF9_QUADSPI;
	HAL_GPIO_Init(GPIOD, &gpioInitStruct);

	/* QSPI D2 GPIO pin configuration  */
	gpioInitStruct.Pin = GPIO_PIN_2;
	gpioInitStruct.Alternate = GPIO_AF9_QUADSPI;
	HAL_GPIO_Init(GPIOE, &gpioInitStruct);

	/* QSPI D3 GPIO pin configuration  */
	gpioInitStruct.Pin = GPIO_PIN_13;
	gpioInitStruct.Alternate = GPIO_AF9_QUADSPI;
	HAL_GPIO_Init(GPIOD, &gpioInitStruct);

	/* NVIC configuration for QSPI interrupt */
	HAL_NVIC_SetPriority(QUADSPI_IRQn, 0x0F, 0);
	HAL_NVIC_EnableIRQ(QUADSPI_IRQn);
}

void CQSPIDriver::resetMemory(QSPI_HandleTypeDef *hqspi) {
	QSPI_CommandTypeDef s_command;

	/* Initialize the reset enable command */
	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction = RESET_ENABLE_CMD;
	s_command.AddressMode = QSPI_ADDRESS_NONE;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode = QSPI_DATA_NONE;
	s_command.DummyCycles = 0;
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	/* Send the command */
	if(HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!= HAL_OK)
		while(1);

	/* Send the reset memory command */
	s_command.Instruction = RESET_MEMORY_CMD;
	if(HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!= HAL_OK)
		while(1);

	/* Configure automatic polling mode to wait the memory is ready */
	autoPollingMemReady(hqspi, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}

void CQSPIDriver::autoPollingMemReady(QSPI_HandleTypeDef *hqspi, uint32_t Timeout) {
	QSPI_CommandTypeDef s_command;
	QSPI_AutoPollingTypeDef s_config;

	/* Configure automatic polling mode to wait for memory ready */
	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction = READ_STATUS_REG_CMD;
	s_command.AddressMode = QSPI_ADDRESS_NONE;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode = QSPI_DATA_1_LINE;
	s_command.DummyCycles = 0;
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	s_config.Match = 0;
	s_config.Mask = N25Q128A_SR_WIP;
	s_config.MatchMode = QSPI_MATCH_MODE_AND;
	s_config.StatusBytesSize = 1;
	s_config.Interval = 0x10;
	s_config.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

	if(HAL_QSPI_AutoPolling(hqspi, &s_command, &s_config, Timeout)!= HAL_OK)
		while(1);
}

void CQSPIDriver::dummyCyclesCfg(QSPI_HandleTypeDef *hqspi) {
	QSPI_CommandTypeDef s_command;
	uint8_t reg;

	/* Initialize the read volatile configuration register command */
	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction = READ_VOL_CFG_REG_CMD;
	s_command.AddressMode = QSPI_ADDRESS_NONE;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode = QSPI_DATA_1_LINE;
	s_command.DummyCycles = 0;
	s_command.NbData = 1;
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	/* Configure the command */
	if(HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!= HAL_OK)
		while(1);

	/* Reception of the data */
	if(HAL_QSPI_Receive(hqspi, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!= HAL_OK)
		while(1);

	/* Enable write operations */
	writeEnable(hqspi);

	/* Update volatile configuration register (with new dummy cycles) */
	s_command.Instruction = WRITE_VOL_CFG_REG_CMD;
	MODIFY_REG(reg, N25Q128A_VCR_NB_DUMMY,
			(N25Q128A_DUMMY_CYCLES_READ_QUAD << POSITION_VAL(N25Q128A_VCR_NB_DUMMY)));

	/* Configure the write volatile configuration register command */
	if(HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!= HAL_OK)
		while(1);

	/* Transmission of the data */
	if(HAL_QSPI_Transmit(hqspi, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!= HAL_OK)
		while(1);
}

void CQSPIDriver::writeEnable(QSPI_HandleTypeDef *hqspi) {
	QSPI_CommandTypeDef s_command;
	QSPI_AutoPollingTypeDef s_config;

	/* Enable write operations */
	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction = WRITE_ENABLE_CMD;
	s_command.AddressMode = QSPI_ADDRESS_NONE;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode = QSPI_DATA_NONE;
	s_command.DummyCycles = 0;
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	if(HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!= HAL_OK)
		while(1);

	/* Configure automatic polling mode to wait for write enabling */
	s_config.Match = N25Q128A_SR_WREN;
	s_config.Mask = N25Q128A_SR_WREN;
	s_config.MatchMode = QSPI_MATCH_MODE_AND;
	s_config.StatusBytesSize = 1;
	s_config.Interval = 0x10;
	s_config.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

	s_command.Instruction = READ_STATUS_REG_CMD;
	s_command.DataMode = QSPI_DATA_1_LINE;

	if(HAL_QSPI_AutoPolling(hqspi, &s_command, &s_config,
			HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!= HAL_OK)
		while(1);
}

void CQSPIDriver::memoryMappedMode(void) {
	QSPI_CommandTypeDef s_command;
	QSPI_MemoryMappedTypeDef s_mem_mapped_cfg;

	/* Configure the command for the read instruction */
	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction = QUAD_INOUT_FAST_READ_CMD;
	s_command.AddressMode = QSPI_ADDRESS_4_LINES;
	s_command.AddressSize = QSPI_ADDRESS_24_BITS;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode = QSPI_DATA_4_LINES;
	s_command.DummyCycles = N25Q128A_DUMMY_CYCLES_READ_QUAD;
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	/* Configure the memory mapped mode */
	s_mem_mapped_cfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_ENABLE;
	s_mem_mapped_cfg.TimeOutPeriod = 1;

	HAL_QSPI_MemoryMapped(&m_QSPIHandle, &s_command, &s_mem_mapped_cfg);
	/* Configure QSPI: LPTR register with the low-power time out value */
	WRITE_REG(QUADSPI->LPTR, 0xFFF);
}

void CQSPIDriver::read(uint8_t* pData, uint32_t ReadAddr, uint32_t Size) {
	QSPI_CommandTypeDef s_command;

	/* Initialize the read command */
	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction = QUAD_INOUT_FAST_READ_CMD;
	s_command.AddressMode = QSPI_ADDRESS_4_LINES;
	s_command.AddressSize = QSPI_ADDRESS_24_BITS;
	s_command.Address = ReadAddr;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode = QSPI_DATA_4_LINES;
	s_command.DummyCycles = N25Q128A_DUMMY_CYCLES_READ_QUAD;
	s_command.NbData = Size;
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	/* Configure the command */
	HAL_QSPI_Command(&m_QSPIHandle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

	/* Reception of the data */
	HAL_QSPI_Receive(&m_QSPIHandle, pData, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}

void CQSPIDriver::write(uint8_t* pData, uint32_t WriteAddr, uint32_t Size) {
	QSPI_CommandTypeDef s_command;
	uint32_t end_addr, current_size, current_addr;

	/* Calculation of the size between the write address and the end of the page */
	current_addr = 0;

	while (current_addr <= WriteAddr) {
		current_addr += N25Q128A_PAGE_SIZE;
	}
	current_size = current_addr - WriteAddr;

	/* Check if the size of the data is less than the remaining place in the page */
	if (current_size > Size) {
		current_size = Size;
	}

	/* Initialize the adress variables */
	current_addr = WriteAddr;
	end_addr = WriteAddr + Size;

	/* Initialize the program command */
	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction = EXT_QUAD_IN_FAST_PROG_CMD;
	s_command.AddressMode = QSPI_ADDRESS_4_LINES;
	s_command.AddressSize = QSPI_ADDRESS_24_BITS;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode = QSPI_DATA_4_LINES;
	s_command.DummyCycles = 0;
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	/* Perform the write page by page */
	do {
		s_command.Address = current_addr;
		s_command.NbData = current_size;

		/* Enable write operations */
		writeEnable(&m_QSPIHandle);

		/* Configure the command */
		HAL_QSPI_Command(&m_QSPIHandle, &s_command,
				HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

		/* Transmission of the data */
		HAL_QSPI_Transmit(&m_QSPIHandle, pData, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

		/* Configure automatic polling mode to wait for end of program */
		autoPollingMemReady(&m_QSPIHandle, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

		/* Update the address and size variables for next page programming */
		current_addr += current_size;
		pData += current_size;
		current_size =
				((current_addr + N25Q128A_PAGE_SIZE) > end_addr) ?
						(end_addr - current_addr) : N25Q128A_PAGE_SIZE;
	} while (current_addr < end_addr);
}

void CQSPIDriver::eraseBlock(uint32_t BlockAddress) {
	QSPI_CommandTypeDef s_command;

	/* Initialize the erase command */
	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction = SUBSECTOR_ERASE_CMD;
	s_command.AddressMode = QSPI_ADDRESS_1_LINE;
	s_command.AddressSize = QSPI_ADDRESS_24_BITS;
	s_command.Address = BlockAddress;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode = QSPI_DATA_NONE;
	s_command.DummyCycles = 0;
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	/* Enable write operations */
	writeEnable(&m_QSPIHandle);

	/* Send the command */
	HAL_QSPI_Command(&m_QSPIHandle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

	/* Configure automatic polling mode to wait for end of erase */
	autoPollingMemReady(&m_QSPIHandle, N25Q128A_SUBSECTOR_ERASE_MAX_TIME);
}

void CQSPIDriver::eraseChip(void) {
	QSPI_CommandTypeDef s_command;

	/* Initialize the erase command */
	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction = BULK_ERASE_CMD;
	s_command.AddressMode = QSPI_ADDRESS_NONE;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode = QSPI_DATA_NONE;
	s_command.DummyCycles = 0;
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	/* Enable write operations */
	writeEnable(&m_QSPIHandle);

	/* Send the command */
	HAL_QSPI_Command(&m_QSPIHandle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

	/* Configure automatic polling mode to wait for end of erase */
	autoPollingMemReady(&m_QSPIHandle, N25Q128A_BULK_ERASE_MAX_TIME);
}

CQSPIDriver::QSPIStatus CQSPIDriver::getStatus(void) {
	QSPI_CommandTypeDef s_command;
	uint8_t reg;

	/* Initialize the read flag status register command */
	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction = READ_FLAG_STATUS_REG_CMD;
	s_command.AddressMode = QSPI_ADDRESS_NONE;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode = QSPI_DATA_1_LINE;
	s_command.DummyCycles = 0;
	s_command.NbData = 1;
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	/* Configure the command */
	if (HAL_QSPI_Command(&m_QSPIHandle, &s_command,
			HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
		return ERROR;
	}

	/* Reception of the data */
	if (HAL_QSPI_Receive(&m_QSPIHandle, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
			!= HAL_OK) {
		return ERROR;
	}

	/* Check the value of the register */
	if ((reg
			& (N25Q128A_FSR_PRERR | N25Q128A_FSR_VPPERR | N25Q128A_FSR_PGERR
					| N25Q128A_FSR_ERERR)) != 0) {
		return ERROR;
	} else if ((reg & (N25Q128A_FSR_PGSUS | N25Q128A_FSR_ERSUS)) != 0) {
		return SUSPENDED;
	} else if ((reg & N25Q128A_FSR_READY) != 0) {
		return OK;
	} else {
		return BUSY;
	}
}

CQSPIDriver::QSPIInfo* CQSPIDriver::getInfo() {
	/* Configure the structure with the memory configuration */
	m_info.FlashSize = N25Q128A_FLASH_SIZE;
	m_info.EraseSectorSize = N25Q128A_SUBSECTOR_SIZE;
	m_info.EraseSectorsNumber = (N25Q128A_FLASH_SIZE / N25Q128A_SUBSECTOR_SIZE);
	m_info.ProgPageSize = N25Q128A_PAGE_SIZE;
	m_info.ProgPagesNumber = (N25Q128A_FLASH_SIZE / N25Q128A_PAGE_SIZE);

	return &m_info;
}

QSPI_HandleTypeDef* CQSPIDriver::getQspiHandle(){
	return &m_QSPIHandle;
}
