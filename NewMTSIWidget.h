#pragma once

#include <QWidget>
#include "ui_NewMTSIWidget.h"

class NewMTSIWidget : public QWidget
{
	Q_OBJECT

public:
	NewMTSIWidget(QWidget* parent = nullptr);
	~NewMTSIWidget();

	Ui::NewMTSIWidgetClass ui;
};
