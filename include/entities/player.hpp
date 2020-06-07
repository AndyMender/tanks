/*
 * player.hpp
 *
 *  Created on: May 7, 2020
 *      Author: amender
 */

#pragma once

#include <vector>

#include <allegro5/allegro.h>

#include <entities/bullet.hpp>
#include <entities/entity.hpp>
#include <entities/objects.hpp>
#include <entities/ranged.hpp>


/**
 * Player entity.
 */
class Player: public RangedEntity {
using RangedEntity::RangedEntity;

public:
	Player();
	Player(const EntityBlueprint&);

	void moveLeft(const float);
	void moveRight(const float);
	void moveUp(const float);
	void moveDown(const float);

	void update() override {};
	void update(const ALLEGRO_EVENT&, std::vector<BulletEntity>&);

	void draw() const override {};
	void drawStencils() const override;
};
