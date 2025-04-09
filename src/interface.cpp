//*********************************************************
//
// classe para fazer o carregamento de arquivos no formato BMP
// Autor: Cesar Tadeu Pozzer
//        pozzer@inf.ufsm.br
//  Versao 09/2010
//
//**********************************************************

#include "Interface.h"
#include <string.h>
#include "gl_canvas2d.h"

#define posBotoesClick 8.5/10
#define larguraBotoesClick 46
#define alturaBotoesClick 30
#define distanciaEntreBotoesClick 5

Interface::Interface(int screenWidth, int screenHeight)
{
    bordaMenuLateralX = screenWidth * 3 / 4;
    grossuraBordasLateraisNasCamadas = 10;
    inicioMenuLateralX = bordaMenuLateralX + grossuraBordasLateraisNasCamadas;
    tamanhoLadoQuadradosFundo = 10;
    borda1X = grossuraBordasLateraisNasCamadas;
    borda1Y = grossuraBordasLateraisNasCamadas;
    borda2X = bordaMenuLateralX;
    borda2Y = screenHeight - grossuraBordasLateraisNasCamadas;

    submenuArquivos.aberto = 0;
    tamanhoBotaoArquivos = 10;
    qntArquivos = 0;
    carregarNomeArquivos();

    botaoAddImagem.borda1X = inicioMenuLateralX + 5;
    botaoAddImagem.borda1Y = screenHeight * 9 / 10;
    botaoAddImagem.borda2X = screenWidth - 5;
    botaoAddImagem.borda2Y = botaoAddImagem.borda1Y + 30;
    botaoAddImagem.tem_borda = 1;

    clicar.borda1X = inicioMenuLateralX + 5;
    clicar.borda1Y = screenHeight * posBotoesClick;
    clicar.borda2X = clicar.borda1X + larguraBotoesClick;
    clicar.borda2Y = clicar.borda1Y + alturaBotoesClick;
    clicar.tem_borda = 1;

    pincel.borda1X = clicar.borda2X + distanciaEntreBotoesClick;
    pincel.borda1Y = screenHeight * posBotoesClick;
    pincel.borda2X = pincel.borda1X + larguraBotoesClick;
    pincel.borda2Y = pincel.borda1Y + alturaBotoesClick;
    pincel.tem_borda = 0;

    spray.borda1X = pincel.borda2X + distanciaEntreBotoesClick;
    spray.borda1Y = screenHeight * posBotoesClick;
    spray.borda2X = spray.borda1X + larguraBotoesClick;
    spray.borda2Y = spray.borda1Y + alturaBotoesClick;
    spray.tem_borda = 0;

    marcaTexto.borda1X = spray.borda2X + distanciaEntreBotoesClick;
    marcaTexto.borda1Y = screenHeight * posBotoesClick;
    marcaTexto.borda2X = marcaTexto.borda1X + larguraBotoesClick;
    marcaTexto.borda2Y = marcaTexto.borda1Y + alturaBotoesClick;
    marcaTexto.tem_borda = 0;

    balde.borda1X = marcaTexto.borda2X + distanciaEntreBotoesClick;
    balde.borda1Y = screenHeight * posBotoesClick;
    balde.borda2X = balde.borda1X + larguraBotoesClick;
    balde.borda2Y = balde.borda1Y + alturaBotoesClick;
    balde.tem_borda = 0;

    borracha.borda1X = balde.borda2X + distanciaEntreBotoesClick;
    borracha.borda1Y = screenHeight * posBotoesClick;
    borracha.borda2X = borracha.borda1X + larguraBotoesClick;
    borracha.borda2Y = borracha.borda1Y + alturaBotoesClick;
    borracha.tem_borda = 0;

    sliderR.inicioX = inicioMenuLateralX + 5;
    sliderR.fimX = balde.borda2X - 10;
    sliderR.Y = screenHeight * 8 / 10;
    sliderR.valorMinimo = 0;
    sliderR.valorMaximo = 255;
    sliderR.valorAtual = 255;
    sliderR.segurando = 0;

    sliderG.inicioX = inicioMenuLateralX + 5;
    sliderG.fimX = balde.borda2X - 10;
    sliderG.Y = sliderR.Y - 30;
    sliderG.valorMinimo = 0;
    sliderG.valorMaximo = 255;
    sliderG.valorAtual = 0;
    sliderG.segurando = 0;

    sliderB.inicioX = inicioMenuLateralX + 5;
    sliderB.fimX = balde.borda2X - 10;
    sliderB.Y = sliderG.Y - 30;
    sliderB.valorMinimo = 0;
    sliderB.valorMaximo = 255;
    sliderB.valorAtual = 0;
    sliderB.segurando = 0;

    sliderRaio.inicioX = inicioMenuLateralX + 5;
    sliderRaio.fimX = balde.borda2X - 10;
    sliderRaio.Y = sliderB.Y - 30;
    sliderRaio.valorMinimo = 1;
    sliderRaio.valorMaximo = 50;
    sliderRaio.valorAtual = 10;
    sliderRaio.segurando = 0;

    botaoSelecionado = 0;
    raioCor = 10;
    RGBA[0] = 255;
    RGBA[1] = 0;
    RGBA[2] = 0;
    RGBA[3] = 1;
}

