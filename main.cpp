#include <cstdlib>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <sstream>

using namespace std;
using namespace sf;


int mapa[25][40] = {0};
int velocidad=4;

class juego{
public:
    const int M=25;
    const int N=40;
    int ts=18;
    int velocidad=5;

    void drop(int y, int x);
    void jugar();
    void crearMapa();
};

struct Enemy{
    juego velocidad;
    juego ts;
    int x,y,dx,dy;
    Enemy(){
        x=300;
        y=300;
        dx=velocidad.velocidad-rand()%10;
        dy=velocidad.velocidad-rand()%10;

    }

    void move(){

        x+=dx;
        if (mapa[(y)/ts.ts][x/ts.ts]==1) {
            dx=-dx;
            x+=dx;
        }
        y+=dy;
        if (mapa[(y)/ts.ts][x/ts.ts]==1) {
            dy=-dy;
            y+=dy;
        }
    }
    void move1(){
        x+=dx;
        if (mapa[(y)/ts.ts][x/ts.ts]==1) {
            if (y<0||y>24)
                mapa[(y)/ts.ts][x/ts.ts]=0;

            dx=-dx;
            x+=dx;
        }
        y+=dy;
        if (mapa[(y)/ts.ts][x/ts.ts]==1) {
            dy=-dy;

            y+=dy;

        }
    }
};

void juego::drop(int y,int x){
    if (mapa[y][x]==0) 		mapa[y][x]=-1;
    if (mapa[y-1][x]==0) 		drop(y-1,x);
    if (mapa[y+1][x]==0) 		drop(y+1,x);
    if (mapa[y][x-1]==0) 		drop(y,x-1);
    if (mapa[y][x+1]==0) 		drop(y,x+1);
}

