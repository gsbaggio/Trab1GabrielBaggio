//*********************************************************
//
// classe para fazer o carregamento de arquivos no formato BMP
// Autor: Cesar Tadeu Pozzer
//        pozzer@inf.ufsm.br
//  Versao 09/2010
//
//**********************************************************

#include "GerenciadorCamadas.h"
#include <string.h>
#include "gl_canvas2d.h"
#include <vector>

gerenciadorCamadas::gerenciadorCamadas(int grossuraBordasLateraisNasCamadas, int bordaMenuLateralX, int screenHeight)
{
    borda1X = grossuraBordasLateraisNasCamadas;
    borda1Y = grossuraBordasLateraisNasCamadas;
    borda2X = bordaMenuLateralX;
    borda2Y = screenHeight - grossuraBordasLateraisNasCamadas;
    width = borda2X - borda1X;
    height = borda2Y - borda1Y;
    pintando = 0;
    qntCamadas = 0;
}

void gerenciadorCamadas::carregaCamada(unsigned char *data, int imgWidth, int imgHeight){
    Camada novaCamada;
    novaCamada.camada = new unsigned char[width * height * 4];
    int i, j, posRGBA, posRGB;
    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            posRGBA = (i * width + j) * 4;
            novaCamada.camada[posRGBA] = 1;
            novaCamada.camada[posRGBA + 1] = 1;
            novaCamada.camada[posRGBA + 2] = 1;
            novaCamada.camada[posRGBA + 3] = 0;
        }
    }

    for(i = 0; i < imgHeight; i++){
        for(j = 0; j < imgWidth; j++){
            posRGBA = ((width * height / 2 + width / 2) - (imgHeight * width / 2 + imgWidth / 2) + (i * width + j)) * 4; // carrega no centro
            posRGB = (i * imgWidth + j) * 3;
            novaCamada.camada[posRGBA] = data[posRGB];
            novaCamada.camada[posRGBA+1] = data[posRGB+1];
            novaCamada.camada[posRGBA+2] = data[posRGB+2];
            novaCamada.camada[posRGBA+3] = 1;
        }
    }
    camadas.push_back(novaCamada);
    qntCamadas++;
    camadaAtiva = qntCamadas - 1;
}

void gerenciadorCamadas::render(){
    int i, j, posRGBA, deslocX = borda1X, deslocY = borda1Y;
    float r, g, b;
    for(Camada camada : camadas){
        for(i = 0; i < height; i++){
            for(j = 0; j < width; j++){
                posRGBA = (i * width + j) * 4;
                r = camada.camada[posRGBA];
                g = camada.camada[posRGBA+1];
                b = camada.camada[posRGBA+2];
                if(camada.camada[posRGBA+3] == 1){ // � visivel
                    CV::color(r / 255, g / 255, b / 255);
                    CV::rectFill(j + deslocX, i + deslocY, j + deslocX + 1, i + deslocY + 1);
                }
            }
        }
    }
    renderBotaoCamada();
}

bool gerenciadorCamadas::verificaMouseCamada(int mouseX, int mouseY){
    if(mouseX > borda1X && mouseX < borda2X && mouseY > borda1Y && mouseY < borda2Y){
        return 1;
    }
    return 0;
}

void gerenciadorCamadas::setPintando(bool valor){
    pintando = valor;
}

bool gerenciadorCamadas::getPintando(){
    return pintando;
}

void gerenciadorCamadas::addBotaoCamada(int camadaAtiva, int screenWidth, int screenHeight, int inicioMenuLateralX){
    BotaoCamadas novoBotao;
    novoBotao.borda1X = inicioMenuLateralX + 30;
    novoBotao.borda1Y = screenHeight * (camadaAtiva) / 20 + 20;
    novoBotao.borda2X = screenWidth - 10;
    novoBotao.borda2Y = novoBotao.borda1Y + 30;
    novoBotao.moveCima.borda1X = novoBotao.borda1X - 15;
    novoBotao.moveCima.borda1Y = novoBotao.borda1Y + 16;
    novoBotao.moveCima.borda2X = novoBotao.borda1X - 2;
    novoBotao.moveCima.borda2Y = novoBotao.borda2Y;
    novoBotao.moveCima.cima = 1;

    novoBotao.moveBaixo.borda1X = novoBotao.borda1X - 15;
    novoBotao.moveBaixo.borda1Y = novoBotao.borda1Y;
    novoBotao.moveBaixo.borda2X = novoBotao.borda1X - 2;
    novoBotao.moveBaixo.borda2Y = novoBotao.moveBaixo.borda1Y + 14;
    novoBotao.moveBaixo.cima = 0;

    novoBotao.bordaHideX = (novoBotao.borda1X * 2 + novoBotao.borda2X * 8) / 10;

    novoBotao.posCamada = camadaAtiva;
    novoBotao.visivel = 1;
    char nome[50];
    sprintf(nome, "Camada %d", camadaAtiva + 1);
    strcpy(novoBotao.nome, nome);
    botaoCamadas.push_back(novoBotao);
}

void gerenciadorCamadas::renderBotaoSwitch(BotaoSwitch botaoSwitch){
    CV::color(0.3, 0.3, 0.3);
    CV::rectFill(botaoSwitch.borda1X, botaoSwitch.borda1Y, botaoSwitch.borda2X, botaoSwitch.borda2Y);
    CV::color(1, 1, 1);
    float vector1X[3] = {botaoSwitch.borda1X, (botaoSwitch.borda1X + botaoSwitch.borda2X)/2, botaoSwitch.borda2X};
    float vector1Y[3] = {botaoSwitch.borda1Y, botaoSwitch.borda2Y, botaoSwitch.borda1Y};
    float vector2X[3] = {botaoSwitch.borda1X, (botaoSwitch.borda1X + botaoSwitch.borda2X)/2, botaoSwitch.borda2X};
    float vector2Y[3] = {botaoSwitch.borda2Y, botaoSwitch.borda1Y, botaoSwitch.borda2Y};
    if(botaoSwitch.cima == 1){
        CV::polygonFill(vector1X, vector1Y, 3);
    }
    else{
        CV::polygonFill(vector2X, vector2Y, 3);
    }
}

void gerenciadorCamadas::renderBotaoCamada(){
    for(BotaoCamadas botaoCamada : botaoCamadas){
        CV::color(0.3, 0.3, 0.3);
        CV::rectFill(botaoCamada.borda1X, botaoCamada.borda1Y, botaoCamada.borda2X, botaoCamada.borda2Y);
        CV::color(1, 1, 1);
        if(camadaAtiva == botaoCamada.posCamada){
            CV::rect(botaoCamada.borda1X, botaoCamada.borda1Y, botaoCamada.borda2X, botaoCamada.borda2Y);
        }
        renderBotaoSwitch(botaoCamada.moveCima);
        renderBotaoSwitch(botaoCamada.moveBaixo);
        CV::color(0, 0, 0);
        CV::line(botaoCamada.bordaHideX, botaoCamada.borda1Y, botaoCamada.bordaHideX, botaoCamada.borda2Y);
        CV::color(1, 1, 1);
        CV::text(botaoCamada.bordaHideX + 7, (botaoCamada.borda1Y + botaoCamada.borda2Y) /2 - 2, "Hide");

        CV::text(botaoCamada.borda1X + 5, (botaoCamada.borda1Y + botaoCamada.borda2Y) /2 - 2, botaoCamada.nome);
    }
}

int gerenciadorCamadas::getQntCamadas(){
    return qntCamadas;
}