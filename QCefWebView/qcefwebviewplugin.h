#ifndef QCEFWEBVIEWPLUGIN_H
#define QCEFWEBVIEWPLUGIN_H

#include <QtDesigner/QDesignerCustomWidgetInterface>

class QCefWebViewPlugin : public QObject, public QDesignerCustomWidgetInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface" FILE "qcefwebviewplugin.json")
	Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
	QCefWebViewPlugin(QObject *parent = 0);

	bool isContainer() const;
	bool isInitialized() const;
	QIcon icon() const;
	QString domXml() const;
	QString group() const;
	QString includeFile() const;
	QString name() const;
	QString toolTip() const;
	QString whatsThis() const;
	QWidget *createWidget(QWidget *parent);
	void initialize(QDesignerFormEditorInterface *core);

private:
	bool initialized;
};

#endif // QCEFWEBVIEWPLUGIN_H
