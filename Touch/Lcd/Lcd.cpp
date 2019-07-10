/*
 * Lcd.cpp
 *
 *  Created on: 31 sie 2016
 *      Author: Uzume
 */

#include "Lcd.h"
#include <cstdarg>
#include "../Touch.h"
#include "cmsis_os.h"

uint16_t Lcd::m_width;
uint16_t Lcd::m_height;
uint32_t Lcd::m_layer1Address = 0xC0000000;
uint8_t Lcd::m_bitDepth;

Lcd::Lcd() {
	setBitDepth(16);
	m_layer1Enable = true;
	m_layer2Enable = false;
}

Lcd::~Lcd() {
	// TODO Auto-generated destructor stub
}

void Lcd::clockConfig(){
	RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;
	/* LCD clock configuration */
	/* PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz */
	/* PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAIN = 192 Mhz */
	/* PLLLCDCLK = PLLSAI_VCO Output/PLLSAIR = 192/5 = 38.4 Mhz */
	/* LTDC clock frequency = PLLLCDCLK / LTDC_PLLSAI_DIVR_4 = 38.4/4 = 9.6Mhz */
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
	PeriphClkInitStruct.PLLSAI.PLLSAIN = 192;
	PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
	PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_4;
	HAL_RCCEx_PeriphCLKConfig (&PeriphClkInitStruct);
}


void Lcd::initialize(uint16_t width, uint16_t height) {
	m_width = width;
	m_height = height;

	clockConfig();
	pinsInit();
	/* LTDC Initialization -------------------------------------------------------*/

	  /* Polarity configuration */
	  /* Initialize the horizontal synchronization polarity as active low */
	m_hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
	  /* Initialize the vertical synchronization polarity as active low */
	m_hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
	  /* Initialize the data enable polarity as active low */
	m_hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
	  /* Initialize the pixel clock polarity as input pixel clock */
	m_hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;

	  /* The RK043FN48H LCD 480x272 is selected */
	  /* Timing Configuration */
	m_hltdc.Init.HorizontalSync = (RK043FN48H_HSYNC - 1);
	m_hltdc.Init.VerticalSync = (RK043FN48H_VSYNC - 1);
	m_hltdc.Init.AccumulatedHBP = (RK043FN48H_HSYNC + RK043FN48H_HBP - 1);
	m_hltdc.Init.AccumulatedVBP = (RK043FN48H_VSYNC + RK043FN48H_VBP - 1);
	m_hltdc.Init.AccumulatedActiveH = (RK043FN48H_HEIGHT + RK043FN48H_VSYNC + RK043FN48H_VBP - 1);
	m_hltdc.Init.AccumulatedActiveW = (RK043FN48H_WIDTH + RK043FN48H_HSYNC + RK043FN48H_HBP - 1);
	m_hltdc.Init.TotalHeigh = (RK043FN48H_HEIGHT + RK043FN48H_VSYNC + RK043FN48H_VBP + RK043FN48H_VFP - 1);
	m_hltdc.Init.TotalWidth = (RK043FN48H_WIDTH + RK043FN48H_HSYNC + RK043FN48H_HBP + RK043FN48H_HFP - 1);

	  /* Configure R,G,B component values for LCD background color : all black background */
	m_hltdc.Init.Backcolor.Blue = 0;
	m_hltdc.Init.Backcolor.Green = 0;
	m_hltdc.Init.Backcolor.Red = 0;

	m_hltdc.Instance = LTDC;

	  /* Configure the LTDC */
	if (HAL_LTDC_Init(&m_hltdc) != HAL_OK) {
		/* Initialization Error */
		while (1) {
		}
	}
	if(Touch::USE_VSYNC){
		HAL_LTDC_ProgramLineEvent(&m_hltdc, m_hltdc.Init.AccumulatedActiveH + 1);
    }

	if(m_layer1Enable)
		layerConfig(1);
	if(m_layer2Enable)
		layerConfig(2);
}