void Interface::render(int screenWidth, int screenHeight){
    renderFundo();
    CV::color(0.3, 0.3, 0.3);
    CV::rectFill(bordaMenuLateralX, 0, bordaMenuLateralX + grossuraBordasLateraisNasCamadas, screenHeight);
    CV::rectFill(0, 0, bordaMenuLateralX, grossuraBordasLateraisNasCamadas);
    CV::rectFill(0, 0, grossuraBordasLateraisNasCamadas, screenHeight);
    CV::rectFill(0, screenHeight - grossuraBordasLateraisNasCamadas, bordaMenuLateralX, screenHeight);
    CV::color(0.5, 0.5, 0.5);
    CV::rectFill(inicioMenuLateralX, 0, screenWidth, screenHeight);
    renderBotaoAdd();
    renderBotaoClicar();
    renderBotaoPincel();
    renderBotaoSpray();
    renderBotaoMarcaTexto();
    renderBotaoBalde();
    renderBotaoBorracha();
    renderSliderR();
    renderSliderG();
    renderSliderB();
    renderSliderRaio();
    renderPreviewCor(screenWidth);

    if(submenuArquivos.aberto){
        renderSubmenuArquivos();
    }
}

int Interface::getBordaMenuLateralX(){
    return bordaMenuLateralX;
}

int Interface::getGrossuraBordasLaterais(){
    return grossuraBordasLateraisNasCamadas;
}

void Interface::renderFundo(){
    int i, j;
    int linha = 0, coluna;
    for(i = borda1Y; i < borda2Y; i += tamanhoLadoQuadradosFundo){
        coluna = 0;
        for(j = borda1X; j < borda2X; j += tamanhoLadoQuadradosFundo){
            if((linha + coluna)%2==0){
                CV::color(0.8, 0.8, 0.8);
            }
            else{
                CV::color(0.4, 0.4, 0.4);
            }
            CV::rectFill(j, i, j + tamanhoLadoQuadradosFundo, i + tamanhoLadoQuadradosFundo);
            coluna++;
        }
        linha++;
    }
}

void Interface::renderBotao(BOTAO botao){
    CV::color(0.3, 0.3, 0.3);
    CV::rectFill(botao.borda1X, botao.borda1Y, botao.borda2X, botao.borda2Y);

    if(botao.tem_borda){
        CV::color(0.9, 0.9, 0.9);
        CV::rect(botao.borda1X, botao.borda1Y, botao.borda2X, botao.borda2Y);
    }

}

bool Interface::verificaClickBotao(BOTAO botao, int mouseX, int mouseY){
    if(mouseX > botao.borda1X && mouseX < botao.borda2X && mouseY > botao.borda1Y && mouseY < botao.borda2Y){
        return 1;
    }
    return 0;
}

