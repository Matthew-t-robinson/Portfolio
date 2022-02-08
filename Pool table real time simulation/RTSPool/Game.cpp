#include "Game.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>
#include "Circles.h"
#include "Walls.h"

void Game::run()
{
    float radius = 20.f;
    //this creates the window
    sf::RenderWindow window(sf::VideoMode(1080, 720), "RTS");
    window.setFramerateLimit(60);
    sf::Font font;
    if (!font.loadFromFile("fonts\\ARCADECLASSIC.ttf"))
    {
        std::cout << "failed" << "\n";
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    text.setPosition(820, 0);
    text.setString("High Score " + std::to_string(HighScore));
    sf::Text text2;
    text2.setFont(font);
    text2.setCharacterSize(40);
    text2.setFillColor(sf::Color::White);
    text2.setPosition(750, 50);
    text2.setString("Current Score " + std::to_string(bounces));
    //this creates all of the shapes that are used
    for (size_t i = 0; i < 15; i++)
    {
        
        Circles* ball = new Circles;
        g_balls.push_back(ball);
        g_balls[i]->circle.setRadius(radius);
        g_balls[i]->velocity = sf::Vector2f(0,0 );
        g_balls[i]->position = sf::Vector2f(rand()%1040, rand()%680);
        g_balls[i]->circle.setPosition(g_balls[i]->position);
    }
    Walls* wall1 = new Walls;
    wall1->line[0].position = sf::Vector2f(1, 1);
    wall1->line[0].color = sf::Color::Green;
    wall1->line[1].position = sf::Vector2f(1, 720);
    wall1->line[1].color = sf::Color::Green;
    g_walls.push_back(wall1);
    Walls* wall2 = new Walls;
    wall2->line[0].position = sf::Vector2f(1080, 0);
    wall2->line[0].color = sf::Color::Green;
    wall2->line[1].position = sf::Vector2f(1080, 1080);
    wall2->line[1].color = sf::Color::Green;
    g_walls.push_back(wall2);
    Walls* wall3 = new Walls;
    wall3->line[0].position = sf::Vector2f(0, 1);
    wall3->line[0].color = sf::Color::Green;
    wall3->line[1].position = sf::Vector2f(1080, 1);
    wall3->line[1].color = sf::Color::Green;
    g_walls.push_back(wall3);
    Walls* wall4 = new Walls;
    wall4->line[0].position = sf::Vector2f(0, 719);
    wall4->line[0].color = sf::Color::Green;
    wall4->line[1].position = sf::Vector2f(1080, 719);
    wall4->line[1].color = sf::Color::Green;
    g_walls.push_back(wall4);


    g_balls[0]->circle.setFillColor(sf::Color::Green);
    float mouseX = 0;
    float mouseY = 0;
    float distanceX = 0;
    float distanceY = 0;

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {

            mouseX = 0;
            mouseY = 0;
            g_balls[0]->velocity = sf::Vector2f(0, 0);
            mouseX = sf::Mouse::getPosition(window).x;
            mouseY = sf::Mouse::getPosition(window).y;
            distanceX = mouseX - (g_balls[0]->position.x + 20);
            distanceY = mouseY - (g_balls[0]->position.y + 20);
            g_balls[0]->velocity.x = distanceX / 30;
            g_balls[0]->velocity.y = distanceY / 30;
            bounces = 0;


        }
        for (size_t i = 0; i < g_balls.size(); i++)
        {
            g_balls[i]->position += g_balls[i]->velocity;
        }
        collision();
        //this checks to see if the wall has collided with a wall and changes the velocity accordingly so it bounces off 
        for (size_t i = 0; i < g_balls.size(); i++)
        {
            if (g_balls[i]->position.x <= 0)
            {

                g_balls[i]->velocity.x *= -1;

                g_balls[i]->position.x += g_balls[i]->velocity.x;


            }
            if (g_balls[i]->position.x >= 1080 - 40)
            {
                g_balls[i]->velocity.x *= -1;

                g_balls[i]->position.x += g_balls[i]->velocity.x;



            }
            
            if (g_balls[i]->position.y <= 0)
            {
                g_balls[i]->velocity.y *= -1;
                g_balls[i]->position.y += g_balls[i]->velocity.y;

            }
            if (g_balls[i]->position.y >= 720 - 40)
            {
                g_balls[i]->velocity.y *= -1;
                g_balls[i]->position.y += g_balls[i]->velocity.y;
            }
            if (g_balls[i]->velocity.x == 0)
            {
                g_balls[i]->velocity.x = g_balls[i]->velocity.x;
            }
            if (g_balls[i]->velocity.y == 0)
            {
                g_balls[i]->velocity.y = g_balls[i]->velocity.y;

            }

            g_balls[i]->circle.setPosition(g_balls[i]->position);
            //this applies the friction to the balls
            if ((0.01 > g_balls[i]->velocity.x) && (g_balls[i]->velocity.x > -0.01))
            {

                g_balls[i]->velocity.x = 0;
            }
            if ((0.01 > g_balls[i]->velocity.y) && (g_balls[i]->velocity.y > -0.01))
            {

                g_balls[i]->velocity.y = 0;
            }
            if (g_balls[i]->velocity.x > 0)
            {
                g_balls[i]->velocity.x = g_balls[i]->velocity.x * 0.99;

            }
            if (g_balls[i]->velocity.y > 0)
            {
                g_balls[i]->velocity.y = g_balls[i]->velocity.y * 0.99;
            }
            if (g_balls[i]->velocity.x < 0)
            {
                g_balls[i]->velocity.x = g_balls[i]->velocity.x * 0.99;

            }
            if (g_balls[i]->velocity.y < 0)
            {
                g_balls[i]->velocity.y = g_balls[i]->velocity.y * 0.99;
            }
        }

        //this draws the everything onto the screen
        window.clear();
        for (size_t i = 0; i < g_balls.size(); i++)
        {
            window.draw(g_balls[i]->circle);

        }
        for (size_t i = 0; i <g_walls.size(); i++)
        {
            window.draw(g_walls[i]->line,2,sf::Lines);
        }
        if (bounces > HighScore)
        {
            HighScore = bounces;
        }
        text.setString("High Score " + std::to_string(HighScore));
        text2.setString("Current Score " + std::to_string(bounces));
        window.draw(text);
        window.draw(text2);
        window.display();
    }
}

