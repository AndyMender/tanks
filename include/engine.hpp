/*
 * engine.hpp
 *
 *  Created on: May 6, 2020
 *      Author: amender
 */

#pragma once

#include <vector>

#include <allegro5/allegro.h>

#include <config.hpp>
#include <entities/enemy.hpp>
#include <entities/objects.hpp>
#include <entities/player.hpp>


class Engine {
public:
	Engine();
	~Engine();

	// engine is unique - cannot copy/move!
	Engine(const Engine&) = delete;
	Engine(const Engine&&) = delete;	// move constructor
	Engine& operator=(const Engine&) = delete;
	Engine& operator=(Engine&&) = delete; // move + assignment

	constexpr bool isInitialized() const { return this->initialized; };

	void init();
	void tearDown();
	void runMainLoop();

private:
	// can't use smart pointers due to allegro5 internals
	ALLEGRO_DISPLAY* display = nullptr;
	ALLEGRO_TIMER* timer = nullptr;
	ALLEGRO_EVENT_QUEUE* eventQueue = nullptr;
	ALLEGRO_EVENT event;

	// engine state
	bool initialized = false;

	// init player
	// TODO: move init to level code?
	// TODO: init requires a blueprint now!
	Player player;

	// entity collections
	std::vector<BulletEntity> enemyBullets;
	std::vector<BulletEntity> playerBullets;
	std::vector<EnemyEntity> enemies;

	// initial setup
	void initColors();
	void initFonts();
	void initPrimitives();
	void initInputs();

	// updating
	// TODO: add state machine!
	void update();
	void spawnEnemies();

	// collisions
	void collide();

	// drawing
	void drawBackground() const;
	void drawHud() const;
	void draw() const;

	// clean-up
	void destroyEnemyBullets();
	void destroyPlayerBullets();
	void destroyEnemies();
	void destroyDead();

	// debugging
	void drawStencils() const;
	void showFps() const;
};
