// This is not met to be an user friendly easy to use API
// Maybe I will turn it into one in the future

#pragma once

#include "type.hpp"

#include <LiquidCrystal_I2C.h>

using LcdI2c = LiquidCrystal_I2C;

namespace LcdI2cUi {
	class LcdI2cUiPar {
		protected:
			LcdI2c *lcd;
			u8 x = 0;
			u8 y = 0;
			String text;

		public:
			LcdI2cUiPar(LcdI2c *lcd, String text); 
			~LcdI2cUiPar() = default;
		
		public:
			virtual void set_pos(u8 x, u8 y) {
				this->x = x;
				this->y = y;
			}
			
			virtual void show() {
				this->lcd->setCursor(this->x, this->y);
				this->lcd->print(this->text);
			}
	};

	class LcdI2cUi_Text : public LcdI2cUiPar {
		public:
			LcdI2cUi_Text(LcdI2c *lcd, String text);
			~LcdI2cUi_Text() = default;
	};

	class LcdI2cUi_Option : public LcdI2cUiPar {
		private:
			static u8 option_count;
			static u8 cursor_pos;
			u8 id;

		public:
			LcdI2cUi_Option(LcdI2c *lcd, String text, u8 y);
			~LcdI2cUi_Option() = default;

		public:
			void show() override {
				this->lcd->setCursor(this->x, this->y);
				if (this->id == this->cursor_pos) {
					this->lcd->print(">");
					this->lcd->setCursor(this->x + 1, this->y);
					this->lcd->print(this->text);
				} else {
					this->lcd->print(this->text);
				}
			}

			void set_pos(u8 x, u8 y) override { return; }

			static void move_cur_up();
			static void move_cur_down();
			static u8 get_cursor_pos();
	};
}
