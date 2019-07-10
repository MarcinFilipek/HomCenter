/*
 * MainView.cpp
 *
 *  Created on: 5 maj 2017
 *      Author: Uzume
 */

#include "MainView.h"
#include "../Touch/Color/Color.h"
#include "../../ResourcesOut/Texts/TextKeysAndLanguages.h"
#include "../../ResourcesOut/Images/BitmapDatabase.h"

void MainView::setupScreen(void) {
	m_imageBackground.setBitmap(Bitmap(BITMAP_BACKGROUND_ID));
	m_imageBackground.setXY(0, 0);

	m_imageExit.setBitmap(Bitmap(BITMAP_EXIT_ID));
	m_imageExit.setXY(5, 85);

	m_imageKafelek.setBitmap(Bitmap(BITMAP_KAFELEK_ID));
	m_imageKafelek.setXY(0, 0);

	m_buttonPower.setBitmaps(Bitmap(BITMAP_POWER_ID), Bitmap(BITMAP_POWER_DOWN_ID));
	m_buttonPower.setXY(-10, -10);
	m_buttonPower.setAction(buttonClicedCallback);

	m_buttonPower2.setBitmaps(Bitmap(BITMAP_CHECKED_ID), Bitmap(BITMAP_POWER_DOWN_ID));
	m_buttonPower2.setXY(406, 10);
	m_buttonPower2.setAction(buttonClicedCallback);

	m_textCzesc.setTypedText(TypedText(T_DODAJ_POKOJ));
	m_textCzesc.setPosition(200, 150, 150, 50);
	m_textCzesc.setColor(Color::getColorFrom24BitRGB(0xFF, 0x00, 0x00));

	m_textDlugi.setTypedText(TypedText(T_POCHODZE_Z));
	m_textDlugi.setPosition(10,125, 200, 20);
	m_textDlugi.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));

	m_textDlugiLF.setTypedText(TypedText(T_TEKST_NA_DWIE_LINIE));
	m_textDlugiLF.setPosition(20,150, 150, 55);
	m_textDlugiLF.setColor(Color::getColorFrom24BitRGB(0x00, 0xFF, 0x00));

	m_textWildcard.setWildcard(m_buffer);
	m_textWildcard.setTypedText(TypedText(T_MAM_NA_IMIE));
	m_textWildcard.setPosition(0, 220, 100, 30);
	m_textWildcard.setColor(Color::getColorFrom24BitRGB(0xFF, 0x00, 0x00));
	Unicode::strncpy(m_buffer, "Man", 3);
	m_buffer[3]=0;

	m_kontener.setPosition(40, 40, 150, 150);
	m_kontener.add(&m_imageKafelek);
	m_kontener.add(&m_buttonPower);

	add(&m_imageBackground);
	add(&m_imageExit);
	add(&m_kontener);
	add(&m_buttonPower2);
	add(&m_textCzesc);
	add(&m_textDlugi);
	add(&m_textDlugiLF);
	add(&m_textWildcard);
}

void MainView::tearDownScreen(void) {
}

void MainView::buttonClicked(const AbstractButton& source) {
	if (&source == &m_buttonPower) {
		m_imageExit.setXY(m_imageExit.getX() + 5, m_imageExit.getY());
		m_imageExit.invalidate();
		m_textCzesc.setXY(m_textCzesc.getX() - 4, m_textCzesc.getY() + 4);
		m_textCzesc.invalidate();
		presenter->upPressed();
		m_kontener.insert(0, &m_imageKafelek);
		m_kontener.invalidate();
	}
	if (&source == &m_buttonPower2) {
		m_textCzesc.setXY(m_textCzesc.getX() + 4, m_textCzesc.getY() - 4);
		m_textCzesc.invalidate();
		presenter->downPressed();
		m_kontener.remove(&m_imageKafelek);
		m_kontener.invalidate();
	}
}
