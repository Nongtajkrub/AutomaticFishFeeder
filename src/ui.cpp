#include "ui.hpp"

#include <Arduino.h>

using namespace LcdI2cUi;

// Ui_Parent

LcdI2cUiPar::LcdI2cUiPar(LcdI2c *lcd, String text) : 
	lcd(lcd), text(text)
{}

// Ui_Text

LcdI2cUi_Text::LcdI2cUi_Text(LcdI2c *lcd, String text) :
	LcdI2cUiPar(lcd, text)
{}

// Ui_Choice

u8 LcdI2cUi_Option::option_count = 0;
u8 LcdI2cUi_Option::cursor_pos = 0;

LcdI2cUi_Option::LcdI2cUi_Option(LcdI2c *lcd, String text, u8 y) :
	LcdI2cUiPar(lcd, text), id(option_count)
{
	this->x = 0;
	this->y = y;
	this->option_count++;
}


void LcdI2cUi_Option::move_cur_up() {
	if (cursor_pos == 0) {
		return;
	}

	cursor_pos--;
}


void LcdI2cUi_Option::move_cur_down() {
	if (cursor_pos == option_count) {
		return;
	}

	cursor_pos++;
}

u8 LcdI2cUi_Option::get_cursor_pos() {
	return cursor_pos;
}
