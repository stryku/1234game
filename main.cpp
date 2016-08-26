#include <iostream>
/*

*/

#define X 20
#define board(x,y,z) b[x][y][z]
#define v(a) (a >=0 && a < X)
#define condition(x,y) (v(x) && v(y))
#define valid(x,y) if(condition(x,y))
#define notvalid if(!condition(x,y))
#define bossIndex zombiesInPlague-1

char b[X][X][X], playerX = 10, playerY = 10, direction;
char displayBoard[X][X + 1];
int bulletX, bulletY;
double bulletPower = 1;
int health = 1009999;
int maxHealth = 100;
int bossFactor = 30;

struct Zombie
{
    int strength;
    int x, y;
    bool alive;
    int health;
};

struct BossBomb
{
    int x, y, type, countDown;
} bossBomb;

Zombie zombies[999];
int plague;
int zombiesInPlague;
int zombiesAlive = 0;

void generateZombies()
{
    zombiesInPlague = zombiesAlive = plague*15;

    for (int i = 0; i < zombiesInPlague; ++i)
    {
        int r = rand() % 100;
        int x = 0, y = 0;

        //x = y = 15;

        /*if (i % 2)
            x += (15 + rand() % (i/3+1)) * (rand() % 2 ? -1 : 1);
        else
            x += rand() % X;

        if (!(i % 2))
            y += (15 + rand() % (i/3 + 1)) * (rand() % 2 ? -1 : 1);
        else
            y += rand() % X;*/

        int step = 2;

        if (i % 2)
        {
            int v = rand() % ((i / step + 1) * step) + i;
            if (rand() % 2)
            {
                v = -v;
            }
            else
            {
                v += X;
            }
            x = v;
        }
        else
            x += rand() % X;

        if (!(i % 2))
        {
            int v = rand() % ((i / step + 1) * step) + i;
            if (rand() % 2)
            {
                v = -v;
            }
            else
            {
                v += X;
            }
            y = v;
        }
        else
            y += rand() % X;


        zombies[i].alive = true;/*
        zombies[i].x = 3 * (rand() % 2 ? -1 : 1) + (i / 5) * 5;
        zombies[i].y = 3 * (rand() % 2 ? -1 : 1) + (i / 5) * 5;*/


        zombies[i].x = x;
        zombies[i].y = y; 

        if (i == bossIndex)
        {
            zombies[i].strength = plague * bossFactor/3;
            zombies[i].health = plague * bossFactor;
        }
        else if (r < 10)
        {
            zombies[i].health = plague + 2;
            zombies[i].strength = plague + 2;
        }
        else if (r < 30)
        {
            zombies[i].health = plague +1;
            zombies[i].strength = plague + 1;
        }
        else
        {
            zombies[i].health = plague;
            zombies[i].strength = plague;
        }
    }
}

void upgradeStats()
{
    int points = 1;
    while (points)
    {
        std::cout << "points left " << points << "\n";
        std::cin >> direction;
        if (direction == 'w')
        {
            bulletPower +=1;
            --points;
        }
        if (direction == 'h')
        {
            maxHealth += 30;
            --points;
        }
    }
}

void newPlague()
{
    ++plague;
    //bulletPower = plague*2;
    generateZombies();
    upgradeStats();
    maxHealth += 10;
    health = maxHealth;
}

void bossBehavior()
{
    if (zombies[bossIndex].alive && bossBomb.type == -1)
    {
        switch (rand() % 4)
        {
        case 1:
        case 2:
            bossBomb.x = rand() % X;
            bossBomb.y = rand() % X;
            bossBomb.type = rand() % 2;
            bossBomb.countDown = 1;
        case 3:
        case 4:
            break;
        }
    }
    else
    {

    }
}

void zombiesBehavior()
{
    
    for (int i = 0; i < zombiesInPlague; ++i)
    {
        if (!zombies[i].alive)
            continue;

        if (condition(zombies[i].x, zombies[i].y))
        {
            if (zombies[i].x > playerX)
                zombies[i].x--;
            else if (zombies[i].x < playerX)
                zombies[i].x++;

            if (zombies[i].y > playerY)
                zombies[i].y--;
            else if (zombies[i].y < playerY)
                zombies[i].y++;
        }
        else
        {
            if (condition(zombies[i].x, 15))
            {
                if (zombies[i].y < 0)
                    zombies[i].y++;
                else
                    zombies[i].y--;
            }
            else
            {
                if (zombies[i].x < 0)
                    zombies[i].x++;
                else
                    zombies[i].x--;

            }
        }
        

        if (playerX >= zombies[i].x - 1 && playerX <= zombies[i].x + 1 &&
            playerY >= zombies[i].y - 1 && playerY <= zombies[i].y + 1)
        {
            health -= zombies[i].strength;
        }

        if (i == bossIndex && condition(zombies[bossIndex].x, zombies[bossIndex].y))
        {
            bossBehavior();
        }
    }
}

void move()
{
    if (direction < 3) // dol
    {
        if (playerY + 1 < X)
            ++playerY;
    }
    else if (direction < 5) // lewo
    {
        if (playerX > 0)
            --playerX;
    }
    else if (direction < 7) // prawo
    {
        if (playerX + 1 < X)
            ++playerX;
    }
    else if (direction < 9) // gora
    {
        if (playerY > 0)
            --playerY;
    }
}

