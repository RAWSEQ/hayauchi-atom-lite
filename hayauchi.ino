/****************************************************************
 * Hayauchi ATOM LITE
****************************************************************/
#include "M5Atom.h"

uint8_t scene = 0;
uint64_t step = 0;
uint16_t wait_count = 0;
uint8_t level = 0;

int level_wait[18]={50,40,30,25,22,20,18,16,14,12,10,9,8,7,6,5,4,3};

bool btnDown = false;

void setup()
{
    M5.begin(true, false, true);
    delay(50);
    M5.dis.drawpix(0, 0x6800B7);
}

void loop()
{
    btnCheck();

    switch (scene)
    {
    case 0:
        start();
        break;
    case 1:
        fadeout();
        break;
    case 2:
        rnd_wait();
        break;
    case 3:
        flag();
        break;
    case 4:
        fail();
        break;
    case 5:
        win();
        break;
    }

    delay(10);
    M5.update();
}

void start()
{
    if (step == 0)
    {
        M5.dis.drawpix(0, 0x6800B7);
        level = 0;
    }

    if (btnTapped())
    {
        scene = 1;
        step = 0;
    }
}

void fadeout()
{
    M5.dis.drawpix(0, 0xffffff);
    delay(50);
    M5.dis.drawpix(0, 0xeeeeee);
    delay(50);
    M5.dis.drawpix(0, 0xdddddd);
    delay(50);
    M5.dis.drawpix(0, 0xcccccc);
    delay(50);
    M5.dis.drawpix(0, 0xbbbbbb);
    delay(50);
    M5.dis.drawpix(0, 0xaaaaaa);
    delay(50);
    M5.dis.drawpix(0, 0x999999);
    delay(50);
    M5.dis.drawpix(0, 0x888888);
    delay(50);
    M5.dis.drawpix(0, 0x777777);
    delay(50);
    M5.dis.drawpix(0, 0x666666);
    delay(50);
    M5.dis.drawpix(0, 0x555555);
    delay(100);
    M5.dis.drawpix(0, 0x444444);
    delay(100);
    M5.dis.drawpix(0, 0x333333);
    delay(150);
    M5.dis.drawpix(0, 0x222222);
    delay(150);
    M5.dis.drawpix(0, 0x111111);
    delay(200);
    M5.dis.drawpix(0, 0x000000);
    delay(250);

    scene = 2;
    step = 0;
}

void rnd_wait()
{
    if (step == 0)
    {
        wait_count = random(360, 520);
        M5.dis.drawpix(0, 0x000000);
    }

    step++;

    if (step > wait_count)
    {
        scene = 3;
        step = 0;
    }

    if (btnTapped())
    {
        scene = 4;
        step = 0;
    }
}

void flag()
{
    M5.dis.drawpix(0, 0x98F300);

    step++;

    if (step >= level_wait[level])
    {
        scene = 4;
        step = 0;
    }

    if (btnTapped())
    {
        scene = 5;
        step = 0;
    }
}

void fail()
{
    switch (((int)(step / 5)) % 2)
    {
    case 0:
        M5.dis.drawpix(0, 0x00ff00);
        break;
    case 1:
        M5.dis.drawpix(0, 0x000000);
        break;
    }
    step++;

    if (step > 100 && btnTapped())
    {
        scene = 0;
        step = 0;
    }
}

void win()
{
    if (step == 0) {
        M5.dis.drawpix(0, 0xffffff);
        delay(500);
    }

    switch (((int)(step / 5)) % 7)
    {
    case 0:
        M5.dis.drawpix(0, 0x00f000);
        break;
    case 1:
        M5.dis.drawpix(0, 0x98F300);
        break;
    case 2:
        M5.dis.drawpix(0, 0xF1FF00);
        break;
    case 3:
        M5.dis.drawpix(0, 0x990044);
        break;
    case 4:
        M5.dis.drawpix(0, 0x6800B7);
        break;
    case 5:
        M5.dis.drawpix(0, 0x201D88);
        break;
    case 6:
        M5.dis.drawpix(0, 0x079283);
        break;
    }
    step++;

    if (btnTapped())
    {
        scene = 1;
        step = 0;
        level++;
    }
}

bool btnCheck()
{
    if (!M5.Btn.wasPressed())
        btnDown = false;
}

bool btnTapped()
{
    if (!btnDown && M5.Btn.wasPressed())
    {
        btnDown = true;
        return true;
    }
    else
    {
        return false;
    }
}
