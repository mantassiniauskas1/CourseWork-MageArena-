#include <sfml\Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <windows.h>
#define PI 3.14159265
using namespace std;
using namespace sf;
float EnemySpeed = 1.f;
float playerSpeed = 5.f;

class Spell
{
private:
    bool airActive = 0, waterActive = 0, earthActive = 0, fireActive = 0;
    int activeSum = 0;
    RectangleShape Icon[4];
    Texture IconSprite[4];
public:
    void MakeActivate(char sel)
    {
        if (sel == 'A')
        {
            airActive = 1;
        }
        if (sel == 'W')
        {
            waterActive = 1;
        }
        if (sel == 'E')
        {
            earthActive = 1;
        }
        if (sel == 'F')
        {
            fireActive = 1;
        }
    }
    void MakeDeactivate(char sel)
    {
        if (sel == 'A')
        {
            airActive = 0;
        }
        if (sel == 'W')
        {
            waterActive = 0;
        }
        if (sel == 'E')
        {
            earthActive = 0;
        }
        if (sel == 'F')
        {
            fireActive = 0;
        }
    }
    void GetActiveSpells()
    {
        cout << "Air=" << airActive << "   " << "Water=" << waterActive << "   " << "Earth=" << earthActive << "   " << "Fire=" << fireActive << endl;
    }
    bool GetAirActive()
    {
        return airActive;
    }
    bool GetWaterActive()
    {
        return waterActive;
    }
    bool GetEarthActive()
    {
        return earthActive;
    }
    bool GetFireActive()
    {
        return fireActive;
    }
    void ActiveSum()
    {
        activeSum = airActive + waterActive + earthActive + fireActive;
    }
    int GetActiveSum()
    {
        ActiveSum();
        return activeSum;
    }
    void GetIconTextures()
    {
        if (!IconSprite[0].loadFromFile("assets/AirIcon.png"))
        {
            cout << "Couldn't load AirIcon.png" << endl;
            system("pause");
        }
        if (!IconSprite[1].loadFromFile("assets/WaterIcon.png"))
        {
            cout << "Couldn't load WaterIcon.png" << endl;
            system("pause");
        }
        if (!IconSprite[2].loadFromFile("assets/EarthIcon.png"))
        {
            cout << "Couldn't load EarthIcon.png" << endl;
            system("pause");
        }
        if (!IconSprite[3].loadFromFile("assets/FireIcon.png"))
        {
            cout << "Couldn't load FireIcon.png" << endl;
            system("pause");
        }

        for (int i = 0; i <= 3; i++)
            Icon[i].setTexture(&IconSprite[i]);
    }
    RectangleShape Draw(char iconSel)
    {
        for (int i = 0; i <= 3; i++)
        {
            Icon[i].setSize(Vector2f(50.0f, 50.0f));
            Icon[i].setOutlineColor(Color(255, 255, 51));
        }
        if (airActive)
            Icon[0].setOutlineThickness(3);
        else
            Icon[0].setOutlineThickness(0);
        if (waterActive)
            Icon[1].setOutlineThickness(3);
        else
            Icon[1].setOutlineThickness(0);
        if (earthActive)
            Icon[2].setOutlineThickness(3);
        else
            Icon[2].setOutlineThickness(0);
        if (fireActive)
            Icon[3].setOutlineThickness(3);
        else
            Icon[3].setOutlineThickness(0);
        Icon[0].setPosition(25.0f, 80.f);
        Icon[1].setPosition(25.0f, 140.f);
        Icon[2].setPosition(25.0f, 200.f);
        Icon[3].setPosition(25.0f, 260.f);
        if (iconSel == 'A')
            return Icon[0];
        else if (iconSel == 'W')
            return Icon[1];
        else if (iconSel == 'E')
            return Icon[2];
        else if (iconSel == 'F')
            return Icon[3];
    }
};

class ManaBar
{
private:
    float maxMana = 200.f, currentMana = 200.f;
    RectangleShape manaBar;
public:
    void ManaDrain(float drain)
    {
        currentMana -= drain;
        if (currentMana < 0)
            currentMana = 0;
    }
    void ManaRegenerate(float regen)
    {
        if (currentMana <= maxMana)
            currentMana += regen;
    }
    RectangleShape Draw()
    {
        manaBar.setSize(Vector2f(currentMana, 20.f));
        manaBar.setPosition(Vector2f(25.f, 25.f));
        manaBar.setFillColor(Color(0, 191, 255));
        manaBar.setOutlineThickness(2);
        manaBar.setOutlineColor(Color(255, 255, 51));
        return manaBar;
    }
    float GetCurrentMana()
    {
        return currentMana;
    }
    void SetCurrentMana(float x)
    {
        currentMana = x;
    }
};

