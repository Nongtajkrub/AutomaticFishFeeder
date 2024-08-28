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

u8 LcdI2cUi_Option::opt_count = 0;
u8 LcdI2cUi_Option::cur_pos = 0;

LcdI2cUi_Option::LcdI2cUi_Option(LcdI2c *lcd, String text, u8 y) :
	LcdI2cUiPar(lcd, text), id(opt_count)
{
	this->x = 0;
	this->y = y;
	this->opt_count++;
}


void LcdI2cUi_Option::move_cur_up() {
	if (cur_pos == 0) {
		return;
	}

	cur_pos--;
}


void LcdI2cUi_Option::move_cur_down() {
	if (cur_pos == opt_count) {
		return;
	}

	cur_pos++;
}

u8 LcdI2cUi_Option::get_cur_pos() {
	return cur_pos;
}
