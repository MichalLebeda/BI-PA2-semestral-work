cmake_minimum_required(VERSION 3.16)
project(semestral-work)

set(CMAKE_CXX_STANDARD 14)

#added
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${semestral-work_SOURCE_DIR}/cmake")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR})
#end

add_executable(semestral-work src/main.cpp src/level/Level.cpp src/level/Level.h src/level/Tile.cpp src/level/Tile.h src/Game.cpp src/Game.h src/Assets.cpp src/Assets.h src/graphics/Sprite.cpp src/graphics/Sprite.h src/graphics/Renderable.h src/graphics/CameraRenderer.cpp src/graphics/CameraRenderer.h src/Util.cpp src/Util.h src/graphics/TextureRegion.cpp src/graphics/TextureRegion.h src/graphics/Animation.cpp src/graphics/Animation.h src/physics/PhysWorld.cpp src/physics/PhysWorld.h src/physics/PhysBody.cpp src/physics/PhysBody.h src/entities/PhysicalEntity.cpp src/entities/PhysicalEntity.h src/entities/Player.cpp src/entities/Player.h src/entities/DepthSortedSprite.cpp src/entities/DepthSortedSprite.h src/physics/PhysWorldDebugRenderer.cpp src/physics/PhysWorldDebugRenderer.h src/physics/WorldContactListener.cpp src/physics/WorldContactListener.h src/level/AnimatedTile.cpp src/level/AnimatedTile.h src/rpg/RPGCharacter.cpp src/rpg/RPGCharacter.h src/graphics/PlayerAnimFrame.h src/level/DistanceTile.cpp src/level/DistanceTile.h src/rpg/RPGItem.cpp src/rpg/RPGItem.h src/rpg/RPGInventory.cpp src/rpg/RPGInventory.h src/rpg/RPGPlayer.cpp src/rpg/RPGPlayer.h src/level/Item.cpp src/level/Item.h src/ui/hud/inventory/EquipBar.cpp src/ui/hud/inventory/EquipBar.h src/ui/hud/Hud.cpp src/ui/hud/Hud.h src/ui/hud/inventory/ConsumablesBar.cpp src/ui/hud/inventory/ConsumablesBar.h src/ui/hud/inventory/ItemInfoText.cpp src/ui/hud/inventory/ItemInfoText.h src/Serializable.h src/entities/enemies/Enemy.cpp src/entities/enemies/Enemy.h src/entities/enemies/Enemies.cpp src/entities/enemies/Enemies.h src/entities/enemies/Bird.cpp src/entities/enemies/Bird.h  src/entities/enemies/Ghost.cpp src/entities/enemies/Ghost.h src/ui/Menu.cpp src/ui/Menu.h src/ui/Button.cpp src/ui/Button.h)

#added
target_link_libraries(semestral-work ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})
#end