//
// Created by michal on 3/9/20.
//

#ifndef SEMESTRAL_WORK_LEVEL_H
#define SEMESTRAL_WORK_LEVEL_H

#include "Tile.h"

#include "../Assets.h"
#include "../physics/PhysWorld.h"
#include "../entities/Player.h"
#include "../physics/PhysWorldDebugRenderer.h"
#include "Item.h"
#include "../entities/enemies/Enemy.h"
#include "../entities/enemies/Enemies.h"

/**
 * Whole level containing floor, walls, live entities. Can be rendered on screen
 */
class Level : Renderable {
public:

    /**
     * Enum representing Player location when loading new level
     */
    enum PlayerLocation {
        LOADED_FROM_FILE, NEXT_TO_STAIRS_UP, NEXT_TO_STAIRS_DOWN
    };

    /**
     *
     * @param index Index of the level (starting from 0 to n based on game depth)
     * @param mapFilename Filename used for level loading
     * @param assets Assets instance
     * @param renderer CameraRenderer
     * @param playerLocation PlayerLocation indicating where the player should be located
     * @param rpgPlayer RPGPlayer shared across whole game
     */
    Level(int index, const string &mapFilename, const Assets *assets, CameraRenderer *renderer,
          PlayerLocation playerLocation, RPGPlayer *rpgPlayer);

    ~Level() override;

    void render(CameraRenderer *renderer) override;

    /**
     * @brief Render debug representation including phys. bodies
     * @param renderer
     */
    void renderDebug(CameraRenderer *renderer);

    /**
     * @brief Get width of the map
     * @return number of tiles horizontal
     */
    int getWidth() const;

    /**
     * @brief Get height of the map
     * @return number of tiles vertical
     */
    int getHeight() const;

    /**
     * @brief Get world
     * @return ptr to PhysWorld instance
     */
    PhysWorld *getWorld() const;

    /**
     * enum representing possible request level can make to game
     */
    enum Request {
        DO_NOTHING, GO_LEVEL_DOWN, GO_LEVEL_UP
    };

    Request request = DO_NOTHING;

    /**
     * @brief Get Request, usually used in Game main loop to decide if load another Level or not
     * @return current Request
     */
    Request getRequest() const;

    /**
     * @brief set Request used for informing Game instance about what to do
     * @param request Request to be set
     */
    void setRequest(Request request);

    /**
     * Get player
     * @return ptr to player
     */
    Player *getPlayer();

    /**
     * @brief Pickup item player is standing if no such item exists
     */
    void pickupItemUnderPlayer();

    /**
     * @brief Get item player is standing on
     * @return return ptr to RPGItem or nullptr
     */
    const RPGItem *getItemUnderPlayer();

    /**
     * @brief Save all in level
     * @param os stream to save to
     */
    void save(ostream &os);

    /**
     * @brief Get patch filename from current level
     * @param index index of level
     * @return string path to level patch file
     */
    static string getPatchPath(int index);

    /**
     * get background color
     * @return SDL_Color of the background
     */
    SDL_Color &getBgColor();

    Player *player;
private:
    class WorldContactListenerImpl : public WorldContactListener {
    public:
        explicit WorldContactListenerImpl(Level *level);

        void onContact(PhysBody *bodyA, PhysBody *bodyB) override;

        ~WorldContactListenerImpl() override = default;

    private:
        Level *level;
    };

    /**
     * @brief allocates map grid
     */
    void allocateGrid();

    /**
     * @brief loads width and height of the map grid
     * @param stream
     */
    void loadGridDimensions(ifstream &stream);

    /**
     * @brief load floor layer
     * @param stream stream to load from
     */
    void loadFloorTileLayer(ifstream &stream);

    /**
     * @brief load second tile layer eg. walls
     * @param stream stream to load from
     */
    void loadSecondTileLayer(ifstream &stream);

    /**
     * @brief loads collision layer of the map
     * @param stream stream to load from
     * @param location location of the player (if should be loaded or is next to stairs)
     */
    void loadCollisionLayer(ifstream &stream, PlayerLocation location);

    /**
     * @brief load int and handle errors
     * @param stream to load int from
     * @param read target int ref to load int
     */
    void loadInt(ifstream &stream, int &read);

    /**
     * @brief Method to be called when something bad during loading occurs
     */
    static void badMap();

    /**
     * @brief method for PhysWorld initialization
     */
    void initializeWorld();

    /**
     * @brief Sets a body which is known to colide with player (from item layer)
     * @param body PhysBody under Player
     */
    void setBodyUnderPlayer(PhysBody *body);

    /**
     * @brief Load items from stream
     * @param is stream to read from
     */
    void loadItems(istream &is);

    /**
     * @brief Serialize items to stream
     * @param os stream to write to
     */
    void saveItems(ostream &os);

    int index;
    SDL_Color bgColor;
    string filename;
    int width;
    int height;
    Enemies *enemies;
    Tile ***tiles;
    PhysWorld *world;
    vector<Item *> items;

    PhysBody *bodyUnderPlayer = nullptr;

    PhysWorldDebugRenderer worldDebugRenderer;

    const Assets *assets;

    WorldContactListenerImpl *worldContactListener;

};


#endif //SEMESTRAL_WORK_LEVEL_H
