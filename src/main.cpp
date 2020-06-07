/*
 * main.cpp
 *
 *  Created on: Apr 27, 2020
 *      Author: amender
 */

#include <iostream>

#include <engine.hpp>
#include <main.hpp>

int main(void) {
	Engine engine;

	// check engine
	if (!engine.isInitialized()) {
		return -1;
	}

	// start main loop
	engine.runMainLoop();

	return 0;
}
