// This is not met to be an user friendly easy to use API
// Maybe I will turn it into one in the future

#pragma once

#include "type.hpp"

#include <LiquidCrystal_I2C.h>

using LcdI2c = LiquidCrystal_I2C;

namespace LcdI2cUi {
	class LcdI2cUiParent {
		protected:
			LcdI2c *m_lcd;
			u8 m_x = 0;
			u8 m_y = 0;
			String m_text;

		public:
			LcdI2cUiParent(LcdI2c *lcd, String text); 
			~LcdI2cUiParent() = default;
		
		public:
			virtual void setPos(u8 x, u8 y) {
				x = x;
				y = y;
			}
			
			virtual void show() {
				m_lcd->setCursor(m_x, m_y);
				m_lcd->print(m_text);
			}
	};

	class LcdI2cUi_Text : public LcdI2cUiParent {
		public:
			LcdI2cUi_Text(LcdI2c *lcd, String text);
			~LcdI2cUi_Text() = default;
	};

	class LcdI2cUi_Option : public LcdI2cUiParent {
		private:
			static u8 option_count;
			static u8 cursor_pos;
			u8 m_id;

		public:
			LcdI2cUi_Option(LcdI2c *lcd, String text, u8 y);
			~LcdI2cUi_Option() = default;

		public:
			void show() override {
				m_lcd->setCursor(m_x, m_y);
				if (m_id == cursor_pos) {
					m_lcd->print(">");
					m_lcd->setCursor(m_x + 1, m_y);
					m_lcd->print(m_text);
				} else {
					m_lcd->print(m_text);
				}
			}

			void setPos(u8 x, u8 y) override { return; }

			static void moveCursorUp();
			static void moveCursorDown();
			static u8 getCursorPos();
	};
}
