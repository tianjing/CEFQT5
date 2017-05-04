#pragma once
#include "util.h"

class QCefRequest {
public:

	QCefRequest(const CefRefPtr<CefRequest> p_Request)
	{
		m_Request = p_Request;
	}
	~QCefRequest()
	{

	}

	virtual bool IsReadOnly() {
		return m_Request->IsReadOnly();
	}

	virtual QString GetURL() {
		return  QCefUtil::ToString(m_Request->GetURL());
	}

	virtual QString GetMethod() {
		return QCefUtil::ToString(m_Request->GetMethod());
	}

	virtual QString GetReferrerURL(){
		return QCefUtil::ToString(m_Request->GetReferrerURL());
	}

	virtual void GetHeaderMap(QMap<QString, QString>& headerMap) {
		std::multimap<CefString, CefString> map;
		m_Request->GetHeaderMap(map);
		return QCefUtil::CopyMap(map,headerMap);
	}


private:
	CefRefPtr<CefRequest> m_Request;
};


class QCefResponse {

public:
	QCefResponse(const CefRefPtr<CefResponse> p_Response)
	{
		m_Response = p_Response;
	}
	~QCefResponse()
	{
	}

	virtual bool IsReadOnly() {
		return m_Response->IsReadOnly();
	}
	virtual int GetStatus() {
		return m_Response->GetStatus();
	}
	virtual void SetStatus(int status) {
		m_Response->SetStatus(status);
	}

	virtual QString GetStatusText() {
		return QCefUtil::ToString(m_Response->GetStatusText());
	}
	virtual void SetStatusText(const QString& statusText) {
		return  m_Response->SetStatusText(QCefUtil::ToString(statusText));
	}

	virtual QString GetMimeType() {
		return QCefUtil::ToString(m_Response->GetMimeType());
	}

	virtual void SetMimeType(const QString& mimeType) {
		CefString mime = QCefUtil::ToString(mimeType);
		return  m_Response->SetMimeType(mime);
	}

private:
	CefRefPtr<CefResponse> m_Response;
};



class QCefFrame {
public:
	QCefFrame(const CefRefPtr<CefFrame> p_Frame)
	{
		m_Frame = p_Frame;
	}
	~QCefFrame()
	{
	}

	virtual bool IsValid() {
		return m_Frame->IsValid();
	}

	virtual void Undo() {
		m_Frame->Undo();
	}

	virtual void Redo() {
		m_Frame->Redo();
	}

	virtual void Cut() {
		m_Frame->Cut();
	}


	virtual void Copy() {
		m_Frame->Copy();
	}


	virtual void Paste() {
		m_Frame->Paste();
	}

	virtual void Delete() {
		m_Frame->Delete();
	}

	virtual void SelectAll() {
		m_Frame->SelectAll();
	}

	virtual void ViewSource() {
		m_Frame->ViewSource();
	}

	virtual void LoadURL(const QString& url) {
		m_Frame->LoadURL(QCefUtil::ToString(url));
	}
	virtual void LoadString(const QString& string_val) {
		this->LoadString(string_val, QString(""));
	}
	virtual void LoadString(const QString& string_val,
		const QString& url) {
		m_Frame->LoadString(QCefUtil::ToString(string_val), QCefUtil::ToString(url));
	}

	virtual void ExecuteJavaScript(const QString& code) {
		this->ExecuteJavaScript(code, QString(""), 0);
	}
	virtual void ExecuteJavaScript(const QString& code,
		const QString& script_url,
		int start_line) {
		m_Frame->ExecuteJavaScript(QCefUtil::ToString(code), QCefUtil::ToString(script_url), start_line);
	}

	virtual bool IsMain() {
		return m_Frame->IsMain();
	}

	virtual bool IsFocused() {
		return m_Frame->IsFocused();
	}
	virtual QString GetName() {
		return QCefUtil::ToString(m_Frame->GetName());
	}
	virtual INT64 GetIdentifier() {
		return m_Frame->GetIdentifier();
	}

	virtual QString GetURL() {
		return QCefUtil::ToString(m_Frame->GetURL());
	}


private:
	CefRefPtr<CefFrame> m_Frame;
};

class QCefBrowser {
public:
	QCefBrowser(const CefRefPtr<CefBrowser> p_Browser)
	{
		m_Browser = p_Browser;
	}
	~QCefBrowser()
	{
	}

	virtual bool CanGoBack() {
		return m_Browser->CanGoBack();
	}


	virtual void GoBack() {
		m_Browser->GoBack();
	}


	virtual bool CanGoForward() {
		return m_Browser->CanGoForward();
	}

	virtual void GoForward() {
		return m_Browser->GoForward();
	}


	virtual bool IsLoading() {
		return m_Browser->IsLoading();
	}

	virtual void Reload() {
		m_Browser->Reload();
	}


	virtual void ReloadIgnoreCache() {
		m_Browser->ReloadIgnoreCache();
	}

	virtual void StopLoad() {
		m_Browser->StopLoad();
	}


	virtual int GetIdentifier() {
		return m_Browser->GetIdentifier();
	}


	virtual bool IsPopup() {
		return m_Browser->IsPopup();
	}


	virtual bool HasDocument() {
		return m_Browser->HasDocument();
	}
	virtual size_t GetFrameCount() {
		return m_Browser->GetFrameCount();
	}

	virtual void GetFrameNames(std::vector<QString>& names) {
		std::vector<CefString> cefnames= std::vector<CefString>();
		m_Browser->GetFrameNames(cefnames);
		QCefUtil::CopyList(cefnames, names);
	}

private:
	CefRefPtr<CefBrowser> m_Browser;
};


class QCefCallback {
public:
	QCefCallback(const CefRefPtr<CefCallback> p_Callback)
	{
		m_Callback = p_Callback;
	}
	~QCefCallback()
	{
	}
	virtual void Continue() {
		m_Callback->Continue();
	}

	virtual void Cancel() {
		m_Callback->Cancel();
	}

private:
	CefRefPtr<CefCallback> m_Callback;
};