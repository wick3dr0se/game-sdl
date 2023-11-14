#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>
#include "../dev/imgui/imgui.h"
#include "../dev/imgui/imgui_impl_sdl.h"
#include "../dev/imgui/imgui_impl_sdlrenderer.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,800,640 };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& enemy(manager.addEntity());
auto& label(manager.addEntity());

auto& tiles(manager.getGroup(Game::groupMap));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& players(manager.getGroup(Game::groupPlayers));
auto& enemies(manager.getGroup(Game::groupEnemies));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int x, int y, int w, int h, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystem initialized!" << std::endl;

        window = SDL_CreateWindow(title, x, y, w, h, flags);
        if (window)
        {
            std::cout << "Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer Created!" << std::endl;

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;

            ImGui::StyleColorsDark(); //ImGui::StyleColorsLight();

            ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
            ImGui_ImplSDLRenderer_Init(renderer);
        }

        isRunning = true;
    }
    else {
        isRunning = false;
    }

    if (TTF_Init() == -1)
    {
        std::cout << "Error: SDL_TTF" << SDL_GetError() << std::endl;
    }

    assets->AddTexture("terrain", "assets/terrain_ss.png");
    map = new Map("terrain", 3, 32);
    map->LoadMap("assets/map.map", 25, 20);

    assets->AddTexture("player", "assets/player_anims.png");
    player.addComponent<TransformComponent>(640, 680, 32, 32, 3);
    player.addComponent<SpriteComponent>("player", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);

    assets->AddTexture("enemy", "assets/enemy_anims.png");
    enemy.addComponent<TransformComponent>(720, 680, 32, 32, 3);
    enemy.addComponent<SpriteComponent>("enemy", true);
    enemy.addComponent<AIController>();
    enemy.addComponent<ColliderComponent>("enemy");
    enemy.addGroup(groupEnemies);

    assets->AddTexture("projectile", "assets/pot_leaf.png");

    SDL_Color white = { 255, 255, 255, 255 };
    assets->AddFont("arial", "assets/arial.ttf", 16);
    label.addComponent<UILabel>(10, 10, "test", "arial", white);
}

void Game::preRender()
{
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void Game::handleEvents()
{
    SDL_PollEvent(&event);
    ImGui_ImplSDL2_ProcessEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}

void Game::update()
{
    ColliderComponent playerCol = player.getComponent<ColliderComponent>();
    ColliderComponent enemyCol = enemy.getComponent<ColliderComponent>();
    Vector2D playerPos = player.getComponent<TransformComponent>().position;
    Vector2D enemyPos = enemy.getComponent<TransformComponent>().position;

    std::stringstream ss;
    ss << "Player position: " << playerPos;
    label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");

    manager.refresh();
    manager.update();

    for (auto& c : colliders)
    {
        ColliderComponent cCol = c->getComponent<ColliderComponent>();

        if (Collision::AABB(cCol, playerCol))
        {
            player.getComponent<TransformComponent>().position = playerPos;
        }

        if (Collision::AABB(cCol, enemyCol))
        {
            enemy.getComponent<TransformComponent>().position = enemyPos;
        }
    }

    for (auto& p : projectiles)
    {
        ColliderComponent projCol = p->getComponent<ColliderComponent>();

        for (auto& e : enemies)
        {
            ColliderComponent enemyCol = e->getComponent<ColliderComponent>();

            if (Collision::AABB(projCol, enemyCol))
            {
                std::cout << "Enemy hit!" << std::endl;
                e->destroy();
                p->destroy();
            }
        }
    }

    camera.x = static_cast<int>(playerPos.x - 400);
    camera.y = static_cast<int>(playerPos.y - 320);

    if (camera.x < 0) { camera.x = 0; }
    if (camera.y < 0) { camera.y = 0; }
    if (camera.x > camera.w) { camera.x = camera.w; }
    if (camera.y > camera.h) { camera.y = camera.h; }

    //ImGui::ShowDemoWindow();
}

void Game::render()
{
    SDL_RenderClear(renderer);
    
    for (auto& t : tiles) { t->draw(); }
    for (auto& c : colliders) { c->draw(); }
    for (auto& p : players) { p->draw(); }
    for (auto& e : enemies) { e->draw(); }
    for (auto& p : projectiles) { p->draw(); }

    label.draw();

    ImGui::Render();
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
    std::cout << "Game Cleaned!" << std::endl;
}