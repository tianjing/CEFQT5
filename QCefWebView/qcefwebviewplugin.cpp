#include "stdafx.h"
#include "qcefwebview.h"

#include <QtCore/QtPlugin>
#include "qcefwebviewplugin.h"


QCefWebViewPlugin::QCefWebViewPlugin(QObject *parent)
	: QObject(parent)
{
	initialized = false;
}

void QCefWebViewPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
	if (initialized)
		return;

	initialized = true;
}

bool QCefWebViewPlugin::isInitialized() const
{
	return initialized;
}

QWidget *QCefWebViewPlugin::createWidget(QWidget *parent)
{
	return new QCefWebView(parent);
}

QString QCefWebViewPlugin::name() const
{
	return "QCefWebView";
}

QString QCefWebViewPlugin::group() const
{
	return "My Plugins";
}

QIcon QCefWebViewPlugin::icon() const
{
	return QIcon();
}

QString QCefWebViewPlugin::toolTip() const
{
	return QString();
}

QString QCefWebViewPlugin::whatsThis() const
{
	return QString();
}

bool QCefWebViewPlugin::isContainer() const
{
	return false;
}

QString QCefWebViewPlugin::domXml() const
{
	return "<widget class=\"QCefWebView\" name=\"qCefWebView\">\n"
		" <property name=\"geometry\">\n"
		"  <rect>\n"
		"   <x>0</x>\n"
		"   <y>0</y>\n"
		"   <width>100</width>\n"
		"   <height>100</height>\n"
		"  </rect>\n"
		" </property>\n"
		"</widget>\n";
}

QString QCefWebViewPlugin::includeFile() const
{
	return "qcefwebview.h";
}

