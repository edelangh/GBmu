#ifndef DBWINDOW_H
#define DBWINDOW_H

#include <QDialog>

namespace Ui {
	class DbWindow;
}

class QTableWidget;
class QLineEdit;
class Memory;
typedef struct s_register t_register;

class DbWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DbWindow(t_register *r, Memory *mem);
    virtual	~DbWindow();

	void 	updateRegister(t_register& r);
	void	updateOtherRegister(Memory& mem);
	void 	updateMemory(Memory& m);
	void	updateDisassembler(t_register& r, Memory& mem);

	QTableWidget	*tableRegisters;
	QTableWidget	*tableOtherRegisters;
	QTableWidget	*tableVideoRegisters;
	QTableWidget	*tableDisassembler;
	QTableWidget	*tableMemory;

	QPushButton		*buttonReset;
	QPushButton		*buttonStep;
	QPushButton		*buttonFrame;
	QPushButton		*buttonOpen;

	QLineEdit		*lineAddr;

	signals:
		void	stepPressedSign();
		void	resetPressedSign();
		void	openPressedSign(std::string path);
	public slots:
		void	stepPressedSlot();
		void	resetPressedSlot();
		void	openPressedSlot();
		void	updateAllSlot();
		void	lineAddrEditedSlot();

private:
    Ui::DbWindow	*ui;

	t_register		*_r;
	Memory			*_mem;

	unsigned int	_start;
};

#endif // DBWINDOW_H
