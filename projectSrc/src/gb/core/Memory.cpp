#include <iostream>
#include <cstring>
#include "Memory.hpp"

Memory::Memory(void)
{
}

Memory::~Memory(void) {}


void			Memory::Init(void)
{
	this->reset();
}

void			Memory::reset(void)
{
	memset(this->_m_wram, 0, 32768);
	memset(this->_m_vram, 0, 16384);
	memset(this->_m_oam, 0, 160);
	memset(this->_m_io, 0, 127);
	memset(this->_m_zp, 0, 127);
}

uint8_t			Memory::read_byte(uint16_t addr)
{
	switch (addr & 0xF000){
		case 0x0000:
		case 0x1000:
		case 0x2000:
		case 0x3000:
		case 0x4000:
		case 0x5000:
		case 0x6000:
		case 0x7000:
			// ROM
			return this->_rom.read(addr);
			break;
		case 0x8000:
		case 0x9000:
			// VRAM
			return this->_m_wram[(this->_m_io[(VBK & 0xFF)] & 0x01)][(addr & 0x0FFF)];
			break;
		case 0xA000:
		case 0xB000:
			// ERAM
			return this->_rom.read(addr);
			break;
		case 0xC000:
		case 0xD000:
			// WRAM
			if ((addr & 0xF000) < 0xD000)
				return this->_m_wram[0][(addr & 0x0FFF)];
			else
				return this->_m_wram[(this->_m_io[(SVBK & 0xFF)] & 0x03)][(addr & 0x0FFF)];
			break;
		case 0xF000:
			switch (addr & 0x0F00){
				case 0x0E00:
					if ((addr & 0xFF) <= 0x9F)
					{
						// SPRITE
						return this->_m_oam[(addr & 0xFF)];
					}
					break;
				case 0x0F00:
					if ((addr & 0xFF) <= 0x7F)
					{
						// I/O
						return this->_m_io[(addr & 0xFF)];
					}
					else
					{
						// Zero page
						return this->_m_zp[(addr & 0xFF) - 0x7F];
					}
					break;
			}
			break;
	}
	return 0;
}

void			Memory::write_byte(uint16_t addr, uint8_t val)
{
	switch (addr & 0xF000){
		case 0x0000:
		case 0x1000:
		case 0x2000:
		case 0x3000:
		case 0x4000:
		case 0x5000:
		case 0x6000:
		case 0x7000:
			// ROM
			this->_rom.write(addr, val);
			break;
		case 0x8000:
		case 0x9000:
			// VRAM
			this->_m_wram[(this->_m_io[(VBK & 0xFF)] & 0x01)][(addr & 0x0FFF)] = val;
			break;
		case 0xA000:
		case 0xB000:
			// ERAM
			this->_rom.write(addr, val);
			break;
		case 0xC000:
		case 0xD000:
			// WRAM
			if ((addr & 0xF000) < 0xD000)
				this->_m_wram[0][(addr & 0x0FFF)] = val;
			else
				this->_m_wram[(this->_m_io[(SVBK & 0xFF)] & 0x03)][(addr & 0x0FFF)] = val;
			break;
		case 0xF000:
			switch (addr & 0x0F00){
				case 0x0E00:
					if ((addr & 0xFF) <= 0x9F)
					{
						// SPRITE
						this->_m_oam[(addr & 0xFF)] = val;
					}
					break;
				case 0x0F00:
					if ((addr & 0xFF) <= 0x7F)
					{
						// I/O
						this->_m_io[(addr & 0xFF)] = val;
					}
					else
					{
						// Zero page
						this->_m_zp[(addr & 0xFF) - 0x7F] = val;
					}
					break;
			}
			break;
	}
}

uint16_t		Memory::read_word(uint16_t addr)
{
	return this->read_byte(addr) + (this->read_byte(addr + 1) << 8);
}

void			Memory::write_word(uint16_t addr, uint16_t val)
{
	this->write_byte(addr, (val & 0xFF));
	this->write_byte(addr + 1, ((val & 0xFF00) >> 8));
}