void juego::jugar(){
    juego M;
    juego N;
    juego ts;
    Enemy a[10];
    Enemy b[8];
    RenderWindow window(VideoMode(720, 500), "Juego Xonix!");
    window.setFramerateLimit(60);
    SoundBuffer buffer, muerte, gaov, win;
    buffer.loadFromFile("music/Fondo.ogg");
    muerte.loadFromFile("music/Muerte.ogg");
    gaov.loadFromFile("music/Gameover.ogg");
    win.loadFromFile("music/Win.ogg");
    Sound sound, ssmuerte, ssgaov, swin;
    sound.setBuffer(buffer);
    swin.setBuffer(win);
    sound.play();
    ssmuerte.setBuffer(muerte);
    ssgaov.setBuffer(gaov);
    Texture t1,t2,t3,t4, fondo, ganaste, inicio, inicio1, plata, helado, enemy2;
    t1.loadFromFile("images/tiles1.png");
    t2.loadFromFile("images/gameover.png");
    t3.loadFromFile("images/enemy.png");
    t4.loadFromFile("images/pack1.png");
    fondo.loadFromFile("images/fondo.png");
    ganaste.loadFromFile("images/ganaste.png");
    inicio.loadFromFile("images/inicio.png");
    plata.loadFromFile("images/plata.png");
    helado.loadFromFile("images/hel.png");
    enemy2.loadFromFile("images/enemy2.png");
    Sprite sTile(t1), sGameover(t2), sEnemy(t3), sPack(t4), sfondo(fondo), sganaste(ganaste), sinicio(inicio), sinicio1(inicio1) , splata(plata), shel(helado), senemy2(enemy2);
    sTile.setOrigin(0,0);
    sGameover.setPosition(100,100);
    sEnemy.setOrigin(7,7);
    senemy2.setOrigin(7,7);
    sganaste.setPosition(150,150);
    int plx=rand()%700-18;
    int ply=rand()&380-18;
    int hex=rand()%700-18;
    int hey=rand()&380-18;
    splata.setPosition(plx,ply);
    shel.setPosition(hex,hey);

    int enemyCount = 4;
    int enemy2222=4;

    bool Game=true;
    int x=0, y=0, dx=0, dy=0;
    float timer=0, veljugador=0.07;
    Clock clock;
    int j=0;
    int vidas=3;
    int puntaje=-126;
    int progreso=0;
    int nivel=1;
    bool pal =true, pal1=true;

    string cadena="";
    string spuntaje="";
    string sprogreso="";
    string snivel="";
    cadena = to_string(vidas);
    spuntaje=to_string(puntaje);
    sprogreso=to_string(progreso);
    snivel=to_string(nivel);
    int n=1;
    while (window.isOpen()){
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        Font font;
        font.loadFromFile("cabeza.ttf");
        window.draw(sfondo);

        Text text("Vidas:  ",font,18), text1("Score:  ",font,18), text2("Progreso:",font,18), text3("Nivel:",font,18), text4(cadena,font,18), text5(spuntaje,font,18), text6(sprogreso,font,18), text7(snivel,font,18);
        text1.setOrigin(-150,-465); text1.setColor(Color::Yellow);
        text.setOrigin(-5,-465); text.setColor(Color::Yellow);
        text2.setOrigin(-475,-465); text2.setColor(Color::Yellow);
        text3.setOrigin(-325,-465); text3.setColor(Color::Yellow);
        text4.setOrigin(-90,-465); text4.setColor(Color::White);
        text5.setOrigin(-250,-465); text5.setColor(Color::White);
        text6.setOrigin(-625,-465); text6.setColor(Color::White);
        text7.setOrigin(-420,-465); text7.setColor(Color::White);
        window.draw(text); 		window.draw(text1);		window.draw(text2);		window.draw(text3);		window.draw(text4);		window.draw(text7);


        Event e;
        while (window.pollEvent(e)){
            if(n==-1){
                Game=false;
            }
            else if(n==1){
                Game=true;
            }
            if (e.type == Event::Closed)
                window.close();

            if (e.type == Event::KeyPressed)
                if (e.key.code==Keyboard::Escape){
                    for (int i=1;i<M.M-1;i++)
                        for (int j=1;j<N.N-1;j++)
                            mapa[i][j]=0;
                    veljugador=0.07;
                    x=10;y=0;
                    Game=true;
                    vidas=3;
                    cadena=to_string(vidas);
                    window.draw(text4);
                }
            if(e.type==Event::KeyPressed){
                if (e.key.code==Keyboard::P){
                    n=n*(-1);
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)){
            dx=-1;
            dy=0;
            t1.loadFromFile("images/tiles2.png");
        };
        if (Keyboard::isKeyPressed(Keyboard::Right)){
            dx=1;
            dy=0;
            t1.loadFromFile("images/tiles1.png");
        };
        if (Keyboard::isKeyPressed(Keyboard::Up)){
            dx=0;
            dy=-1;
            t1.loadFromFile("images/tiles3.png");
        };
        if (Keyboard::isKeyPressed(Keyboard::Down)){
            dx=0;
            dy=1;
            t1.loadFromFile("images/tiles4.png");
        };

        if (!Game) continue;

        if (timer>veljugador){
            x+=dx;
            y+=dy;

            if (x<0)
                x=0;
            if (x>N.N-1)
                x=N.N-1;
            if (y<0)
                y=0;
            if (y>M.M-1)
                y=M.M-1;
            bool aaa=true;
            if (mapa[y][x]==2){
                for (int i=0;i<M.M;i++)
                    for (int j=0;j<N.N;j++)
                        if (mapa[i][j]==2){
                            mapa[i][j]=0;

                        };
                mapa[y][x]=0;
                Game=false;
                aaa=false;
            }
            if (mapa[y][x]==0) if (aaa==true) mapa[y][x]=2;
            timer=0;
        }

        for (int i=0;i<enemyCount;i++) a[i].move();

        for (int j=0;j<enemy2222;j++) b[j].move1();

        if (mapa[y][x]==1){
            dx=dy=0;

            for (int i=0;i<enemyCount;i++)
                drop(a[i].y/ts.ts, a[i].x/ts.ts);

            for (int i=0;i<M.M;i++)
                for (int j=0;j<N.N;j++)
                    if (mapa[i][j]==-1) mapa[i][j]=0;
                    else mapa[i][j]=1;
        }

        for (int i=0;i<enemyCount;i++)
            if  (mapa[a[i].y/ts.ts][a[i].x/ts.ts]==2){
                for (int i=0;i<M.M;i++)
                    for (int j=0;j<N.N;j++)
                        if (mapa[i][j]==2) mapa[i][j]=0;
                Game=false;
            }
        /////////draw//////////


        for (int i=0;i<M.M;i++)
            for (int j=0;j<N.N;j++)
            {if(mapa[i][j]==1){
                    puntaje=puntaje+1;
                    spuntaje=to_string(puntaje);
                    window.draw(text5);
                }

                if (mapa[i][j]==0) continue;
                if (mapa[i][j]==1) sTile.setTextureRect(IntRect( 0,0,ts.ts,ts.ts));
                if (mapa[i][j]==2) sTile.setTextureRect(IntRect(54,0,ts.ts,ts.ts));
                if (mapa[i][j]==3) sTile.setTextureRect(IntRect(72,0,ts.ts,ts.ts));
                sTile.setPosition(j*ts.ts,i*ts.ts);
                window.draw(sTile);
            }

        sTile.setTextureRect(IntRect(18,0,ts.ts,ts.ts));
        sTile.setPosition(x*ts.ts,y*ts.ts);
        window.draw(sTile);

        progreso=progreso+puntaje*100/874;
        sprogreso=to_string(progreso);
        window.draw(text6);


        for (int i=0;i<enemyCount;i++){
            sEnemy.setPosition(a[i].x,a[i].y);
            window.draw(sEnemy);
        }
        for (int j=0;j<enemyCount;j++){
            senemy2.setPosition(b[j].x,b[j].y);
            window.draw(senemy2);
        }

        if(x==plx/18 && y==ply/18){
            pal=false;
            veljugador=0.04;
        }
        if(puntaje>500 && x==hex/18 && y==hey/18 &&pal1==true){
            pal1=false;
            vidas=vidas+1;
            cadena=to_string(vidas);
            window.draw(text4);
        }
        if(puntaje>100 && pal==true){
            window.draw(splata);
        }
        if(puntaje>500 && pal1==true){
            window.draw(shel);
        }
        else if(progreso>80){
            swin.play();
            window.draw(sganaste);
            Game=false;
            vidas=vidas+1;
            nivel=nivel+1;

        }

        if(vidas>0){
            if (!Game){
                vidas=vidas-1;
                cadena=to_string(vidas);
                window.draw(text4);
                if(vidas>0){
                    ssmuerte.play();
                }
                x=0;y=0;
                Game=true;
            }
        }
        else{
            window.draw(sGameover);
            sound.pause();
            ssgaov.play();
            Game=false;


        }
        progreso=0;
        puntaje=-126;

        if(j==0){
            window.draw(sinicio);
        }

        if (Keyboard::isKeyPressed(Keyboard::Space)){
            window.draw(sinicio1);
            j=j+1;
        };
        window.display();
    }
}
void juego::crearMapa(){
    juego M;
    juego N;

    for (int i=0;i<M.M;i++){
        for (int j=0;j<N.N;j++){

            if (i==0 || j==0 || i==M.M-1 || j==N.N-1){
                mapa[i][j]=1;

            }
        }
    }


}
int main(){

    juego crearMapa;
    juego jugar;
    srand(time(0));
    crearMapa.crearMapa();
    jugar.jugar();

    return 0;
}