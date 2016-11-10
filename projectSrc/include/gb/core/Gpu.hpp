
#pragma once

typedef	enum	s_gpuMode
{
	OAM_READ,
	VRAM_READ,
	HBLANK,
	VBLANK
}				t_gpuMode;


class Gpu
{
	protected:
		unsigned int	_clock;
		t_gpuMode		_mode;
		unsigned int	_line;

	private:
		Gpu();
		~Gpu();

	public:
		static Gpu		_gpuInstance;
		static Gpu		&Instance();

		void	step();
		void	accClock(unsigned int clock);
};