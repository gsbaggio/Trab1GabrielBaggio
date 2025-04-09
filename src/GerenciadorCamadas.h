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
    int caixaBotoes1X, caixaBotoes1Y, caixaBotoes2X, caixaBotoes2Y;
    std::vector<Camada> camadas;
    std::vector<BotaoCamadas> botaoCamadas;

public:
   gerenciadorCamadas(int grossuraBordasLateraisNasCamadas, int bordaMenuLateralX, int screenHeight, int screenWidth, int inicioMenuLateralX);
   void render();
   void carregaCamada(unsigned char *data, int imgWidth, int imgHeight);
   bool verificaMouseCamada(int mouseX, int mouseY);
   void setPintando(bool valor);
   bool getPintando();
   void addBotaoCamada(int qntCamadas, int screenWidth, int screenHeight, int inicioMenuLateralX);
   void renderBotaoSwitch(BotaoSwitch botaoSwitch);
   void renderBotaoCamada();
   void renderCaixaCamadas();
   int getQntCamadas();
   bool verificaBotaoHide(int mouseX, int mouseY);
   bool verificaBotaoAtiva(int mouseX, int mouseY);
   bool verificaBotaoCima(int mouseX, int mouseY);
   bool verificaBotaoBaixo(int mouseX, int mouseY);
   void pintarCamada(int mouseX, int mouseY, unsigned char *RGBA, int tipoPintura, int raio);
};

#endif
