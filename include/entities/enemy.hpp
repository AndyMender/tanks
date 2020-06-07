/*
 * enemy.hpp
 *
 *  Created on: Jun 3, 2020
 *      Author: amender
 */

#pragma once

#include <vector>

#include <entities/bullet.hpp>
#include <entities/entity.hpp>
#include <entities/objects.hpp>
#include <entities/ranged.hpp>


/**
 * Class for enemy entities.
 */
class EnemyEntity: public RangedEntity {
using RangedEntity::RangedEntity;

public:
	EnemyEntity();
	EnemyEntity(const EntityBlueprint&);

	void moveLeft(const float);
	void moveRight(const float);
	void moveUp(const float);
	void moveDown(const float);

	void update() override {};
	void update(std::vector<BulletEntity>&);

	void draw() const override {};
	void drawStencils() const override;
};
