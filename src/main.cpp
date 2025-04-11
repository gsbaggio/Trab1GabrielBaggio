// código da main do programa, serve pra captar mouse e chamar as outras funções, assim como chamar os render

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include "gl_canvas2d.h"

#include "Bmp.h"
#include "GerenciadorCamadas.h"
#include "Interface.h"
#include <string>

//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 1280, screenHeight = 720;

// declaração das classes
Bmp *img1;
Interface *interface;
gerenciadorCamadas *gCamadas;

void carregarImagemNaCamada(char *nome_arquivo){ // funcao para carregar, se nao estiver no limite
    if(gCamadas->getQntCamadas() >= MAX_CAMADAS){
        return;
    }
    img1 = new Bmp(nome_arquivo);
    img1->convertBGRtoRGB();
    gCamadas->carregaCamada(img1->getImage(), img1->getWidth(), img1->getHeight());
    gCamadas->addBotaoCamada(gCamadas->getQntCamadas() - 1, screenWidth, screenHeight, interface->getBordaMenuLateralX());
}

void render() // aqui so chama os render das classes principais
{
    interface->render(screenWidth, screenHeight);
    gCamadas->render();
    Sleep(10); //nao eh controle de FPS. Somente um limitador de FPS.
}

void keyboard(int key)
{
    // nao usa
}

void keyboardUp(int key)
{
   // nao usa
}

void trataSubmenuAberto(int x, int y){ // funcao pra tratar clicks quando o submenu esta aberto. Verifica se esta dentro ou fora
    if(interface->verificaClickSubmenu(interface->getSubmenuArquivos(), x, y) == 0){
        interface->setAbertoSubmenuArquivos(0, 0, 0);
    }
    else{
        char nome_arquivo[512]; 
        std::string nomeArquivoRetornado = (interface->verificaArquivoParaAbrir(x, y).c_str());
        sprintf(nome_arquivo, ".\\Trab1GabrielBaggio\\images\\%s", nomeArquivoRetornado.c_str());
        carregarImagemNaCamada(nome_arquivo);
        interface->setAbertoSubmenuArquivos(0, 0, 0);

    }
}

bool verificaClickGerenciadorCamadas(int x, int y){ // funcao pra tratar os clicks no gerenciador de camadas
    if(gCamadas->verificaBotaoHide(x, y)){
        return 1;
    }
    else if(gCamadas->verificaBotaoAtiva(x, y)){
        return 1;
    }
    else if(gCamadas->verificaBotaoCima(x, y)){
        return 1;
    }
    else if(gCamadas->verificaBotaoBaixo(x, y)){
        return 1;
    }
    return 0;
}

bool verificaClickBotaoInterface(int x, int y){ // funcao pra tratar os clicks nos botoes da interface
    if(interface->verificaClickBotao(interface->getBotaoAddImagem(), x, y)){
        interface->setAbertoSubmenuArquivos(1, x, y);
        return 1;
    }
    else if(interface->verificaClickBotao(interface->getBotaoClicar(), x, y)){
        interface->alteraBotaoSelecionado(0);
        return 1;
    }
    else if(interface->verificaClickBotao(interface->getBotaoPincel(), x, y)){
        interface->alteraBotaoSelecionado(1);
        return 1;
    }
    else if(interface->verificaClickBotao(interface->getBotaoSpray(), x, y)){
        interface->alteraBotaoSelecionado(2);
        return 1;
    }
    else if(interface->verificaClickBotao(interface->getBotaoMarcaTexto(), x, y)){
        interface->alteraBotaoSelecionado(3);
        return 1;
    }
    else if(interface->verificaClickBotao(interface->getBotaoBalde(), x, y)){
        interface->alteraBotaoSelecionado(4);
        return 1;
    }
    else if(interface->verificaClickBotao(interface->getBotaoBorracha(), x, y)){
        interface->alteraBotaoSelecionado(5);
        return 1;
    }
    return 0;
}

