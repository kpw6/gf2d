#include <SDL.h>
#include "SDL_ttf.h"
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"

#include "gfc_audio.h"
#include "gfc_input.h"

#include "fonts.h"

#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "crops.h"
#include "monsters.h"

#include "level.h"
#include "borders.h"
#include "timer.h"
#include "menus.h"

int main_menu(menu* men) {
    Sprite* background;
    Sound* music;

    if (!men) return 1;

    men->active = 1;
    background = gf2d_sprite_load_image("images/backgrounds/bg_flat.png");
    music = gfc_sound_load("sounds/Menu.mp3", 1, 0);
    gfc_sound_play(music, 500, 1, -1, -1);
    while (men->active) {

        gf2d_graphics_clear_screen();
        gf2d_sprite_draw_image(background, vector2d(0, 0));
        gfc_input_update();
        menu_draw(men);
        menu_think(men);
        gf2d_grahics_next_frame();

        if (!men->active && men->current_button == 2) {
            gfc_sound_clear_all();
            return 1;
        }

    }
    gfc_sound_clear_all();
    return 0;
}


int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    Sprite *sprite;
    level *lev;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    SDL_Rect rect;
    int mx,my;
    float mf = 0;
    Entity* mouse, * other, * crop;
    Vector4D mouseColor = {255,100,255,200};
    Input in;
    menu *men, *mainM;
    TTF_Font* font;
    
    /*program initializtion*/
    init_logger("gf2d.log");

    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        1200,
        720,
        1200,
        720,
        vector4d(0,0,0,255),
        0);
    fonts_init();
    font = TTF_OpenFont("PKMN.ttf", 25);
    SDL_Color color = { 255, 255, 0 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Why won't you show up", color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gf2d_graphics_get_renderer(), surface);
    gf2d_graphics_set_frame_delay(16);
    gfc_input_init("config/inputs.json");
    gfc_audio_init(128, 2, 2, 2, 1, 1);
    gf2d_sprite_init(1024);
    entity_system_init(1024);
    borders_init(64);
    menu_manager_init(32);
    level_manager_init(32);
    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/
    sprite = gf2d_sprite_load_image("images/backgrounds/Test_Area.png");

    men = menu_load("config/menus.json", "shop");

    mainM = menu_load("config/menus.json", "main");

    done = main_menu(mainM);

    rect.x = 100;
    rect.y = 100;
    rect.h = 100;
    rect.w = 100;

    currentLevel = level_load("levels/testlevel.json");


    /*main game loop*/
    while(!done)
    {
        frameStart = SDL_GetTicks();
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);

        timer_update();


        gfc_input_update();

        
        entity_layer_sort();

        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            level_draw();
            SDL_RenderCopy(gf2d_graphics_get_renderer(), texture, NULL, &rect);
            if (men->active && men != NULL) {
                menu_think(men);
                menu_draw(men);
            }
            else {
                level_update();
            }            

        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
        slog("FPS: %i", frameTime);
        if (gfc_input_command_pressed("Menu")) men->active = 1;

        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
    }
    TTF_Quit;
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
