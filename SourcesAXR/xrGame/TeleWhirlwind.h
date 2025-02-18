#ifndef TELE_WHIRLWIND
#define TELE_WHIRLWIND
#include "ai/monsters/telekinesis.h"
#include "ai/monsters/telekinetic_object.h"
#include "../xrphysics/PHImpact.h"

class CTeleWhirlwind;
class CGameObject;
class CTeleWhirlwindObject : public CTelekineticObject
{
	typedef			CTelekineticObject	inherited;
	CTeleWhirlwind		*m_telekinesis;
	bool				b_destroyable;
	float				throw_power;
	
public:
	virtual							~CTeleWhirlwindObject	(){};
									CTeleWhirlwindObject	();
	bool				init					(CTelekinesis* tele,CPhysicsShellHolder *obj, float s, float h, u32 ttk, bool rot = true) override; 
				void				set_throw_power			(float throw_pow);
	bool				can_activate			(CPhysicsShellHolder *obj) override;
	void				raise					(float step) override;
	void				raise_update			() override;
	void				keep					() override;
	void				release					() override;
	virtual		void				fire					(const Fvector &target);
	void				fire					(const Fvector &target, float power) override;
	void				switch_state			(ETelekineticState new_state) override;
	virtual		bool				destroy_object			(const Fvector dir,float val);


};

class CTeleWhirlwind : public CTelekinesis
{
typedef	CTelekinesis inherited;
		Fvector				m_center;
		float				m_keep_radius;
		float				m_throw_power;
		CGameObject*		m_owner_object;
		PH_IMPACT_STORAGE	m_saved_impacts;
		shared_str			m_destroying_particles;

public: 
								CTeleWhirlwind			();
		CGameObject*    		OwnerObject				()const									{return m_owner_object;}
  const	Fvector&				Center					()const									{return m_center;}
		void					SetCenter				(const Fvector center)					{m_center.set(center);}
		void					SetOwnerObject			(CGameObject* owner_object)				{m_owner_object=owner_object;}
		void					add_impact				(const Fvector& dir,float val)			;
		void					draw_out_impact			(Fvector& dir,float& val)				;
		void					clear_impacts			()										;
		void					set_destroing_particles (const shared_str& destroying_particles){m_destroying_particles=destroying_particles;}
		const shared_str&		destroing_particles		()										{return m_destroying_particles;}
		void					play_destroy			(CTeleWhirlwindObject* obj);
CTelekineticObject*		activate				(CPhysicsShellHolder *obj, float strength, float height, u32 max_time_keep, bool rot = true) override;
void					clear					() override;
void					clear_notrelevant		() override;
CTelekineticObject*		alloc_tele_object		() override {return static_cast<CTelekineticObject*>(xr_new<CTeleWhirlwindObject>());}
		float					keep_radius				()										{return m_keep_radius;}
		void					set_throw_power			(float throw_pow);
};


#endif