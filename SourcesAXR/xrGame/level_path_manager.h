////////////////////////////////////////////////////////////////////////////
//	Module 		: level_path_manager.h
//	Created 	: 02.10.2001
//  Modified 	: 12.11.2003
//	Author		: Dmitriy Iassenev
//	Description : Level path manager
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "abstract_path_manager.h"

template <
	typename _VertexEvaluator,
	typename _vertex_id_type,
	typename _index_type
>
class 
	CBasePathManager<
		CLevelGraph,
		_VertexEvaluator,
		_vertex_id_type,
		_index_type
	> :
	public CAbstractPathManager<
		CLevelGraph,
		_VertexEvaluator,
		_vertex_id_type,
		_index_type
	>
{
	typedef CAbstractPathManager<
		CLevelGraph,
		_VertexEvaluator,
		_vertex_id_type,
		_index_type
	> inherited;
private:
	friend class CMovementManager;
	friend class CLevelPathBuilder;

protected:
	IC void	before_search				(const _vertex_id_type start_vertex_id, const _vertex_id_type dest_vertex_id) override;
	IC void	after_search				() override;
	IC bool	check_vertex				(const _vertex_id_type vertex_id) const override;

public:
	IC					CBasePathManager			(CRestrictedObject *object);
	IC			void	reinit						(const CLevelGraph *graph = nullptr);
	IC			bool	actual						() const;
	IC			void	on_restrictions_change		();
	IC			void	build_path					(const _vertex_id_type start_vertex_id, const _vertex_id_type dest_vertex_id);
};

#include "level_path_manager_inline.h"
