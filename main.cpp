#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sfeMovie/Movie.hpp>
#include "include/TI.h"

#define G 0
#define R 1
#define Y 2
#define B 3

#define COR_VERDE sf::Color::Green
#define COR_VERMELHO sf::Color::Red
#define COR_AMARELO sf::Color::Yellow
#define COR_AZUL sf::Color::Blue


using namespace std;

int main() {
    sf::ContextSettings propriedades;
    propriedades.antialiasingLevel = 0;
    sf::RenderWindow window(sf::VideoMode(800,600), "Trabalho Integrado", sf::Style::Default, propriedades);
    sf::View view( sf::FloatRect( 0, 0, 800, 600 ) );
    window.setView( view );
    window.setFramerateLimit(60); // Limita o framerate
    //window.setMouseCursorVisible( false ); //Desabilita o cursor do mouse

    const int LIM_NOTAS = 30;
    const int POSICAO_NOTA = 620;
    const int CENTRO_TELA_X = window.getSize().x / 2;
    const int LARGURA_MESA_CIMA = 180;
    const int LARGURA_MESA_BAIXO = 180;
    const int MESA_INICIO = 0;
    const int MESA_FINAL = 550;
    const int COMPRIMENTO_NOTA = 25;
    const int LARGURA_NOTA = LARGURA_MESA_BAIXO/4;
    const int SENSOR_IN = 585;
    const int SENSOR_OUT = 640;

    bool status_press[4] = {0,0,0,0};


/// *****************************************************************************************************************************
/// ==== CRIAÇÃO DOS OBJETOS ====================================================================================================
/// *****************************************************************************************************************************


    /// ------------ CRIA TEXTURA -----------------------------------------

    sf::Sprite imgFundo;
    sf::Texture texFundo;
    texFundo.loadFromFile( "res/img/guitarra2.jpg" );
    imgFundo.setTexture( texFundo );

    sf::Sprite imgFundo2;
    sf::Texture texFundo2;
    texFundo2.loadFromFile( "res/img/guitarra2top.png" );
    imgFundo2.setTexture( texFundo2 );

    sf::Sprite tubosSprite;
    sf::Texture tubosTex;
    tubosTex.loadFromFile( "res/img/MetalTubes.png" );
    tubosSprite.setTexture( tubosTex );
    tubosSprite.setOrigin(sf::Vector2f( tubosSprite.getGlobalBounds().width/2, tubosSprite.getGlobalBounds().height ));
    tubosSprite.setPosition(sf::Vector2f( (window.getSize().x)/2, (window.getSize().y) ));
    tubosSprite.setScale(sf::Vector2f(1, 1.3));
    sf::Sprite tubosSprite2;
    sf::Texture tubosTex2;
    tubosTex2.loadFromFile( "res/img/MetalTubes2.png" );
    tubosSprite2.setTexture( tubosTex2 );
    tubosSprite2.setOrigin(sf::Vector2f( tubosSprite2.getGlobalBounds().width/2, tubosSprite2.getGlobalBounds().height ));
    tubosSprite2.setPosition(sf::Vector2f( (window.getSize().x)/2, (window.getSize().y) ));
    tubosSprite2.setScale(sf::Vector2f(1, 1.3));

    /// Sprites animados
    ANIM chamas1("res/img/chama/chamaX.png", 6), chamas2("res/img/chama/chamaX.png", 6),\
         chamas3("res/img/chama/chamaX.png", 6), chamas4("res/img/chama/chamaX.png", 6);

    chamas1.setPos(sf::Vector2f( CENTRO_TELA_X - (LARGURA_NOTA*2) + ((1*LARGURA_NOTA) - (LARGURA_NOTA/2)), POSICAO_NOTA));
    chamas2.setPos(sf::Vector2f( CENTRO_TELA_X - (LARGURA_NOTA*2) + ((2*LARGURA_NOTA) - (LARGURA_NOTA/2)), POSICAO_NOTA));
    chamas3.setPos(sf::Vector2f( CENTRO_TELA_X - (LARGURA_NOTA*2) + ((3*LARGURA_NOTA) - (LARGURA_NOTA/2)), POSICAO_NOTA));
    chamas4.setPos(sf::Vector2f( CENTRO_TELA_X - (LARGURA_NOTA*2) + ((4*LARGURA_NOTA) - (LARGURA_NOTA/2)), POSICAO_NOTA));
    chamas1.setScale(sf::Vector2f(0.25, 0.3));
    chamas2.setScale(sf::Vector2f(0.25, 0.3));
    chamas3.setScale(sf::Vector2f(0.25, 0.3));
    chamas4.setScale(sf::Vector2f(0.25, 0.3));

    ANIM smoke1("res/img/smoke/smoke_puff_000X.png", 9), smoke2("res/img/smoke/smoke_puff_000X.png", 9),\
         smoke3("res/img/smoke/smoke_puff_000X.png", 9), smoke4("res/img/smoke/smoke_puff_000X.png", 9);

    smoke1.setPos(sf::Vector2f( CENTRO_TELA_X - (LARGURA_NOTA*2) + ((1*LARGURA_NOTA) - (LARGURA_NOTA/2)), POSICAO_NOTA - 35));
    smoke2.setPos(sf::Vector2f( CENTRO_TELA_X - (LARGURA_NOTA*2) + ((2*LARGURA_NOTA) - (LARGURA_NOTA/2)), POSICAO_NOTA - 35));
    smoke3.setPos(sf::Vector2f( CENTRO_TELA_X - (LARGURA_NOTA*2) + ((3*LARGURA_NOTA) - (LARGURA_NOTA/2)), POSICAO_NOTA - 35));
    smoke4.setPos(sf::Vector2f( CENTRO_TELA_X - (LARGURA_NOTA*2) + ((4*LARGURA_NOTA) - (LARGURA_NOTA/2)), POSICAO_NOTA - 35));
    smoke1.setScale(sf::Vector2f(0.13, 0.2));
    smoke2.setScale(sf::Vector2f(0.13, 0.2));
    smoke3.setScale(sf::Vector2f(0.13, 0.2));
    smoke4.setScale(sf::Vector2f(0.13, 0.2));

    ANIM raio_inicial("res/img/bolt_strike/bolt_strike_000X.png", 9);
    raio_inicial.setPos(sf::Vector2f( CENTRO_TELA_X, POSICAO_NOTA + 55));
    raio_inicial.setScale(sf::Vector2f(0.6, 0.4));
    raio_inicial.playOnceSetSound("res/som/squeak.wav");
    raio_inicial.playOnceResetPress(); /// Ativa no inicio

    /// CRIA TEXTO -------------------------------------------------------

    sf::Font fonte;
    if (!fonte.loadFromFile("res/fonts/GoodTimes.ttf")){return EXIT_FAILURE;}

    /// CRIA FORMA -------------------------------------------------------

    // SENSOR
    sf::RectangleShape sensor;
    sensor.setSize(sf::Vector2f(LARGURA_MESA_BAIXO, SENSOR_OUT - SENSOR_IN));
    sensor.setOrigin( sf::Vector2f( sensor.getGlobalBounds().width / 2, sensor.getGlobalBounds().height));
    sensor.setPosition(sf::Vector2f(CENTRO_TELA_X, SENSOR_IN));
    sensor.setFillColor(sf::Color( 255, 0, 0, 50 ));

    // PRESS
    sf::RectangleShape forma_press[4];
    forma_press[G].setFillColor(COR_VERDE);
    forma_press[R].setFillColor(COR_VERMELHO);
    forma_press[Y].setFillColor(COR_AMARELO);
    forma_press[B].setFillColor(COR_AZUL);
    for(int i=0; i<4; i++) {
        forma_press[i].setSize(sf::Vector2f(LARGURA_NOTA -10, COMPRIMENTO_NOTA));
        forma_press[i].setOrigin(sf::Vector2f(forma_press[0].getGlobalBounds().width / 2, forma_press[i].getGlobalBounds().height));
        forma_press[i].setPosition(sf::Vector2f(CENTRO_TELA_X - (LARGURA_NOTA * 2) + (((i + 1) * LARGURA_NOTA)
                                                                                      - (LARGURA_NOTA / 2)), POSICAO_NOTA));
    }

    // LINHAS
    sf::ConvexShape linha1( 4 );
    linha1.setPoint( 0, sf::Vector2f(CENTRO_TELA_X - (LARGURA_MESA_CIMA/4) -1, MESA_INICIO ));
    linha1.setPoint( 1, sf::Vector2f(CENTRO_TELA_X - (LARGURA_MESA_CIMA/4) +1, MESA_INICIO ));
    linha1.setPoint( 2, sf::Vector2f(CENTRO_TELA_X - (LARGURA_MESA_BAIXO/4) +1, MESA_FINAL));
    linha1.setPoint( 3, sf::Vector2f(CENTRO_TELA_X - (LARGURA_MESA_BAIXO/4) -1, MESA_FINAL));
    sf::ConvexShape linha2( 4 );
    linha2.setPoint( 0, sf::Vector2f(CENTRO_TELA_X -1, MESA_INICIO ));
    linha2.setPoint( 1, sf::Vector2f(CENTRO_TELA_X +1, MESA_INICIO ));
    linha2.setPoint( 2, sf::Vector2f(CENTRO_TELA_X +1, MESA_FINAL));
    linha2.setPoint( 3, sf::Vector2f(CENTRO_TELA_X -1, MESA_FINAL));
    sf::ConvexShape linha3( 4 );
    linha3.setPoint( 0, sf::Vector2f(CENTRO_TELA_X + (LARGURA_MESA_CIMA/4) -1, MESA_INICIO ));
    linha3.setPoint( 1, sf::Vector2f(CENTRO_TELA_X + (LARGURA_MESA_CIMA/4) +1, MESA_INICIO ));
    linha3.setPoint( 2, sf::Vector2f(CENTRO_TELA_X + (LARGURA_MESA_BAIXO/4) +1, MESA_FINAL));
    linha3.setPoint( 3, sf::Vector2f(CENTRO_TELA_X + (LARGURA_MESA_BAIXO/4) -1, MESA_FINAL));

    // MESA
    sf::ConvexShape mesaPlayer( 4 );
    mesaPlayer.setPoint( 0, sf::Vector2f( CENTRO_TELA_X - (LARGURA_MESA_CIMA/2), MESA_INICIO ) );
    mesaPlayer.setPoint( 1, sf::Vector2f( CENTRO_TELA_X + (LARGURA_MESA_CIMA/2), MESA_INICIO ) );
    mesaPlayer.setPoint( 2, sf::Vector2f( CENTRO_TELA_X + (LARGURA_MESA_BAIXO/2), MESA_FINAL ) );
    mesaPlayer.setPoint( 3, sf::Vector2f( CENTRO_TELA_X - (LARGURA_MESA_BAIXO/2), MESA_FINAL ) );
    mesaPlayer.setFillColor( sf::Color( 150, 150, 200, 80 ) );
    mesaPlayer.setOutlineThickness( 5 );
    mesaPlayer.setOutlineColor( sf::Color::White );

    /// CRIA TEMPO ----------------------------------------------------------

    sftools::Chronometer clock;
    sf::Time tempo;

    /// VIDEO ---------------------------------------------------------------

    //sfe::Movie video;
    //video.openFromFile("res/vid/wulf.mp4");
    //video.play();

    /// MUSICA ---------------------------------------------------------------

    sf::Music musicaBackground, musicaJogo;
    musicaBackground.openFromFile("res/mus/Metallica-One/background.ogg");
    musicaJogo.openFromFile("res/mus/Metallica-One/jogo.ogg");
    musicaBackground.setVolume(60);
    musicaJogo.setVolume(60);

    musicaBackground.play();
    musicaJogo.play();

    /// SOM ------------------------------------------------------------------

    sf::SoundBuffer somBufferPluck;
    sf::Sound somPluck;
    somBufferPluck.loadFromFile( "res/som/pluck.wav" );
    somPluck.setBuffer( somBufferPluck );

    /// JOGO -----------------------------------------------------------------

    int score = 0;
    TI seq("res/mus/Metallica-One/sequencia.mus");
    seq.getNewLine();

    RASTRO notas[LIM_NOTAS];
    for(int i=0; i<LIM_NOTAS; i++) notas[i].setDim(window, LARGURA_MESA_CIMA, MESA_INICIO, MESA_FINAL, SENSOR_IN, SENSOR_OUT);

    float RemoveTime = ( seq.getTimeFront() + seq.getTimeTable() + 2*seq.getDurTime());
    bool flag_final = false;
    bool flag_sensor[LIM_NOTAS]; for(int i=0; i<LIM_NOTAS; i++) flag_sensor[i] = false;
    bool flag_ponto[LIM_NOTAS]; for(int i=0; i<LIM_NOTAS; i++) flag_ponto[i] = false;
    bool flag_compara = false;
    int ponto = 0;
    int status_player = 0;
    sf::Time tempo_sensor;
    bool flag_delaySensor[LIM_NOTAS]; for(int i=0; i<LIM_NOTAS; i++) flag_delaySensor[i] = false;
    bool pause = false;
    bool nadaNoSensor = true;
    bool flag_nadaNoSensor = false;
    int indicador = 0; /// Indica qual nota deve ser pressionada no momento
    int multiplicador = 1;
    int multiplicadorCont = 0;


/// *****************************************************************************************************************************
/// ==== LOOP PRINCIPAL =========================================================================================================
/// *****************************************************************************************************************************
    while(window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::EventType::Closed:
                    window.close();
                    break;
                case sf::Event::EventType::Resized:
                    break;
                case sf::Event::EventType::LostFocus:
                    break;
                case sf::Event::EventType::GainedFocus:
                    break;

                case sf::Event::EventType::KeyReleased:

                    flag_nadaNoSensor = false;

                    switch (event.key.code) {
                        case sf::Keyboard::Key::Num1:
                            status_press[G] = false;
                            smoke1.playOnceResetRealease();
                            break;
                        case sf::Keyboard::Key::Num2:
                            status_press[R] = false;
                            break;
                        case sf::Keyboard::Key::Num3:
                            status_press[Y] = false;
                            break;
                        case sf::Keyboard::Key::Num4:
                            status_press[B] = false;
                            break;
                        case sf::Keyboard::Key::Escape:
                            pause = !pause;
                            break;
                        default:
                            break;
                    }       break;

                default: break;
            }
        }

        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Num1 ) ) { status_press[G] = true; }
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Num2 ) ) { status_press[R] = true; }
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Num3 ) ) { status_press[Y] = true; }
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Num4 ) ) { status_press[B] = true; }
        status_player = status_press[G] + 2*status_press[R] + 4*status_press[Y] + 8*status_press[B];


