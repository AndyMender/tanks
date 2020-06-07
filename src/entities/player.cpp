/*
 * player.cpp
 *
 *  Created on: May 7, 2020
 *      Author: amender
 */

#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <colors.hpp>
#include <config.hpp>
#include <entities/entity.hpp>
#include <entities/player.hpp>


Player::Player() {
	// set coordinates
	this->x = -50;
	this->y = -50;

	// defaults for remaining stats
	this->entityId = Entities::PLAYER;
	this->direction = Directions::DOWN;
	this->state = Behaviors::IDLE;
	this->alive = true;
	this->size = 30;
	this->lives = 5;
	this->speed = 10;

	this->maxBullets = 3;
	this->bulletSpeed = 1;
	this->bulletRange = 250;
}

/**
 * Player-bound constructor.
*/
Player::Player(const EntityBlueprint& entity) {
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
void Player::moveLeft(const float val) {
	// modify states
	this->direction = Directions::LEFT;
	this->state = Behaviors::MOVE;

	// translate along X-axis
	this->x = std::max(this->x - val, 0.0f);
}

/**
 * X-axis movement to the right.
 */
void Player::moveRight(const float val) {
	// modify states
	this->direction = Directions::RIGHT;
	this->state = Behaviors::MOVE;

	// translate along X-axis
	this->x = std::min(this->x + val, static_cast<float>(ScreenWidth - this->size));
}

/**
 * Y-axis movement up.
 */
void Player::moveUp(const float val) {
	// modify states
	this->direction = Directions::UP;
	this->state = Behaviors::MOVE;

	// translate along Y-axis
	this->y = std::max(this->y - val, 0.0f);
}

/**
 * Y-axis movement down.
 */
void Player::moveDown(const float val) {
	// modify states
	this->direction = Directions::DOWN;
	this->state = Behaviors::MOVE;

	// translate along Y-axis
	this->y = std::min(this->y + val, static_cast<float>(ScreenHeight - this->size));
}

/**
 * Player-bound event-based "update" implementation.
 */
void Player::update(const ALLEGRO_EVENT &event, std::vector<BulletEntity>& bullets) {
	// resolve movement
	// TODO: add behavior triggers
	switch(event.keyboard.keycode) {
		// X-axis
		case ALLEGRO_KEY_LEFT:
			this->moveLeft(this->speed);
			break;
		case ALLEGRO_KEY_RIGHT:
			this->moveRight(this->speed);
			break;

		// Y-axis
		case ALLEGRO_KEY_UP:
			this->moveUp(this->speed);
			break;
		case ALLEGRO_KEY_DOWN:
			this->moveDown(this->speed);
			break;

		// shoot bullets
		// TODO: "space" used for jumping?
		case ALLEGRO_KEY_SPACE:
			if (bullets.size() < this->maxBullets)
				bullets.push_back(std::move(this->shootBullet()));
			break;
	}

	// TODO: can cause race conditions inside internal state?
	this->update();
}

/**
 * Draw stencils for debugging purposes.
 */
void Player::drawStencils() const {
	// pick color based on behavior
	ALLEGRO_COLOR pickedColor;

	switch(this->state) {
	case Behaviors::HIT:
		pickedColor = colorRed;
		break;
	default:
		pickedColor = colorNull;
	}

	al_draw_rectangle(this->x, this->y, this->x + this->size, this->y + this->size, pickedColor, StencilThickness);
}
