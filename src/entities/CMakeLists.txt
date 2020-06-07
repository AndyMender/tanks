# add core entity
add_library(Entity entity.cpp)

# add projectile entity
add_library(BulletEntity bullet.cpp)

target_link_libraries(
	BulletEntity
	PRIVATE ${ALLEGRO5}
	PRIVATE ${ALLEGRO5_PRIMITIVES}
	PRIVATE Entity
)

# add enemy entity
add_library(EnemyEntity enemy.cpp)

target_link_libraries(
	EnemyEntity
	PRIVATE ${ALLEGRO5}
	PRIVATE ${ALLEGRO5_PRIMITIVES}
	PRIVATE Entity
	PRIVATE BulletEntity
	PRIVATE RangedEntity
)

# add ranged entity
add_library(RangedEntity ranged.cpp)

target_link_libraries(
	RangedEntity
	PRIVATE Entity
	PRIVATE BulletEntity
)
	
# add player entity
add_library(PlayerEntity player.cpp)

target_link_libraries(
	PlayerEntity 
	PRIVATE ${ALLEGRO5}
	PRIVATE ${ALLEGRO5_PRIMITIVES}
	PRIVATE Entity
	PRIVATE RangedEntity
	PRIVATE BulletEntity
)