LTDC_HandleTypeDef* Lcd::getLtdcHandle(void){
	return &m_hltdc;
}
void Lcd::layerConfig(int8_t numberLayer) {
	switch (numberLayer) {
	case 1:
		/* Layer1 Configuration ------------------------------------------------------*/
		/* Windowing configuration */
		/* In this case all the active display area is used to display a picture then :
		 Horizontal start = horizontal synchronization + Horizontal back porch = 43
		 Vertical start   = vertical synchronization + vertical back porch     = 12
		 Horizontal stop = Horizontal start + window width -1 = 43 + 480 -1
		 Vertical stop   = Vertical start + window height -1  = 12 + 272 -1      */
		m_layer1.WindowX0 = 0;
		m_layer1.WindowX1 = m_width;
		m_layer1.WindowY0 = 0;
		m_layer1.WindowY1 = m_height;

		/* Pixel Format configuration*/
		m_layer1.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;

		/* Start Address configuration : frame buffer is located at FLASH memory */
		m_layer1.FBStartAdress = m_layer1Address;

		/* Alpha constant (255 == totally opaque) */
		m_layer1.Alpha = 255;

		/* Default Color configuration (configure A,R,G,B component values) : no background color */
		m_layer1.Alpha0 = 0; /* fully transparent */
		m_layer1.Backcolor.Blue = 0;
		m_layer1.Backcolor.Green = 0;
		m_layer1.Backcolor.Red = 0xFF;

		/* Configure blending factors */
		m_layer1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
		m_layer1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;

		/* Configure the number of lines and number of pixels per line */
		m_layer1.ImageWidth = m_width;	//480
		m_layer1.ImageHeight = m_height;	//272

		/* Configure the Layer*/
		if (HAL_LTDC_ConfigLayer(&m_hltdc, &m_layer1, numberLayer-1) != HAL_OK) {
			/* Initialization Error */
			while (1) {
			}
		}
		break;
	case 2:
		/* Layer1 Configuration ------------------------------------------------------*/
		/* Windowing configuration */
		/* In this case all the active display area is used to display a picture then :
		 Horizontal start = horizontal synchronization + Horizontal back porch = 43
		 Vertical start   = vertical synchronization + vertical back porch     = 12
		 Horizontal stop = Horizontal start + window width -1 = 43 + 480 -1
		 Vertical stop   = Vertical start + window height -1  = 12 + 272 -1      */
		m_layer2.WindowX0 = 0;
		m_layer2.WindowX1 = m_width;
		m_layer2.WindowY0 = 0;
		m_layer2.WindowY1 = m_height;

		/* Pixel Format configuration*/
		m_layer2.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;

		/* Start Address configuration : frame buffer is located at FLASH memory */
		m_layer2.FBStartAdress = 0xC0000000 + (480*272*4);

		/* Alpha constant (255 == totally opaque) */
		m_layer2.Alpha = 255;

		/* Default Color configuration (configure A,R,G,B component values) : no background color */
		m_layer2.Alpha0 = 0; /* fully transparent */
		m_layer2.Backcolor.Blue = 0;
		m_layer2.Backcolor.Green = 0;
		m_layer2.Backcolor.Red = 0;

		/* Configure blending factors */
		m_layer2.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
		m_layer2.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;

		/* Configure the number of lines and number of pixels per line */
		m_layer2.ImageWidth = m_width;
		m_layer2.ImageHeight = m_height;

		/* Configure the Layer*/
		if (HAL_LTDC_ConfigLayer(&m_hltdc, &m_layer2, numberLayer-1) != HAL_OK) {
			/* Initialization Error */
			while (1) {
			}
		}
		break;
	default:
		break;
	}
}

