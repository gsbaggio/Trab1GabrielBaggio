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

#ifndef ___INTERFACE__H___
#define ___INTERFACE__H___

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <dirent.h>

#define uchar unsigned char

typedef struct {
   int borda1X, borda1Y, borda2X, borda2Y;
   bool tem_borda;
} BOTAO;

typedef struct {
    int borda1X, borda1Y, borda2X, borda2Y;
    bool aberto;
}Submenu;

typedef struct {
    std::string nome;
    int deltaY;
}BotaoArquivo;


class Interface
{
private:
    int bordaMenuLateralX, grossuraBordasLateraisNasCamadas, inicioMenuLateralX;
    int tamanhoLadoQuadradosFundo, borda1X, borda1Y, borda2X, borda2Y;
    BOTAO botaoAddImagem;
    BOTAO clicar;
    BOTAO pintar;
    BOTAO cor[10];
    int botaoSelecionado;
    unsigned char RGBA[4];

    Submenu submenuArquivos;
    int qntArquivos;
    int tamanhoBotaoArquivos;
    std::vector<BotaoArquivo> botaoArquivos;

public:
    Interface(int screenWidth, int screenHeight);
    void render(int screenWidth, int screenHeight);
    int getBordaMenuLateralX();
    int getGrossuraBordasLaterais();
    void renderFundo();
    void renderBotao(BOTAO botao);
    bool verificaClickBotao(BOTAO botao, int mouseX, int mouseY);
    void renderBotaoAdd();
    BOTAO getBotaoAddImagem();
    void carregarNomeArquivos();
    void renderSubmenuArquivos();
    void setAbertoSubmenuArquivos(bool aberto, int mouseX, int mouseY);
    bool getAbertoSubmenuArquivos();
    Submenu getSubmenuArquivos();
    bool verificaClickSubmenu(Submenu submenu, int mouseX, int mouseY);
    std::string verificaArquivoParaAbrir(int mouseX, int mouseY);
    int getBotaoSelecionado();
    unsigned char *getRGBA();
};

#endif
