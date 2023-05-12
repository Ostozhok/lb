#include "tetramino.hpp"
#include <random>
 
Tetramino::Tetramino(Texture& texture, int correct_x, int correct_y)
: m_type{ static_cast<int>((std::mt19937(std::random_device{}())() % 7)) },
    m_tetratype
{
    1,3,5,7, // I
    2,4,5,7, // S
    3,5,4,6, // Z
    3,5,4,7, // T
    2,3,5,7, // L
    3,5,7,6, // J
    2,3,4,5  // O
},
m_sprites_cords{ 0 }, m_color
{
    Color::White,
    Color::Red,
    Color::Green,
    Color::Yellow
},
m_correction_x{ correct_x }, m_correction_y{ correct_y }
{
    Color color = m_color.at(std::mt19937(std::random_device{}())() % 4);
    for (int i = 0; i < m_sprites.size(); i++)
    {
        m_sprites_cords.at(i).x = m_tetratype.at(m_type).at(i) % 2;
        m_sprites_cords.at(i).y = m_tetratype.at(m_type).at(i) / 2;
        spriteCordCalculation(i);
        m_sprites.at(i).setTexture(texture);
        m_sprites.at(i).setTextureRect(IntRect(0, 0, 18, 18));
        m_sprites.at(i).setColor(color);
    }
}
 
void Tetramino::setSpritesCords(std::array<Point, 4>& arr)
{
    m_sprites_cords = arr;
    for (int i = 0; i < m_sprites.size(); i++)
    {
        spriteCordCalculation(i);
    }
}
 
void Tetramino::moveRight()
{
    for (int i = 0; i < m_sprites.size(); i++)
    {
        m_sprites_cords.at(i).x += 1;
        spriteCordCalculation(i);
    }
}
 
void Tetramino::moveLeft()
{
    for (int i = 0; i < m_sprites.size(); i++)
    {
        m_sprites_cords.at(i).x -= 1;
        spriteCordCalculation(i);
    }
}
 
void Tetramino::makeRotation()
{
    Point center = m_sprites_cords.at(1); // указываем центр вращения
    for (int i = 0; i < m_sprites_cords.size(); i++)
    {
        int x = m_sprites_cords.at(i).y - center.y; // y - y0
        int y = m_sprites_cords.at(i).x - center.x; // x - x0
        m_sprites_cords.at(i).x = center.x - x;
        m_sprites_cords.at(i).y = center.y + y;
        spriteCordCalculation(i);
    }
}
 
void Tetramino::spriteCordCalculation(int sprite_index)
{
    m_sprites.at(sprite_index).setPosition(m_correction_x + m_sprites_cords.at(sprite_index).x * 18.f, m_correction_y + m_sprites_cords.at(sprite_index).y * 18.f);
}
