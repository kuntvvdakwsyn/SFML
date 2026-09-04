#include "header.hpp"

int main() {
  srand(time(0));
  float win_or_lose = 0; // variabile to verificate if player win or lose
  float x = 800.f;       // position hp bar
  RenderWindow w(VideoMode(800, 850), "SFML");
  w.setFramerateLimit(60);
  CircleShape c(75.f); // player
  c.setFillColor(Color::Green);
  Player player;
  c.setPosition(player.x, player.y);

  RectangleShape ukazatel(
      Vector2f(18.75, 18.75)); // it will show where player see
  ukazatel.setFillColor(Color::Red);
  ukazateli u;

  RectangleShape bullet; // bullet
  bullet.setFillColor(Color::Yellow);
  Bullet b;

  CircleShape enemy(75.f); // enemy
  enemy.setFillColor(Color::Red);
  enemy.setPosition(500.f, 350.f);
  Enemy enem;

  // hp bar :
  RectangleShape hud(Vector2f(800.f, 50.f));
  hud.setFillColor(Color::Red);
  hud.setPosition(0.f, 800.f);
  RectangleShape hp(Vector2f(800.f, 50.f));
  hp.setFillColor(Color::Green);
  hp.setPosition(x, 800.f);

  while (w.isOpen()) {
    Event event;
    while (w.pollEvent(event)) {
      if (event.type == Event::Closed) {
        w.close();
      }
      player.control(event);
      if (event.type == Event::KeyPressed) {
        if (event.key.code == Keyboard::Space) { // space to spawn bullet
          if (b.is_Active == true) {
            b.create(player);
            b.speed(player);
            b.is_Active = false;
          }
        }
      }
    }
    w.clear(Color::White);

    // it will plase the bullet vertical or orizontal
    if (b.vert == true) {
      bullet.setSize(Vector2f(20.f, 45.f));
    } else {
      bullet.setSize(Vector2f(45.f, 20.f));
    }
    u.new_pos(player);

    player.physic(); // player won't exit to the place
    c.setPosition(player.x, player.y);
    ukazatel.setPosition(u.x, u.y);

    draw_all(w, c, ukazatel);
    bullet.setPosition(b.pos_x, b.pos_y);
    if (b.is_Active == false) {
      w.draw(bullet);
      b.pos_x = b.pos_x + b.x;
      b.pos_y = b.pos_y + b.y;
      b.kill();
    }
    w.draw(enemy);
    if (bullet.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
      enem.spawn(player);
      enemy.setPosition(enem.x, enem.y);
      b.is_Active = true;
      b.pos_x = -100.f;
      b.pos_y = -100.f;
      x -= 160;
      hp.setPosition(x, 800.f);
    }
    if (c.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
      x += 160.f;
      enem.spawn(player);
      enemy.setPosition(enem.x, enem.y);
    }
    if (x <= 0.f) {
      draw_all(w, hud, hp);
      win_or_lose = 2; // player will win
      break;
    }
    if (x > 800.f) {
      draw_all(w, hud, hp);
      win_or_lose = 1; // player will lose
      break;
    }
    hp.setPosition(x, 800.f);
    draw_all(w, hud, hp);
    w.display();
  }
  if (win_or_lose == 1) {
    Texture Lose;
    Lose.loadFromFile("../win.png");
    Sprite lose;
    lose.setTexture(Lose);
    lose.setPosition(197.f, 220.f);
    while (w.isOpen()) {
      Event event;
      while (w.pollEvent(event)) {
        if (event.type == Event::Closed) {
          w.close();
        }
      }
      w.clear(Color::White);
      draw_all(w, c, ukazatel, hud, lose);
      w.display();
    }
  } else if (win_or_lose == 2) {
    Texture Win;
    Win.loadFromFile("../wiin.png");
    Sprite win;
    win.setTexture(Win);
    win.setScale(400.f / 818.f, 400.f / 818.f);
    win.setPosition(200.f, 312.f);
    while (w.isOpen()) {
      Event event;
      while (w.pollEvent(event)) {
        if (event.type == Event::Closed) {
          w.close();
        }
      }
      hp.setPosition(0, 800.f);
      w.clear(Color::White);
      draw_all(w, c, ukazatel, hp, win);
      w.display();
    }
  }
}