void Lcd::pinsInit() {
	GPIO_InitTypeDef GPIO_Init_Structure;
	/*##-1- Enable peripherals and GPIO Clocks #################################*/
	/* Enable the LTDC Clock */
	__HAL_RCC_LTDC_CLK_ENABLE()
	;

	/*** LTDC Pins configuration ***/
	/* GPIOE configuration */
	GPIO_Init_Structure.Pin = GPIO_PIN_4;
	GPIO_Init_Structure.Mode = GPIO_MODE_AF_PP;
	GPIO_Init_Structure.Pull = GPIO_NOPULL;
	GPIO_Init_Structure.Speed = GPIO_SPEED_FAST;
	GPIO_Init_Structure.Alternate = GPIO_AF14_LTDC;
	HAL_GPIO_Init(GPIOE, &GPIO_Init_Structure);

	/* GPIOG configuration */
	GPIO_Init_Structure.Pin = GPIO_PIN_12;
	GPIO_Init_Structure.Mode = GPIO_MODE_AF_PP;
	GPIO_Init_Structure.Alternate = GPIO_AF9_LTDC;
	HAL_GPIO_Init(GPIOG, &GPIO_Init_Structure);

	/* GPIOI LTDC alternate configuration */
	GPIO_Init_Structure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
	GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_Init_Structure.Mode = GPIO_MODE_AF_PP;
	GPIO_Init_Structure.Alternate = GPIO_AF14_LTDC;
	HAL_GPIO_Init(GPIOI, &GPIO_Init_Structure);

	/* GPIOJ configuration */
	GPIO_Init_Structure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3
			|GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 |
			GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |
			GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_Init_Structure.Mode = GPIO_MODE_AF_PP;
	GPIO_Init_Structure.Alternate = GPIO_AF14_LTDC;
	HAL_GPIO_Init(GPIOJ, &GPIO_Init_Structure);

	/* GPIOK configuration */
	GPIO_Init_Structure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4
			|
			GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_Init_Structure.Mode = GPIO_MODE_AF_PP;
	GPIO_Init_Structure.Alternate = GPIO_AF14_LTDC;
	HAL_GPIO_Init(GPIOK, &GPIO_Init_Structure);

	/* LCD_DISP GPIO configuration */
	GPIO_Init_Structure.Pin = GPIO_PIN_12; /* LCD_DISP pin has to be manually controlled */
	GPIO_Init_Structure.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOI, &GPIO_Init_Structure);

	/* LCD_BL_CTRL GPIO configuration */
	GPIO_Init_Structure.Pin = GPIO_PIN_3; /* LCD_BL_CTRL pin has to be manually controlled */
	GPIO_Init_Structure.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOK, &GPIO_Init_Structure);

	/* Assert display enable LCD_DISP pin */
	HAL_GPIO_WritePin(GPIOI, GPIO_PIN_12, GPIO_PIN_SET);

	/* Assert backlight LCD_BL_CTRL pin */
	HAL_GPIO_WritePin(GPIOK, GPIO_PIN_3, GPIO_PIN_SET);

	if(Touch::USE_VSYNC){
		HAL_NVIC_SetPriority(LTDC_IRQn, 0x6, 0);
		HAL_NVIC_EnableIRQ(LTDC_IRQn);

		HAL_NVIC_SetPriority(LTDC_ER_IRQn, 0x6, 0);
		HAL_NVIC_EnableIRQ(LTDC_ER_IRQn);
	}
}

void Lcd::setLayerAddress(uint32_t layerIndex, uint32_t address){
	m_layer1Address = address;
}
void Lcd::switchFrame(void){
	HAL_LTDC_SetAddress(&m_hltdc, m_layer1Address, 0);
}
uint16_t Lcd::getWidth(void){
	return m_width;
}

uint16_t Lcd::getHeight(void){
	return m_height;
}

void Lcd::setBitDepth(uint8_t bitDepth){
	m_bitDepth = bitDepth;
}

uint8_t Lcd::getBitDepth(){
	return m_bitDepth;
}

