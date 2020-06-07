/*
 * entity.hpp
 *
 *  Created on: May 6, 2020
 *      Author: amender
 */

#pragma once

#include <entities/objects.hpp>


/**
 * Base class for in-game entities.
 */
class Entity {
public:
	Entity();
	Entity(const EntityBlueprint&);

	virtual ~Entity() = default;
	Entity(const Entity&) = default;
	Entity(Entity&&) = default;
	Entity& operator=(const Entity&) = default;
	Entity& operator=(Entity&&) = default;

	constexpr float getX() const { return this->x; };
	constexpr float getY() const { return this->y; };
	constexpr bool isAlive() const { return this->alive; };
	constexpr int getSize() const { return this->size; };
	constexpr int getLives() const { return this->lives; };
	constexpr Behaviors getState() const { return this->state; };

	void setX(const float val) { this->x = val; };
	void setY(const float val) { this->y = val; };
	void setLives(const int);
	void setState(const Behaviors& val) { this->state = val; };

	virtual void draw() const = 0;
	virtual void drawStencils() const = 0;
	virtual void update() = 0;

protected:
	// coordinates
	float x, y;

	// other stats
	enum Entities entityId;
	enum Directions direction;	// facing direction
	enum Behaviors state;		// behavior triggers, animations, etc.
	bool alive;
	int lives;
	int size;
	float speed;
};
