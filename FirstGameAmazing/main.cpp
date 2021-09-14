#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
//#include <Windows.h>
using namespace std;

int main()
{
    /*
    char path[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, path);
    MessageBoxA(NULL, path, "Current Directory", MB_OK);
    */

    sf::Cursor cursor;
    sf::Clock clock;
    sf::Clock BulletTime;
    int windowHeight = 720;
    int windowWidth = 1280;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Amazing Game", sf::Style::Close);
    /*sf::CircleShape Player(40.f);
    Player.setRadius(40.f);
    Player.setOrigin(40, 40);
    Player.setFillColor(sf::Color::Blue);
    Player.setPosition(windowWidth / 2.f, windowHeight / 2.f);*/
    Player Player1(sf::CircleShape(40.f), (float)40.f, sf::Color(51, 255, 255), (int)40, (int)40, (int)windowWidth / 2.f, (int)windowHeight / 2.f);
    Enemy Enemy1(sf::CircleShape(40.f), (float)40.f, sf::Color(255, 1, 1), (int)40, (int)40, (int)500, (int)500);
    Enemy Enemy2(sf::CircleShape(40.f), (float)40.f, sf::Color(255, 200, 1), (int)40, (int)40, (int)400, (int)500);
    /*sf::CircleShape Bullet(10.f);
    Bullet.setRadius(10.f);
    Bullet.setOrigin(10, 10);
    Bullet.setFillColor(sf::Color::White);
    Bullet.setPosition(windowWidth / 2.f, windowHeight / 2.f);*/
    Bullet Bullet1(sf::CircleShape(10.f), (float)10.f, sf::Color(160, 160, 160), (int)10, (int)10, (int)windowWidth / 2.f, (int)windowHeight / 2.f);
    int BulletSpeed = 2;
    /*sf::CircleShape Enemy(40.f);
    Enemy.setRadius(40.f);
    Enemy.setOrigin(40, 40);
    Enemy.setFillColor(sf::Color::Green);
    Enemy.setPosition(windowWidth / 2.5f, windowHeight / 2.5f);*/

    //sf::Vector2f position = woasd.getPosition();
    sf::Font mainFont;
    if (!mainFont.loadFromFile("Roboto-Regular.ttf"))
    {
        cout << "Fail";
    }
    sf::Text GameOver;
    GameOver.setFont(mainFont);
    GameOver.setString("Game Over");
    GameOver.setCharacterSize(50);
    GameOver.setOrigin(70, 50);
    GameOver.setPosition(windowWidth / 2.f + 50, windowHeight / 2.f);
    GameOver.setFillColor(sf::Color::Black);
    sf::Text Health;
    sf::Clock EnRes;
    sf::Clock EnRes2;
    
    Health.setFont(mainFont);
    Health.setString("Health: ");
    Health.setCharacterSize(20);
    //GameOver.setPosition(windowWidth / 2.f + 50, windowHeight / 2.f);
    Health.setFillColor(sf::Color::Black);
    float EnemySpeed = .01f;
 
    
    while (window.isOpen())
    {
        sf::Event event;
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        sf::Vector2f mPos = window.mapPixelToCoords(mouse);
        sf::Vector2f position = Player1.Circle.getPosition();
        sf::Vector2f mouseDiff{ position.x - mPos.x, position.y - mPos.y };
        float rad = atan2f(mouseDiff.y, mouseDiff.x) + 3.14159f;
        sf::Vector2f direction{ cosf(rad), sinf(rad) };
        rad = (rad >= 0 ? rad : (2 * 3.1415f) + rad) * (180 / 3.1415f);
        Player1.Circle.setRotation(rad);
        sf::VertexArray LinePo;
        LinePo.append(sf::Vertex({ position.x + direction.x * 10 , position.y + direction.y * 10 }, sf::Color(0, 0, 255)));
        LinePo.append(sf::Vertex({ position.x + (direction.x * 100) , position.y + (direction.y * 100) }, sf::Color(0, 0, 255)));
        LinePo.append(position);
        LinePo.setPrimitiveType(sf::PrimitiveType::Lines);
        //float bulletTime = BulletTime.getElapsedTime().asSeconds();
        
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left && Player1.isDead == false)
                {
                    //BulletTime.restart();
                    //Bullet1.IsSpawned = true;
                    window.setKeyRepeatEnabled(false);
                    std::cout << " pressed" << std::endl;
                    Bullet1.Circle.setPosition(position.x, position.y);
                    Bullet1.Circle.move(direction.x, direction.y);
                    Bullet1.Circle.setPosition(mPos);
                    
                    
                    
                
                }
                
            }
            
               
        }
        //sf::Time elapsed = clock.restart();
        sf::Vector2f PlayerPos = Player1.Circle.getPosition();
        sf::Vector2f EnemyPos = Enemy1.Circle.getPosition();
        sf::Vector2f BulletPos = Bullet1.Circle.getPosition();
        sf::VertexArray En2Pl(sf::LineStrip, 2);
        En2Pl[0].position = sf::Vector2f(EnemyPos.x, EnemyPos.y);
        En2Pl[1].position = sf::Vector2f(PlayerPos.x, PlayerPos.y);
        sf::VertexArray Bu2Pl(sf::LineStrip, 2);
        Bu2Pl[0].position = sf::Vector2f(BulletPos.x, BulletPos.y);
        Bu2Pl[1].position = sf::Vector2f(PlayerPos.x, PlayerPos.y);
        float delta = clock.restart().asSeconds() * 60;
        sf::Vector2f direction2Pl = Player1.Circle.getPosition() - Enemy1.Circle.getPosition();
        Enemy1.Circle.move(delta * EnemySpeed * direction2Pl);\
        sf::Vector2f direction2Pl2 = Player1.Circle.getPosition() - Enemy2.Circle.getPosition();
        Enemy2.Circle.move(delta * EnemySpeed * direction2Pl2);
        if (cursor.loadFromSystem(sf::Cursor::Hand))
            window.setMouseCursor(cursor);
        //if (bulletTime == 3);
        //{
           // Bullet1.IsSpawned = false;
        //}
        //cout << bulletTime.asSeconds() << endl;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && Player1.isDead == false)
        {
            Player1.Circle.move(0.f, -1.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && Player1.isDead == false)
        {
            Player1.Circle.move(0.f, 1.f);
            
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && Player1.isDead == false)
        {
            Player1.Circle.move(-1.f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && Player1.isDead == false)
        {
            Player1.Circle.move(1.f, 0.f);
        }
        //cout << Player1.Circle.Position.x << endl;
        if (PlayerPos.y >= 680)
            Player1.Circle.move(0.f, -1.f);
        if (PlayerPos.y <= 41)
            Player1.Circle.move(0.f, 1.f);
        if (PlayerPos.x <= 41)
            Player1.Circle.move(1.f, 0.f);
        if (PlayerPos.x >= 1239)
            Player1.Circle.move(-1.f, 0.f);
        
        sf::FloatRect PlayerHitbox = Player1.Circle.getGlobalBounds();
        sf::FloatRect BulletHitbox = Bullet1.Circle.getGlobalBounds();
        
        
        sf::FloatRect Enemy1Hitbox = Enemy1.Circle.getGlobalBounds();
        sf::FloatRect Enemy2Hitbox = Enemy2.Circle.getGlobalBounds();

        //Enemy1.Circle.move();
       

        
        //cout << Player1.HP << endl;
        window.clear(sf::Color(195,98,65));
        if (Player1.isDead == false)
            window.draw(Player1.Circle);
        if (Enemy1.isDead == false)
        {
            if (!BulletHitbox.intersects(Enemy1Hitbox))
                window.draw(Enemy1.Circle);
            else if (BulletHitbox.intersects(Enemy1Hitbox))
                Enemy1.isDead = true;
        }
        
        if (Enemy2.isDead == false)
        {
            if (!BulletHitbox.intersects(Enemy2Hitbox) )
                window.draw(Enemy2.Circle);
            else if (BulletHitbox.intersects(Enemy2Hitbox))
                Enemy2.isDead = true;
        }
        
        if (Player1.isDead == false)
        {
            window.draw(Bullet1.Circle);
            //window.draw(LinePo);
        }
           
        //window.draw(GameOver);
        if (PlayerHitbox.intersects(Enemy1Hitbox) && Enemy1.isDead == false && Player1.isDead == false)
        {
            Player1.HP -= 1;
            //Player1.isDead = true;
            
        }
        if (PlayerHitbox.intersects(Enemy2Hitbox) && Enemy2.isDead == false && Player1.isDead == false)
        {
            Player1.HP -= 1;
            //Player1.isDead = true;

        }
        
        if (Player1.HP <= 0)
        {
            Player1.Lives -= 1;
            Player1.Circle.setPosition(windowWidth / 2.f, windowHeight / 2.f);
            Player1.HP = 100;
            if (Player1.Lives == 0)
                Player1.isDead = true;
        }
            
        if (Player1.isDead == true)
            window.draw(GameOver);
        window.draw(Health);
        if (EnRes.getElapsedTime().asSeconds() != 0 && Enemy1.isDead == false)
            EnRes.restart();
        if (EnRes2.getElapsedTime().asSeconds() != 0 && Enemy2.isDead == false)
            EnRes2.restart();
        if (Enemy1.isDead == true)
        {
            float times = EnRes.getElapsedTime().asSeconds();
            cout << times << endl;
            if ( times >= 4 )
            {

                int SpaX = rand() %  1280 + 1;
                int SpaY = rand() % 720 + 1;
                Enemy1.Circle.setPosition(SpaX, SpaY);
                Enemy1.isDead = false;
                
            }
                 
               
        }
        if (Enemy2.isDead == true)
        {
            float times = EnRes2.getElapsedTime().asSeconds();
            cout << times << endl; 
            if (times >= 4)
            {

                int SpaX = rand() % 1280 + 1;
                int SpaY = rand() % 720 + 1;
                Enemy2.Circle.setPosition(SpaX, SpaY);
                Enemy2.isDead = false;

            }


        }

        //window.draw(En2Pl);
        //window.draw(Bu2Pl);
        window.display();
        window.setFramerateLimit(144);
    }

    return 0;
}