bool verificaClickAddEfeito(int x, int y){ // funcao pra tratar os clicks nas aplicacoes de efeitos
    if(interface->verificaClickBotao(interface->getBotaoAddBrilho(), x, y) && gCamadas->getQntCamadas() > 0){
        gCamadas->adicionarBrilho(interface->getValorBrilho());
        return 1;
    }
    else if(interface->verificaClickBotao(interface->getBotaoAddGama(), x, y) && gCamadas->getQntCamadas() > 0){
        gCamadas->adicionarGama(interface->getValorGama());
        return 1;
    }
    else if(interface->verificaClickBotao(interface->getBotaoVertical(), x, y) && gCamadas->getQntCamadas() > 0){
        gCamadas->flipVertical();
        return 1;
    }
    else if(interface->verificaClickBotao(interface->getBotaoHorizontal(), x, y) && gCamadas->getQntCamadas() > 0){
        gCamadas->flipHorizontal();
        return 1;
    }
    else if(interface->verificaClickBotao(interface->getBotaoCinza(), x, y) && gCamadas->getQntCamadas() > 0){
        gCamadas->aplicarTonsDecinza();
        return 1;
    }
    return 0;
}

void iniciaDrags(int x, int y){ // inicia um 'drag do mouse', o evento de quando o mouse é pressionada
    if(gCamadas->verificaMouseCamada(x, y)){
        gCamadas->setPintando(1);
    }
    else if(interface->verificaSegurandoSlider(interface->getSliderR(), x, y)){
        interface->setSegurandoR(1);
    }
    else if(interface->verificaSegurandoSlider(interface->getSliderG(), x, y)){
        interface->setSegurandoG(1);
    }
    else if(interface->verificaSegurandoSlider(interface->getSliderB(), x, y)){
        interface->setSegurandoB(1);
    }
    else if(interface->verificaSegurandoSlider(interface->getSliderRaio(), x, y)){
        interface->setSegurandoRaio(1);
    }
    else if(interface->verificaSegurandoSlider(interface->getSliderBrilho(), x, y)){
        interface->setSegurandoBrilho(1);
    }
    else if(interface->verificaSegurandoSlider(interface->getSliderGama(), x, y)){
        interface->setSegurandoGama(1);
    }
}

void fimDrags(){ // quando solta o mouse, tira o 'drag'
    gCamadas->setPintando(0);
    interface->setSegurandoR(0);
    interface->setSegurandoG(0);
    interface->setSegurandoB(0);
    interface->setSegurandoRaio(0);
    interface->setSegurandoBrilho(0);
    interface->setSegurandoGama(0);
}

void trataDrags(int x, int y){  // trata a movimentacao do mouse quando tem um drag
    if(gCamadas->getPintando() && gCamadas->verificaMouseCamada(x, y) && gCamadas->getQntCamadas() > 0){
        gCamadas->pintarCamada(x, y, interface->getRGBA(), interface->getBotaoSelecionado(), interface->getRaioCor());
    }
    else if(interface->getSegurandoR()){
        interface->mudaValorSliderR(x);
    }
    else if(interface->getSegurandoG()){
        interface->mudaValorSliderG(x);
    }
    else if(interface->getSegurandoB()){
        interface->mudaValorSliderB(x);
    }
    else if(interface->getSegurandoRaio()){
        interface->mudaValorSliderRaio(x);
    }
    else if(interface->getSegurandoBrilho()){
        interface->mudaValorSliderBrilho(x);
    }
    else if(interface->getSegurandoGama()){
        interface->mudaValorSliderGama(x);
    }
}

void mouse(int button, int state, int wheel, int direction, int x, int y) // funções gerais do mouse
{
    if(button == 0 && state == 1){
        if(interface->getAbertoSubmenuArquivos()){ trataSubmenuAberto(x, y); }
        else if(verificaClickGerenciadorCamadas(x, y));
        else if(verificaClickBotaoInterface(x, y));
        else if(verificaClickAddEfeito(x, y));
        fimDrags();
    }
    else if(button == 0 && state == 0){
        iniciaDrags(x, y);
    }
    trataDrags(x, y);
}

int main(void)
{
    interface = new Interface(screenWidth, screenHeight);
    gCamadas = new gerenciadorCamadas(interface->getGrossuraBordasLaterais(), interface->getBordaMenuLateralX(), screenHeight, screenWidth, interface->getBordaMenuLateralX());


    CV::init(&screenWidth, &screenHeight, "Gabriel Baggio Image Manipulation Program (GBIMP)");
    CV::run();
}