void Interface::renderBotaoAdd(){
    renderBotao(botaoAddImagem);
    CV::color(0.9, 0.9, 0.9);
    CV::text(botaoAddImagem.borda1X + 5, (botaoAddImagem.borda1Y + botaoAddImagem.borda2Y) /2 - 2, "Adicionar uma imagem/camada");
}

void Interface::renderBotaoClicar(){
    renderBotao(clicar);
    CV::color(0.9, 0.9, 0.9);
    CV::text(clicar.borda1X + 5, (clicar.borda1Y + clicar.borda2Y) /2 - 2, "Clck");
}

void Interface::renderBotaoPincel(){
    renderBotao(pincel);
    CV::color(0.9, 0.9, 0.9);
    CV::text(pincel.borda1X + 5, (pincel.borda1Y + pincel.borda2Y) /2 - 2, "Pncl");
}

void Interface::renderBotaoSpray(){
    renderBotao(spray);
    CV::color(0.9, 0.9, 0.9);
    CV::text(spray.borda1X + 5, (spray.borda1Y + spray.borda2Y) /2 - 2, "Spry");
}

void Interface::renderBotaoMarcaTexto(){
    renderBotao(marcaTexto);
    CV::color(0.9, 0.9, 0.9);
    CV::text(marcaTexto.borda1X + 5, (marcaTexto.borda1Y + marcaTexto.borda2Y) /2 - 2, "mcTx");
}

void Interface::renderBotaoBalde(){
    renderBotao(balde);
    CV::color(0.9, 0.9, 0.9);
    CV::text(balde.borda1X + 5, (balde.borda1Y + balde.borda2Y) /2 - 2, "Blde");
}

void Interface::renderBotaoBorracha(){
    renderBotao(borracha);
    CV::color(0.9, 0.9, 0.9);
    CV::text(borracha.borda1X + 5, (borracha.borda1Y + borracha.borda2Y) /2 - 2, "Eras");
}

BOTAO Interface::getBotaoAddImagem(){
    return botaoAddImagem;
}

BOTAO Interface::getBotaoClicar(){
    return clicar;
}

BOTAO Interface::getBotaoPincel(){
    return pincel;
}

BOTAO Interface::getBotaoSpray(){
    return spray;
}

BOTAO Interface::getBotaoMarcaTexto(){
    return marcaTexto;
}

BOTAO Interface::getBotaoBalde(){
    return balde;
}

BOTAO Interface::getBotaoBorracha(){
    return borracha;
}

void Interface::alteraBotaoSelecionado(int botaoSelecionado){
    this->botaoSelecionado = botaoSelecionado;
    clicar.tem_borda = 0;
    pincel.tem_borda = 0;
    spray.tem_borda = 0;
    marcaTexto.tem_borda = 0;
    balde.tem_borda = 0;
    borracha.tem_borda = 0;

    switch(botaoSelecionado){
        case 0:
            clicar.tem_borda = 1;
            break;
        case 1:
            pincel.tem_borda = 1;
            break;
        case 2:
            spray.tem_borda = 1;
            break;
        case 3:
            marcaTexto.tem_borda = 1;
            break;
        case 4:
            balde.tem_borda = 1;
            break;
        case 5:
            borracha.tem_borda = 1;
            break;
    }
}

void Interface::carregarNomeArquivos(){
    struct dirent *entry;
    DIR *dp = opendir(".\\Trab1GabrielBaggio\\images");

    if (dp == nullptr)
        printf("Erro ao abrir diretorio das imagens, ajeitar nos diretorios do windows pra ficar certo");
    int cont = 0;
    while ((entry = readdir(dp))){
        if(cont > 1){
            BotaoArquivo novoBotao;
            novoBotao.deltaY = tamanhoBotaoArquivos * qntArquivos;
            novoBotao.nome = entry->d_name;
            botaoArquivos.push_back(novoBotao);
            qntArquivos++;
        }
        cont++;
    }

    closedir(dp);
}

