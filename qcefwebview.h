#ifndef QCEFWEBVIEW_H
#define QCEFWEBVIEW_H

#include "qcefclienthandler.h"
#include "qcefmessageevent.h"
#include "QHandlers\QCetRequestHandler.h"
class QCefWebView_EXPORT QCefWebView :
	public QWidget,
	public QCefClientHandler::Listener
{
	Q_OBJECT

public:
	enum BrowserState
	{
		kNone,
		kCreating,
		kCreated
	};

	static const QString kUrlBlank;
	QCefWebView(QWidget *parent);
	virtual ~QCefWebView();

	void load(const QUrl & url);
	void setHtml(const QString & html, const QUrl & baseUrl = QUrl());

	QUrl url() const;

public slots:
	void back();
	void forward();
	void reload();
	void stop();
	virtual QCetRequestHandler& RequestHandler()override;
signals:
	void titleChanged(const QString & title);
	void urlChanged(const QUrl & url);
	void loadStarted();
	void loadFinished(bool ok);
	void navStateChanged(bool canGoBack, bool canGoForward);
	void getResource(QCefResourceEvent & e);

protected:
	virtual void resizeEvent(QResizeEvent * event) override;
	virtual void closeEvent(QCloseEvent * event) override;
	virtual void showEvent(QShowEvent * event) override;
	virtual void customEvent(QEvent * event) override;

	virtual void OnAddressChange(const QString & url) override;
	virtual void OnTitleChange(const QString & title) override;
	virtual void SetLoading(bool isLoading) override;
	virtual void SetNavState(bool canGoBack, bool canGoForward) override;
	virtual void OnAfterCreated() override;
	virtual void OnMessageEvent(QCefMessageEvent * e) override;

private:
	void SetupUi();
	bool CreateBrowser(const QSize & size);
	CefRefPtr<CefBrowser> GetBrowser() const;
	void ResizeBrowser(const QSize & size);
	bool BrowserLoadUrl(const QUrl & url);

	QCetRequestHandler requesthandler_;
	BrowserState browserState_;
	bool needResize_;
	bool needLoad_;
	QUrl url_;
	QMutex mutex_;

	Q_DISABLE_COPY(QCefWebView);
};

#endif // QCEFWEBVIEW_H
