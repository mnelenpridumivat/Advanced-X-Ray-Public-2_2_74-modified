#pragma once
#include "UIScrollBar.h"

class CUI3tButton;
class CUIScrollBox;
class CUIFrameLineWnd;

class CUIFixedScrollBar :public CUIScrollBar
{
private:
	typedef CUIWindow inherited;
protected:
	CUI3tButton*		m_ScrollBox;
	Ivector2			m_ScrollBoxOffset;

	void UpdateScrollBar() override;
	void ClampByViewRect() override;
	void SetPosScrollFromView(float view_pos, float view_width, float view_offs) override;
public:
	CUIFixedScrollBar();
	~CUIFixedScrollBar() override;
	virtual	void InitScrollBar(Fvector2 pos, bool horizontal, LPCSTR profile = "pda");
	void SetWidth(float width) override {};
	void SetHeight(float height) override {};
	void Draw() override {inherited::Draw();};

	void SendMessage(CUIWindow *pWnd, s16 msg, void *pData) override;
	bool OnMouseAction(float x, float y, EUIMessages mouse_action) override;
	bool OnMouseDown(int mouse_btn) override;
	bool OnMouseDownEx() override;
	void OnMouseUp(int mouse_btn) override;
	bool OnKeyboardHold(int dik) override;

};