void Lcd::drawPartialBitmap(Bitmap bitmap, int16_t x, int16_t y, Rect rect, uint8_t alpha){
	uint8_t bitDepthDst;
	uint8_t bitDepthSrc;
	switch(m_bitDepth){
	case 32:
		bitDepthDst = 4;
		break;
	case 24:
		bitDepthDst = 3;
		break;
	case 16:
		bitDepthDst = 2;
		break;
	}
	if(bitmap.getFormat() == Bitmap::ARGB8888){
		bitDepthSrc = 4;
	} else if (bitmap.getFormat() == Bitmap::RGB888){
		bitDepthSrc = 3;
	} else {
		bitDepthSrc = 2;
	}
	if(!rect.isEmpty()){
		uint32_t pDst = m_layer1Address + (((rect.m_y * m_width) + rect.m_x)*bitDepthDst);
		DmaOperation::OpStruct* op;
		op = (DmaOperation::OpStruct*)osMailAlloc(Touch::m_mailLcdToDmaId, osWaitForever);
		(bitmap.getFormat() == Bitmap::RGB565) ? op->operation =  DmaOperation::OP_COPY : op->operation = DmaOperation::OP_COPY_ARGB8888;
		op->pDst = (uint8_t*)pDst;
		op->pSrc = bitmap.getData() + (((rect.m_y - y) * bitmap.getWidth()) + (rect.m_x - x)) * bitDepthSrc;
		op->nSteps = rect.m_width;
		op->nLoop = rect.m_height;
		op->srcLoopStride = bitmap.getWidth() - rect.m_width;
		op->dstLoopStride = m_width - rect.m_width;
		op->alpha = alpha;
		op->color = 0x00;
		osSemaphoreWait(Touch::osSemaphoreDmaStopWork, osWaitForever);
		osMailPut(Touch::m_mailLcdToDmaId, op);
	}
}


