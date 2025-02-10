#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Particle {
public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float radius;
    sf::Color color;

    Particle(float x, float y, float r, sf::Color c) {
        position = {x, y};
        velocity = {0, 0};
        acceleration = {0, 0};
        radius = r;
        color = c;
    }

    void applyForce(sf::Vector2f force) {
        acceleration += force;
    }

    void update() {
        velocity += acceleration;
        position += velocity;
        acceleration = {0, 0};
    }

    void checkBounds(int width, int height) {
        if (position.x - radius < 0 || position.x + radius > width) {
            velocity.x *= -0.9f;
        }
        if (position.y - radius < 0 || position.y + radius > height) {
            velocity.y *= -0.9f;
            position.y = height - radius;
        }
    }
};

int main() {
    const int width = 800, height = 600;
    sf::RenderWindow window(sf::VideoMode(width, height), "Black & White Particle Face");
    window.setFramerateLimit(60);

    sf::Image image;
    if (!image.loadFromFile("face.png")) {
        std::cerr << "Kunde inte ladda bilden!" << std::endl;
        return -1;
    }

    std::vector<Particle> particles;
    int imgWidth = image.getSize().x;
    int imgHeight = image.getSize().y;

    for (int y = 0; y < imgHeight; y += 5) {
        for (int x = 0; x < imgWidth; x += 5) {
            sf::Color pixelColor = image.getPixel(x, y);

            int brightness = (pixelColor.r + pixelColor.g + pixelColor.b) / 3;

            if (brightness > 50) { 
                float worldX = (x / (float)imgWidth) * width;
                float worldY = (y / (float)imgHeight) * height;

                float radius = brightness / 50.0f;

                sf::Color grayColor(brightness, brightness, brightness);

                particles.emplace_back(worldX, worldY, radius, grayColor);
            }
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black); 

        for (auto &p : particles) {
            p.applyForce({0, 0.05f}); 
            p.update();
            p.checkBounds(width, height);

            sf::CircleShape shape(p.radius);
            shape.setPosition(p.position);
            shape.setFillColor(p.color);
            shape.setOrigin(p.radius, p.radius);
            window.draw(shape);
        }

        window.display();
    }
    return 0;
}
