/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/RenderThread.hpp"
#include "game/player/HumanPlayer.hpp"

game::player::HumanPlayer::HumanPlayer(gfx::RenderThread& render_thread) :
	Player(Type::HUMAN, render_thread.getMemoryPool()),
	m_render_thread(render_thread)
{
}

game::player::HumanPlayer::~HumanPlayer()
{
}

bool game::player::HumanPlayer::feed(const GL::Event& ev)
{
	return false;
}

void game::player::HumanPlayer::update()
{
	getServerEventQueue().dequeue(*this);
}

void game::player::HumanPlayer::handle(event::PlayerAcceptedEvent& ev)
{
}

void game::player::HumanPlayer::handle(event::PlayerRejectedEvent& ev)
{
}

void game::player::HumanPlayer::handle(event::PlayerUpdateEvent& ev)
{
}

void game::player::HumanPlayer::handle(event::TickEvent& ev)
{
	getEntityEventQueue().dequeue(*this);
}

void game::player::HumanPlayer::handle(event::AddHubEvent& ev)
{
	auto& data = ev.get<0>();
	auto& scene = m_render_thread.getScene();

	scene.addHub(data.id, data.seed, data.size, data.position);
}

void game::player::HumanPlayer::handle(event::AddTransportEvent& ev)
{
	auto& data = ev.get<0>();
	auto& scene = m_render_thread.getScene();

	scene.addTransport(data.id, data.position1.hub_id, data.position1.platform_id, data.position2.hub_id, data.position2.platform_id);
}

void game::player::HumanPlayer::handle(event::AddChargeEvent& ev)
{
	auto& data = ev.get<0>();
	auto& scene = m_render_thread.getScene();

	scene.addCharge(data.id, data.position.hub_id, data.position.platform_id);
}

void game::player::HumanPlayer::handle(event::AddResourceEvent& ev)
{
	auto& data = ev.get<0>();
	auto& scene = m_render_thread.getScene();

	scene.addResource(data.id, data.value, data.position.hub_id, data.position.platform_id);
}

void game::player::HumanPlayer::handle(event::AddTraceEvent& ev)
{
	auto& data = ev.get<0>();
	auto& scene = m_render_thread.getScene();

	scene.addTrace(data.id, data.color, data.position.hub_id, data.position.platform_id);
}

void game::player::HumanPlayer::handle(event::AddSpawnEvent& ev)
{
	auto& data = ev.get<0>();
	auto& scene = m_render_thread.getScene();

	scene.addSpawn(data.id, data.color, data.position.hub_id, data.position.platform_id);
}

void game::player::HumanPlayer::handle(event::AddPortalEvent& ev)
{
	auto& data = ev.get<0>();
	auto& scene = m_render_thread.getScene();

	scene.addPortal(data.id, data.position.hub_id, data.position.platform_id);
}

void game::player::HumanPlayer::handle(event::AddTrapEvent& ev)
{
	auto& data = ev.get<0>();
	auto& scene = m_render_thread.getScene();

	scene.addTrap(data.id, data.color, data.position.hub_id, data.position.platform_id);
}

void game::player::HumanPlayer::handle(event::AddCreatureEvent& ev)
{
	auto& data = ev.get<0>();
	auto& scene = m_render_thread.getScene();

	scene.addCreature(data.id, data.seed, data.color, data.position.hub_id, data.position.platform_id);
}

void game::player::HumanPlayer::handle(event::RemoveChargeEvent& ev)
{
	auto& data = ev.get<0>();
	auto& scene = m_render_thread.getScene();

	scene.removeCharge(data.id);
}

void game::player::HumanPlayer::handle(event::RemoveResourceEvent& ev)
{
	auto& data = ev.get<0>();
	auto& scene = m_render_thread.getScene();

	scene.removeResource(data.id);
}

void game::player::HumanPlayer::handle(event::RemoveTraceEvent& ev)
{
	auto& data = ev.get<0>();
	auto& scene = m_render_thread.getScene();

	scene.removeTrace(data.id);
}

void game::player::HumanPlayer::handle(event::RemoveTrapEvent& ev)
{
	auto& data = ev.get<0>();
	auto& scene = m_render_thread.getScene();

	scene.removeTrap(data.id);
}

void game::player::HumanPlayer::handle(event::RemoveCreatureEvent& ev)
{
	auto& data = ev.get<0>();
	auto& scene = m_render_thread.getScene();

	scene.removeCreature(data.id);
}

void game::player::HumanPlayer::handle(event::ChangeHubColorEvent& ev)
{
	auto& data = ev.get<0>();
	auto& scene = m_render_thread.getScene();

	scene.changeHubColor(data.id, data.color);
}

void game::player::HumanPlayer::handle(event::ChangeSpawnColorEvent& ev)
{
	auto& data = ev.get<0>();
	auto& scene = m_render_thread.getScene();

	scene.changeSpawnColor(data.id, data.color);
}

void game::player::HumanPlayer::handle(event::ChangeCreatureColorEvent& ev)
{
	auto& data = ev.get<0>();
	auto& scene = m_render_thread.getScene();

	scene.changeCreatureColor(data.id, data.color);
}

void game::player::HumanPlayer::handle(event::MoveCreatureEvent& ev)
{
	auto& data = ev.get<0>();
	auto& scene = m_render_thread.getScene();

	scene.moveCreature(data.id, data.position.hub_id, data.position.platform_id);
}
