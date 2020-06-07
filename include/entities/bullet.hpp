/*
 * bullet.hpp
 *
 *  Created on: May 11, 2020
 *      Author: amender
 */

#pragma once

#include <entities/entity.hpp>
#include <entities/objects.hpp>


class BulletEntity: public Entity {
using Entity::Entity;

public:
	BulletEntity();
	BulletEntity(const EntityBlueprint&);

	void moveLeft(const float);
	void moveRight(const float);
	void moveUp(const float);
	void moveDown(const float);

	void update() override;

	template<class EntityB>
	void collide(EntityB& entity) {
		bool collided = false;

		// check collision
		if (this->x + this->size > entity.getX() &&
			entity.getX() + entity.getSize() > this->x + this->size &&
			this->y + this->size > entity.getY() &&
			entity.getY() + entity.getSize() > this->y + this->size)
			collided = true;

		// resolve collision
		if (collided) {
			this->setLives(0);

			entity.setLives(entity.getLives() - 1);
			entity.setState(Behaviors::HIT);
		}
	}
	void draw() const override {};
	void drawStencils() const override;

protected:
	float origX, origY;	// initial coordinates
	float range;
};

