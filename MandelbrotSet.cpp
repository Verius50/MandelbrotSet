#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
VertexArray dots(Points, 0);
int DotInMultitude(long double x, long double y, long double factor, int depth)
{
    double xn = x, yn = y, xTemp = 0, yTemp = 0;
    if (xn * xn + yn * yn > 4.0)
        return 0;
    for (int i = 0; i < depth; i++){
        xTemp = xn * xn - yn * yn + x;
        yTemp = 2 * xn * yn + y;
        xn = xTemp;
        yn = yTemp;
        if (xn*xn + yn*yn > 4.0)
            return i;
    }

    return -1;
}
void CountDots(long double xbias, long double ybias, long double increaseCoef, int depth, bool color) {
    dots.clear();
    int answer;
    for (long double x = -2  / increaseCoef - xbias; x < 2 / increaseCoef- xbias; x += 0.01f / increaseCoef)
        for (long double y = -2 / increaseCoef - ybias; y < 2 / increaseCoef- ybias; y += 0.01f / increaseCoef) {
            answer = DotInMultitude(x, y, increaseCoef, depth);
            if (answer == -1)
            {
                dots.resize(dots.getVertexCount() + 1);
                dots[dots.getVertexCount() - 1].position = Vector2f(400 + (x + xbias) * 100.0 * increaseCoef, 300 + (y+ybias) * 100.0 * increaseCoef);
                dots[dots.getVertexCount() - 1].color = Color();
            }
            if (color)
                if ( answer > 0){
                dots.resize(dots.getVertexCount() + 1);
                dots[dots.getVertexCount() - 1].position = Vector2f(400 + (x + xbias) * 100.0 * increaseCoef, 300 + (y + ybias) * 100.0 * increaseCoef);
                switch (answer)
                {
                case 1:
                    break;
                }
                dots[dots.getVertexCount() - 1].color = Color(answer * 20 % 255, answer * 10 % 255, answer * 50 % 255, 255);
            }
        }
}

int main()
{
    RenderWindow window(sf::VideoMode(800, 600), "MandelbrotSet");
    window.setFramerateLimit(60);
    Font font;
    font.loadFromFile("arial.ttf");
    Text information("", font);
    information.setFillColor(Color::Black);
    VertexArray CoordsLines(Lines, 4);
    CoordsLines[0].position = Vector2f(200, 300);
    CoordsLines[1].position = Vector2f(600, 300);
    CoordsLines[2].position = Vector2f(400, 100);
    CoordsLines[3].position = Vector2f(400, 500);
    for (size_t i = 0; i < CoordsLines.getVertexCount(); i++)
        CoordsLines[i].color = Color::Black;
    RectangleShape square;
    square.setSize(Vector2f(window.getSize().x / 2, window.getSize().x / 2));
    square.setPosition(Vector2f(window.getSize().x / 4, window.getSize().y / 6)); 
    square.setFillColor(Color(255, 255, 255, 0));
    square.setOutlineThickness(2);
    square.setOutlineColor(Color(0, 0, 0, 255));
    
    long double xpos = 0, ypos = 0, increase = 1, depth = 50;
    CountDots(xpos, ypos, increase, depth, 0);
    

    bool pressed = 0, color = 0;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseWheelMoved)
                increase+= increase * event.mouseWheel.delta / 50.0f;
        }
        window.clear(Color::White);

        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            xpos -= 0.01 / increase;
            pressed = 1;
            for (size_t i = 0; i < dots.getVertexCount(); i++)
                dots[i].position.x--;
        }
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            xpos += 0.01/ increase;
            pressed = 1;
            for (size_t i = 0; i < dots.getVertexCount(); i++)
                dots[i].position.x++;
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            ypos -= 0.01 / increase;
            pressed = 1;
            for (size_t i = 0; i < dots.getVertexCount(); i++)
                dots[i].position.y--;
        }
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            ypos += 0.01 / increase;
            pressed = 1;
            for (size_t i = 0; i < dots.getVertexCount(); i++)
                dots[i].position.y++;
        }
        if (Keyboard::isKeyPressed(Keyboard::Enter) && !pressed)
        {
            CountDots(xpos, ypos, increase, depth, color);
            pressed = 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::Enter) && pressed)
            pressed = 0;
        if (Keyboard::isKeyPressed(Keyboard::C))
            color = true;
        if (Keyboard::isKeyPressed(Keyboard::B))
            color = false;
        if (Keyboard::isKeyPressed(Keyboard::LShift))
            depth += depth / 120;
        if (Keyboard::isKeyPressed(Keyboard::LControl))
            depth -= depth / 120;
        information.setString("X position" + std::to_string(xpos)+"\n Increase: " + std::to_string(increase)
            +"\nDepth: " + std::to_string(depth) + "\nColor: "+ std::to_string(color));
        window.draw(square);
        window.draw(dots);    
        window.draw(CoordsLines);
        window.draw(information);
        window.display();
    }
}