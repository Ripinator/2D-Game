#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

// Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init(SDL_Window **window, SDL_Surface **screenSurface);
SDL_Surface *loadImage(const char *path);
void closeSDL(SDL_Window *window, SDL_Surface *image);

int main(int argc, char *args[])
{
    SDL_Window *window = NULL;
    SDL_Surface *screenSurface = NULL;
    SDL_Surface *image = NULL;

    // Initialize SDL
    if (!init(&window, &screenSurface))
    {
        printf("Failed to initialize SDL.\n");
        return 1;
    }

    // Load image
    const char *imagePath = "/home/david/2D_Game/02_getting_an_image_on_the_screen/preview.bmp"; // Update with the path to your BMP file
    image = loadImage(imagePath);
    if (image == NULL)
    {
        printf("Failed to load image %s.\n", imagePath);
        closeSDL(window, image);
        return 1;
    }

    // Display image
    SDL_BlitSurface(image, NULL, screenSurface, NULL); // Copy the image onto the screen
    SDL_UpdateWindowSurface(window);                  // Update the screen

    // Wait for user to close the window
    bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    // Free resources and close SDL
    closeSDL(window, image);
    return 0;
}

bool init(SDL_Window **window, SDL_Surface **screenSurface)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create window
    *window = SDL_CreateWindow("SDL2 Image Display", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Get window surface
    *screenSurface = SDL_GetWindowSurface(*window);

    return true;
}

SDL_Surface *loadImage(const char *path)
{
    // Load BMP image
    SDL_Surface *loadedImage = SDL_LoadBMP(path);
    if (loadedImage == NULL)
    {
        printf("Unable to load image %s! SDL_Error: %s\n", path, SDL_GetError());
    }
    return loadedImage;
}

void closeSDL(SDL_Window *window, SDL_Surface *image)
{
    // Free loaded image
    SDL_FreeSurface(image);

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();
}