void Lcd::drawString(Rect widgetArea, const Rect& invalidatedArea,
		StringVisuals& stringVisuals, const Unicode::UnicodeChar* format, ...){
	uint8_t bitDepthDst;
	switch(m_bitDepth){
	case 32:
		bitDepthDst = 4;
		break;
	case 24:
		bitDepthDst = 3;
		break;
	case 16:
		bitDepthDst = 2;
		break;
	}
	const uint8_t* adres = 0;
	uint8_t bpp = 0;
	DmaOperation::OpStruct* op;
	Unicode::UnicodeChar* wildcard = 0;

	Rect rectGlyph;							//obszar znaku
	Rect invAreaGlph;						//obszar wspolny znaku oraz obszaru do przerysowania
	int16_t posY = widgetArea.m_y;			//pozycja Y tekstu (moze sie zmieniac w przypadku gdy jest multiline)
	uint32_t pDst = m_layer1Address + (((posY * m_width) + widgetArea.m_x + stringVisuals.indentation) * bitDepthDst);
	while(*format != 0x0000){
		if(*format == 0x000A){
			posY += stringVisuals.font->getFontHeight() + stringVisuals.linespace;
			pDst = m_layer1Address + (((posY * m_width) + widgetArea.m_x + stringVisuals.indentation) * bitDepthDst);
		} else if(*format == 0x0020){
			pDst += stringVisuals.font->getCharWidth(*format) * bitDepthDst;
		} else if(*format == 0x0002){
			va_list ap;
			va_start(ap, format);
			wildcard = va_arg(ap, Unicode::UnicodeChar*);
			while(*wildcard != 0x0000){
				if(*wildcard == 0x0020){
					pDst += stringVisuals.font->getCharWidth(*wildcard) * bitDepthDst;
				} else {
					int16_t xGlyph = ((pDst - m_layer1Address) / bitDepthDst) - (posY * m_width);
					rectGlyph.m_x = xGlyph;
					rectGlyph.m_y = posY;
					rectGlyph.m_width = stringVisuals.font->getCharWidth(*wildcard);
					rectGlyph.m_height = stringVisuals.font->getGlyph(*wildcard)->height();

					invAreaGlph = rectGlyph & invalidatedArea;
					if(!invAreaGlph.isEmpty()){
						stringVisuals.font->getGlyph(*wildcard, adres, bpp);
						op = (DmaOperation::OpStruct*)osMailAlloc(Touch::m_mailLcdToDmaId, osWaitForever);
						op->operation = stringVisuals.font->getBitsPerPixel() == 8 ? DmaOperation::OP_COPY_A8 : DmaOperation::OP_COPY_A4;
						op->pDst = (uint8_t*)(m_layer1Address + (((invAreaGlph.m_y * m_width) + invAreaGlph.m_x)*bitDepthDst));
						uint32_t ofset = ((invAreaGlph.m_y - rectGlyph.m_y) * stringVisuals.font->getCharWidth(*wildcard)) + (invAreaGlph.m_x - rectGlyph.m_x);
						op->pSrc = (uint8_t*)(adres + ofset);
						op->nSteps = invAreaGlph.m_width;
						op->nLoop = invAreaGlph.m_height;
						op->srcLoopStride = stringVisuals.font->getCharWidth(*wildcard) - invAreaGlph.m_width;
						op->dstLoopStride = m_width - invAreaGlph.m_width;
						op->alpha = stringVisuals.alpha;
						op->color = stringVisuals.color;
						osSemaphoreWait(Touch::osSemaphoreDmaStopWork, osWaitForever);
						osMailPut(Touch::m_mailLcdToDmaId, op);
					}
					pDst += (2 + stringVisuals.font->getCharWidth(*wildcard)) * bitDepthDst;
				}
				wildcard++;
			}
			va_end(ap);
		} else {
			int16_t xGlyph = ((pDst - m_layer1Address) / bitDepthDst) - (posY * m_width);
			rectGlyph.m_x = xGlyph;
			rectGlyph.m_y = posY;
			rectGlyph.m_width = stringVisuals.font->getCharWidth(*format);
			rectGlyph.m_height = stringVisuals.font->getGlyph(*format)->height();

			invAreaGlph = rectGlyph & invalidatedArea;
			if(!invAreaGlph.isEmpty()){
				stringVisuals.font->getGlyph(*format, adres, bpp);
				op = (DmaOperation::OpStruct*)osMailAlloc(Touch::m_mailLcdToDmaId, osWaitForever);
				op->operation = stringVisuals.font->getBitsPerPixel() == 8 ? DmaOperation::OP_COPY_A8 : DmaOperation::OP_COPY_A4;
				op->pDst = (uint8_t*)(m_layer1Address + (((invAreaGlph.m_y * m_width) + invAreaGlph.m_x)*bitDepthDst));
				uint32_t ofset = ((invAreaGlph.m_y - rectGlyph.m_y) * stringVisuals.font->getCharWidth(*format)) + (invAreaGlph.m_x - rectGlyph.m_x);
				op->pSrc = (uint8_t*)(adres + ofset);
				op->nSteps = invAreaGlph.m_width;
				op->nLoop = invAreaGlph.m_height;
				op->srcLoopStride = stringVisuals.font->getCharWidth(*format) - invAreaGlph.m_width;
				op->dstLoopStride = m_width - invAreaGlph.m_width;
				op->alpha = stringVisuals.alpha;
				op->color = stringVisuals.color;
				osSemaphoreWait(Touch::osSemaphoreDmaStopWork, osWaitForever);
				osMailPut(Touch::m_mailLcdToDmaId, op);
			}
			pDst += (2 + stringVisuals.font->getCharWidth(*format)) * bitDepthDst;
		}
		format++;
	}
}

void Lcd::copyFrameBufferRegionToMemory(uint8_t* srcBuffer, uint8_t* dstBuffer){
	DmaOperation::OpStruct* op;
	op = (DmaOperation::OpStruct*)osMailAlloc(Touch::m_mailLcdToDmaId, osWaitForever);
//		op->operation = DmaOperation::OP_COPY_ARGB8888;
	op->operation = DmaOperation::OP_COPY;
	op->pDst = dstBuffer;
	op->pSrc = srcBuffer;
	op->nSteps = m_width;
	op->nLoop = m_height;
	op->srcLoopStride = 0x00;
	op->dstLoopStride = 0x00;
	op->alpha = 255;
	op->color = 0x00;
	osSemaphoreWait(Touch::osSemaphoreDmaStopWork, osWaitForever);
	osMailPut(Touch::m_mailLcdToDmaId, op);
}
