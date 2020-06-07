/*
 * entity.cpp
 *
 *  Created on: May 6, 2020
 *      Author: amender
 */

#include <config.hpp>
#include <entities/entity.hpp>


/**
 * Dummy constructor.
 */
Entity::Entity() {
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
}

/**
 * Base constructor.
 */
Entity::Entity(const EntityBlueprint& entity)  {
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
}

/**
 * Update lives/HP of Entity. Set to "dead" if lives = 0.
 */
void Entity::setLives(const int l) {
	this->lives = (l < 0) ? 0 : l;

	if (!this->lives) this->alive = false;
}
