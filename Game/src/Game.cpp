#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include "Network/NetworkManager.h"
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

boost::asio::io_service io_service_;
NetworkManager* Game::network = nullptr;

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& label(manager.addEntity());

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int x, int y, int w, int h, bool fullscreen, bool online)
{
    auto const serverIp = "127.0.0.1";
    auto const serverPort = 9949;

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

        if (online)
        {
            network = new NetworkManager(io_service_, serverIp, serverPort);
            std::cout << "Connected to server!" << std::endl;
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
    assets->AddTexture("player", "assets/player_anims.png");
    assets->AddTexture("projectile", "assets/pot_leaf.png");

    assets->AddFont("arial", "assets/arial.ttf", 16);

    map = new Map("terrain", 3, 32);

    map->LoadMap("assets/map.map", 25, 20);

    player.addComponent<TransformComponent>(640, 680, 32, 32, 3);
    player.addComponent<SpriteComponent>("player", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);

    SDL_Color white = { 255, 255, 255, 255 };
    label.addComponent<UILabel>(10, 10, "test", "arial", white);

    assets->CreateProjectile(Vector2D(540, 600), Vector2D(2, 0), 200, 2, "projectile");
    assets->CreateProjectile(Vector2D(540, 620), Vector2D(2, 1), 200, 2, "projectile");
    assets->CreateProjectile(Vector2D(540, 630), Vector2D(2, 2), 200, 2, "projectile");
    assets->CreateProjectile(Vector2D(540, 640), Vector2D(2, -1), 200, 2, "projectile");
    assets->CreateProjectile(Vector2D(540, 650), Vector2D(2, -2), 200, 2, "projectile");

}

void Game::preRender()
{
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& players(manager.getGroup(Game::groupPlayers));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

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
    SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = player.getComponent<TransformComponent>().position;

    std::stringstream ss;
    ss << "Player position: " << playerPos;
    label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");

    manager.refresh();
    manager.update();

    for (auto& c : colliders)
    {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(cCol, playerCol))
        {
            player.getComponent<TransformComponent>().position = playerPos;
        }
    }

    for (auto& p : projectiles)
    {
        if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
        {
            std::cout << "Player hit!" << std::endl;
            p->destroy();
        }
    }

    camera.x = player.getComponent<TransformComponent>().position.x - 400;
    camera.y = player.getComponent<TransformComponent>().position.y - 320;

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