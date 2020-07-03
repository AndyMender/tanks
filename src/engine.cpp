/*
 * engine.cpp
 *
 *  Created on: May 6, 2020
 *      Author: amender
 */

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

#include <config.hpp>
#include <engine.hpp>
#include <entities/bullet.hpp>
#include <entities/enemy.hpp>
#include <entities/player.hpp>


// core colors
ALLEGRO_COLOR colorNull;
ALLEGRO_COLOR colorWhite;
ALLEGRO_COLOR colorRed;
ALLEGRO_COLOR colorGreen;
ALLEGRO_COLOR colorBlue;

// extra colors
ALLEGRO_COLOR colorAqua;
ALLEGRO_COLOR colorBisque;

// fonts
ALLEGRO_FONT *fontS;
ALLEGRO_FONT *fontM;
ALLEGRO_FONT *fontL;


/**
 * Default constructor.
 */
Engine::Engine() {
	this->init();

	if (this->initialized) {
		std::cout << "Engine initialized successfully." << std::endl;
	}
	else {
		std::cout << "Engine initialization failed!" << std::endl;
	}
}

/**
 * Default destructor.
 */
Engine::~Engine() {
	if (this->initialized) {
		this->tearDown();

		std::cout << "Engine terminated successfully." << std::endl;
	}
}

/**
 * Engine initialization and resource allocation.
 */
void Engine::init() {
	// seed the RNG
	std::srand(std::time(nullptr));

	// bootstrap allegro and check
	if (!al_init()) {
		al_show_native_message_box(nullptr, nullptr, nullptr,
				"Failed to initialize allegro!", nullptr, 0);

		return;
	}

	// set display flags
	// al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

	// create the actual display and check
	this->display = al_create_display(ScreenWidth, ScreenHeight);

	if (!this->display) {
		al_show_native_message_box(nullptr, nullptr, nullptr,
				"Failed to initialize display!", nullptr, 0);

		return;
	}

	// create game timer
	this->timer = al_create_timer(1.0/FPS);

	// create event queue
	this->eventQueue = al_create_event_queue();

	// run all auxiliary inits
	this->initColors();
	this->initFonts();
	this->initPrimitives();
	this->initInputs();

	// initialize player
	this->player.setX(ScreenWidth/2 - this->player.getSize());
	this->player.setY(ScreenHeight/2 - this->player.getSize());

	this->initialized = true;
}

/**
 * Engine clean-up and deallocation.
 */
void Engine::tearDown() {
	al_shutdown_font_addon();
	al_shutdown_primitives_addon();

	al_destroy_timer(this->timer);

	if (this->display) {
		al_destroy_display(this->display);
	}

	this->initialized = false;
}

void Engine::initColors() {
	colorNull = al_color_name("black");
	colorWhite = al_color_name("white");
	colorRed = al_color_name("crimson");
	colorGreen = al_color_name("darkgreen");
	colorBlue = al_color_name("royalblue");

	colorAqua = al_color_name("aquamarine");
	colorBisque = al_color_name("bisque");
}

void Engine::initFonts() {
	al_init_font_addon();
	al_init_ttf_addon();

	fontS = al_load_font("./assets/fonts/liberation.ttf", 18, 0);
	fontM = al_load_font("./assets/fonts/liberation.ttf", 24, 0);
	fontL = al_load_font("./assets/fonts/liberation.ttf", 36, 0);
}

/**
 * Triangles, rectangles and such.
 */
void Engine::initPrimitives() {
	al_init_primitives_addon();
}

/**
 * Enable user inputs, etc.
 */
void Engine::initInputs() {
	al_install_keyboard();

	// register input events
	if (this->eventQueue) {
		// keyboard events
		al_register_event_source(this->eventQueue, al_get_keyboard_event_source());

		// display window events
		al_register_event_source(this->eventQueue, al_get_display_event_source(this->display));

		// timer events
		al_register_event_source(this->eventQueue, al_get_timer_event_source(this->timer));
	}
	else {
		al_show_native_message_box(nullptr, nullptr, nullptr,
				"Event queue not initialized. Cannot register input events.", nullptr, 0);
	}
}

/**
 * Main event loop.
*/
void Engine::runMainLoop() {
	// TODO: make engine global?
	bool loopable = true;

	// start timer (NOTE: must be close to the actual loop!)
	al_start_timer(this->timer);

	// start loop
	while (loopable) {
		al_wait_for_event(this->eventQueue, &this->event);

		// TODO: move event processing to state machine
		switch(this->event.type) {
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				loopable = false;
				break;

			// triggered player events
			case ALLEGRO_EVENT_KEY_CHAR:
				this->player.update(this->event, this->playerBullets);
				break;

			// regular updates, collision, drawing and clean-up
			case ALLEGRO_EVENT_TIMER:
				this->update();
				this->spawnEnemies();
				this->collide();
				this->draw();
				this->destroyDead();

				// flip back buffer to front
				al_flip_display();
				break;
		}
	}
}

/**
 * Main handler for regular "update" operations.
 */
