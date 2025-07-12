#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class Entity {
protected:
    std::string name;
    int health;
    int energy;
    int intellect;
    int willpower;

public:
    Entity(std::string n, int h, int e, int i, int w)
        : name(n), health(h), energy(e), intellect(i), willpower(w) {}

    virtual void specialAbility(Entity& target) = 0;

    virtual void displayStatus() {
        std::cout << name << " | Health: " << health
                  << " | Energy: " << energy << "\n";
    }

    bool isDefeated() const { return health <= 0; }

    void takeDamage(int amount) {
        health -= amount;
        if (health < 0) health = 0;
    }

    std::string getName() const { return name; }
};

class Dream : public Entity {
public:
    Dream() : Entity("Dream of the Endless", 150, 100, 90, 80) {}

    void specialAbility(Entity& target) override {
        if (energy >= 25) {
            std::cout << name << " casts 'Endless Nightmare'.\n";
            int damage = intellect + rand() % 20;
            target.takeDamage(damage);
            energy -= 25;
        } else {
            std::cout << name << " is low on energy.\n";
        }
    }
};

class Lucifer : public Entity {
public:
    Lucifer() : Entity("Lucifer Morningstar", 180, 120, 95, 95) {}

    void specialAbility(Entity& target) override {
        if (energy >= 30) {
            std::cout << name << " uses 'Will of the Morningstar'.\n";
            int damage = willpower + rand() % 25;
            target.takeDamage(damage);
            energy -= 30;
        } else {
            std::cout << name << " is low on energy.\n";
        }
    }
};

void simulateBattle() {
    Dream dream;
    Lucifer lucifer;
    int turn = 0;

    std::cout << "⚔️ Dream vs. Lucifer - Cosmic Showdown Begins! ⚔️\n";

    while (!dream.isDefeated() && !lucifer.isDefeated()) {
        std::cout << "\n--- Turn " << ++turn << " ---\n";
        dream.displayStatus();
        lucifer.displayStatus();

        if (turn % 2 == 1) {
            dream.specialAbility(lucifer);
        } else {
            lucifer.specialAbility(dream);
        }

        if (dream.isDefeated()) {
            std::cout << "\n💀 Dream has been defeated. Lucifer wins!\n";
        } else if (lucifer.isDefeated()) {
            std::cout << "\n💤 Lucifer has fallen to the dream. Dream wins!\n";
        }
    }
}

int main() {
    srand(time(0));
    simulateBattle();
    return 0;
}
