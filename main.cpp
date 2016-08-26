#include <iostream>

#define X 20
#define board(x,y,z) b[x][y][z]
#define v(a) (a >=0 && a < X)
#define c(x,y) (v(x) && v(y))
#define valid(x,y) if(c(x,y))
#define notvalid if(!c(x,y))
#define bossIndex zip-1
#define r rand()%
#define z za[i]
#define bs za[bossIndex]
#define ou std::cout<<
#define in std::cin>>
#define f(i,x) for(int i=0;i<x;++i)
#define dbl double

char b[X][X][X], px = 10, py = 10, dir;
char db[X][X + 1];
dbl bp = 1;
int health = 1009999;
int mh = 100;
int bf = 30;

struct Zombie
{
    int s;
    int x, y;
    bool a;
    int h;
};

struct bb
{
    int x, y, t = -1, cd;
} bb;

Zombie za[9999];
int p;
int zip;
int zal;

#define se(va, co) if(co){int vv=r((i/2+1)*2)+i;vv=r 2?-vv:vv+X;va=vv;}else va+=r X;

void generateZombies()
{
    zip = zal = p * 15;

    f(i, zip)
    {
        int random = r 100;

        se(z.x, i % 2)
            se(z.y, !(i % 2))

            z.a = true;

        if (i == bossIndex)
        {
            z.s = p * bf / 3;
            z.h = p * bf;
        }
        else
            z.h = z.s = p + (random < 10 ? 2 : (random < 30 ? 1 : 0));
    }
}

void upgradeStats()
{
    while (1)
    {
        ou "points left 1\n";
        in dir;
        if (dir == 'w')
        {
            bp += 1;
            return;
        }
        if (dir == 'h')
        {
            mh += 30;
            return;
        }
    }
}

void newPlague()
{
    ++p;
    generateZombies();
    upgradeStats();
    mh += 10;
    health = mh;
}

void bossBehavior()
{
    if (bs.a && bb.t == -1 && r 4 < 2)
    {
        bb.x = r X;
        bb.y = r X;
        bb.t = r 2;
        bb.cd = 1;
    }
}

void zombiesBehavior()
{
    f(i, zip)
    {
        if (!z.a)
            continue;

        if (c(z.x, z.y))
        {
            if (z.x > px)
                z.x--;
            else if (z.x < px)
                z.x++;

            if (z.y > py)
                z.y--;
            else if (z.y < py)
                z.y++;
        }
        else
        {
            if (c(z.x, 15))
            {
                if (z.y < 0)
                    z.y++;
                else
                    z.y--;
            }
            else
            {
                if (z.x < 0)
                    z.x++;
                else
                    z.x--;

            }
        }


        if (px >= z.x - 1 && px <= z.x + 1 &&
            py >= z.y - 1 && py <= z.y + 1)
        {
            health -= z.s;
        }

        if (i == bossIndex && c(bs.x, bs.y))
        {
            bossBehavior();
        }
    }
}


#define siema(vv,j,d,t,cc) vv=dir<3?j:(dir<5?d:(dir<7?t:(dir<9?cc:0)));
#define ddd int xd,yd;siema(xd,0,-1,1,0) siema(yd,1,0,0,-1)

void move()
{
    ddd
        xd += px;
    yd += py;
    valid(xd, yd)
    {
        px = xd;
        py = yd;
    }
}


void shoot()
{
    int x = px;
    int y = py;

    ddd

        int bst = bp;

    if (dir >= 9)
        return;

    while (c(x, y))
    {
        f(i, zip)
        {
            if (z.a &&
                z.x == x && z.y == y)
                if (z.h > bst)
                {
                    z.h -= bst;
                    return;
                }
                else
                {
                    bst -= z.h;
                    z.a = false;
                    z.h = 0;
                    --zal;
                }
        }

        x += xd;
        y += yd;

        if (bst == 0)
            return;
    }
}

int bossBombArea()
{
    return 4 * (1.0 - (dbl)bs.h / (dbl)(p * bf)) + 1;
}

#define bbt(a,b) if(bb.t>0){b}else if(bb.t>-1){a}

void bossBombBehavior()
{
    bbt(if (px == bb.x || py == bb.y)
        health -= bs.s; ,
        if (abs(px - bb.x) < bossBombArea() * 2 + 1 && abs(py - bb.y) < bossBombArea() * 2 + 1)
            health -= bs.s;)
}

#define bbta f(i,X){db[i][bb.x]='X';db[bb.y][i]='X';}
#define bbtb f(i,vv)f(j,vv){int x,y;x=bb.x-bossBombArea()+i;y=bb.y-bossBombArea()+j;if(c(x, y))db[y][x]='O';}

void drawBossBomb()
{
    if (bb.cd)
    {
        bbt(db[bb.y][bb.x] = 'X'; , db[bb.y][bb.x] = 'O'; )
    }
    else
    {
        int vv = bossBombArea() * 2 + 1;
        bbt(bbta, bbtb)
    }
}

void display()
{
    f(i, X)
        f(j, X)
        board(i, j, 0) = 0;

    f(i, zip)
        if (z.a)
            valid(z.x, z.y)
            if (i == bossIndex)
                board(z.y, z.x, 0) = -1;
            else
                board(z.y, z.x, 0) += z.h;

    f(y, X)
        f(x, X)
    {
        int zc = board(y, x, 0);
        char ch;
        if (board(y, x, 0) > 0)
            ch = zc < 10 ? zc + '0' :
            zc < 20 ? '+' :
            zc < 30 ? '*' : '!';
        else if (board(y, x, 0) == -1)
            ch = 'B';
        else
            ch = ' ';
        db[y][x] = ch;
    }

    if (bb.cd > 0)
    {
        drawBossBomb();
        bb.cd--;
    }
    else if (bb.t != -1)
    {
        drawBossBomb();
        bossBombBehavior();
        bb.t = -1;
    }

    db[py][px] = 'P';

    f(y, X)
        ou db[y] << "\n";

    ou "health: " << ((health > 0) ? health : 0) << "\n";
    ou "bullet power: " << bp << "\n";
    ou "za left: " << zal << "\n";
    ou "bs: " << bs.h << "\n";
}

int main()
{
    while (1)
    {
        if (!zal)
            newPlague();

        f(i, 2)
            //for (int i = 0; i < 2; ++i)
        {
            in dir;
            if (dir >= '0' && dir <= '9')
            {
                dir -= '0';
                move();
            }
            else if (dir >= 'a' && dir <= 'z')
            {
                dir -= 'a';
                shoot();
            }
            display();
        }
        zombiesBehavior();
        display();
        if (health <= 0)
        {
            ou "You're dead\n";
            break;
        }
    }

    return 0;
}