void Engine::update() {
	// update player (event-less behavior)
	this->player.update();

	// update enemies
	for (auto& enemy: this->enemies) {
		enemy.update(this->enemyBullets);
	}

	// update bullets
	for (auto& bullet: this->playerBullets) {
		bullet.update();
	}

	for (auto& bullet: this->enemyBullets) {
		bullet.update();
	}
}

/**
 * Main handler for generating/loading enemy entities.
 */
void Engine::spawnEnemies() {
	// initialize enemies at random
	if (std::rand() % 100 == 0) {
		// pick position from
		int x, y;
		const int randomPos = std::rand() % static_cast<int>(SpawnPoints.size());
		x = SpawnPoints[randomPos][0];
		y = SpawnPoints[randomPos][1];

		// template and spawn enemy
		// TODO: load from file template!
		EntityBlueprint enemyBlueprint;
		enemyBlueprint.x = x;
		enemyBlueprint.y = y;
		enemyBlueprint.size = 30;
		enemyBlueprint.speed = 5;
		enemyBlueprint.maxBullets = 3;
		enemyBlueprint.bulletSpeed = 1;
		enemyBlueprint.bulletRange = 250;
		this->enemies.push_back(EnemyEntity { enemyBlueprint });
	}
}

/**
 * Main handler for collision resolution.
 */
void Engine::collide() {
	// player bullets vs enemy entities
	for (auto& bullet: this->playerBullets) {
		for (auto& enemy: this->enemies) {
			bullet.collide(enemy);
		}
	}

	// enemy bullets vs player entity
	for (auto& bullet: this->enemyBullets) {
		bullet.collide(this->player);
	}
}

/**
 * Main handler for all "draw" operations.
 */
void Engine::draw() const {
	// fill back buffer with solid color (BACKGROUND)
	this->drawBackground();

	// draw player
	this->player.draw();

	// draw enemies
	for (const auto& enemy: this->enemies) {
		enemy.draw();
	}

	// draw bullets
	for (const auto& bullet: this->playerBullets) {
		bullet.draw();
	}

	for (const auto& bullet: this->enemyBullets) {
		bullet.draw();
	}

	// draw HUD
	this->drawHud();

	// TODO: debug features - make toggleable
	this->drawStencils();
	this->showFps();
}

/**
 * Draw "dead" background below bitmaps.
 */
void Engine::drawBackground() const {
	// TODO: pick a reasonable color for the background
	al_clear_to_color(colorWhite);
}

/**
 * Draw the Heads-up Display.
 */
void Engine::drawHud() const {
	// create frame
	al_draw_filled_rectangle(0, 0, ScreenWidth, 45, colorNull);

	// create entries
	// TODO: get data from global and/or player state!
	al_draw_textf(fontS, colorWhite, 15, 10, 0, "LIVES: %d", this->player.getLives());
	al_draw_textf(fontS, colorWhite, 110, 10, 0, "SHIELDS: %d", 100);
	al_draw_textf(fontS, colorWhite, 250, 10, 0, "AMMO: %d", 10);
	al_draw_textf(fontS, colorWhite, 360, 10, 0, "PLAYER STATE: %d", this->player.getState());
}

/**
 * Remove "dead" bullets generated by enemy entities.
 */
void Engine::destroyEnemyBullets() {
	decltype(this->enemyBullets) bulletsNew;

	for (const auto& bullet: this->enemyBullets) {
		if (bullet.isAlive()) bulletsNew.push_back(bullet);
	}

	this->enemyBullets = std::move(bulletsNew);
}

/**
 * Remove "dead" bullets generated by the player entity.
 */
void Engine::destroyPlayerBullets() {
	decltype(this->playerBullets) bulletsNew;

	for (const auto& bullet: this->playerBullets) {
		if (bullet.isAlive()) bulletsNew.push_back(bullet);
	}

	this->playerBullets = std::move(bulletsNew);
}

/**
 * Remove "dead" enemy entities.
 */
void Engine::destroyEnemies() {
	decltype(this->enemies) enemiesNew;

	for (const auto& enemy: this->enemies) {
		if (enemy.isAlive()) enemiesNew.push_back(enemy);
	}

	this->enemies = std::move(enemiesNew);
}

/**
 * Clean up "dead" entities.
 */
void Engine::destroyDead() {
	// clean up bullets
	this->destroyEnemyBullets();
	this->destroyPlayerBullets();

	// clean up entities
	this->destroyEnemies();
}

/**
 * Draw guide lines for collision testing, object positioning, etc.
 */
void Engine::drawStencils() const {
	// write some text to the screen
	al_draw_text(fontM, colorNull, ScreenWidth/2 - 80, 100, 0, "Hello World!");

	// draw player
	this->player.drawStencils();

	// draw enemies
	for (const auto& enemy: this->enemies) {
		enemy.drawStencils();
	}

	// draw bullets
	for (const auto& bullet: this->enemyBullets) {
		bullet.drawStencils();
	}

	for (const auto& bullet: this->playerBullets) {
		bullet.drawStencils();
	}
}

/**
 * Display in-game frame rate
 */
void Engine::showFps() const {
	const short timerValue = al_get_timer_count(this->timer) % 60;

	al_draw_textf(fontS, colorWhite, ScreenWidth - 80, 10, 0, "FPS: %02d", timerValue);
}
