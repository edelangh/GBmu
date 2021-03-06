#include <iostream>
#include <functional>

#ifndef _OPCODE_HPP
# define _OPCODE_HPP

#include <array>

typedef std::function<void()>	opcodeFct;

typedef struct	s_opcode
{
	uint8_t		opcode;
	uint8_t		mask;
	uint8_t		cycleOpcodeFlag;
	uint8_t		cycleOpcodeNoFlag;
	uint8_t		lengthData;
	opcodeFct	functionOpcode;
	std::string	instructionName;
	uint16_t	data;
}				t_opcode;

extern std::array<t_opcode, 256>	_opcodeMap;
extern std::array<t_opcode, 256>	_CBopcodeMap;
#endif
