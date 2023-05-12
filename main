#include <array>
#include "tetramino.hpp"
 
using namespace sf;
 
const int Y = 21;
const int X = 10;
 
std::array <std::array <bool, Y>, X> is_field_sprite{ false };
std::array <std::array <Sprite, Y>, X> field_sprites;
 
void fEvents(RenderWindow& window, Tetramino& tetramino, float& delay);
void fCheck_field(Tetramino& tetramino, std::array <Point, 4>& good_points);
bool fGoDown(Tetramino& tetramino, float& timer, float& delay, Clock& clock);
void fSearchAndDelLines();
void fDeleteLine(int line);
bool fIsGameOver(Tetramino& tetramino);
void fPrintText(std::string text, Font &font, RenderWindow &window);
 
int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(320, 480), "The Game!", Style::Default, settings);
    Texture texture_cube, texture_background, texture_frame;
    texture_cube.loadFromFile("/Users/sashastozhok/Desktop/img/tiles.png");
    texture_frame.loadFromFile("/Users/sashastozhok/Desktop/img/frame.png");
    texture_background.loadFromFile("/Users/sashastozhok/Desktop/img/Background.png");
    Sprite frame(texture_frame);
    Sprite background(texture_background);
    Font font;

    bool new_tetramino = true;
    bool game_over = false;
    Tetramino tetramino;
    std::array <Point, 4> good_points;
    float timer = 0, delay = 0.3f;
    Clock clock;
    while (window.isOpen())
    {
        window.clear(Color::White);
        window.draw(background);
        window.draw(frame);
        if (new_tetramino && !game_over)
        {
            tetramino = Tetramino(texture_cube, 28, 31);
            new_tetramino = false;
 
            if (fIsGameOver(tetramino))
                game_over = true;
        }
        
        if (!fGoDown(tetramino, timer, delay, clock))
            new_tetramino = true;
 
        fCheck_field(tetramino, good_points);
 
        fSearchAndDelLines();
 
        std::array <Sprite, 4> temp_sprites{ tetramino.getSprites() };
        for (int i = 0; i < temp_sprites.size(); i++)
            window.draw(temp_sprites.at(i));
 
        for (int x = 0; x < field_sprites.size(); x++)
            for (int y = 0; y < field_sprites.at(x).size(); y++)
                window.draw(field_sprites.at(x).at(y));
 
        fEvents(window, tetramino, delay);
 
        if (game_over)
            fPrintText("Game Over!", font, window);
 
        window.display();
    }
    return 0;
}
 
void fEvents(RenderWindow& window, Tetramino& tetramino, float& delay)
{
    Event event;
    while (window.pollEvent(event))
    {
        // Пользователь нажал на «крестик» и хочет закрыть окно?
        if (event.type == Event::Closed)
            // тогда закрываем его
            window.close();
        if (event.type == Event::KeyPressed){
            if (event.key.code == Keyboard::Right)
            {
                tetramino.moveRight();
            }
            else if (event.key.code == Keyboard::Left)
            {
                tetramino.moveLeft();
            }
            else if (event.key.code == Keyboard::Up)
            {
                tetramino.makeRotation();
            }
            else if (event.key.code == Keyboard::Down)
            {
                delay = 0.05f;
            }
        }
    }
}
 
void fCheck_field(Tetramino& tetramino, std::array <Point, 4>& good_points)
{
    std::array <Point, 4> temp = tetramino.getSpritesCords();
    int count = 0;
    for (int i = 0; i < good_points.size(); i++)
    {
        if (temp.at(i).x < X && temp.at(i).x >= 0 && temp.at(i).y < Y-1 && temp.at(i).y >= 0 &&
            is_field_sprite.at(temp.at(i).x).at(temp.at(i).y+1) == false)
            count++;
        else
            break;
    }
    if (count == 4)
    {
        good_points = temp;
    }
    else
        tetramino.setSpritesCords(good_points);
}
 

bool fGoDown(Tetramino& tetramino, float& timer, float& delay, Clock& clock)
{
    bool result = true;
    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    timer += time;
    std::array <Point, 4> sprites_cords = tetramino.getSpritesCords();
    if (timer > delay)
    {
        for (int i = 0; i < sprites_cords.size(); i++)
        {
            sprites_cords.at(i).y += 1;
            if (sprites_cords.at(i).y == Y - 1 ||
                (sprites_cords.at(i).y > 0 &&
                    (sprites_cords.at(i).y > 0 && is_field_sprite.at(sprites_cords.at(i).x).at(sprites_cords.at(i).y + 1))))
            {
                delay = 0.3f;
                result = false;
            }
        }
        if (!result)
            for (int i = 0; i < sprites_cords.size(); i++)
            {
                is_field_sprite.at(sprites_cords.at(i).x).at(sprites_cords.at(i).y) = true;
                field_sprites.at(sprites_cords.at(i).x).at(sprites_cords.at(i).y) = tetramino.getSprites().at(i);
            }
        tetramino.setSpritesCords(sprites_cords);
        timer = 0;
    }
    return result;
}
void fSearchAndDelLines()
{
    for (int y = 1; y < is_field_sprite.at(0).size(); y++)
    {
        int count = 0;
        for (int x = 0; x < is_field_sprite.size(); x++)
        {
            if (!is_field_sprite.at(x).at(y))
                break;
            else
                count++;
        }
        if (count == is_field_sprite.size())
            fDeleteLine(y);
    }
}
void fDeleteLine(int line)
{
    for (int y = line; y > 0; y--)
        for (int x = 0; x < is_field_sprite.size(); x++)
        {
            is_field_sprite.at(x).at(y) = is_field_sprite.at(x).at(y - 1);
            field_sprites.at(x).at(y) = field_sprites.at(x).at(y - 1);
            field_sprites.at(x).at(y).move(0, 18);
        }
}
bool fIsGameOver(Tetramino& tetramino)
{
    std::array <Point, 4> temp = tetramino.getSpritesCords();
    for (int i = 0; i < temp.size(); i++)
    {
        if (is_field_sprite.at(temp.at(i).x).at(temp.at(i).y))
            return true;
    }
    return false;
}
