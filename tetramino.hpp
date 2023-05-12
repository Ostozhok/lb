#pragma once
#include <array>
#include <SFML/Graphics.hpp>
using namespace sf;
 
struct Point
{
    int x, y;
};
 
class Tetramino
{
public:
    Tetramino()
        : m_type{ 0 }, m_tetratype{ 0 }, m_sprites{ Sprite{} }, m_sprites_cords{ 0 },
        m_color{ Color::Black }
    {}
    Tetramino(Texture& texture, int correct_x = 0, int correct_y = 0);
    std::array <Sprite, 4> getSprites() { return m_sprites; }
    std::array <Point, 4> getSpritesCords() { return m_sprites_cords; }
    void setSpritesCords(std::array <Point, 4>& arr);
    void moveRight();
    void moveLeft();
    void makeRotation();
private:
    int m_type, m_correction_x, m_correction_y;
    std::array <std::array <int, 4>, 7> m_tetratype;
    std::array <Sprite, 4> m_sprites;
    std::array <Point, 4> m_sprites_cords;
    std::array <Color, 4> m_color;
    void spriteCordCalculation(int sprite_index);
};