void Interface::renderSubmenuArquivos(){
    int i = 0;
    CV::color(0.2, 0.2, 0.2);
    CV::rectFill(submenuArquivos.borda1X, submenuArquivos.borda1Y, submenuArquivos.borda2X, submenuArquivos.borda2Y);
    CV::color(1, 1, 1);
    for(BotaoArquivo botaoArquivo : botaoArquivos){
        CV::text(submenuArquivos.borda1X, submenuArquivos.borda1Y + botaoArquivo.deltaY, botaoArquivo.nome.c_str());
        i++;
    }
}

void Interface::setAbertoSubmenuArquivos(bool aberto, int mouseX, int mouseY){
    submenuArquivos.aberto = aberto;
    submenuArquivos.borda1X = mouseX;
    submenuArquivos.borda1Y = mouseY - qntArquivos * 10;
    submenuArquivos.borda2X = mouseX + 150;
    submenuArquivos.borda2Y = mouseY;
}

bool Interface::getAbertoSubmenuArquivos(){
    return submenuArquivos.aberto;
}

Submenu Interface::getSubmenuArquivos(){
    return submenuArquivos;
}

bool Interface::verificaClickSubmenu(Submenu submenu, int mouseX, int mouseY){
    if(mouseX > submenu.borda1X && mouseX < submenu.borda2X && mouseY > submenu.borda1Y && mouseY < submenu.borda2Y){
        return 1;
    }
    return 0;
}

std::string Interface::verificaArquivoParaAbrir(int mouseX, int mouseY){
    int i = 0;
    for(BotaoArquivo botaoArquivo : botaoArquivos){
        if(mouseX > submenuArquivos.borda1X - 2 && mouseX < submenuArquivos.borda2X + 2 && mouseY > submenuArquivos.borda1Y + botaoArquivo.deltaY - 2 && mouseY < submenuArquivos.borda1Y + botaoArquivo.deltaY + tamanhoBotaoArquivos + 2){
            return botaoArquivo.nome;
        }
    }
    return botaoArquivos[0].nome;
}

int Interface::getBotaoSelecionado(){
    return botaoSelecionado;
}

void Interface::setBotaoSelecionado(int botaoSelecionado){
    this->botaoSelecionado = botaoSelecionado;
}

unsigned char *Interface::getRGBA(){
    return RGBA;
}

int Interface::getRaioCor(){
    return raioCor;
}

void Interface::renderSlider(Slider slider){
    CV::color(0.3, 0.3, 0.3);
    CV::rectFill(slider.inicioX, slider.Y, slider.fimX + 10, slider.Y + 10);
    CV::color(0.9, 0.9, 0.9);
    CV::rectFill(slider.inicioX + (slider.fimX - slider.inicioX) * (slider.valorAtual - slider.valorMinimo) / (slider.valorMaximo - slider.valorMinimo), slider.Y, slider.inicioX + (slider.fimX - slider.inicioX) * (slider.valorAtual - slider.valorMinimo) / (slider.valorMaximo - slider.valorMinimo) + 10, slider.Y + 10);
}

void Interface::renderSliderR(){
    renderSlider(sliderR);
    CV::color(0.9, 0.9, 0.9);
    CV::text(sliderR.inicioX, sliderR.Y + 15, "R: ");
    CV::text(sliderR.fimX - 30, sliderR.Y + 15, std::to_string(sliderR.valorAtual).c_str());
}
void Interface::renderSliderG(){
    renderSlider(sliderG);
    CV::color(0.9, 0.9, 0.9);
    CV::text(sliderG.inicioX, sliderG.Y + 15, "G: ");
    CV::text(sliderG.fimX - 30, sliderG.Y + 15, std::to_string(sliderG.valorAtual).c_str());
}
void Interface::renderSliderB(){
    renderSlider(sliderB);
    CV::color(0.9, 0.9, 0.9);
    CV::text(sliderB.inicioX, sliderB.Y + 15, "B: ");
    CV::text(sliderB.fimX - 30, sliderB.Y + 15, std::to_string(sliderB.valorAtual).c_str());
}

