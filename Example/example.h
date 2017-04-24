#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QtWidgets/QMainWindow>
#include "ui_example.h"


class Example : public QMainWindow
{
	Q_OBJECT

public:
	Example(QWidget *parent = 0);
	~Example();

private:
	Ui::ExampleClass ui;
};

#endif // EXAMPLE_H
