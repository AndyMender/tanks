/*
 * ranged.hpp
 *
 *  Created on: May 16, 2020
 *      Author: amender
 */

#pragma once

#include <vector>

#include <entities/bullet.hpp>
#include <entities/entity.hpp>
#include <entities/objects.hpp>


/**
 * Base class for shooting entities.
 */
class RangedEntity: public Entity {
using Entity::Entity;

public:
	RangedEntity();
	RangedEntity(const EntityBlueprint&);

	virtual void update() override = 0;

	virtual void draw() const override = 0;
	virtual void drawStencils() const override = 0;

	BulletEntity shootBullet();

protected:
	int maxBullets;
	float bulletSpeed;
	float bulletRange;
};