/// *****************************************************************************************************************************
/// ===== O QUE VAI APARECER NA TELA ============================================================================================
/// *****************************************************************************************************************************
        window.clear();

        window.draw(imgFundo);
        window.draw(linha1); window.draw(linha2); window.draw(linha3);
        window.draw(mesaPlayer);
        window.draw(tubosSprite2);

///================================================================================================
///     CONTROLE DA SEQUENCIA
///================================================================================================

        if(!pause)clock.resume();
        else clock.pause();

        tempo = clock;
        seq.setTime(tempo);

        if(flag_final && seq.getSize() < 1) pause = true; // Encerra

        if(tempo.asSeconds() > RemoveTime){ // Remove da tela
            seq.remove();

            RemoveTime = ( seq.getTimeFront(0) + seq.getTimeTable() + 2*seq.getDurTime(0));

            ///---------------------
            for(int i=0; i<seq.getSize(); i++){
                flag_sensor[i] = flag_sensor[i+1];
                flag_ponto[i] = flag_ponto[i+1];
            }
            ///---------------------

            for(int i=0; i<seq.getSize(); i++){
                notas[i].reset(notas[i+1].getTam(), notas[i+1].getPos(), notas[i+1].getCor(), notas[i+1].getPos2(), notas[i+1].getCor2());
            }
        }

        if(tempo.asSeconds() > seq.getTimeFront() - seq.getTimeTable()){ //Add nota
            if(!flag_final){
                seq.addNew();
                notas[seq.getSize() - 1].reset(seq.getNote(), seq.getDurTime());
                seq.getNewLine();
                if(seq.getTimeFront() == 999) flag_final = true;
            }
        }

        for(int i=0; i<LIM_NOTAS; i++){
            notas[i].move(pause);
            notas[i].draw(window);
        }

        if(pause){
            musicaBackground.pause();
            musicaJogo.pause();
        }else{
            if(!musicaBackground.Playing) musicaBackground.play();
            if(!musicaJogo.Playing) musicaJogo.play();
        }

        smoke1.playOnce(window, tempo, 0.25); /// Fumaca 1
        smoke2.playOnce(window, tempo, 0.25); /// Fumaca 2
        smoke3.playOnce(window, tempo, 0.25); /// Fumaca 3
        smoke4.playOnce(window, tempo, 0.25); /// Fumaca 4
        raio_inicial.playOnce(window, tempo, 1.2, 8); /// Eletricidade inicial

        window.draw(imgFundo2);

        /// PERCURSO DA NOTA *************************************************

        for(int i=0; i<seq.getSize(); i++){ /// Percorre o vetor de notas

        /// ANTES DO SENSOR --------------------------------------------------

            if(nadaNoSensor){
                if(!flag_nadaNoSensor){
                    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Num1 ) ){
                        ponto--;
                        flag_nadaNoSensor = true;
                    }
                    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Num2 ) ){
                        ponto--;
                        flag_nadaNoSensor = true;
                    }
                    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Num3 ) ){
                        ponto--;
                        flag_nadaNoSensor = true;
                    }
                    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Num4 ) ){
                        ponto--;
                        flag_nadaNoSensor = true;
                    }
                }
            }

            //if(tempo.asSeconds() > tempo_sensor.asSeconds() + seq.getDurTime(0)) flag_nadaNoSensor = true;

        /// NO SENSOR --------------------------------------------------------

            if(notas[i].onSensor() == 1){   /// Quando colidir com o sensor

                indicador = i;

                if(flag_nadaNoSensor)
                {
                    tempo_sensor = tempo;
                    nadaNoSensor = false;
                }

                if(!flag_sensor[i]){        /// Bloco de Verificacao

                    if(status_player == seq.getNote(i)){ /// Se a nota for igual a pressionada
                        flag_compara = true;
                        ponto++; ///           ++ Incrementa o medidor
                        score = score + multiplicador; ///           ++ Incrementa o score
                        multiplicadorCont++;
                        flag_sensor[i] = true;/// Bloqueia o bloco de verificacao
                        flag_ponto[i] = true; /// Registra que modificou o medidor
                    }
                    if(status_player != seq.getNote(i) && status_player != 0){ /// Se a nota for diferente da pressionada

                        somPluck.play();
                        ponto--; ///            -- Decrementa o medidor
                        multiplicadorCont = 0;

                        flag_sensor[i] = true; /// Bloqueia o bloco de verificacao
                        flag_ponto[i] = true;  /// Registra que modificou o medidor
                    }


                } /// ~Fim do Bloco de verificacao
            } /// ~Fim da colisao

            /// DEPOIS DO SENSOR ---------------------------------------------------

            if(notas[i].outSensor() == 1){      /// Quando sair do sensor

                if(!flag_sensor[i]){            /// Necessario para decrementar apenas uma vez

                    somPluck.play();
                    if(!flag_ponto[i]) ponto--; /// Caso nenhuma alteracao seja feita no medidor
                    ///                ^   ^     -- Decrementa o medidor
                    multiplicadorCont = 0;

                    flag_ponto[i] = false;      /// Reseta o flag do medidor
                    flag_delaySensor[i] = false;/// Reseta o flag do delay do medidor
                    flag_sensor[i] = true;      /// Bloqueia esse bloco
                } /// ~Bloco Bloqueado
            } /// ~Nota sai da tela

        } /// ~Pula para a nota seguinte

        cout << indicador <<  endl;

        if(flag_compara){
            if( status_press[G] ) { chamas1.draw(window, tempo); }
            if( status_press[R] ) { chamas2.draw(window, tempo); }
            if( status_press[Y] ) { chamas3.draw(window, tempo); }
            if( status_press[B] ) { chamas4.draw(window, tempo); }
        }

        if(!flag_compara){
            if( status_press[G] ) { smoke1.playOnceResetPress(); }
            if( status_press[R] ) { smoke2.playOnceResetPress(); }
            if( status_press[Y] ) { smoke3.playOnceResetPress(); }
            if( status_press[B] ) { smoke4.playOnceResetPress(); }
        }

        /// TIMER -------------------------------------

        TIMER timer;
        timer.setTime(tempo);
        timer.setFont(fonte);
        timer.setSize( 25 );
        timer.setColor( sf::Color::White );
        timer.setPos( sf::Vector2f( 20, 430 ) ) ;
        timer.draw(window);

        /// MEDIDOR ----------------------------------

        sf::Text Medidor;
        stringstream MedidorString;
        MedidorString << "Medidor:\n" << ponto;
        Medidor.setString( MedidorString.str().c_str() );
        Medidor.setFont(fonte);
        Medidor.setCharacterSize( 20 );
        if(ponto <= -3) Medidor.setFillColor( sf::Color::Red );
        if(ponto >= 3) Medidor.setFillColor( sf::Color::Green );
        if(ponto > -3 && ponto < 3) Medidor.setFillColor( sf::Color::Yellow );
        Medidor.setPosition( 20, 510 ) ;
        window.draw(Medidor);

        /// MULTIPLICADOR -----------------------------
        if(multiplicadorCont>-1 && multiplicadorCont<5) multiplicador = 1;
        if(multiplicadorCont>4 && multiplicadorCont<10) multiplicador = 2;
        if(multiplicadorCont>9 && multiplicadorCont<15) multiplicador = 4;
        if(multiplicadorCont>14 && multiplicadorCont<20) multiplicador = 8;

        sf::Text MultiplicadorTexto;
        stringstream MultiplicadorString;
        MultiplicadorString << multiplicador << "X" << endl;
        MultiplicadorTexto.setString( MultiplicadorString.str().c_str() );
        MultiplicadorTexto.setFont(fonte);
        MultiplicadorTexto.setCharacterSize( 45 );
        MultiplicadorTexto.setPosition( CENTRO_TELA_X + LARGURA_MESA_BAIXO / 2 + 20, MESA_FINAL - 10 ) ;
        if(multiplicador > 1) window.draw(MultiplicadorTexto);

        /// SCORE -------------------------------------

        sf::Text ScoreText;
        stringstream ScoreString;
        ScoreString << "Score:\n" << score;
        ScoreText.setString( ScoreString.str().c_str() );
        ScoreText.setFont(fonte);
        ScoreText.setCharacterSize( 20 );
        ScoreText.setFillColor( sf::Color::Cyan );
        ScoreText.setPosition( 170, 510 ) ;
        window.draw(ScoreText);

        ///--------------------------------------------

        window.draw(tubosSprite);
        window.draw(sensor);

        window.display();
    }
    return 0;
}