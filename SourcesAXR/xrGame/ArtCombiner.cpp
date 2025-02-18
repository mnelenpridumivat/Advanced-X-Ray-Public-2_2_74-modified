#include "stdafx.h"
#include "ArtCombiner.h"
#include "../xrCore/xr_hash_set.h"

void CArtCombiner::Load(LPCSTR section)
{
	CArtefact::Load(section);
	CArtContainer::Load(section);
}

BOOL CArtCombiner::net_Spawn(CSE_Abstract* DC)
{
	return CArtefact::net_Spawn(DC);
}

void CArtCombiner::save(NET_Packet& output_packet)
{
	CArtefact::save(output_packet);
	CArtContainer::save(output_packet);
}

void CArtCombiner::load(IReader& input_packet)
{
	CArtefact::load(input_packet);
	CArtContainer::load(input_packet);
}

u32 CArtCombiner::Cost() const
{
	auto res = CArtefact::Cost();
	res += CArtContainer::Cost();
	return res;
}

float CArtCombiner::Weight() const
{
	auto res = CArtefact::Weight();
	res += CArtContainer::Weight();
	return res;
}

bool CArtCombiner::CanStoreArt(CArtefact* art)
{
	return smart_cast<CArtCombiner*>(art) == nullptr;
}

bool CArtCombiner::CheckInventoryIconItemSimilarity(CInventoryItem* other)
{
	if (!inherited::CheckInventoryIconItemSimilarity(other))
	{
		return false;
	}
	auto comb = smart_cast<CArtCombiner*>(other);
	VERIFY(comb);
	if(comb->m_sArtefactsInside.size() != m_sArtefactsInside.size())
	{
		return false;
	}
	xr_hash_set<xr_string> sections;
	sections.reserve(m_sArtefactsInside.size() * 2);
	for (const auto& art : m_sArtefactsInside) {
		sections.insert(art->m_section_id.c_str());
	}
	for (const auto& art : comb->m_sArtefactsInside) {
		sections.insert(art->m_section_id.c_str());
	}
	return sections.size() == m_sArtefactsInside.size();
}

float CArtCombiner::GetHealthPower() const
{
	auto base = CArtefact::GetHealthPower();

	for (const auto& artefact : m_sArtefactsInside)
	{
		base += artefact->GetHealthPower();
	}

	return base;
}

float CArtCombiner::GetRadiationPower() const
{
	auto base = CArtefact::GetRadiationPower();

	for (const auto& artefact : m_sArtefactsInside)
	{
		base += artefact->GetRadiationPower();
	}

	return base;
}

float CArtCombiner::GetSatietyPower() const
{
	auto base = CArtefact::GetSatietyPower();

	for (const auto& artefact : m_sArtefactsInside)
	{
		base += artefact->GetSatietyPower();
	}

	return base;
}

float CArtCombiner::GetPowerPower() const
{
	auto base = CArtefact::GetPowerPower();

	for (const auto& artefact : m_sArtefactsInside)
	{
		base += artefact->GetPowerPower();
	}

	return base;
}

float CArtCombiner::GetBleedingPower() const
{
	auto base = CArtefact::GetBleedingPower();

	for (const auto& artefact : m_sArtefactsInside)
	{
		base += artefact->GetBleedingPower();
	}

	return base;
}

float CArtCombiner::AdditionalInventoryWeight() const
{
	auto base = CArtefact::AdditionalInventoryWeight();

	for (const auto& artefact : m_sArtefactsInside)
	{
		base += artefact->AdditionalInventoryWeight();
	}

	return base;
}

float CArtCombiner::GetThirstPower() const
{
	auto base = CArtefact::GetThirstPower();

	for (const auto& artefact : m_sArtefactsInside)
	{
		base += artefact->GetThirstPower();
	}

	return base;
}

float CArtCombiner::GetIntoxicationPower() const
{
	auto base = CArtefact::GetIntoxicationPower();

	for (const auto& artefact : m_sArtefactsInside)
	{
		base += artefact->GetIntoxicationPower();
	}

	return base;
}

float CArtCombiner::GetSleepenessPower() const
{
	auto base = CArtefact::GetSleepenessPower();

	for (const auto& artefact : m_sArtefactsInside)
	{
		base += artefact->GetSleepenessPower();
	}

	return base;
}

float CArtCombiner::GetAlcoholismPower() const
{
	auto base = CArtefact::GetAlcoholismPower();

	for (const auto& artefact : m_sArtefactsInside)
	{
		base += artefact->GetAlcoholismPower();
	}

	return base;
}

float CArtCombiner::GetNarcotismPower() const
{
	auto base = CArtefact::GetNarcotismPower();

	for (const auto& artefact : m_sArtefactsInside)
	{
		base += artefact->GetNarcotismPower();
	}

	return base;
}

float CArtCombiner::GetPsyHealthPower() const
{
	auto base = CArtefact::GetPsyHealthPower();

	for (const auto& artefact : m_sArtefactsInside)
	{
		base += artefact->GetPsyHealthPower();
	}

	return base;
}

float CArtCombiner::GetJumpPower() const
{
	auto base = CArtefact::GetJumpPower();

	for (const auto& artefact : m_sArtefactsInside)
	{
		base *= artefact->GetJumpPower();
	}

	return base;
}

float CArtCombiner::GetWalkPower() const
{
	auto base = CArtefact::GetWalkPower();

	for (const auto& artefact : m_sArtefactsInside)
	{
		base *= artefact->GetWalkPower();
	}

	return base;
}

float CArtCombiner::GetImmunity(ALife::EHitType hit_type)
{
	auto base = m_ArtefactHitImmunities.GetHitImmunity(hit_type);

	for (const auto& artefact : m_sArtefactsInside)
	{
		base += artefact->GetImmunity(hit_type);
	}
	return base;
}

float CArtCombiner::ArtAffectHit(float power, ALife::EHitType hit_type)
{
	auto base = CArtefact::ArtAffectHit(power, hit_type);

	for (const auto& artefact : m_sArtefactsInside)
	{
		base += artefact->ArtAffectHit(power, hit_type);
	}
	return base;
}