class Enemy
{
private:
    RectangleShape enemy;
    Vector2f enemydiff;
    Vector2f enemyPos;
    double enemyAngle;
    float enemySpeed = EnemySpeed;
    bool exist = 1;
    RectangleShape hp;
    float currentHP = 50.f;
public:
    void EnemySpawn(Vector2f& wizardPos, Texture& enemySprite)
    {
        enemy = (RectangleShape(Vector2f(50.0f, 90.0f)));
        enemy.setPosition((rand() % 10) * 100.f, (rand() % 10) * 100.f);
        enemy.setTexture(&enemySprite);
        enemydiff = (Vector2f((wizardPos.x - enemyPos.x), (wizardPos.y - enemyPos.y)));

        hp = RectangleShape(Vector2f(currentHP, 10.f));
        hp.setFillColor(Color(220, 20, 60));
        hp.setOutlineThickness(1.f);
        hp.setOutlineColor(Color(245, 245, 245));
    }
    RectangleShape EnemyMove(Vector2f& wizardPos)
    {
        enemyPos = enemy.getPosition();
        enemydiff = (Vector2f((wizardPos.x - enemyPos.x), (wizardPos.y - enemyPos.y)));
        enemyAngle = atan2(enemydiff.y, enemydiff.x);
        enemy.move(enemySpeed * cos(enemyAngle), enemySpeed * sin(enemyAngle));
        hp.setPosition(enemyPos.x, enemyPos.y - 20.f);
        hp.setFillColor(Color(220, 20, 60));
        hp.setOutlineThickness(1.f);
        hp.setOutlineColor(Color(245, 245, 245));

        return enemy;
    }
    void EnemyKill()
    {
        exist = 0;
    }
    bool DoesExist()
    {
        return exist;
    }
    RectangleShape Inter()
    {
        return enemy;
    }
    void DecreaseHP(float dec)
    {
        currentHP -= dec;
        if (currentHP < 0.f)
            currentHP = 0.f;
        hp = RectangleShape(Vector2f(currentHP, 10.f));
    }
    float GetCurrentHP()
    {
        return currentHP;
    }
    RectangleShape DrawHPbar()
    {
        return hp;
    }
    void SetHP(float x)
    {
        currentHP = x;
    }
    void SetSpeed(float x)
    {
        enemySpeed = EnemySpeed;
    }
};

class Score
{
private:
    int points;
public:
    Score() : points(0) {}
    Score(int x) : points(x) {}
    ~Score() {}
    void AddPoints(int add)
    {
        points += add;
    }
    int GetPoints()
    {
        return points;
    }
    void operator !()
    {
        points = 0;
    }

};

void LoadFromFile(Texture& background, Texture& wizardSpriteR, Texture& wizardSpriteL, Texture& AFSprite, Texture& AESprite, Texture& enemySprite, Font& font, Texture& spuSprite, Texture& mpuSprite)
{
    if (!background.loadFromFile("assets/background.png"))
    {
        cout << "Couldn't load background.png";
        system("pause");
    }
    if (!wizardSpriteR.loadFromFile("assets/wizardSpriteR.png"))
    {
        cout << "Couldn't load wizardSpriteR.png";
        system("pause");
    }
    if (!wizardSpriteL.loadFromFile("assets/wizardSpriteL.png"))
    {
        cout << "Couldn't load wizardSpriteL.png";
        system("pause");
    }
    if (!AFSprite.loadFromFile("assets/AFSprite.png"))
    {
        cout << "Couldn't load AFSprite.png";
        system("pause");
    }
    if (!AESprite.loadFromFile("assets/AESprite.png"))
    {
        cout << "Couldn't load AESprite.png";
        system("pause");
    }
    if (!enemySprite.loadFromFile("assets/enemySprite.png"))
    {
        cout << "Couldn't load enemySprite.png";
        system("pause");
    }
    if (!font.loadFromFile("assets/arial.ttf"))
    {
        cout << "Couldn't load arial.ttf";
        system("pause");
    }
    if (!spuSprite.loadFromFile("assets/spuSprite.png"))
    {
        cout << "Couldn't load spuSprite.png";
        system("pause");
    }
    if (!mpuSprite.loadFromFile("assets/mpuSprite.png"))
    {
        cout << "Couldn't load mpuSprite.png";
        system("pause");
    }

}

class BasePU
{
protected:
    RectangleShape pickUp;
    bool isOnScreen = 0;
public:
    void Spawn(Texture& pickup)
    {
        pickUp = (RectangleShape(Vector2f(30.0f, 30.0f)));
        pickUp.setTexture(&pickup);
        pickUp.setPosition((rand() % 10+5) * 50.f, (rand() % 10+5) * 50.f);
        isOnScreen = 1;
    }
    bool GetIsOnScreen()
    {
        return isOnScreen;
    }
    void pickedUp()
    {
        isOnScreen = 0;
        pickUp.setPosition(1000.f, 0.f);
    }
    RectangleShape ReturnPU()
    {
        return pickUp;
    }
};
class SpeedPickUp : public BasePU
{
    public:
};
class ManaPickUp : public BasePU
{
    public:
};