void Game::collision()
{

    for (size_t i = 0; i < g_balls.size(); i++)
    {
        sf::Vector2f ball1Position = g_balls[i]->position + sf::Vector2f(20.f,20.f); //creates a vector position that is at the centre of the ball
        sf::Vector2f ball1Velocity = g_balls[i]->velocity;
        int radius = 20;
        for (size_t j = 0; j < g_balls.size(); j++)
        {
            float distance = sqrt(pow(ball1Position.x - (g_balls[j]->position.x + 20), 2) + pow(ball1Position.y - (g_balls[j]->position.y + 20), 2)); //works out the distance
            if (i == j);
            else
            {
                if (((abs(ball1Velocity.x) > 0.0001f || abs(ball1Velocity.y > 0.0001f)) && (abs(g_balls[j]->velocity.y) > 0.0001f || abs(g_balls[j]->velocity.x) > 0.0001f)) && distance >= radius * 2) //checks to see if the balls are both moving
                {
                    movingCollision(g_balls[j], g_balls[i]);// if they are both moving it checks for movement collision
                }
                else
                {

                    sf::Vector2f ball2Position = g_balls[j]->position + sf::Vector2f(20.f, 20.f); // creates a vector position that is at the centre of the 2nd ball.
                    sf::Vector2f A{ ball2Position.x - ball1Position.x, ball2Position.y - ball1Position.y };// this works out the vector from the centre of ball 1 to the centre of ball 2
                    float aLength = sqrt(pow(A.x, 2) + pow(A.y, 2));//this works out the length of a
                    float cosa = CosOfAngle(A,ball1Velocity);//the cos of the angle between the vector a and the vector of the ball 1 velocity
                    float alpha = acos(cosa); // this works out the actual angle from the cos angle
                    float d = sin(alpha) * aLength;//this works out the distacne between the 2 centres along the ball 1 velocity vector
                    if (d <= radius * 2)//this checks if the distance is less than the sum of the 2 radii
                    {

                        float e = sqrt(pow(radius * 2, 2) - pow(d, 2));//this works out how fa along ball 1s velocity is the centre of ball 2.
                        float CollisionDistance = cosa * aLength - e; //this works out the distance till the collision
                        if (CollisionDistance >= 0 && CollisionDistance <= sqrt(pow(ball1Velocity.x, 2) + pow(ball1Velocity.y, 2)))// this checks if the collision distance is smaller than the velocity length.
                        {
                            
                            float length = sqrt(pow(ball2Position.x - ball1Position.x, 2) + pow(ball2Position.y - ball1Position.y, 2)); // this works out the length of the vector made found when you subtract the stationary ball position from the moving ball position
                            sf::Vector2f Fd{ (ball2Position.x - ball1Position.x) / length,(ball2Position.y - ball1Position.y) / length };// this works out the direction of the force using the 2 balls positions
                            float VelocityLength = sqrt(pow(ball1Velocity.x, 2) + pow(ball1Velocity.y, 2)); // this works out the length of the ball 1 velocity
                            float cosa2 = ((Fd.x * ball1Velocity.x) + (Fd.y * ball1Velocity.y)) / (VelocityLength); // this works out the cos of the angle between the force direction and the ball 1 velocity
                            float V2X = cosa2 * sqrt(pow(ball1Velocity.x, 2) + pow(ball1Velocity.y, 2)) * Fd.x; //this works out the new velocity of the x axis for ball 2
                            float V2Y = cosa2 * sqrt(pow(ball1Velocity.x, 2) + pow(ball1Velocity.y, 2)) * Fd.y; //this works out the new velocity of the y axis for ball 2
                            sf::Vector2f V2{ V2X,V2Y };
                            g_balls[j]->velocity = V2;// this applies the velocity to ball 2
                            sf::Vector2f V1{ g_balls[i]->velocity - V2 }; //this works out the new velocity of ball 1 by subtracting ball 2s  new velocity from ball 1s initial velocity
                            g_balls[i]->velocity = V1;// this applies the velocity to ball 1
                            bounces += 1;
                        }
                    }
                }
            }

        }
    }

    return;
}

