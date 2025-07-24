// UnstuffDlg.h : interface of the CUnstuffDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

class CUnstuffDlg : public CDialogImpl<CUnstuffDlg>
{
public:
	enum { IDD = IDD_UNSTUFF };
	BEGIN_MSG_MAP(CUnstuffDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	END_MSG_MAP()
	CTreeItem* ti = nullptr;
	SharedCache* sc = nullptr;
	CStatic m_Text;
	CProgressBarCtrl m_Progress;
	CString path;
	CString start;
// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		CenterWindow(GetParent());
		m_Text.Attach(GetDlgItem(IDC_UNSTUFFTEXT));
		m_Progress.Attach(GetDlgItem(IDC_UNSTUFFPROG));
		DWORD dwThreadId;
		HANDLE hThread;
		ti = reinterpret_cast<CTreeItem*>(reinterpret_cast<DWORD*>(lParam)[0]);
		sc = reinterpret_cast<SharedCache*>(reinterpret_cast<DWORD*>(lParam)[1]);
		path = *reinterpret_cast<CString*>(reinterpret_cast<DWORD*>(lParam)[2]);
		hThread = CreateThread(nullptr, 0, Show, reinterpret_cast<LPVOID>(this), 0, &dwThreadId);
		return TRUE;
	}
	void TreeWalker(CTreeItem &ti, std::vector<int> *ret)
	{
		do
		{
			const int out = ti.GetData()-1;
			if(out < 0)
				TreeWalker(ti.GetChild(), ret);
			else
				ret->push_back(out);
			ti = ti.GetNextSibling();
		}while(ti);
	}
	static DWORD WINAPI Show(LPVOID lpParam)
	{
		auto* me = reinterpret_cast<CUnstuffDlg*>(lpParam);
		std::vector<int> ret;
		me->TreeWalker(me->ti->GetChild(), &ret);
		const dword size = static_cast<dword>(ret.size());
		me->m_Progress.SetRange(0, size);
		for(dword i = 0; i < size; ++i)
		{
			CacheEntry *sce = &me->sc->index[ret[i]];
			me->m_Text.SetWindowText(sce->filename.c_str());
			me->m_Progress.SetPos(i);
			me->sc->SaveFile(*sce, me->path, true);
		}
		me->EndDialog(0);
		return 0;
	}
};
