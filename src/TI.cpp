#include "../include/TI.h"
#define RASTRO_VERDE 1
#define RASTRO_VERMELHO 2
#define RASTRO_AMARELO 4
#define RASTRO_AZUL 8

using namespace std;

TI::TI(char *temp_nome_arq){
    strcpy(nome_arq, temp_nome_arq);
    arq = fopen(nome_arq, "r");
}

TI::~TI() {
    fclose(arq);
}

char* TI::getNewLine(){
    while(1) {
        fgets(linha, 100, arq);
        if(*linha != '\n' && *linha != '#') break;
    }
    return linha;
}
void TI::addNew(){
    row.erase (row.begin(),row.end());
    row.push_back(getTimeFront());
    row.push_back(getDurTime() );
    row.push_back(getNote()    );
    vec.push_back(row);
}
void TI::remove(){
    vec.erase(vec.begin());
}
void TI::remove(int pos){
    vec.erase(vec.begin()+pos);
}

void TI::setTime(sf::Time &tempo) {tempoSeq = tempo;}

float TI::getTimeFront(){
    int i;
    float InitTime;
    char InitTimeChar[20];
    for(i=0; i<strlen(linha); i++){
        if(linha[i] == ' '){
            for(int j=0; j<i; j++){
                InitTimeChar[j] = linha[j];
            }   InitTimeChar[i] = '\0'; break;
        }
    }   InitTime = atof(InitTimeChar);
        return InitTime;
}
float TI::getTimeFront(int pos){
    return vec[pos][0];
}
float TI::getDurTime(){
    int cont = 0, cont2 = 0;
    float DurTime;
    char DurTimeChar[20];
    for(int i=0; i<strlen(linha); i++)
    {
        if(linha[i] == ' ') cont++;
        if(cont == 1)
        {
            for(int j = i + 1; linha[j] != ' '; j++)
            {
                DurTimeChar[cont2] = linha[j];
                cont2++;
            }   break;
        }
    }      DurTime = atof(DurTimeChar);
    return DurTime;
}
float TI::getDurTime(int pos) {
    return vec[pos][1];
}
float TI::getNote(){
    int cont = 0, cont2 = 0;
    char NoteChar[20];
    float Note;
    for(int i=0; i<strlen(linha); i++)
    {
        if(linha[i] == ' ') cont++;
        if(cont == 2)
        {
            for(int j = i + 1; linha[j] != '\0'; j++)
            {
                NoteChar[cont2] = linha[j];
                cont2++;
            }   break;
        }
    }      Note = atof(NoteChar);
    return Note;
}
float TI::getNote(int pos) {
    return vec[pos][2];
}

int TI::getSize() {
    int size = vec.size();
    return size;
}
float TI::getFPS() {
    sf::Time vTempo = vClock.getElapsedTime(); // Velocidade em Segundos por Frame
    vClock.restart().asSeconds(); // reseta o tempo
    v = velocidade * vTempo.asSeconds(); // Velocidade em Pixels por Frame
    return (1/vTempo.asSeconds());
}
float TI::getVel_PixelsPerFrame() {
    sf::Time vTempo = vClock.getElapsedTime(); // Velocidade em Segundos por Frame
    vClock.restart().asSeconds(); // reseta o tempo
    v = velocidade * vTempo.asSeconds(); // Velocidade em Pixels por Frame
    return v;
}
float TI::getTimeTable() { // Tempo que a nota leva para percorrer a mesa
    int MESA_COMPRIMENTO = 600;
    float TimeTable = MESA_COMPRIMENTO / velocidade;
    return TimeTable;
}
float TI::getTimeSensor() { // Tempo que a nota leva para percorrer a mesa
    float TimeSensor = (618 - 45) / velocidade;
    return TimeSensor;
}

void TI::show(){
    for (int i = 0; i < vec.size(); i++){
        for (int j = 0; j < vec[i].size(); j++){
            cout << vec[i][j] << " ";
        }
        cout << endl;
    }
}


/// ***********************************************************************************************
/// ***********************************************************************************************

RASTRO::RASTRO() {}

