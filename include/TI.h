#ifndef TI_H
#define TI_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include "../include/sftools/Chronometer.hpp"

#define VELOCIDADE 500

using namespace std;

class TI
{
public:
    TI(char temp_nome_arq[]);
    ~TI();
    char* getNewLine();
    void addNew();
    void remove();
    void remove(int pos);

    void setTime(sf::Time &tempo);

    float getTimeFront();
    float getTimeFront(int pos);
    float getDurTime();
    float getDurTime(int pos);
    float getNote();
    float getNote(int pos);

    int getSize();
    float getFPS();
    float getVel_PixelsPerFrame();
    float getTimeTable();
    float getTimeSensor();

    void show();

private:
    char nome_arq[100];
    FILE *arq;
    char linha[50];
    vector<vector<float>> vec;
    vector<float> row;

    float v;
    int velocidade = VELOCIDADE;

    //Tempo
    sf::Time tempoSeq;
    sf::Clock vClock;
};

class RASTRO
{
public:

    RASTRO();

    void setDim( sf::RenderWindow &window, int LARGURA_MESA_IN, int MESA_INICIO_IN, int MESA_FINAL_IN, int SENSOR_IN, int SENSOR_OUT);
    void reset(int vnota, float duracao);
    void reset(sf::Vector2f Tam, sf::Vector2f Pos, sf::Color Cor, sf::Vector2f Pos2, sf::Color Cor2);
    sf::FloatRect getDimNota1();
    sf::FloatRect getDimNota2();
    sf::Vector2f getTam();
    sf::Vector2f getPos();
    sf::Vector2f getPos2();
    sf::Color getCor();
    sf::Color getCor2();

    bool onSensor();
    bool outSensor();
    void move(bool pause);
    void draw(sf::RenderWindow &window);

private:

    sf::RectangleShape nota, nota2;
    sf::Sprite notaSprite;
    sf::Sprite notaSprite2;
    sf::Texture notaTex;
    sf::Texture notaTex2;

    int LARGURA_MESA;
    int MESA_INICIO;
    int MESA_FINAL;
    int CENTRO_TELA_X;
    int SENSOR_IN;
    int SENSOR_OUT;

    float posVerde;
    float posVermelho;
    float posAmarelo;
    float posAzul;

    float v;
    int velocidade = VELOCIDADE;

    //Tempo
    sf::Time tempoSeq;
    sf::Clock vClock;
};

class TIMER
{
public:

    TIMER();
    void setPos(sf::Vector2f pos);
    void setSize(int size);
    void setColor(sf::Color cor);
    void setTime(sf::Time &time);
    void setFont(sf::Font &fonte);
    void draw(sf::RenderWindow &window);

private:

    sf::Text TimerText;
    stringstream Timer;
    sf::Time tempo;
};

class ANIM {
public:

    ANIM(string local, int n);
    void setPos(sf::Vector2f Position);
    void setScale(sf::Vector2f Scale);
    void draw(sf::RenderWindow &window, sf::Time &tempo, float v = 1);
    void playOnce(sf::RenderWindow &window, sf::Time &tempo, float t, float v = 1);
    void playOnceResetPress();
    void playOnceResetRealease();
    void playOnceSetSound(string local);

private:

    string local;
    int n_img;
    int cont = 0;
    sf::Time tempo_inicial;
    sf::Time tempo_playOnce;
    bool flag_tempo = false;
    bool flag_playOnce1 = false;
    bool flag_playOnce2 = false;
    bool flag_playOnce3 = true;
    sf::Sprite Sprite;
    sf::Texture Tex;
    sf::SoundBuffer somBuffer;
    sf::Sound som;

};

#endif // TI_H
