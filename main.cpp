#include "PetriNetTool.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	PetriNetTool w;
	w.show();
	w.setWindowTitle("PNTool");
	w.setWindowIcon(QIcon("E:/PNcode/PetriNetTool/image/icon1.png"));
	return a.exec();
}
