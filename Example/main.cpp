#include "stdafx.h"
#include "example.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include "QCefClient.h"
#include "qcefwebview.h"
bool IsSubprocess(int & argc, char ** argv)
{
	std::vector<std::string> argVector(argv, argv + argc);

	for (auto i = 0; i < argc; ++i) {
		if (argVector[i].find("--type") != std::string::npos) {
			return true;
		}
	}

	return false;
}

int RunCefSubprocess(int & argc, char ** argv)
{
	CefMainArgs cefMainArgs(GetModuleHandle(nullptr));

	return CefExecuteProcess(cefMainArgs, nullptr, nullptr);
}


int main(int argc, char *argv[])
{
	
	//if (IsSubprocess(argc, argv)) {
	//	std::cout << "subprocess" << std::endl;
	//	return RunCefSubprocess(argc, argv);
	//}
	//else {
		QApplication a(argc, argv);

		int result = QCefInit(argc, argv);
		if (result >= 0) {
			return result;
		}

		Example w;
		w.resize(1024, 768);


		w.show();
		int qt_exit_code = 0;
		try {
		qt_exit_code = a.exec();
		//a.exit(0);
		
		QCefQuit();
		}
		catch (...) {}
		return qt_exit_code;
	//}
}
