/*
 * objects.hpp
 *
 *  Created on: May 9, 2020
 *      Author: amender
 */

#pragma once

#include <string>
#include <vector>

#include <config.hpp>

enum class Directions {
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

enum class Entities {
	DUMMY,
	PLAYER,
	ENEMY,
	BULLET
};

enum class Behaviors {
	IDLE,
	MOVE,
	SHOOT,
	HIT
};

const std::vector<std::vector<int>> SpawnPoints = {
		{ 150, 150 },
		{ 150, ScreenHeight - 150 },
		{ ScreenWidth - 150, 150 },
		{ ScreenWidth - 150, ScreenHeight - 150 }
};

// TODO: implement as POD classes with a proper hierarchy?
class EntityBlueprint {
public:
	enum Entities entityId = Entities::DUMMY;
	enum Directions direction = Directions::DOWN;
	enum Behaviors state = Behaviors::IDLE;
	bool alive = true;
	float x = -50;
	float y = -50;
	int size = 1;
	int lives = 1;
	float speed = 0;

	int maxBullets = 0;
	float bulletSpeed = 0;
	float bulletRange = 0;

	// TODO: populate during object instantiation!
	std::string spritePath = "";
};