void RASTRO::setDim(sf::RenderWindow &window, int LARGURA_MESA_IN, int MESA_INICIO_IN, int MESA_FINAL_IN, int SENSORIN, int SENSOROUT) {
    LARGURA_MESA = LARGURA_MESA_IN;
    MESA_INICIO = MESA_INICIO_IN;
    MESA_FINAL = MESA_FINAL_IN;
    CENTRO_TELA_X = window.getSize().x/2;
    SENSOR_IN = SENSORIN;
    SENSOR_OUT = SENSOROUT;

    posVerde = CENTRO_TELA_X - (LARGURA_MESA/2) + (1*LARGURA_MESA/8);
    posVermelho = CENTRO_TELA_X - (LARGURA_MESA/2) + (3*LARGURA_MESA/8);
    posAmarelo = CENTRO_TELA_X - (LARGURA_MESA/2) + (5*LARGURA_MESA/8);
    posAzul = CENTRO_TELA_X - (LARGURA_MESA/2) + (7*LARGURA_MESA/8);
}
void RASTRO::reset(int vnota, float duracao) {
    nota.setSize( sf::Vector2f( 10, duracao * velocidade ) );
    nota.setOrigin( sf::Vector2f( nota.getGlobalBounds().width / 2, nota.getGlobalBounds().height) );

    nota2.setSize( sf::Vector2f( 10, duracao * velocidade ) );
    nota2.setOrigin( sf::Vector2f( nota2.getGlobalBounds().width / 2, nota2.getGlobalBounds().height) );

    nota2.setPosition(sf::Vector2f(-10, 0)); // Para caso haja apenas uma nota
    notaTex2.loadFromFile( "res/img/notas/NotaVermelha.png" );
    notaSprite2.setTexture( notaTex2 );
    notaSprite2.setOrigin( sf::Vector2f( notaSprite2.getGlobalBounds().width / 2, notaSprite2.getGlobalBounds().height) );
    notaSprite2.setPosition( sf::Vector2f( sf::Vector2f( -50, 0 ) ) ); // Fora da tela


    if(vnota == 1){ // Verde
        nota.setPosition( sf::Vector2f( posVerde, 0 ) );
        nota.setFillColor(sf::Color::Green);

        notaTex.loadFromFile( "res/img/notas/NotaVerde.png" );
        notaSprite.setTexture( notaTex );
        notaSprite.setOrigin( sf::Vector2f( notaSprite.getGlobalBounds().width / 2, notaSprite.getGlobalBounds().height) );
        notaSprite.setPosition( sf::Vector2f( sf::Vector2f( posVerde, 0 ) ) );
    }
    if(vnota == 2){ // Vermelho
        nota.setPosition( sf::Vector2f( posVermelho, 0 ) );
        nota.setFillColor(sf::Color::Red);

        notaTex.loadFromFile( "res/img/notas/NotaVermelha.png" );
        notaSprite.setTexture( notaTex );
        notaSprite.setOrigin( sf::Vector2f( notaSprite.getGlobalBounds().width / 2, notaSprite.getGlobalBounds().height) );
        notaSprite.setPosition( sf::Vector2f( sf::Vector2f( posVermelho, 0 ) ) );
    }
    if(vnota == 3){ // Verde e Vermelho
        nota.setPosition( sf::Vector2f( posVerde, 0 ) );
        nota.setFillColor(sf::Color::Green);
        nota2.setPosition( sf::Vector2f( posVermelho, 0 ) );
        nota2.setFillColor(sf::Color::Red);

        notaTex.loadFromFile( "res/img/notas/NotaVerde.png" );
        notaSprite.setTexture( notaTex );
        notaSprite.setOrigin( sf::Vector2f( notaSprite.getGlobalBounds().width / 2, notaSprite.getGlobalBounds().height) );
        notaSprite.setPosition( sf::Vector2f( sf::Vector2f( posVerde, 0 ) ) );

        notaTex2.loadFromFile( "res/img/notas/NotaVermelha.png" );
        notaSprite2.setTexture( notaTex2 );
        notaSprite2.setOrigin( sf::Vector2f( notaSprite2.getGlobalBounds().width / 2, notaSprite2.getGlobalBounds().height) );
        notaSprite2.setPosition( sf::Vector2f( sf::Vector2f( posVermelho, 0 ) ) );
    }
    if(vnota == 4){ // Amarelo
        nota.setPosition( sf::Vector2f( posAmarelo, 0 ) );
        nota.setFillColor(sf::Color::Yellow);

        notaTex.loadFromFile( "res/img/notas/NotaAmarela.png" );
        notaSprite.setTexture( notaTex );
        notaSprite.setOrigin( sf::Vector2f( notaSprite.getGlobalBounds().width / 2, notaSprite.getGlobalBounds().height) );
        notaSprite.setPosition( sf::Vector2f( sf::Vector2f( posAmarelo, 0 ) ) );
    }
    if(vnota == 5) { // Verde e Amarelo
        nota.setPosition( sf::Vector2f( posVerde, 0 ) );
        nota.setFillColor(sf::Color::Green);
        nota2.setPosition(sf::Vector2f(posAmarelo, 0));
        nota2.setFillColor(sf::Color::Yellow);

        notaTex.loadFromFile( "res/img/notas/NotaVerde.png" );
        notaSprite.setTexture( notaTex );
        notaSprite.setOrigin( sf::Vector2f( notaSprite.getGlobalBounds().width / 2, notaSprite.getGlobalBounds().height) );
        notaSprite.setPosition( sf::Vector2f( sf::Vector2f( posVerde, 0 ) ) );

        notaTex2.loadFromFile( "res/img/notas/NotaAmarela.png" );
        notaSprite2.setTexture( notaTex2 );
        notaSprite2.setOrigin( sf::Vector2f( notaSprite2.getGlobalBounds().width / 2, notaSprite2.getGlobalBounds().height) );
        notaSprite2.setPosition( sf::Vector2f( sf::Vector2f( posAmarelo, 0 ) ) );
    }
    if(vnota == 6){ // Vermelho e Amarelo
        nota.setPosition( sf::Vector2f( posVermelho, 0 ) );
        nota.setFillColor(sf::Color::Red);
        nota2.setPosition( sf::Vector2f( posAmarelo, 0 ) );
        nota2.setFillColor(sf::Color::Yellow);

        notaTex.loadFromFile( "res/img/notas/NotaVermelha.png" );
        notaSprite.setTexture( notaTex );
        notaSprite.setOrigin( sf::Vector2f( notaSprite.getGlobalBounds().width / 2, notaSprite.getGlobalBounds().height) );
        notaSprite.setPosition( sf::Vector2f( sf::Vector2f( posVermelho, 0 ) ) );

        notaTex2.loadFromFile( "res/img/notas/NotaAmarela.png" );
        notaSprite2.setTexture( notaTex2 );
        notaSprite2.setOrigin( sf::Vector2f( notaSprite2.getGlobalBounds().width / 2, notaSprite2.getGlobalBounds().height) );
        notaSprite2.setPosition( sf::Vector2f( sf::Vector2f( posAmarelo, 0 ) ) );
    }
    if(vnota == 8){ // Azul
        nota.setPosition( sf::Vector2f( posAzul, 0 ) );
        nota.setFillColor(sf::Color::Blue);

        notaTex.loadFromFile( "res/img/notas/NotaAzul.png" );
        notaSprite.setTexture( notaTex );
        notaSprite.setOrigin( sf::Vector2f( notaSprite.getGlobalBounds().width / 2, notaSprite.getGlobalBounds().height) );
        notaSprite.setPosition( sf::Vector2f( sf::Vector2f( posAzul, 0 ) ) );
    }
    if(vnota == 9){ // Verde e Azul
        nota.setPosition( sf::Vector2f( posVerde, 0 ) );
        nota.setFillColor(sf::Color::Green);
        nota2.setPosition( sf::Vector2f( posAzul, 0 ) );
        nota2.setFillColor(sf::Color::Blue);

        notaTex.loadFromFile( "res/img/notas/NotaVerde.png" );
        notaSprite.setTexture( notaTex );
        notaSprite.setOrigin( sf::Vector2f( notaSprite.getGlobalBounds().width / 2, notaSprite.getGlobalBounds().height) );
        notaSprite.setPosition( sf::Vector2f( sf::Vector2f( posVerde, 0 ) ) );

        notaTex2.loadFromFile( "res/img/notas/NotaAzul.png" );
        notaSprite2.setTexture( notaTex2 );
        notaSprite2.setOrigin( sf::Vector2f( notaSprite2.getGlobalBounds().width / 2, notaSprite2.getGlobalBounds().height) );
        notaSprite2.setPosition( sf::Vector2f( sf::Vector2f( posAzul, 0 ) ) );
    }
    if(vnota == 10){ // Vermelho e Azul
        nota.setPosition( sf::Vector2f( posVermelho, 0 ) );
        nota.setFillColor(sf::Color::Red);
        nota2.setPosition( sf::Vector2f( posAzul, 0 ) );
        nota2.setFillColor(sf::Color::Blue);
        notaTex.loadFromFile( "res/img/notas/NotaVermelha.png" );

        notaSprite.setTexture( notaTex );
        notaSprite.setOrigin( sf::Vector2f( notaSprite.getGlobalBounds().width / 2, notaSprite.getGlobalBounds().height) );
        notaSprite.setPosition( sf::Vector2f( sf::Vector2f( posVermelho, 0 ) ) );

        notaTex2.loadFromFile( "res/img/notas/NotaAzul.png" );
        notaSprite2.setTexture( notaTex2 );
        notaSprite2.setOrigin( sf::Vector2f( notaSprite2.getGlobalBounds().width / 2, notaSprite2.getGlobalBounds().height) );
        notaSprite2.setPosition( sf::Vector2f( sf::Vector2f( posAzul, 0 ) ) );
    }
    if(vnota == 12){ // Amarelo e Azul
        nota.setPosition( sf::Vector2f( posAmarelo, 0 ) );
        nota.setFillColor(sf::Color::Yellow);
        nota2.setPosition( sf::Vector2f( posAzul, 0 ) );
        nota2.setFillColor(sf::Color::Blue);

        notaTex.loadFromFile( "res/img/notas/NotaAmarela.png" );
        notaSprite.setTexture( notaTex );
        notaSprite.setOrigin( sf::Vector2f( notaSprite.getGlobalBounds().width / 2, notaSprite.getGlobalBounds().height) );
        notaSprite.setPosition( sf::Vector2f( sf::Vector2f( posAmarelo, 0 ) ) );

        notaTex2.loadFromFile( "res/img/notas/NotaAzul.png" );
        notaSprite2.setTexture( notaTex2 );
        notaSprite2.setOrigin( sf::Vector2f( notaSprite2.getGlobalBounds().width / 2, notaSprite2.getGlobalBounds().height) );
        notaSprite2.setPosition( sf::Vector2f( sf::Vector2f( posAzul, 0 ) ) );
    }
}
void RASTRO::reset(sf::Vector2f Tam, sf::Vector2f Pos, sf::Color Cor, sf::Vector2f Pos2, sf::Color Cor2) {
    nota.setSize(Tam);
    nota.setOrigin( sf::Vector2f( nota.getGlobalBounds().width / 2, nota.getGlobalBounds().height) );
    nota.setPosition(Pos);
    nota.setFillColor(Cor);

    nota2.setSize(Tam);
    nota2.setOrigin( sf::Vector2f( nota.getGlobalBounds().width / 2, nota.getGlobalBounds().height) );
    nota2.setPosition(Pos2);
    nota2.setFillColor(Cor2);

    notaSprite.setPosition(Pos);
    notaSprite2.setPosition(Pos2);

    if(Cor == sf::Color::Green) notaTex.loadFromFile( "res/img/notas/NotaVerde.png" );
    if(Cor == sf::Color::Red) notaTex.loadFromFile( "res/img/notas/NotaVermelha.png" );
    if(Cor == sf::Color::Yellow) notaTex.loadFromFile( "res/img/notas/NotaAmarela.png" );
    if(Cor == sf::Color::Blue) notaTex.loadFromFile( "res/img/notas/NotaAzul.png" );

    if(Cor2 == sf::Color::Green) notaTex2.loadFromFile( "res/img/notas/NotaVerde.png" );
    if(Cor2 == sf::Color::Red) notaTex2.loadFromFile( "res/img/notas/NotaVermelha.png" );
    if(Cor2 == sf::Color::Yellow) notaTex2.loadFromFile( "res/img/notas/NotaAmarela.png" );
    if(Cor2 == sf::Color::Blue) notaTex2.loadFromFile( "res/img/notas/NotaAzul.png" );
}
sf::FloatRect RASTRO::getDimNota1() {
    return nota.getGlobalBounds();
}
sf::FloatRect RASTRO::getDimNota2() {
    return nota2.getGlobalBounds();
}
sf::Vector2f RASTRO::getTam() {
    return nota.getSize();
}
sf::Vector2f RASTRO::getPos() {
    return nota.getPosition();
}
sf::Vector2f RASTRO::getPos2() {
    return nota2.getPosition();
}
sf::Color RASTRO::getCor() {
    return nota.getFillColor();
}
sf::Color RASTRO::getCor2() {
    return nota2.getFillColor();
}

