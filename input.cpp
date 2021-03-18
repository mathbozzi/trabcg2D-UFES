#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <time.h>
#include "input.h"
#include "oponente.h"
#include "arena.h"
#include "circulo.h"
#include "lutador.h"
#include "tinyxml2.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

using namespace tinyxml2;
using namespace std;

extern Arena *arenaSVG;
extern Lutador *lutadorPrincipal;
extern Oponente *lutadorOponente;

const Color BLACK = {0, 0, 0};
const Color BLUE = {0, 0, 1};
const Color CYAN = {0, 1, 1};
const Color DARK_GRAY = {0.2, 0.2, 0.2};
const Color GRAY = {0.5, 0.5, 0.5};
const Color GREEN = {0, 1, 0};
const Color LIGHT_GRAY = {0.9, 0.9, 0.9};
const Color MAGENTA = {1, 0, 1};
const Color RED = {1, 0, 0};
const Color WHITE = {1, 1, 1};
const Color YELLOW = {1, 1, 0};

string parseXMLFile(string filePath)
{

  XMLDocument configFile;

  configFile.LoadFile(filePath.c_str());

  if (configFile.ErrorID() != 0)
    cout << "Erro no arquivo de entrada config.xml" << endl;
  else
  {

    XMLElement *adaElement = configFile.FirstChildElement("aplicacao")->FirstChildElement("arquivoDaArena");
    string name = adaElement->Attribute("nome");
    string type = adaElement->Attribute("tipo");
    string path = adaElement->Attribute("caminho");

    return path + name + "." + type;
  }
  return "";
}

Color parseColor(string color)
{
  if (color == "black")
    return BLACK;
  else if (color == "blue")
    return BLUE;
  else if (color == "green")
    return GREEN;
  else if (color == "cyan")
    return CYAN;
  else if (color == "red")
    return RED;
  else if (color == "magenta")
    return MAGENTA;
  else if (color == "yellow")
    return YELLOW;

  return WHITE;
}

void parseCircle(XMLElement *c, int i)
{

  float cx, cy, r;
  c->QueryFloatAttribute("cx", &cx);
  c->QueryFloatAttribute("cy", &cy);
  c->QueryFloatAttribute("r", &r);

  string fill = c->Attribute("fill");
  // string id = c->Attribute("id");

  Point center = {cx, cy};
  Color fillColor = parseColor(fill);

  // Circulo *circ = new Circulo(center, r, fillColor);
  // lutadorSVG = circ;

  if (i == 1)
  {
    lutadorPrincipal = new Lutador(center, r, fillColor, 0);
  }
  else
  {
    lutadorOponente = new Oponente(center, r, fillColor,0);
  }
}

void parseRect(XMLElement *ret)
{

  float x, y, width, height;
  ret->QueryFloatAttribute("x", &x);
  ret->QueryFloatAttribute("y", &y);
  ret->QueryFloatAttribute("width", &width);
  ret->QueryFloatAttribute("height", &height);
  string fill = ret->Attribute("fill");
  Color fillColor = parseColor(fill);

  Arena *arena = new Arena(x, y, width, height, fillColor);

  arenaSVG = arena;
}

void parseSVGFile(string filePath)
{

  XMLDocument arenaFile;

  arenaFile.LoadFile(filePath.c_str());

  if (arenaFile.ErrorID() != 0)
    cout << "Erro no arquivo de entrada config.xml" << endl;
  else
  {
    XMLElement *svgElement = arenaFile.FirstChildElement("svg");

    XMLElement *next = svgElement->FirstChildElement();

    int i = 0;
    while (next != NULL)
    {
      string tagType = next->Value();

      if (tagType == "rect")
      {
        parseRect(next);
      }
      else if (tagType == "circle")
      {
        parseCircle(next, i);
        i = i + 1;
      }
      next = next->NextSiblingElement();
    }
  }
}
