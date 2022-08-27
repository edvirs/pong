#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

using namespace std;

int main(int argc, const char * argv[])
{
    unsigned int displayWidth = 1920;
    unsigned int displayHeight = 1080;
    unsigned int x = displayHeight/10;
    unsigned int borderLenght = 0.75 * x;
    unsigned int borderSpace = 0.25 * x;
    int velocity = 13;
    int velocityDirectionX = 1;
    int velocityDirectionY = 1;
    int inputRectVelocity = 15;
    srand((unsigned int)time(0));
    
    if ((rand() % 2) + 1 > 1) velocityDirectionX = -1;
    if ((rand() % 2) + 1 > 1) velocityDirectionY = -1;
    sf::Vector2f ballVelocity(velocity * velocityDirectionX , velocity * velocityDirectionY);
    
    sf::RenderWindow window(sf::VideoMode(displayWidth, displayHeight), "pong");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    
    sf::RectangleShape leftRect, rightRect, border;
    sf::CircleShape ball;
    
    sf::Vector2f rectSize(25, 150);
    sf::Vector2f borderSize(15, borderLenght);
    sf::Vector2f leftRectPosition(30, 100);
    sf::Vector2f rightRectPosition(displayWidth - (rectSize.x + 30), 100);
    sf::Vector2f borderPosition((displayWidth / 2) - borderSize.x / 2, 0);
    
    leftRect.setSize(rectSize);
    rightRect.setSize(rectSize);
    border.setSize(borderSize);
    ball.setRadius(borderLenght / 3);
    sf::Vector2f ballPosition(displayWidth / 2 - ball.getRadius(), (rand() % displayHeight) - ball.getRadius() * 2);
    
    leftRect.setPosition(leftRectPosition);
    rightRect.setPosition(rightRectPosition);
    border.setPosition(borderPosition);
    ball.setPosition(ballPosition.x, ballPosition.y);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
                
           /* if (event.type == sf::Event::EventType::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
                {
                    leftRectPosition.y -= inputRectVelocity;
                    leftRect.setPosition(leftRectPosition.x, leftRectPosition.y);
                }
                
                else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
                {
                    leftRectPosition.y += inputRectVelocity;
                    leftRect.setPosition(leftRectPosition.x, leftRectPosition.y);v
                }
            } */
        }
        
        
        if (ballPosition.x - rectSize.x < leftRectPosition.x)                                   //Collision
        {
            if(ballPosition.y + ball.getRadius() >= leftRectPosition.y &&
               ballPosition.y - ball.getRadius() <= leftRectPosition.y + rectSize.y)
            {
                ballVelocity.x *= -1;
            }
            
            /*if(ballPosition.y >= leftRectPosition.y - ball.getRadius() &&
                 ballPosition.y <= leftRectPosition.y + ball.getRadius() + rectSize.y)
            {
                ballVelocity.x *= -1;
            }*/
        }
        
        if(ballPosition.x + ball.getRadius() * 2 > rightRectPosition.x)
        {
            ballVelocity.x *= -1;
        }
        
        if (ballPosition.y < 0 || ballPosition.y + ball.getRadius() * 2 > displayHeight)
        {
            ballVelocity.y *= -1;
        }
        
        if (ballPosition.x + ball.getRadius() * 2 < 0 || ballPosition.x > displayWidth)
        {
            if ((rand() % 2) + 1 > 1) velocityDirectionX = -1;
            if ((rand() % 2) + 1 > 1) velocityDirectionY = -1;
            ballVelocity.x = velocity * velocityDirectionX;
            ballVelocity.y = velocity * velocityDirectionY;
            ballPosition.x = displayWidth / 2 - ball.getRadius();
            ballPosition.y = (rand() % displayHeight) - ball.getRadius() * 2;
            ball.setPosition(ballPosition.x, ballPosition.y);
        }
 
        
        ballPosition.x += ballVelocity.x;                                                       //Velocity
        ballPosition.y += ballVelocity.y;
        ball.setPosition(ballPosition.x, ballPosition.y);
        
        
        rightRectPosition.y = ballPosition.y - ((rectSize.y / 2) - ball.getRadius());           //Rects position
        rightRect.setPosition(rightRectPosition.x, rightRectPosition.y);
        
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) &&
            leftRectPosition.y > 0)
        {
            leftRectPosition.y -= inputRectVelocity;
            leftRect.setPosition(leftRectPosition.x, leftRectPosition.y);
        }
        
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) &&
            leftRectPosition.y + rectSize.y < displayHeight)
        {
            leftRectPosition.y += inputRectVelocity;
            leftRect.setPosition(leftRectPosition.x, leftRectPosition.y);
        }

        //leftRectPosition.y = ballPosition.y - ((rectSize.y /2) - ball.getRadius());
        //leftRect.setPosition(leftRectPosition.x, leftRectPosition.y);
        
        window.clear();
        for(int i=0; i < 10; i++)
        {
            window.draw(border);
            borderPosition.y += borderLenght + borderSpace;
            border.setPosition(borderPosition.x, borderPosition.y);
        }
        
        border.setPosition(borderPosition.x, 0);
        borderPosition.y = 0;
        
        window.draw(leftRect);
        window.draw(rightRect);
        window.draw(ball);
        window.display();
    }
}
