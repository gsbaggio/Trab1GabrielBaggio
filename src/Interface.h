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
}BOTAO;

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
    int valorMinimo, valorMaximo;
    int valorAtual;
    bool segurando;
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

    Slider sliderBrilho;
    BOTAO addBrilho;
    Slider sliderGama;
    BOTAO addGama;
    Slider sliderContraste;
    BOTAO addContraste;
    Slider sliderBlur;
    BOTAO addBlur;

    BOTAO fliperVertical;
    BOTAO fliperHorizontal;

    BOTAO tonsCinza;

    BOTAO save;
    BOTAO load;

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
    void renderBotao(BOTAO botao, const char* texto, bool isImage);
    bool verificaClickBotao(BOTAO botao, int mouseX, int mouseY);
    BOTAO getBotaoAddImagem();
    BOTAO getBotaoClicar();
    BOTAO getBotaoPincel();
    BOTAO getBotaoSpray();
    BOTAO getBotaoMarcaTexto();
    BOTAO getBotaoBalde();
    BOTAO getBotaoBorracha();
    BOTAO getBotaoVertical();
    BOTAO getBotaoHorizontal();
    BOTAO getBotaoCinza();
    BOTAO getBotaoAddBrilho();
    BOTAO getBotaoAddGama();
    BOTAO getBotaoAddContraste();
    BOTAO getBotaoAddBlur();
    BOTAO getBotaoSave();
    BOTAO getBotaoLoad();
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
    void renderSlider(Slider slider, const char* texto = nullptr, bool mostrarValor = true, bool porcentagem = false);
    bool verificaSegurandoSlider(Slider slider, int mouseX, int mouseY);
    Slider getSliderR();
    Slider getSliderG();
    Slider getSliderB();
    Slider getSliderRaio();
    Slider getSliderBrilho();
    Slider getSliderGama();
    Slider getSliderContraste();
    Slider getSliderBlur();
    void setSegurandoR(bool segurando);
    void setSegurandoG(bool segurando);
    void setSegurandoB(bool segurando);
    void setSegurandoRaio(bool segurando);
    void setSegurandoBrilho(bool segurando);
    void setSegurandoGama(bool segurando);
    void setSegurandoContraste(bool segurando);
    void setSegurandoBlur(bool segurando);
    void mudaValorSliderR(int mouseX);
    void mudaValorSliderG(int mouseX);
    void mudaValorSliderB(int mouseX);
    void mudaValorSliderRaio(int mouseX);
    void mudaValorSliderBrilho(int mouseX);
    void mudaValorSliderGama(int mouseX);
    void mudaValorSliderContraste(int mouseX);
    void mudaValorSliderBlur(int mouseX);
    void renderPreviewCor(int screenWidth);
};

#endif
