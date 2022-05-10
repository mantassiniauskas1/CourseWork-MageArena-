#include "Classes_Functions.h"

int main()
{
    Spell s;
    ManaBar manaBar;
    Enemy e;
    Score score;
    SpeedPickUp spu;
    ManaPickUp mpu;
    
    srand(time(NULL));

    double AFangle;
    double AEangle;
    int enemySize = 0;
    bool playerAlive = 1;
    bool IncreaseSpeed=0;

    RenderWindow window(VideoMode(1200, 800), "Mage Arena"); // Sukuriamas langas
    window.setFramerateLimit(60); // Uždedamas fps limit'as

    Event event;
    Clock clock;
    Clock spuClock;
    Clock mpuClock;
    Text points;
    Text gameOver;
    Text finalScore;
    Text pressTo;

    Texture background;
    Texture wizardSpriteR;
    Texture wizardSpriteL;
    Texture AFSprite;
    Texture AESprite;
    Texture enemySprite;
    Texture spuSprite;
    Texture mpuSprite;
    Font font;
    LoadFromFile(background, wizardSpriteR, wizardSpriteL, AFSprite, AESprite, enemySprite, font, spuSprite, mpuSprite);
    

    points.setFont(font);
    string pointsString = "SCORE: " + to_string(score.GetPoints());
    points.setPosition(1000.f, 18.f);

    gameOver.setFont(font);
    gameOver.setString("GAME OVER");
    gameOver.setPosition(500.f, 150.f);

    finalScore.setFont(font);
    finalScore.setString("YOUR FINAL SCORE WAS: ");
    finalScore.setPosition(420.f, 200.f);

    pressTo.setFont(font);
    pressTo.setString("PRESS SPACE TO RESTART OR ESC TO QUIT");
    pressTo.setPosition(280.f, 250.f);

    RectangleShape wizard(Vector2f(50.f, 70.f));

    float currentWizardHP = 50.f;
    RectangleShape wizardHPbar(Vector2f(currentWizardHP, 12.f));
    wizardHPbar.setFillColor(Color(220, 20, 60));
    wizardHPbar.setOutlineThickness(1.f);
    wizardHPbar.setOutlineColor(Color(245, 245, 245));

   
    Sprite backgroundSprite;
    backgroundSprite.setTexture(background);
    
    wizard.setTexture(&wizardSpriteR);
    wizard.setPosition(600.0f, 400.0f);
    s.GetIconTextures();

    vector <CircleShape> AF;
    vector <Vector2f> AFdiff;

    vector <CircleShape> AE;
    vector <Vector2f> AEdiff;

    vector <Enemy> enemy;


    while (window.isOpen())
    {
        Vector2f wizardPos = wizard.getPosition();
        wizardHPbar.setPosition(wizardPos.x, wizardPos.y - 15.f);
        Time elapsed = clock.getElapsedTime();
        Time elapsedSPU = spuClock.getElapsedTime();
        Time elapsedMPU = mpuClock.getElapsedTime();
        Event event;
        while (window.pollEvent(event))
        {
            if (Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();

            switch (event.type)
            {
            case Event::KeyPressed:
                if (event.key.code == Keyboard::Num1)
                {
                    if (s.GetAirActive() == 0 && s.GetActiveSum() < 2)
                        s.MakeActivate('A');
                    else
                        s.MakeDeactivate('A');
                }

                if (event.key.code == Keyboard::Num2)
                {
                    if (s.GetWaterActive() == 0 && s.GetActiveSum() < 2)
                        s.MakeActivate('W');
                    else
                        s.MakeDeactivate('W');
                }

                if (event.key.code == Keyboard::Num3)
                {
                    if (s.GetEarthActive() == 0 && s.GetActiveSum() < 2)
                        s.MakeActivate('E');
                    else
                        s.MakeDeactivate('E');
                }

                if (event.key.code == Keyboard::Num4)
                {
                    if (s.GetFireActive() == 0 && s.GetActiveSum() < 2)
                        s.MakeActivate('F');
                    else
                        s.MakeDeactivate('F');
                }


            }


        }


        if (playerAlive)
        {
            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                if (wizardPos.x > 0)
                    wizard.move(-playerSpeed, 0);
                if (wizard.getTexture() != &wizardSpriteL)
                    wizard.setTexture(&wizardSpriteL);
            }
            if (Keyboard::isKeyPressed(Keyboard::D))
            {
                if (wizardPos.x < 1150)
                    wizard.move(playerSpeed, 0);
                if (wizard.getTexture() != &wizardSpriteR)
                    wizard.setTexture(&wizardSpriteR);
            }
            if (Keyboard::isKeyPressed(Keyboard::W) && wizardPos.y > 0)
                wizard.move(0, -playerSpeed);
            if (Keyboard::isKeyPressed(Keyboard::S) && wizardPos.y < 730)
                wizard.move(0, playerSpeed);
        }

        auto mouse_pos = Mouse::getPosition(window);
        auto mousePos = window.mapPixelToCoords(mouse_pos);

        if (enemySize <= 5)
        {
            enemy.push_back(e);
            enemySize++;
            e.EnemySpawn(wizardPos, enemySprite);
            for (int i = 0; i < enemy.size(); i++)
            {
                if (enemy[i].DoesExist() == 0)
                {
                    enemy.erase(enemy.begin() + i);
                    enemySize--;
                }
            }
        }

        if (Mouse::isButtonPressed(Mouse::Left) && playerAlive)
        {
          
            if (s.GetActiveSum() == 2)
            {
                if (s.GetAirActive() == 1 && s.GetFireActive() == 1)
                {
                    if (manaBar.GetCurrentMana() >= 2.0f && elapsed.asSeconds() >= 0.1)
                    {
                        AF.push_back(CircleShape(25.f));
                        manaBar.ManaDrain(10.0f);
                        AF[AF.size() - 1].setTexture(&AFSprite);
                        AF[AF.size() - 1].setPosition(wizard.getPosition());
                        AFdiff.push_back(Vector2f((mousePos.x - wizardPos.x), (mousePos.y - wizardPos.y)));
                        clock.restart();
                    }

                }
                else if (s.GetAirActive() == 1 && s.GetEarthActive() == 1)
                {
                    if (manaBar.GetCurrentMana() >= 50.0f && elapsed.asSeconds()>=1)
                    {
                        AE.push_back(CircleShape(25.f));
                        manaBar.ManaDrain(50.f);
                        AE[AE.size() - 1].setTexture(&AESprite);
                        AE[AE.size() - 1].setPosition(wizard.getPosition());
                        AEdiff.push_back(Vector2f((mousePos.x - wizardPos.x), (mousePos.y - wizardPos.y)));
                        clock.restart();
                    }
                }
            }

        }
        else if (!Mouse::isButtonPressed(Mouse::Left) && playerAlive)
        {
            manaBar.ManaRegenerate(1.0f);
            if(currentWizardHP<=50.f)
                currentWizardHP += 0.1f;
        }

        for (int i = 0; i < AF.size(); i++)
        {
            AFangle = atan2(AFdiff[i].y, AFdiff[i].x);
            AF[i].move(3.f * cos(AFangle), 3.f * sin(AFangle));
            if (AF[i].getPosition().x < 0 || AF[i].getPosition().x > 1200 || AF[i].getPosition().y < 0 || AF[i].getPosition().y > 800)
            {
                AF.erase(AF.begin() + i);
                AFdiff.erase(AFdiff.begin() + i);
            }
        }
        for (int i = 0; i < AE.size(); i++)
        {
            window.draw(AE[i]);
            AEangle = atan2(AEdiff[i].y, AEdiff[i].x);
            AE[i].move(7.0f * cos(AEangle), 7.0f * sin(AEangle));
            if (AE[i].getPosition().x < 0 || AE[i].getPosition().x > 1200 || AE[i].getPosition().y < 0 || AE[i].getPosition().y > 800)
            {
                AE.erase(AE.begin() + i);
                AEdiff.erase(AEdiff.begin() + i);
            }
        }


        for (int j = 0; j < enemySize-1; j++)
        {

            if (enemy[j].Inter().getGlobalBounds().intersects(wizard.getGlobalBounds()))
            {
                if(currentWizardHP>=0.f)
                    currentWizardHP -= 0.5f;
            }

            for (int i = 0; i < AF.size(); i++)
            {
                if (enemy[j].Inter().getGlobalBounds().intersects(AF[i].getGlobalBounds()))
                {
                    if (enemy[j].GetCurrentHP() <= 0.5f)
                    {
                        enemy[j].DecreaseHP(0.5f);
                        enemy.erase(enemy.begin() + j);
                        enemySize--;
                        score.AddPoints(5);
                    }
                    else
                    {
                        enemy[j].DecreaseHP(0.5f);
                    }
                }
                
            }
            for (int i = 0; i < AE.size(); i++)
            {
                if (enemy[j].Inter().getGlobalBounds().intersects(AE[i].getGlobalBounds()))
                {
                    if (enemy[j].GetCurrentHP() <= 20.f)
                    {
                        enemy[j].DecreaseHP(25.f);
                        enemy.erase(enemy.begin() + j);
                        AE.erase(AE.begin() + i);
                        AEdiff.erase(AEdiff.begin() + i);
                        enemySize--;
                        score.AddPoints(5);
                    }
                    else
                    {
                        enemy[j].DecreaseHP(30.f);
                        AE.erase(AE.begin() + i);
                        AEdiff.erase(AEdiff.begin() + i);
                    }
                }

            }

        }
        wizardHPbar.setSize(Vector2f(currentWizardHP, 10.f));

        if (spu.ReturnPU().getGlobalBounds().intersects(wizard.getGlobalBounds()) && spu.GetIsOnScreen() == 1)
        {
            spuClock.restart();
            playerSpeed = 10.f;
            spu.pickedUp();
        }
        if (mpu.ReturnPU().getGlobalBounds().intersects(wizard.getGlobalBounds()) && mpu.GetIsOnScreen() == 1)
        {
            mpuClock.restart();
            mpu.pickedUp();
        }
        
        if (elapsedSPU.asSeconds() >= 3 && spu.GetIsOnScreen()==0)
        {
            playerSpeed = 5.f;
        }

        if (elapsedMPU.asSeconds() <= 3 && mpu.GetIsOnScreen() == 0)
        {
            manaBar.ManaRegenerate(50.f);
        }
        
        if (elapsedSPU.asSeconds() >= 10 && spu.GetIsOnScreen() == 0)
        {
            spu.Spawn(spuSprite);
        }
        else if (elapsedMPU.asSeconds() >= 20 && mpu.GetIsOnScreen() == 0)
        {
            mpu.Spawn(mpuSprite);
        }



        if (score.GetPoints() % 25 == 0 && score.GetPoints() != 0)
        {
            EnemySpeed += 0.5f;
            score.AddPoints(5);
        }
        for (int i = 0; i < enemySize; i++)
            enemy[i].SetSpeed(EnemySpeed);
        
                
        window.clear();
        window.draw(backgroundSprite);
        window.draw(wizard);
        window.draw(manaBar.Draw());
        for (int i = 0; i < AF.size(); i++)
            window.draw(AF[i]);

        for (int i = 0; i < AE.size(); i++)
            window.draw(AE[i]);

        window.draw(s.Draw('A'));
        window.draw(s.Draw('W'));
        window.draw(s.Draw('E'));
        window.draw(s.Draw('F'));

        if (playerAlive)
        {
            window.draw(wizardHPbar);
            for (int i = 0; i < enemy.size(); i++)
            {
                window.draw(enemy[i].EnemyMove(wizardPos));
                window.draw(enemy[i].DrawHPbar());
            }
            if (spu.GetIsOnScreen() == 1)
                window.draw(spu.ReturnPU());
            if (mpu.GetIsOnScreen() == 1)
                window.draw(mpu.ReturnPU());

        }

        pointsString = "SCORE: " + to_string(score.GetPoints());
        points.setString(pointsString);
        window.draw(points);

        if (currentWizardHP <= 0.f)
        {
            playerAlive = 0;
            wizard.setRotation(90.f);
            currentWizardHP = 0.f;
            window.draw(gameOver);
            finalScore.setString("YOUR FINAL SCORE: " + to_string(score.GetPoints()));
            window.draw(finalScore);
            points.setPosition(2000.f, 190.f);
            window.draw(pressTo);
            if (Keyboard::isKeyPressed(Keyboard::Space))
            {

                wizard.setRotation(0.f);
                currentWizardHP = 50.f;
                manaBar.SetCurrentMana(200.f);
                points.setPosition(1000.f, 18.f);
                !score; // reset score
                EnemySpeed = 1.f;
                while (enemySize)
                {
                    enemy.pop_back();
                    enemySize--;
                }
                spuClock.restart();
                mpuClock.restart();
                playerAlive = 1;
            }
        }
        window.display();
    }
    return 0;
}