#ifndef QCEFWEBVIEW_H
#define QCEFWEBVIEW_H

#include "qcefclienthandler.h"
#include "qcefmessageevent.h"
#include "QHandlers\QCefRequestHandler.h"
#include "QHandlers\QCefDisplayHandler.h"
#include "QHandlers\QCefLifeSpanHandler.h"
class QCefWebView_EXPORT QCefWebView :
	public QWidget,
	public QCefClientHandler::Listener, public CListener
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
	virtual QCefRequestHandler& RequestHandler()override
	{
		return requesthandler_;
	}
	virtual QCefDisplayHandler& DisplayHandler() override{
		return displayhandler_;
	}
	virtual QCefLifeSpanHandler& LifeSpanHandler() override {
		return lifeSpanHandler_;
	}

public slots:
	void back();
	void forward();
	void reload();
	void stop();

signals:
	void titleChanged(const QString & title);
	void urlChanged(const QUrl & url);
	void loadStarted();
	void loadFinished(bool ok);
	void navStateChanged(bool canGoBack, bool canGoForward);

protected:
	virtual void resizeEvent(QResizeEvent * event) override;
	virtual void closeEvent(QCloseEvent * event) override;
	virtual void showEvent(QShowEvent * event) override;
	virtual void customEvent(QEvent * event) override;

	virtual void SetLoading(bool isLoading) override;
	virtual void SetNavState(bool canGoBack, bool canGoForward) override;
	virtual void OnAfterCreated(CEventArgs&);
	virtual void OnMessageEvent(QCefMessageEvent * e) override;

private:
	void SetupUi();
	bool CreateBrowser(const QSize & size);
	CefRefPtr<CefBrowser> GetBrowser() const;
	void ResizeBrowser(const QSize & size);
	bool BrowserLoadUrl(const QUrl & url);

	QCefRequestHandler requesthandler_ = QCefRequestHandler();;
	QCefDisplayHandler displayhandler_ = QCefDisplayHandler();;
	QCefLifeSpanHandler lifeSpanHandler_= QCefLifeSpanHandler();
	BrowserState browserState_;
	bool needResize_;
	bool needLoad_;
	QUrl url_;
	QMutex mutex_;
	QCefClientHandler* g_handler1 = new QCefClientHandler();
	Q_DISABLE_COPY(QCefWebView);
};

#endif // QCEFWEBVIEW_H
