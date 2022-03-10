#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"

#include "gfc_audio.h"
#include "gfc_input.h"

#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "crops.h"

#include "level.h"
#include "borders.h"
#include "timer.h"

int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    Sprite *sprite;
    level *lev;
    
    int mx,my;
    float mf = 0;
    Entity* mouse, * other, * crop;
    Vector4D mouseColor = {255,100,255,200};
    Input in;
    
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
    gf2d_graphics_set_frame_delay(16);
    gfc_input_init("config/inputs.json");
    gfc_audio_init(128, 2, 2, 2, 1, 1);
    gf2d_sprite_init(1024);
    entity_system_init(1024);
    borders_init(64);
    level_manager_init(32);
    SDL_ShowCursor(SDL_DISABLE);

    lev = level_load("levels/testlevel.json");
    
    /*demo setup*/
    sprite = gf2d_sprite_load_image("images/backgrounds/Test_Area.png");
    other = enemy_new();
    mouse = player_new();
    crop = crops_new("config/crops.json", CROP_SQUIRTLE, vector2d(200, 100));
    /*main game loop*/
    while(!done)
    {
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
            level_draw(lev);
            entity_think_all();
            entity_update_all();
            entity_collision_tests();

        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
        
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
    }
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
