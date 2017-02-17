/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <cmath>
#include <raz/random.hpp>
#include "common/PI.hpp"
#include "common/Point2D.hpp"
#include "common/BezierCurve.hpp"
#include "ui/scene/Scene.hpp"
#include "ui/scene/model/CreatureModel.hpp"

#pragma warning(push)
#pragma warning(disable: 4267) // possible loss of data

static void insertRingPoints(size_t edges, float height, float radius, GL::Color color, ui::core::MeshBuffer<>& meshbuffer)
{
	const float angle_step = static_cast<float>(common::PI * 2 / edges);
	float angle_rad = 0.f;

	for (size_t i = 0; i < edges; ++i)
	{
		float x = std::sin(angle_rad);
		float z = std::cos(angle_rad);

		ui::core::Vertex v { GL::Vec3(x * radius, height, z * radius), GL::Vec3(x, 0.f, z), color };
		meshbuffer.vertices.push_back(v);
		
		angle_rad += angle_step;
	}
}

static void insertFirstRing(size_t edges, float height, float radius, GL::Color color, ui::core::MeshBuffer<>& meshbuffer)
{
	uint16_t base_index = (uint16_t)meshbuffer.vertices.size();
	insertRingPoints(edges, height, radius, color, meshbuffer);

	for (unsigned i = 1; i < edges - 1; ++i)
	{
		meshbuffer.indices.push_back(base_index);
		meshbuffer.indices.push_back(base_index + i + 1);
		meshbuffer.indices.push_back(base_index + i);
	}

	for (unsigned i = 0; i < edges; ++i)
	{
		uint16_t top1 = base_index + i;
		uint16_t top2 = base_index + ((i + 1) % edges);
		uint16_t bottom1 = base_index + i + edges;
		uint16_t bottom2 = base_index + ((i + 1) % edges) + edges;

		meshbuffer.indices.push_back(top1);
		meshbuffer.indices.push_back(top2);
		meshbuffer.indices.push_back(bottom1);

		meshbuffer.indices.push_back(top2);
		meshbuffer.indices.push_back(bottom2);
		meshbuffer.indices.push_back(bottom1);
	}
}

static void insertRing(size_t edges, float height, float radius, GL::Color color, ui::core::MeshBuffer<>& meshbuffer)
{
	uint16_t base_index = (uint16_t)meshbuffer.vertices.size();
	insertRingPoints(edges, height, radius, color, meshbuffer);

	for (unsigned i = 0; i < edges; ++i)
	{
		uint16_t top1 = base_index + i;
		uint16_t top2 = base_index + ((i + 1) % edges);
		uint16_t bottom1 = base_index + i + edges;
		uint16_t bottom2 = base_index + ((i + 1) % edges) + edges;

		meshbuffer.indices.push_back(top1);
		meshbuffer.indices.push_back(top2);
		meshbuffer.indices.push_back(bottom1);

		meshbuffer.indices.push_back(top2);
		meshbuffer.indices.push_back(bottom2);
		meshbuffer.indices.push_back(bottom1);
	}
}

static void insertLastRing(size_t edges, float height, float radius, GL::Color color, ui::core::MeshBuffer<>& meshbuffer)
{
	uint16_t base_index = (uint16_t)meshbuffer.vertices.size();
	insertRingPoints(edges, height, radius, color, meshbuffer);

	for (unsigned i = 1; i < edges - 1; ++i)
	{
		meshbuffer.indices.push_back(base_index);
		meshbuffer.indices.push_back(base_index + i);
		meshbuffer.indices.push_back(base_index + i + 1);
	}
}

#pragma warning(pop)


ui::scene::model::CreatureModel::CreatureModel(scene::Scene& scene)
{
	GL::Color color(255, 240, 240);
	const size_t height = 6;
	//std::vector<size_t, raz::Allocator<size_t>> dimensions;
	raz::Random random(123456789);


	common::BezierCurve<common::Point2D<float>> curve;
	curve.addPoint({ 0.f, 0.f });
	for (size_t i = 0; i < height; ++i)
	{
		float r = 0.0625f * random(1, 5);
		float h = 0.25f * i;
		curve.addPoint({ r, h - 0.0625f });
		curve.addPoint({ r, h });
		curve.addPoint({ r, h + 0.0625f });
	}
	curve.addPoint({ 0.f, 0.f });

	core::MeshBuffer<> meshbuffer;

	//float max_height = 0.25f * (height);
	//insertFirstRing(6, max_height, 0.065f, color, meshbuffer);
	//for (size_t i = 0; i < height; ++i)
	//{
	//	float h = max_height - (0.25f * (i + 1));
	//	insertRing(6, h + 0.0625f, 0.0625f * dimensions[i], color, meshbuffer);
	//	insertRing(6, h - 0.0625f, 0.0625f * dimensions[i], color, meshbuffer);
	//}
	//insertLastRing(6, 0.f, 0.065f, color, meshbuffer);

	{
		const size_t detail = height * 4;

		auto pfirst = curve(0.f);
		insertFirstRing(8, pfirst.y, pfirst.x, color, meshbuffer);

		for (size_t i = 1; i < detail; ++i)
		{
			float t = (float)i / detail;
			auto p = curve(t);
			insertRing(8, p.y, p.x, color, meshbuffer);
		}

		auto plast = curve(1.f);
		insertLastRing(8, plast.y, plast.x, color, meshbuffer);
	}


	meshbuffer.recalculateNormals();

	auto& mesh = getMesh();
	mesh = meshbuffer.createMesh();
	mesh.bindShader(scene.getShader("hub"_shader));

	setPosition({ 10.f, 0.f, 0.f });
}

void ui::scene::model::CreatureModel::render(scene::Scene& scene)
{
	GL::Mat4 world;
	GL::Mat4 normal;
	getMatrices(world, normal);

	auto& program = scene.getCurrentShader();
	program.SetUniform("world_mat", world);
	program.SetUniform("normal_mat", normal);
	program.SetUniform("screen_mat", scene.getCameraMatrix() * world);
	program.SetUniform("light_source", scene.getCamera().getPosition());

	GL::Context& gl = scene.getContext();
	getMesh().render(gl);
}