void shoot()
{
    int x = playerX;
    int y = playerY;
    int xd=0, yd=0;

    int bulletStr = bulletPower;

    if (direction < 3) // dol
    {
        xd = 0;
        yd = 1;
    }
    else if (direction < 5) // lewo
    {
        xd = -1;
        yd = 0;
    }
    else if (direction < 7) // prawo
    {
        xd = 1;
        yd = 0;
    }
    else if (direction < 9) // gora
    {
        xd = 0;
        yd = -1;
    }
    else
        return;

    while (condition(x,y))
    {

        for (int i = 0; i < zombiesInPlague; ++i)
        {
            if (zombies[i].alive &&
                zombies[i].x == x && zombies[i].y == y)
            {
                if (zombies[i].health > bulletStr)
                {
                    zombies[i].health -= bulletStr;
                    return;
                }
                else
                {
                    bulletStr -= zombies[i].health;
                    zombies[i].alive = false;
                    zombies[i].health = 0;
                    --zombiesAlive;
                }
            }
        }

        x += xd;
        y += yd;

        if (bulletStr == 0)
            return;
    }
}

int bossBombArea()
{
    double percent = 1.0 - (double)zombies[bossIndex].health / (double)(plague * bossFactor);
    return 4 * percent + 1;
}

void bossBombBehavior()
{
    int rx, ry, a = 4;
    
    switch (bossBomb.type)
    {
    case 0: // +
        if (playerX == bossBomb.x || playerY == bossBomb.y)
            health -= zombies[bossIndex].strength;
        break;

    case 1: //area
        rx = abs(playerX - bossBomb.x);
        ry = abs(playerY - bossBomb.y);
        if(rx < bossBombArea()*2+1 && ry < bossBombArea()*2+1)
            health -= zombies[bossIndex].strength;
        break;
    }
}

void drawBossBomb()
{
    if (bossBomb.countDown)
    {
        switch (bossBomb.type)
        {
        case 0:
            displayBoard[bossBomb.y][bossBomb.x] = 'X';
            break;
        case 1:
            displayBoard[bossBomb.y][bossBomb.x] = 'O';
            break;
        }
    }
    else
    {
        int v = bossBombArea() * 2 + 1;
        switch (bossBomb.type)
        {
        case 0:
            for (int i = 0; i < X; ++i)
            {
                displayBoard[i][bossBomb.x] = 'X';
                displayBoard[bossBomb.y][i] = 'X';
            }
            break;

        case 1:


            for (int i = 0; i < bossBombArea()*2+1; ++i)
            {
                for (int j = 0; j < bossBombArea()*2+1; ++j)
                {
                    int x = 0, y = 0;
                    x = bossBomb.x - bossBombArea() + i;
                    y = bossBomb.y - bossBombArea() + j;
                    if (condition(x, y))
                        displayBoard[y][x] = 'O';
                }
            }
            break;
        }

    }
}

void display()
{
    for (int i = 0; i < X; ++i)
        for (int j = 0; j < X; ++j)
            board(i, j, 0) = 0;

    for (int i = 0; i < zombiesInPlague; ++i)
    {
        if(zombies[i].alive)
            valid(zombies[i].x, zombies[i].y)
            {
            if (i == bossIndex)
                board(zombies[i].y, zombies[i].x, 0) = -1;
            else
                board(zombies[i].y, zombies[i].x, 0) += zombies[i].health;
            }
    }

    for (int y =0; y < X; ++y)
        for (int x = 0; x < X; ++x)
        {
            int zombiesCount = board(y, x, 0);
            if (board(y, x, 0) > 0)
                displayBoard[y][x] = zombiesCount < 10 ? zombiesCount + '0' : 
                                     zombiesCount < 20 ? '+' :
                                     zombiesCount < 30 ? '*' : '!';
            else if(board(y, x, 0)==-1)
                displayBoard[y][x] = 'B';
            else
                displayBoard[y][x] = ' ';
        }

    if (bossBomb.countDown > 0)
    {
        drawBossBomb();
        bossBomb.countDown--;
    }
    else if (bossBomb.type != -1)
    {
        drawBossBomb();
        bossBombBehavior();
        bossBomb.type = -1;
    }

    displayBoard[playerY][playerX] = 'P';

    for (int y = 0; y < X; ++y)
        std::cout << displayBoard[y] << "\n";
    
    std::cout << "health: " << ((health > 0) ? health : 0) << "\n";
    std::cout << "bullet power: " << bulletPower << "\n";
    std::cout << "zombies left: " << zombiesAlive << "\n";
    std::cout << "boss: " << zombies[bossIndex].health << "\n";
}

int main()
{
    while (1)
    {
        if (!zombiesAlive)
            newPlague();

        for (int i = 0; i < 2; ++i)
        {
            std::cin >> direction;
            if (direction >= '0' && direction <= '9')
            {
                direction -= '0';
                move();
            }
            else if (direction >= 'a' && direction <= 'z')
            {
                direction -= 'a';
                shoot();
            }
            display();
        }
        zombiesBehavior();
        display();
        if (health <= 0)
        {
            std::cout << "You're dead\n";
            break;
        }
    }

    return 0;
}
