#include "stdafx.h"
#include "WeaponBinoculars.h"

#include "xr_level_controller.h"

#include "level.h"
#include "ui\UIFrameWindow.h"
#include "WeaponBinocularsVision.h"
#include "object_broker.h"
#include "hudmanager.h"
#include "inventory.h"

CWeaponBinoculars::CWeaponBinoculars()
{
	m_binoc_vision	= NULL;
	m_bVision		= false;
}

CWeaponBinoculars::~CWeaponBinoculars()
{
	xr_delete				(m_binoc_vision);
}

void CWeaponBinoculars::Load	(LPCSTR section)
{
	inherited::Load(section);

	// Sounds
	m_sounds.LoadSound(section, "snd_zoomin",  "sndZoomIn",		false, SOUND_TYPE_ITEM_USING);
	m_sounds.LoadSound(section, "snd_zoomout", "sndZoomOut",	false, SOUND_TYPE_ITEM_USING);
	m_bVision = !!pSettings->r_bool(section,"vision_present");
}


bool CWeaponBinoculars::Action(s32 cmd, u32 flags) 
{
	switch(cmd) 
	{
	case kWPN_FIRE : 
		return inherited::Action(kWPN_ZOOM, flags);
	}

	return inherited::Action(cmd, flags);
}

// Lex Addon (correct by Suhar_) 24.10.2018		(begin)
//      
float LastBinocZoomFactor = NULL;

void CWeaponBinoculars::OnZoomIn()
{
	if(H_Parent() && !IsZoomed())
	{
		m_sounds.StopSound("sndZoomOut");
		bool b_hud_mode = (Level().CurrentEntity() == H_Parent());
		m_sounds.PlaySound("sndZoomIn", H_Parent()->Position(), H_Parent(), b_hud_mode);
		if(m_bVision && !m_binoc_vision) 
		{
			m_binoc_vision	= xr_new<CBinocularsVision>(cNameSect());
		}
	}
	inherited::OnZoomIn();

	if (LastBinocZoomFactor)
		m_fRTZoomFactor = LastBinocZoomFactor;
	else
		m_fRTZoomFactor = CurrentZoomFactor();
	float delta, min_zoom_factor;
	GetZoomData(m_zoom_params.m_fScopeZoomFactor, delta, min_zoom_factor);

	clamp(m_fRTZoomFactor, m_zoom_params.m_fScopeZoomFactor, min_zoom_factor);
	SetZoomFactor(m_fRTZoomFactor);
}
// Lex Addon (correct by Suhar_) 24.10.2018		(end)

void CWeaponBinoculars::OnZoomOut		()
{
	if(H_Parent() && IsZoomed() && !IsRotatingToZoom())
	{
		m_sounds.StopSound("sndZoomIn");
		bool b_hud_mode = (Level().CurrentEntity() == H_Parent());	
		m_sounds.PlaySound("sndZoomOut", H_Parent()->Position(), H_Parent(), b_hud_mode);
		VERIFY			(m_binoc_vision);
		xr_delete		(m_binoc_vision);
	}


	inherited::OnZoomOut();
}

BOOL CWeaponBinoculars::net_Spawn(CSE_Abstract* DC)
{
	inherited::net_Spawn	(DC);
	return					TRUE;
}

void	CWeaponBinoculars::net_Destroy()
{
	inherited::net_Destroy();
	xr_delete(m_binoc_vision);
}

void	CWeaponBinoculars::UpdateCL()
{
	inherited::UpdateCL();
	//manage visible entities here...
	if(H_Parent() && IsZoomed() && !IsRotatingToZoom() && m_binoc_vision)
		m_binoc_vision->Update();
}

bool CWeaponBinoculars::render_item_ui_query()
{
	bool b_is_active_item = m_pInventory->ActiveItem()==this;
	return b_is_active_item && H_Parent() && IsZoomed() && !IsRotatingToZoom() && m_binoc_vision;
}

void CWeaponBinoculars::render_item_ui()
{
	m_binoc_vision->Draw();
	inherited::render_item_ui	();
}

void CWeaponBinoculars::ZoomInc()
{
	float delta,min_zoom_factor;
	GetZoomData(m_zoom_params.m_fScopeZoomFactor, delta, min_zoom_factor);

	float f					= GetZoomFactor()-delta;
	clamp					(f,m_zoom_params.m_fScopeZoomFactor,min_zoom_factor);
	SetZoomFactor			( f );
	// Lex Addon (correct by Suhar_) 24.10.2018		(begin)  
	LastBinocZoomFactor = f;
	// Lex Addon (correct by Suhar_) 24.10.2018		(end)
}

void CWeaponBinoculars::GetZoomData(const float scope_factor, float& delta, float& min_zoom_factor)
{
	float def_fov = float(g_fov);
	float min_zoom_k = 0.3f;
	float zoom_step_count = 3.0f;
	float delta_factor_total = def_fov - scope_factor;
	VERIFY(delta_factor_total > 0);
	min_zoom_factor = def_fov - delta_factor_total * min_zoom_k;
	delta = (delta_factor_total * (1 - min_zoom_k)) / zoom_step_count;
}

void CWeaponBinoculars::ZoomDec()
{
	float delta,min_zoom_factor;
	GetZoomData(m_zoom_params.m_fScopeZoomFactor,delta,min_zoom_factor);

	float f					= GetZoomFactor()+delta;
	clamp					(f,m_zoom_params.m_fScopeZoomFactor,min_zoom_factor);
	SetZoomFactor			( f );
	// Lex Addon (correct by Suhar_) 24.10.2018		(begin)        
	LastBinocZoomFactor = f;
	// Lex Addon (correct by Suhar_) 24.10.2018		(end)
}

void CWeaponBinoculars::save(NET_Packet &output_packet)
{
	inherited::save(output_packet);
	save_data		(m_fRTZoomFactor,output_packet);
}

void CWeaponBinoculars::load(IReader &input_packet)
{
	inherited::load(input_packet);
	load_data		(m_fRTZoomFactor,input_packet);
}

bool CWeaponBinoculars::GetBriefInfo( II_BriefInfo& info )
{
	info.clear();
	info.name._set( m_nameShort );
	info.icon._set( cNameSect() );
	return true;
}

void CWeaponBinoculars::net_Relcase	(CObject *object)
{
	if (!m_binoc_vision)
		return;

	m_binoc_vision->remove_links	(object);
}

bool CWeaponBinoculars::can_kill	() const
{
	return			(false);
}