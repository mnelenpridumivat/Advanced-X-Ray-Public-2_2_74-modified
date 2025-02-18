#pragma once
#include "UIWindow.h"
#include "UIWndCallback.h"
#include "../../xrServerEntities/associative_vector.h"
#include "../GameTaskDefs.h"
#include "UICheckButton.h"

class CUIMapWnd;
class CUIStatic;
class CGameTask;
class CUIXml;
class CUITaskItem;
class CUI3tButton;
class CUIFrameLineWnd;
class CUIFrameWindow;
class CUICheckButton;
class UITaskListWnd;
class UIMapLegend;
class UIHint;

class CUITaskWnd			:	public CUIWindow, 
								public CUIWndCallback
{
private:
	typedef CUIWindow		inherited;

	CUIFrameWindow*			m_background;
	CUIStatic*				m_center_background;
	CUIStatic*				m_right_bottom_background;

	CUIMapWnd*				m_pMapWnd;
	CUITaskItem*			m_pStoryLineTaskItem;

	CUI3tButton*			m_BtnTaskListWnd;
	CUIStatic*				m_devider;
	u32						m_actual_frame;

	CUI3tButton*			m_btn_focus;
	
	CUICheckButton*			m_cbTreasures;
	CUICheckButton*			m_cbQuestNpcs;
	CUICheckButton*			m_cbSecondaryTasks;
	CUICheckButton*			m_cbPrimaryObjects;
	bool					m_bTreasuresEnabled;
	bool					m_bQuestNpcsEnabled;
	bool					m_bSecondaryTasksEnabled;
	bool					m_bPrimaryObjectsEnabled;

	UITaskListWnd*			m_task_wnd;
	bool					m_task_wnd_show;
	UIMapLegend*			m_map_legend_wnd;

public:
	UIHint*					hint_wnd;

public:
								CUITaskWnd				();
	~CUITaskWnd				() override;
	void				SendMessage				(CUIWindow* pWnd, s16 msg, void* pData) override;
			void				Init					();
	void				Update					() override;
	void				Draw					() override;
			void				DrawHint				();
	void				Show					(bool status) override;
	void				Reset					() override;

			void				ReloadTaskInfo			();
			void				ShowMapLegend			(bool status);
			void				Switch_ShowMapLegend	();

			bool				IsTreasuresEnabled		(){return m_bTreasuresEnabled;};
			bool				IsQuestNpcsEnabled		(){return m_bQuestNpcsEnabled;};
			bool				IsSecondaryTasksEnabled	(){return m_bSecondaryTasksEnabled;};
			bool				IsPrimaryObjectsEnabled	(){return m_bPrimaryObjectsEnabled;};
			void				TreasuresEnabled		(bool enable) {m_bTreasuresEnabled = enable; m_cbTreasures->SetCheck(enable);};
			void				QuestNpcsEnabled		(bool enable) {m_bQuestNpcsEnabled = enable; m_cbQuestNpcs->SetCheck(enable);};
			void				SecondaryTasksEnabled	(bool enable) {m_bSecondaryTasksEnabled = enable; m_cbSecondaryTasks->SetCheck(enable);};
			void				PrimaryObjectsEnabled	(bool enable) {m_bPrimaryObjectsEnabled = enable; m_cbPrimaryObjects->SetCheck(enable);};

			void				Show_TaskListWnd		(bool status);

private:
	void						TaskSetTargetMap		(CGameTask* task);
	void						TaskShowMapSpot			(CGameTask* task, bool show);

	void						OnNextTaskClicked		();
	void 						OnPrevTaskClicked		();
	void xr_stdcall				OnShowTaskListWnd		(CUIWindow* w, void* d);
	void xr_stdcall				OnTask1DbClicked		(CUIWindow*, void*);

	void xr_stdcall				OnShowTreasures			(CUIWindow*, void*);
	void xr_stdcall				OnShowPrimaryObjects	(CUIWindow*, void*);
	void xr_stdcall				OnShowSecondaryTasks	(CUIWindow*, void*);
	void xr_stdcall				OnShowQuestNpcs			(CUIWindow*, void*);
};

class CUITaskItem : public CUIWindow
{
private:
	typedef CUIWindow			inherited;

	associative_vector<shared_str, CUIStatic*>			m_info;
	CGameTask*											m_owner;
public:
								CUITaskItem				();
	~CUITaskItem			() override;

	void 				OnFocusReceive			() override;
	void	 			OnFocusLost				() override;
	void				Update					() override;
	void				OnMouseScroll			(float iDirection) override;
	bool				OnMouseAction					(float x, float y, EUIMessages mouse_action) override;
	void				SendMessage				(CUIWindow* pWnd, s16 msg, void* pData) override;

	void						Init					(CUIXml& uiXml, LPCSTR path);
	void						InitTask				(CGameTask* task);
	CGameTask*					OwnerTask				()							{return m_owner;}

public:
	bool						show_hint_can;
	bool						show_hint;

protected:
	u32							m_hint_wt;
};