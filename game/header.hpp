#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
using namespace sf;

class Player {
public:
  float x = 100.f;
  float y = 550.f;
  char where_t = 'D';
  void control(Event &event) {
    if (event.type == Event::KeyPressed) {
      if (event.key.code == Keyboard::W) {
        y -= 20;
        where_t = 'W';
      } else if (event.key.code == Keyboard::S) {
        y += 20;
        where_t = 'S';
      }
      if (event.key.code == Keyboard::A) {
        x -= 20;
        where_t = 'A';
      } else if (event.key.code == Keyboard::D) {
        x += 20;
        where_t = 'D';
      }
    }
  }
  void physic() {
    if (x >= 650) {
      x = 650;
    }
    if (y >= 650) {
      y = 650;
    }
    if (x <= 0) {
      x = 0;
    }
    if (y <= 0) {
      y = 0;
    }
  }
};

class ukazateli {
public:
  float x = 165.625f;
  float y = 615.625f;
  void new_pos(Player &player) {
    if (player.where_t == 'W') {
      x = player.x + 65.625f;
      y = player.y + 28.125f;
    } else if (player.where_t == 'A') {
      x = player.x + 28.125f;
      y = player.y + 65.625f;
    } else if (player.where_t == 'S') {
      x = player.x + 65.625f;
      y = player.y + 103.125;
    } else if (player.where_t == 'D') {
      x = player.x + 103.125;
      y = player.y + 65.625f;
    }
  }
};
class Bullet {
public:
  float x;
  float y;
  bool vert = false;
  float pos_x;
  float pos_y;
  bool is_Active = true;
  void speed(Player &player) {
    if (player.where_t == 'W') {
      x = 0;
      y = -20;
    } else if (player.where_t == 'A') {
      x = -20;
      y = 0;
      vert = false;
    } else if (player.where_t == 'S') {
      x = 0;
      y = 20;
    } else if (player.where_t == 'D') {
      x = 20;
      y = 0;
    }
  }
  void kill() {
    if (pos_x >= 900.f || pos_x <= -100.f) {
      is_Active = true;
    }
    if (pos_y >= 900.f || pos_y <= -100.f) {
      is_Active = true;
    }
  }

  void create(Player &player) {
    if (player.where_t == 'W') {
      pos_x = player.x + 65;
      pos_y = player.y - 45;
      vert = true;
    } else if (player.where_t == 'A') {
      pos_x = player.x - 45;
      pos_y = player.y + 65;
      vert = false;
    } else if (player.where_t == 'S') {
      pos_x = player.x + 65;
      pos_y = player.y + 150;
      vert = true;
    } else if (player.where_t == 'D') {
      pos_x = player.x + 150;
      pos_y = player.y + 65;
      vert = false;
    }
  }
};
class Enemy {
private:
  float x1;
  float x2;
  float y1;
  float y2;
  float ptr;

public:
  float x;
  float y;
  void spawn(Player &player) {
    if (player.x < 165.f) {
      x = 165.f + player.x + (rand() % (int)(650 - (165.f + player.x) + 1));
      x1 = -1;
    } else if (player.x > 485.f) {
      x = rand() % (int)(player.x + 1);
      x1 = -1;
    } else {
      x1 = rand() % (int)(player.x + 1);
      x2 = player.x + 165 + (rand() % (int)(650 - (player.x + 165) + 1));
    }
    if (player.y > 485) {
      y = rand() % (int)(player.y + 1);
      y1 = -1;
    } else if (player.y < 315) {
      y = player.y + 165 + rand() % (int)(650 - (player.y + 165) + 1);
      y1 = -1;
    } else {
      y1 = rand() % (int)(player.y - 165);
      y2 = player.y + 165 + (rand() % (int)(650 - (player.y + 165) + 1));
    }

    if (x1 != -1) {
      ptr = 1 + (rand() % (2 - 1 + 1));
      if (ptr == 1) {
        x = x1;
      } else if (ptr == 2) {
        x = x2;
      }
    }
    if (y1 != -1) {
      ptr = 1 + (rand() % (2 - 1 + 1));
      if (ptr == 1) {
        y = y1;
      } else if (ptr == 2) {
        y = y2;
      }
    }
  }
};
template <typename... T> void draw_all(RenderWindow &w, T &&...text) {
  (w.draw(text), ...);
}
