/*
 * bullet.cpp
 *
 *  Created on: May 11, 2020
 *      Author: amender
 */

#include <allegro5/allegro_primitives.h>

#include <colors.hpp>
#include <config.hpp>
#include <entities/bullet.hpp>


/**
 * Bullet-bound dummy constructor.
 */
BulletEntity::BulletEntity() {
	// set coordinates
	this->x = this->origX = -50;
	this->y = this->origY = -50;

	// defaults for remaining stats
	this->entityId = Entities::BULLET;
	this->direction = Directions::DOWN;
	this->state = Behaviors::MOVE;
	this->alive = true;
	this->size = 1;
	this->lives = 1;
	this->speed = 0;
	this->range = 0;
}

/**
 * Bullet-bound constructor.
 */
BulletEntity::BulletEntity(const EntityBlueprint& entity) {
	// set coordinates
	this->x = this->origX = entity.x;
	this->y = this->origY = entity.y;

	// defaults for remaining stats
	this->entityId = entity.entityId;
	this->direction = entity.direction;
	this->state = entity.state;
	this->alive = entity.alive;
	this->size = entity.size;
	this->lives = entity.lives;
	this->speed = entity.speed;
	this->range = entity.bulletRange;
}

/**
 * X-axis movement to the left.
 */
void BulletEntity::moveLeft(const float val) {
	this->x -= val;
	if (this->x < 0 || this->x < (this->origX - this->range)) {
		this->setLives(0);
	}
}

/**
 * X-axis movement to the right.
 */
void BulletEntity::moveRight(const float val) {
	this->x += val;
	if (this->x > ScreenWidth || this->x > (this->origX + this->range)) {
		this->setLives(0);
	}
}

/**
 * Y-axis movement up.
 */
void BulletEntity::moveUp(const float val) {
	this->y -= val;
	if (this->y < 0 || this->y < (this->origY - this->range)) {
		this->setLives(0);
	}
}

/**
 * Y-axis movement down.
 */
void BulletEntity::moveDown(const float val) {
	this->y += val;
	if (this->y > ScreenHeight || this->y > (this->origY + this->range)) {
		this->setLives(0);
	}
}

/**
 * Event-less "update" implementation.
 */
void BulletEntity::update() {
	// ignore if bullet is "dead"
	if (!this->alive) return;

	switch(this->direction) {
	// x-axis
	case Directions::LEFT:
		this->moveLeft(this->speed);
		break;
	case Directions::RIGHT:
		this->moveRight(this->speed);
		break;

	// y-axis
	case Directions::UP:
		this->moveUp(this->speed);
		break;
	case Directions::DOWN:
		this->moveDown(this->speed);
		break;
	}
}

/**
 * Draw stencils for debugging purposes.
 */
void BulletEntity::drawStencils() const {
	al_draw_filled_circle(this->x, this->y, StencilThickness, colorNull);
}
