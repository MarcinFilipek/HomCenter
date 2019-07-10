/*
 * Lcd.h
 *
 *  Created on: 31 sie 2016
 *      Author: Uzume
 */

#ifndef LCD_LCD_H_
#define LCD_LCD_H_

#include "stm32f7xx_hal.h"
#include "../Types/Types.h"
#include "../Bitmap/Bitmap.h"
#include "../Font/Font.h"

class Lcd {
public:
	Lcd();
	virtual ~Lcd();
	static const uint16_t RK043FN48H_WIDTH = 480; /* LCD PIXEL WIDTH            */
	static const uint16_t RK043FN48H_HEIGHT = 272; /* LCD PIXEL HEIGHT           */

	static const uint16_t RK043FN48H_HSYNC = 41; /* Horizontal synchronization */
	static const uint16_t RK043FN48H_HBP = 13; /* Horizontal back porch      */
	static const uint16_t RK043FN48H_HFP = 32; /* Horizontal front porch     */
	static const uint16_t RK043FN48H_VSYNC = 10; /* Vertical synchronization   */
	static const uint16_t RK043FN48H_VBP = 2; /* Vertical back porch        */
	static const uint16_t RK043FN48H_VFP = 2; /* Vertical front porch       */

	struct StringVisuals {
		const Font* font;
		Aligment aligment;
		TextDirection textDirection;
		colortype color;
		uint8_t alpha;
		uint16_t linespace;
		uint8_t indentation;

		StringVisuals() :
				font(0), aligment(LEFT), textDirection(TEXT_DIRECTION_LTR), color(
						0), alpha(255), linespace(0), indentation(0) {
		}

		StringVisuals(const Font* f, colortype col = 0, uint8_t alpha = 255,
				Aligment ali = LEFT, uint16_t lspace = 0,
				TextDirection tDirection = TEXT_DIRECTION_LTR, uint8_t indent = 0) {
			this->font = f;
			this->color = col;
			this->alpha = alpha;
			this->aligment = ali;
			this->linespace = lspace;
			this->textDirection = tDirection;
			this->indentation = indent;
		}
	};

	void initialize(uint16_t width, uint16_t height);
	LTDC_HandleTypeDef* getLtdcHandle(void);
	uint16_t getWidth(void);
	uint16_t getHeight(void);
	void setBufferAddress(uint32_t layerIndex, uint32_t address);
	void setLayerAddress(uint32_t layerIndex, uint32_t address);
	void switchFrame(void);
	void drawPartialBitmap(Bitmap bitmap, int16_t x, int16_t y, Rect rect,
			uint8_t alpha = 255);
	void drawString(Rect widgetArea, const Rect& invalidatedArea,
			StringVisuals& stringVisuals, const Unicode::UnicodeChar* format, ...);
	static void setBitDepth(uint8_t bitDepth);
	static uint8_t getBitDepth(void);
	void copyFrameBufferRegionToMemory(uint8_t* srcBuffer, uint8_t* dstBuffer);
private:
	static uint16_t m_width;
	static uint16_t m_height;
	static uint8_t m_bitDepth;
	LTDC_HandleTypeDef m_hltdc;
	LTDC_LayerCfgTypeDef m_layer1;
	LTDC_LayerCfgTypeDef m_layer2;
	bool m_layer1Enable;
	bool m_layer2Enable;

	static uint32_t m_layer1Address;
	void pinsInit(void);
	void clockConfig(void);
	void layerConfig(int8_t numberLayer);
};

#endif /* LCD_LCD_H_ */
