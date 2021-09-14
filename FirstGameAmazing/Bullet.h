#pragma once
class Bullet
{
private:

    float SetRad{ 0.f };
    sf::Color EnColor;
    int Org1{ 0 };
    int Org2{ 0 };
    int PosX{ 0 };
    int PosY{ 0 };

public:
    sf::CircleShape Circle{ 0.f };
    bool IsSpawned = false;

    Bullet(sf::CircleShape aCircle, float aSetRad, sf::Color aEnColor, int aOrg1, int aOrg2, int aPosX, int aPosY)
    {
        Circle = aCircle;

        Circle.setOrigin(aOrg1, aOrg2);
        Circle.setRadius(aSetRad);
        Circle.setPosition(aPosX, aPosY);
        Circle.setFillColor(aEnColor);
        SetRad = aSetRad;
        EnColor = aEnColor;
        Org1 = aOrg1;
        Org2 = aOrg2;
        PosX = aPosX;
        PosY = aPosY;


    }

};