/*
 * ranged_entity.cpp
 *
 *  Created on: May 16, 2020
 *      Author: amender
 */

#include <vector>

#include <entities/bullet.hpp>
#include <entities/objects.hpp>
#include <entities/ranged.hpp>


/**
 * Empty constructor implementation.
 */
RangedEntity::RangedEntity() {
	// set coordinates
	this->x = -50;
	this->y = -50;

	// defaults for remaining stats
	this->entityId = Entities::DUMMY;
	this->direction = Directions::DOWN;
	this->state = Behaviors::IDLE;
	this->alive = true;
	this->size = 1;
	this->lives = 1;
	this->speed = 0;

	this->maxBullets = 1;
	this->bulletSpeed = 1;
	this->bulletRange = 1;
}

/**
 * Base constructor implementation.
 */
RangedEntity::RangedEntity(const EntityBlueprint& entity) {
	// set coordinates
	this->x = entity.x;
	this->y = entity.y;

	// defaults for remaining stats
	this->entityId = entity.entityId;
	this->direction = entity.direction;
	this->state = entity.state;
	this->alive = entity.alive;
	this->size = entity.size;
	this->lives = entity.lives;
	this->speed = entity.speed;

	this->maxBullets = entity.maxBullets;
	this->bulletSpeed = entity.bulletSpeed;
	this->bulletRange = entity.bulletRange;
}

/**
 * Generate a bullet entity object.
 */
BulletEntity RangedEntity::shootBullet() {
	// modify state
	this->state = Behaviors::SHOOT;

	// TODO: get bullet blueprint from internal spec
	EntityBlueprint bulletBlueprint;
	bulletBlueprint.entityId = Entities::BULLET;
	bulletBlueprint.direction = this->direction;
	bulletBlueprint.state = Behaviors::MOVE;
	bulletBlueprint.speed = this->speed;
	bulletBlueprint.bulletRange = this->bulletRange;

	// initial bullet position depends on direction
	switch(this->direction) {
	// x-axis
	case Directions::LEFT:
		bulletBlueprint.x = this->x;
		bulletBlueprint.y = this->y + this->size/2;
		break;
	case Directions::RIGHT:
		bulletBlueprint.x = this->x + this->size;
		bulletBlueprint.y = this->y + this->size/2;
		break;

	// y-axis
	case Directions::UP:
		bulletBlueprint.x = this->x + this->size/2;
		bulletBlueprint.y = this->y;
		break;
	case Directions::DOWN:
		bulletBlueprint.x = this->x + this->size/2;
		bulletBlueprint.y = this->y + this->size;
		break;
	}

	// create bullet proper
	return { bulletBlueprint };
}
