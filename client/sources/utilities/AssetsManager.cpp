
/* Created by Romain FOUYER on 19/11/2019 at 16:52. */


#include "utilities/AssetsManager.hpp"

rtype::utils::AssetsManager::AssetsManager()
{
    /* Music | Sound */
    _assets["menu_music"] = "./assets/music/menu.ogg";
    _assets["game_music"] = "./assets/music/game.ogg";

    _assets["fire_explosion_sound"] = "./assets/sounds/fire_explosion.wav";
    _assets["lightning_explosion_sound"] = "./assets/sounds/lightning_explosion.wav";

    _assets["shoot"] = "./assets/sounds/shoot.wav";

    /* UI */
    _assets["play_button"] = "./assets/ui/button_play.png";
    _assets["exit_button"] = "./assets/ui/button_exit.png";
    _assets["settings_button"] = "./assets/ui/button_settings.png";

    _assets["start_button"] = "./assets/ui/button_start.png";
    _assets["back_arrow_button"] = "./assets/ui/back_arrow.png";
    _assets["logo"] = "./assets/ui/r_type_logo.png";
    _assets["ip_input_ui"] = "./assets/ui/ip_address_input.png";
    _assets["sample_button"] = "./assets/ui/sample_button.png";
    _assets["create_lobby"] = "./assets/ui/button_create_lobby.png";

    /* Sprites */
    _assets["menu_background"] = "./assets/sprites/space_background.jpg";
    _assets["game_background"] = "./assets/sprites/game_background.png";

    /* Players */
    _assets["player1"] = "./assets/sprites/player_sprite.png";
    _assets["player2"] = "./assets/sprites/player_sprite_green.png";
    _assets["player3"] = "./assets/sprites/player_sprite_orange.png";
    _assets["player4"] = "./assets/sprites/player_sprite_pink.png";

    /* Enemies */
    _assets["enemy_one"] = "./assets/sprites/enemy_one.png";
    _assets["enemy_two"] = "./assets/sprites/enemy_two.png";
    _assets["enemy_three"] = "./assets/sprites/enemy_three.png";
    _assets["enemy_four"] = "./assets/sprites/enemy_four.png";

    /* Effects */
    _assets["fire_explosion"] = "./assets/sprites/effects/fire_explosion.png";
    _assets["lightning_explosion"] = "./assets/sprites/effects/lightning_explosion.png";
    _assets["basic_shoot"] = "./assets/sprites/effects/basic_shoot.png";

    /* Fonts */
    _assets["default_font"] = "./assets/fonts/pixellari.ttf";
    _assets["menu_font"] = "./assets/fonts/newpixel.ttf";
}

rtype::utils::AssetsManager &rtype::utils::AssetsManager::getInstance()
{
    static rtype::utils::AssetsManager instance;

    return instance;
}

std::map<std::string, std::string> rtype::utils::AssetsManager::getAssets() const
{
    return _assets;
}

std::string rtype::utils::AssetsManager::getAsset(const std::string &asset)
{
    return rtype::utils::AssetsManager::getInstance().getAssets().at(asset);
}

const std::string &rtype::utils::AssetsManager::operator[](const std::string &asset)
{
    return _assets[asset];
}