void Game::movingCollision(Circles* one, Circles* two)
{
    //this uses the quadtratric formula to work out how much time it will take for the balls to collide, if the time is 0 at the start
    // and 1 at the end of there velocity vectors
    float xp = (one->position.x + 20) - (two->position.x + 20);
    float yp = (one->position.y + 20) - (two->position.y + 20);
    float xv = one->velocity.x - two->velocity.x;
    float yv = one->velocity.y - two->velocity.y;
    float a_ = (pow(xv, 2)) + (pow(yv, 2));
    float b = (2 * xp * xv) + (2 * yp * yv);
    float c = ((pow(xp, 2)) + (pow(yp, 2))) - (pow(40, 2));
    float t1 = (-b + sqrt((pow(b, 2)) - (4 * a_ * c))) / (2 * a_);
    float t2 = (-b - sqrt((pow(b, 2)) - (4 * a_ * c))) / (2 * a_);
    if ((t1 > 0 && t1 < 1) || (t2>0 && t2 < 1))// this checks to see if the time is between 0 and 1 and if it is, that means that they are going to collide during the next time it moves
    {
        sf::Vector2f s1{ one->position + sf::Vector2f{20,20} };
        sf::Vector2f s2{ two->position + sf::Vector2f{20,20} };
        sf::Vector2f velocity1{ one->velocity };
        sf::Vector2f velocity2{ two->velocity };
        float cosA2 = CosOfAngle((s2 - s1), velocity1); //this works out the cos of the angle between the ball 2 centre - ball 1 centre and the velocity of ball 1
        float cosB = CosOfAngle((s1 - s2), velocity2); //this works out the cos of the angle between the ball 1 centre - ball 2 centre and the velocity of ball 1

        float division = sqrt(pow(s2.x - s1.x, 2) + pow(s2.y - s1.y, 2));//this works out the length of the vector found when doing ball 2 centre - ball1 centre
        sf::Vector2f FD1{ (s2 - s1) / (division)}; // this works out the first ball direction
        sf::Vector2f FD2{ -FD1 };//this works out the second ball direction
        float v1Length = sqrt(pow(velocity1.x, 2) + pow(velocity1.y, 2)); // this works out the ball 1 velocity length
        float v2Length = sqrt(pow(velocity2.x, 2) + pow(velocity2.y, 2)); // this works out the ball 2 velocity length
        sf::Vector2f f12{ cosA2 * v1Length * FD1}; // this works out the force acting on ball 2 from ball 1
        sf::Vector2f f21{ cosB * v2Length * FD2}; // this works out the force acting on ball 1 from ball 2
        sf::Vector2f V2FD{ velocity2 + f12 - f21}; //this works out the post collision velocity for ball 2
        sf::Vector2f V1FD{ velocity1 + velocity2 - V2FD}; // this works out the post collision velocity for ball 1

        one->setVelocity(V1FD);//this applies the velocity to ball 1
        two->setVelocity(V2FD);//this applies the velocity to ball 2
        bounces += 1;
    }
}


float Game::CosOfAngle(sf::Vector2f AVector, sf::Vector2f BVector)
{
    float aL = sqrt(pow(AVector.x, 2) + pow(AVector.y, 2));
    float bL = sqrt(pow(BVector.x, 2) + pow(BVector.y, 2));
    float answer = ((AVector.x * BVector.x) + (AVector.y * BVector.y)) / (aL * bL);
    return answer;
}
