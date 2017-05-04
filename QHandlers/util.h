#pragma once
#include <qmap.h> 
#include "stdafx.h"

class QCefUtil {
public:
	static QString ToString(CefString  p_String) 
	{
		return QString::fromStdWString(p_String.ToWString());
	}
	static CefString ToString(QString  p_String)
	{
		return CefString(p_String.toStdWString());
	}
	static void CopyMap(std::multimap<CefString, CefString>& p_SourceMap, QMap<QString, QString>& p_TargetMap)
	{
		std::multimap<CefString, CefString>::iterator begin, end;
		begin = p_SourceMap.begin();
		end = p_SourceMap.end();
		while (begin != end)
		 {
			p_TargetMap.insert(QCefUtil::ToString(begin->first), QCefUtil::ToString(begin->second));
			 ++begin;
		}
	}

	static void CopyMap(QMap<QString, QString>& p_SourceMap,std::multimap<CefString, CefString>& p_TargetMap)
	{
		QMap<QString, QString>::iterator begin, end;
		begin = p_SourceMap.begin();
		end = p_SourceMap.end();
		while (begin != end)
		{
			CefString key= QCefUtil::ToString(begin.key());
			CefString value= QCefUtil::ToString(begin.value());
			p_TargetMap.insert(std::pair<CefString, CefString>(key, value));
			++begin;
		}
	}
	static void CopyList(std::vector<QString>& p_Source, std::vector<CefString>& p_Target)
	{
		size_t size = p_Source.size();
		for (int i = 0; i < size; i++)
		{
			p_Target.push_back(QCefUtil::ToString(p_Source.at(i)));
		}
	}
	static void CopyList(std::vector<CefString>& p_Source, std::vector<QString>& p_Target)
	{
		size_t size = p_Source.size();
		for (int i = 0; i < size; i++)
		{
			p_Target.push_back(QCefUtil::ToString(p_Source.at(i)));
		}
	}
};