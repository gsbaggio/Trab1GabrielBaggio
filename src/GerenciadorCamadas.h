//*********************************************************
//
// classe para fazer o carregamento de arquivos no formato BMP
// Autor: Cesar Tadeu Pozzer
//        pozzer@inf.ufsm.br
//
//  Referencia:  http://astronomy.swin.edu.au/~pbourke/dataformats/bmp/
//  Versao 09/2010
//
//**********************************************************

#ifndef ___GERENCIADORCAMADAS__H___
#define ___GERENCIADORCAMADAS__H___

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define uchar unsigned char

typedef struct {
   unsigned char* camada;
   bool visivel;
} Camada;

typedef struct {
   int borda1X, borda1Y, borda2X, borda2Y;
   bool cima;
} BotaoSwitch;

typedef struct {
   int borda1X, borda1Y, borda2X, borda2Y;
   int bordaHideX;
   int posCamada;
   bool visivel;
   BotaoSwitch moveCima;
   BotaoSwitch moveBaixo;
   char nome[50];
}BotaoCamadas;

class gerenciadorCamadas
{
private:
    int borda1X, borda1Y, borda2X, borda2Y, width, height;
    int camadaAtiva;
    int qntCamadas;
    bool pintando;
    std::vector<Camada> camadas;
    std::vector<BotaoCamadas> botaoCamadas;

public:
   gerenciadorCamadas(int grossuraBordasLateraisNasCamadas, int bordaMenuLateralX, int screenHeight);
   void render();
   void carregaCamada(unsigned char *data, int imgWidth, int imgHeight);
   bool verificaMouseCamada(int mouseX, int mouseY);
   void setPintando(bool valor);
   bool getPintando();
   void addBotaoCamada(int qntCamadas, int screenWidth, int screenHeight, int inicioMenuLateralX);
   void renderBotaoSwitch(BotaoSwitch botaoSwitch);
   void renderBotaoCamada();
   int getQntCamadas();
};

#endif
