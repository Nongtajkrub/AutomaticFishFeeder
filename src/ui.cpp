#include "ui.hpp"

#include <Arduino.h>

// Ui_Parent

LcdI2cUi::LcdI2cUiParent::LcdI2cUiParent(LcdI2c *lcd, String text) : 
	m_lcd(lcd), m_text(text)
{}

// Ui_Text

LcdI2cUi::LcdI2cUi_Text::LcdI2cUi_Text(LcdI2c *lcd, String text) :
	LcdI2cUi::LcdI2cUiParent(lcd, text)
{}

// Ui_Choice

u8 LcdI2cUi::LcdI2cUi_Option::option_count = 0;
u8 LcdI2cUi::LcdI2cUi_Option::cursor_pos = 0;

LcdI2cUi::LcdI2cUi_Option::LcdI2cUi_Option(LcdI2c *lcd, String text, u8 y) :
	LcdI2cUi::LcdI2cUiParent(lcd, text), m_id(option_count)
{
	m_x = 0;
	m_y = y;
	option_count++;
}


void LcdI2cUi::LcdI2cUi_Option::moveCursorUp() {
	if (cursor_pos == 0) {
		return;
	}

	cursor_pos--;
}


void LcdI2cUi::LcdI2cUi_Option::moveCursorDown() {
	if (cursor_pos == option_count) {
		return;
	}

	cursor_pos++;
}

u8 LcdI2cUi::LcdI2cUi_Option::getCursorPos() {
	return cursor_pos;
}
