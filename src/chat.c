#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define TILE_SIZE 64
#define FOV (60 * M_PI / 180) // Field of View in radians
#define NUM_RAYS SCREEN_WIDTH

// Simple map with walls (1) and empty spaces (0)
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

// Player's position and direction
float playerX = 300;
float playerY = 300;
float playerAngle = 0.0f;

SDL_Renderer *renderer;

// Draw the 2D map grid
void draw_map() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            SDL_Rect tile = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            if (map[y][x] == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White for walls
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black for empty spaces
            }
            SDL_RenderFillRect(renderer, &tile);
        }
    }
}

// Cast rays and visualize them
void cast_rays() {
    for (int i = 0; i < NUM_RAYS; i++) {
        // Calculate the angle for the current ray
        float ray_angle = playerAngle - FOV / 2 + i * (FOV / NUM_RAYS);
        float rayX = playerX;
        float rayY = playerY;

        // Step size for each ray (increase/decrease X and Y)
        float stepX = cos(ray_angle);
        float stepY = sin(ray_angle);

        bool hit_wall = false;
        while (!hit_wall) {
            // Move the ray forward
            rayX += stepX;
            rayY += stepY;

            // Check if the ray hit a wall
            int mapX = (int)rayX / TILE_SIZE;
            int mapY = (int)rayY / TILE_SIZE;

            if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT && map[mapY][mapX] == 1) {
                hit_wall = true;

                // Draw the ray
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for rays
                SDL_RenderDrawLine(renderer, playerX, playerY, rayX, rayY);
            }
        }
    }
}

// Handle keyboard input to move the player
void handle_input(SDL_Event event) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_W]) {
        // Move forward
        playerX += cos(playerAngle) * 5;
        playerY += sin(playerAngle) * 5;
    }
    if (state[SDL_SCANCODE_S]) {
        // Move backward
        playerX -= cos(playerAngle) * 5;
        playerY -= sin(playerAngle) * 5;
    }
    if (state[SDL_SCANCODE_A]) {
        // Turn left
        playerAngle -= 0.05f;
    }
    if (state[SDL_SCANCODE_D]) {
        // Turn right
        playerAngle += 0.05f;
    }
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Raycasting Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Handle player movement
        handle_input(event);

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        // Draw the 2D map
        draw_map();

        // Cast and draw rays
        cast_rays();

        // Update the screen
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Cap at ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
