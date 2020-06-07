# add core engine lib
add_library(Engine engine.cpp)

target_link_libraries(
	Engine 
	PRIVATE ${ALLEGRO5}
	PRIVATE ${ALLEGRO5_COLOR}
	PRIVATE ${ALLEGRO5_DIALOG}
	PRIVATE ${ALLEGRO5_FONT}
	PRIVATE ${ALLEGRO5_TTF}
	PRIVATE ${ALLEGRO5_PRIMITIVES}
	PRIVATE BulletEntity
	PRIVATE EnemyEntity
	PRIVATE PlayerEntity
)

# specify main target
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Engine)