bool RASTRO::onSensor(){
    if(nota.getPosition().y > SENSOR_IN && nota.getPosition().y < SENSOR_OUT) return 1;
    else return 0;
}
bool RASTRO::outSensor(){
    if(nota.getPosition().y > SENSOR_OUT) return 1;
    else return 0;
}
void RASTRO::move(bool pause) {
    if(!pause){
        sf::Time vTempo = vClock.getElapsedTime(); // Velocidade em Segundos por Frame
        vClock.restart().asSeconds(); // reseta o tempo
        //v = velocidade * vTempo.asSeconds(); // Velocidade em Pixels por Frame
        v = velocidade * vTempo.asSeconds();
        nota.move( sf::Vector2f(  0, v ) );
        nota2.move( sf::Vector2f(  0, v ) );
        notaSprite.move( sf::Vector2f(  0, v ) );
        notaSprite2.move( sf::Vector2f(  0, v ) );
    } else vClock.restart();
}
void RASTRO::draw(sf::RenderWindow &window){
    window.draw(nota);
    window.draw(nota2);
    window.draw(notaSprite);
    window.draw(notaSprite2);
}



/// ***********************************************************************************************
/// ***********************************************************************************************

TIMER::TIMER() {
    Timer.str(std::string());
}

void TIMER::setPos(sf::Vector2f pos){
    TimerText.setPosition( pos ) ;
}
void TIMER::setSize(int size){
    TimerText.setCharacterSize( size );
}
void TIMER::setColor(sf::Color cor){
    TimerText.setFillColor( cor );
}
void TIMER::setTime(sf::Time &time) {
    tempo = time;
}
void TIMER::setFont(sf::Font &fonte) {
    TimerText.setFont(fonte);
}
void TIMER::draw(sf::RenderWindow &window){
    Timer << "TEMPO:\n" << tempo.asSeconds();
    TimerText.setString( Timer.str().c_str() );
    window.draw( TimerText );
}


