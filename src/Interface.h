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

typedef struct {
    int inicioX, fimX, Y;
    float porcentagem;
    int valorMinimo, valorMaximo;
    int valorAtual;
}Slider;


class Interface
{
private:
    int bordaMenuLateralX, grossuraBordasLateraisNasCamadas, inicioMenuLateralX;
    int tamanhoLadoQuadradosFundo, borda1X, borda1Y, borda2X, borda2Y;
    BOTAO botaoAddImagem;
    BOTAO clicar;
    BOTAO pincel;
    BOTAO spray;
    BOTAO marcaTexto;
    BOTAO balde;
    BOTAO borracha;
    Slider sliderR;
    Slider sliderG;
    Slider sliderB;
    Slider sliderRaio;

    BOTAO flipVertical;
    BOTAO flipHorizontal;
    Slider controleBrilho;
    int botaoSelecionado; // 0 = clicar, 1 = pincel, 2 = spray, 3 = marca texto, 4 = balde, 5 = borracha
    int raioCor;
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
    void renderBotaoClicar();
    void renderBotaoPincel();
    void renderBotaoSpray();
    void renderBotaoMarcaTexto();
    void renderBotaoBalde();
    void renderBotaoBorracha();
    BOTAO getBotaoAddImagem();
    BOTAO getBotaoClicar();
    BOTAO getBotaoPincel();
    BOTAO getBotaoSpray();
    BOTAO getBotaoMarcaTexto();
    BOTAO getBotaoBalde();
    BOTAO getBotaoBorracha();
    void alteraBotaoSelecionado(int botaoSelecionado);
    void carregarNomeArquivos();
    void renderSubmenuArquivos();
    void setAbertoSubmenuArquivos(bool aberto, int mouseX, int mouseY);
    bool getAbertoSubmenuArquivos();
    Submenu getSubmenuArquivos();
    bool verificaClickSubmenu(Submenu submenu, int mouseX, int mouseY);
    std::string verificaArquivoParaAbrir(int mouseX, int mouseY);
    int getBotaoSelecionado();
    void setBotaoSelecionado(int botaoSelecionado);
    unsigned char *getRGBA();
    int getRaioCor();
};

#endif