void Interface::renderSliderRaio(){
    renderSlider(sliderRaio);
    CV::color(0.9, 0.9, 0.9);
    CV::text(sliderRaio.inicioX, sliderRaio.Y + 15, "Raio: ");
    CV::text(sliderRaio.fimX - 30, sliderRaio.Y + 15, std::to_string(sliderRaio.valorAtual).c_str());
}

bool Interface::verificaSegurandoSlider(Slider slider, int mouseX, int mouseY){
    if(mouseX > slider.inicioX && mouseX < slider.fimX + 10 && mouseY > slider.Y && mouseY < slider.Y + 10){
        return 1;
    }
    return 0;
}

Slider Interface::getSliderR(){
    return sliderR;
}
Slider Interface::getSliderG(){
    return sliderG;
}
Slider Interface::getSliderB(){
    return sliderB;
}
Slider Interface::getSliderRaio(){
    return sliderRaio;
}

void Interface::setSegurandoR(bool segurando){
    sliderR.segurando = segurando;
}
void Interface::setSegurandoG(bool segurando){
    sliderG.segurando = segurando;
}
void Interface::setSegurandoB(bool segurando){
    sliderB.segurando = segurando;
}
void Interface::setSegurandoRaio(bool segurando){
    sliderRaio.segurando = segurando;
}

bool Interface::getSegurandoR(){
    return sliderR.segurando;
}

bool Interface::getSegurandoG(){
    return sliderG.segurando;
}

bool Interface::getSegurandoB(){
    return sliderB.segurando;
}

bool Interface::getSegurandoRaio(){
    return sliderRaio.segurando;
}

void Interface::mudaValorSliderR(int mouseX){
    int valor = (sliderR.valorMaximo - sliderR.valorMinimo) * (mouseX - sliderR.inicioX) / (sliderR.fimX - sliderR.inicioX) + sliderR.valorMinimo;
    if(valor > sliderR.valorMaximo){
        valor = 255;
    }
    if(valor < sliderR.valorMinimo){
        valor = 0;
    }
    sliderR.valorAtual = valor;
    RGBA[0] = valor;
}

void Interface::mudaValorSliderG(int mouseX){
    int valor = (sliderG.valorMaximo - sliderG.valorMinimo) * (mouseX - sliderG.inicioX) / (sliderG.fimX - sliderG.inicioX) + sliderG.valorMinimo;
    if(valor > sliderG.valorMaximo){
        valor = 255;
    }
    if(valor < sliderG.valorMinimo){
        valor = 0;
    }
    sliderG.valorAtual = valor;
    RGBA[1] = valor;
}

void Interface::mudaValorSliderB(int mouseX){
    int valor = (sliderB.valorMaximo - sliderB.valorMinimo) * (mouseX - sliderB.inicioX) / (sliderB.fimX - sliderB.inicioX) + sliderB.valorMinimo;
    if(valor > sliderB.valorMaximo){
        valor = 255;
    }
    if(valor < sliderB.valorMinimo){
        valor = 0;
    }
    sliderB.valorAtual = valor;
    RGBA[2] = valor;
}

void Interface::mudaValorSliderRaio(int mouseX){
    int valor = (sliderRaio.valorMaximo - sliderRaio.valorMinimo) * (mouseX - sliderRaio.inicioX) / (sliderRaio.fimX - sliderRaio.inicioX) + sliderRaio.valorMinimo;
    if(valor > sliderRaio.valorMaximo){
        valor = 50;
    }
    if(valor < sliderRaio.valorMinimo){
        valor = 1;
    }
    sliderRaio.valorAtual = valor;
    raioCor = valor;
}

void Interface::renderPreviewCor(int screenWidth){
    CV::color(0.3, 0.3, 0.3);
    CV::rect(sliderRaio.fimX + 15, sliderRaio.Y, screenWidth - 5, sliderR.Y + 15);
    CV::color((float)RGBA[0] / 255, (float)RGBA[1] / 255, (float)RGBA[2] / 255);
    CV::rectFill(sliderRaio.fimX + 15, sliderRaio.Y, screenWidth - 5, sliderR.Y + 15);
}