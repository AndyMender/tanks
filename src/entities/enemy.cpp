/*
 * enemy.cpp
 *
 *  Created on: Jun 3, 2020
 *      Author: amender
 */

#include <cstdlib>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <colors.hpp>
#include <config.hpp>
#include <entities/enemy.hpp>


/**
 * Empty constructor implementation.
 */
EnemyEntity::EnemyEntity() {
	// set coordinates
	this->x = -50;
	this->y = -50;

	// defaults for remaining stats
	this->entityId = Entities::ENEMY;
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
 * Enemy-bound constructor.
*/
EnemyEntity::EnemyEntity(const EntityBlueprint& entity) {
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
 * X-axis movement to the left.
 */
void EnemyEntity::moveLeft(const float val) {
	// modify states
	this->direction = Directions::LEFT;
	this->state = Behaviors::MOVE;

	// translate along X-axis
	this->x = std::max(this->x - val, 0.0f);
}

/**
 * X-axis movement to the right.
 */
void EnemyEntity::moveRight(const float val) {
	// modify states
	this->direction = Directions::RIGHT;
	this->state = Behaviors::MOVE;

	// translate along X-axis
	this->x = std::min(this->x + val, static_cast<float>(ScreenWidth - this->size));
}

/**
 * Y-axis movement up.
 */
void EnemyEntity::moveUp(const float val) {
	// modify states
	this->direction = Directions::UP;
	this->state = Behaviors::MOVE;

	// translate along Y-axis
	this->y = std::max(this->y - val, 0.0f);
}

/**
 * Y-axis movement down.
 */
void EnemyEntity::moveDown(const float val) {
	// modify states
	this->direction = Directions::DOWN;
	this->state = Behaviors::MOVE;

	// translate along Y-axi
	this->y = std::min(this->y + val, static_cast<float>(ScreenHeight - this->size));
}

/**
 * Enemy-bound event-less "update" implementation.
 */
void EnemyEntity::update(std::vector<BulletEntity>& bullets) {
	// pick behavior
	// TODO: add internal params to control ratios?

	// move, shoot or do nothing
	if (std::rand() % 5 == 0) {
		const enum Directions randDirection = static_cast<Directions>(std::rand() % 4);
		switch(randDirection) {
		// X-axis
		case Directions::LEFT:
			this->moveLeft(this->speed);
			break;
		case Directions::RIGHT:
			this->moveRight(this->speed);
			break;
			// Y-axis

		case Directions::UP:
			this->moveUp(this->speed);
			break;
		case Directions::DOWN:
			this->moveDown(this->speed);
			break;
		}
	} else if (std::rand() % 10 == 0) {
		// TODO: is the bullet vector shared across entities?
		bullets.push_back(std::move(this->shootBullet()));
	} else {
		this->state = Behaviors::IDLE;
	}
}

/**
 * Draw stencils for debugging purposes.
 */
void EnemyEntity::drawStencils() const {
	// pick color based on behavior
	ALLEGRO_COLOR pickedColor;

	switch(this->state) {
	case Behaviors::MOVE:
		pickedColor = colorGreen;
		break;
	case Behaviors::SHOOT:
		pickedColor = colorAqua;
		break;
	case Behaviors::HIT:
		pickedColor = colorRed;
		break;
	default:
		pickedColor = colorNull;
	}

	al_draw_rectangle(this->x, this->y, this->x + this->size, this->y + this->size, pickedColor, StencilThickness);
}
