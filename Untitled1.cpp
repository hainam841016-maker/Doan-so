#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

struct Particle {
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float life;
};

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    const unsigned WIDTH = 1000;
    const unsigned HEIGHT = 650;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "BAN RUOI - Neon Arcade");
    window.setFramerateLimit(60);

    sf::Font font;
    // SFML does not bundle a font. Put a font file named arial.ttf beside the game.
    const bool hasFont = font.loadFromFile("arial.ttf");

    sf::Text title, hud, message, hint, restartText;
    if (hasFont) {
        title.setFont(font); hud.setFont(font); message.setFont(font);
        hint.setFont(font); restartText.setFont(font);
        title.setCharacterSize(30);
        hud.setCharacterSize(21);
        message.setCharacterSize(32);
        hint.setCharacterSize(17);
        restartText.setCharacterSize(22);
        title.setFillColor(sf::Color(100, 235, 255));
        hud.setFillColor(sf::Color(235, 242, 255));
        message.setFillColor(sf::Color::White);
        hint.setFillColor(sf::Color(170, 185, 220));
        restartText.setFillColor(sf::Color(8, 15, 35));
        title.setPosition(28.f, 18.f);
        hud.setPosition(30.f, 68.f);
        message.setPosition(275.f, 270.f);
        hint.setPosition(30.f, 610.f);
        restartText.setString("CHOI LAI");
        restartText.setPosition(440.f, 414.f);
    }

    sf::RectangleShape background(sf::Vector2f((float)WIDTH, (float)HEIGHT));
    background.setFillColor(sf::Color(7, 10, 27));

    std::vector<sf::CircleShape> stars;
    for (int i = 0; i < 100; ++i) {
        sf::CircleShape star((float)(std::rand() % 2 + 1));
        star.setPosition((float)(std::rand() % WIDTH), (float)(std::rand() % HEIGHT));
        star.setFillColor(sf::Color(65, 100, 155, (sf::Uint8)(80 + std::rand() % 150)));
        stars.push_back(star);
    }

    sf::Vector2f flyPos(450.f, 300.f);
    sf::Vector2f flyVel(175.f, 115.f);
    float flyRadius = 23.f;
    int score = 0;
    int lives = 3;
    float timeLeft = 60.f;
    bool gameOver = false;
    sf::Clock clock;
    sf::Clock elapsedClock;
    std::vector<Particle> particles;

    sf::CircleShape flyBody(flyRadius);
    flyBody.setOrigin(flyRadius, flyRadius);
    flyBody.setFillColor(sf::Color(80, 235, 180));
    flyBody.setOutlineThickness(3.f);
    flyBody.setOutlineColor(sf::Color(105, 255, 230));

    sf::CircleShape wing1(13.f), wing2(13.f);
    wing1.setScale(0.75f, 1.35f);
    wing2.setScale(0.75f, 1.35f);
    wing1.setFillColor(sf::Color(175, 220, 255, 210));
    wing2.setFillColor(sf::Color(175, 220, 255, 210));
    wing1.setOrigin(13.f, 13.f);
    wing2.setOrigin(13.f, 13.f);

    sf::CircleShape eye(5.f);
    eye.setFillColor(sf::Color(12, 20, 38));
    sf::CircleShape pupil(2.f);
    pupil.setFillColor(sf::Color::White);

    sf::CircleShape restartButton(78.f);
    restartButton.setScale(1.0f, 0.42f);
    restartButton.setPosition(422.f, 395.f);
    restartButton.setFillColor(sf::Color(100, 235, 255));
    restartButton.setOutlineThickness(2.f);
    restartButton.setOutlineColor(sf::Color(190, 250, 255));
                } else {
                    showShot = true;
                    shotClock.restart();
                    float dx = click.x - flyPos.x;
                    float dy = click.y - flyPos.y;
                    float hitRadius = flyRadius + 7.f;
                    if (dx * dx + dy * dy <= hitRadius * hitRadius) {
                        score += 10;
                        for (int i = 0; i < 18; ++i) {
                            float angle = (float)i * 6.2831853f / 18.f;
                            Particle part;
                            part.shape = sf::CircleShape((float)(2 + std::rand() % 4));
                            part.shape.setOrigin(part.shape.getRadius(), part.shape.getRadius());
                            part.shape.setFillColor(i % 2 ? sf::Color(98, 235, 255) : sf::Color(255, 225, 100));
                            part.shape.setPosition(flyPos);
                            float speed = 70.f + std::rand() % 190;
                            part.velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
                            part.life = 0.55f + (std::rand() % 30) / 100.f;
                            particles.push_back(part);
                        }
                        flyPos = sf::Vector2f(80.f + std::rand() % (WIDTH - 160),
                                              145.f + std::rand() % (HEIGHT - 230));
                        float speedX = 150.f + std::min(score * 1.2f, 180.f);
                        float speedY = 100.f + std::min(score * 0.8f, 150.f);
                        flyVel = sf::Vector2f((std::rand() % 2 ? 1.f : -1.f) * speedX,
                                              (std::rand() % 2 ? 1.f : -1.f) * speedY);
                    } else {
                        lives--;
                        if (lives <= 0) gameOver = true;
                    }
                }
            }
        }

        if (!gameOver) {
            timeLeft -= dt;
            if (timeLeft <= 0.f) { timeLeft = 0.f; gameOver = true; }

            flyPos += flyVel * dt;
            if (flyPos.x < 55.f || flyPos.x > WIDTH - 55.f) flyVel.x *= -1.f;
            if (flyPos.y < 125.f || flyPos.y > HEIGHT - 80.f) flyVel.y *= -1.f;
            flyPos.x = std::max(55.f, std::min((float)WIDTH - 55.f, flyPos.x));
            flyPos.y = std::max(125.f, std::min((float)HEIGHT - 80.f, flyPos.y));
        }

        for (auto it = particles.begin(); it != particles.end();) {
            it->life -= dt;
            it->shape.move(it->velocity * dt);
            it->velocity *= 0.97f;
            if (it->life <= 0.f) it = particles.erase(it);
            else ++it;
        }

        window.clear();
        window.draw(background);
        for (const auto& star : stars) window.draw(star);

        // Subtle neon frame
        sf::RectangleShape frame(sf::Vector2f(940.f, 520.f));
        frame.setPosition(30.f, 95.f);
        frame.setFillColor(sf::Color::Transparent);
        frame.setOutlineThickness(1.f);
        frame.setOutlineColor(sf::Color(35, 90, 145));
        window.draw(frame);

        if (hasFont) {
            title.setString("BAN RUOI  //  NEON ARCADE");
            window.draw(title);
            hud.setString("DIEM: " + std::to_string(score) +
                          "       MANG: " + std::to_string(lives) +
                          "       THOI GIAN: " + std::to_string((int)std::ceil(timeLeft)) + "s");
            window.draw(hud);
            hint.setString("Di chuot de ngam  |  Nhan chuot trai de ban  |  Ban trung +10 diem, ban truot -1 mang");
            window.draw(hint);
        }

        if (!gameOver) {
            // Wings, body, eyes: simple fly drawn with SFML shapes.
            wing1.setPosition(flyPos.x - 12.f, flyPos.y - 13.f);
            wing2.setPosition(flyPos.x + 12.f, flyPos.y - 13.f);
            window.draw(wing1);
            window.draw(wing2);
            flyBody.setPosition(flyPos);
            window.draw(flyBody);
            eye.setPosition(flyPos.x + 6.f, flyPos.y - 5.f);
            window.draw(eye);
            pupil.setPosition(flyPos.x + 7.f, flyPos.y - 6.f);
            window.draw(pupil);
        }

        for (const auto& particle : particles) window.draw(particle.shape);

        // Crosshair cursor
        sf::CircleShape ring(12.f);
        ring.setOrigin(12.f, 12.f);
        ring.setPosition(aim);
        ring.setFillColor(sf::Color::Transparent);
        ring.setOutlineThickness(2.f);
        ring.setOutlineColor(sf::Color(100, 235, 255));
        window.draw(ring);
        sf::Vertex cross1[] = {
            sf::Vertex(sf::Vector2f(aim.x - 19.f, aim.y), sf::Color(100, 235, 255)),
            sf::Vertex(sf::Vector2f(aim.x - 7.f, aim.y), sf::Color(100, 235, 255))
        };
        sf::Vertex cross2[] = {
            sf::Vertex(sf::Vector2f(aim.x + 7.f, aim.y), sf::Color(100, 235, 255)),
            sf::Vertex(sf::Vector2f(aim.x + 19.f, aim.y), sf::Color(100, 235, 255))
        };
        sf::Vertex cross3[] = {
            sf::Vertex(sf::Vector2f(aim.x, aim.y - 19.f), sf::Color(100, 235, 255)),
            sf::Vertex(sf::Vector2f(aim.x, aim.y - 7.f), sf::Color(100, 235, 255))
        };
        sf::Vertex cross4[] = {
            sf::Vertex(sf::Vector2f(aim.x, aim.y + 7.f), sf::Color(100, 235, 255)),
            sf::Vertex(sf::Vector2f(aim.x, aim.y + 19.f), sf::Color(100, 235, 255))
        };
        window.draw(cross1, 2, sf::Lines); window.draw(cross2, 2, sf::Lines);
        window.draw(cross3, 2, sf::Lines); window.draw(cross4, 2, sf::Lines);

        if (showShot && shotClock.getElapsedTime().asSeconds() < 0.08f) {
            sf::CircleShape flash(25.f);
            flash.setOrigin(25.f, 25.f);
            flash.setPosition(aim);
            flash.setFillColor(sf::Color::Transparent);
            flash.setOutlineThickness(3.f);
            flash.setOutlineColor(sf::Color(255, 245, 160));
            window.draw(flash);
        }

        if (gameOver) {
            sf::RectangleShape shade(sf::Vector2f((float)WIDTH, (float)HEIGHT));
            shade.setFillColor(sf::Color(3, 5, 18, 210));
            window.draw(shade);
            if (hasFont) {
                message.setString("GAME OVER");
                sf::FloatRect bounds = message.getLocalBounds();
                message.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
                message.setPosition(WIDTH / 2.f, 315.f);
                message.setFillColor(sf::Color(100, 235, 255));
                window.draw(message);

                sf::Text result;
                result.setFont(font);
                result.setCharacterSize(24);
                result.setFillColor(sf::Color::White);
                result.setString("DIEM CUA BAN: " + std::to_string(score));
                bounds = result.getLocalBounds();
                result.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
                result.setPosition(WIDTH / 2.f, 365.f);
                window.draw(result);
                window.draw(restartButton);
                window.draw(restartText);
                sf::Text small;
                small.setFont(font);
                small.setCharacterSize(16);
                small.setFillColor(sf::Color(180, 195, 220));
                small.setString("Nhan nut CHOI LAI de thu lai");
                bounds = small.getLocalBounds();
                small.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
                small.setPosition(WIDTH / 2.f, 475.f);
                window.draw(small);
            }
        }

        window.display();
    }
    return 0;
}

   