/// ***********************************************************************************************
/// ***********************************************************************************************

ANIM::ANIM(string local_arq, int n){
    local = local_arq;
    n_img = n;

    local.replace(local.end() - 5, local.end() - 4, to_string(cont+1));
    Tex.loadFromFile( local );
    Sprite.setTexture(Tex);
    Sprite.setOrigin(sf::Vector2f(Sprite.getGlobalBounds().width / 2, Sprite.getGlobalBounds().height));
}

void ANIM::setPos(sf::Vector2f Position) {
    Sprite.setPosition(Position);
}
void ANIM::setScale(sf::Vector2f Scale) {
    Sprite.setScale(Scale);
}

void ANIM::draw(sf::RenderWindow &window, sf::Time &tempo, float v) {
    if(!flag_tempo){
        tempo_inicial = tempo;
        flag_tempo = true;
    }
    if(tempo.asSeconds() > tempo_inicial.asSeconds() + v*0.015){
        flag_tempo = false;
        cont++;
        if(cont > n_img - 1) cont = 0;
    }

    local.replace(local.end() - 5, local.end() - 4, to_string(cont+1));
    Tex.loadFromFile( local );
    Sprite.setTexture(Tex);

    window.draw(Sprite);
}
void ANIM::playOnce(sf::RenderWindow &window, sf::Time &tempo, float t, float v) {
    if(flag_playOnce1){

        if(flag_playOnce2){
            som.play();
            tempo_playOnce = tempo;
            flag_playOnce2 = false;
            cont = 0;
        }

        draw(window, tempo, v);

        if(tempo.asSeconds() > tempo_playOnce.asSeconds() + t){
            flag_playOnce1 = false;
        }
    }
}
void ANIM::playOnceResetPress() {
    if(flag_playOnce3){
        flag_playOnce1 = true;
        flag_playOnce2 = true;
        flag_playOnce3 = false;
    }
}
void ANIM::playOnceResetRealease() {
    flag_playOnce3 = true;
}
void ANIM::playOnceSetSound(string local) {
    somBuffer.loadFromFile( local );
    som.setBuffer( somBuffer );
}