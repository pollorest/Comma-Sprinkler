#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

string palabra;
int nodos = 0;
map<string, int> palabras;
vector<bool> numero_comas(0);
vector<int> comas_completadas;
vector<string> texto_ingresado;
vector<bool> puntos;
vector<vector<int> > lados;

void colas(int nodo) {
    queue<int> cola;
    cola.push(nodo);
    while (!cola.empty()) {
        int arr = cola.front();
        cola.pop();
        if (!numero_comas[arr]) {
            numero_comas[arr] = true;
            for (int i = 0; i < lados[arr].size(); i++)
                cola.push(lados[arr][i]);
        }
    }
}

int main() {
    cin.tie(0);
    cout.tie(0);
    bool primera = true;
    while (cin >> palabra) {
        bool punto = false, coma = false;
        if (palabra.back() == ',') {
            palabra.pop_back();
            coma = true;
        } else if (palabra.back() == '.') {
            palabra.pop_back();
            punto = true;
        }
        if (palabras.find(palabra) == palabras.end())
            palabras[palabra] = nodos++;
        int indice1 = palabras[palabra];
        if (coma)
            comas_completadas.push_back(indice1);
        if (primera || puntos.back()) {
            primera = false;
            texto_ingresado.push_back(palabra);
            puntos.push_back(punto);
            continue;
        }
        texto_ingresado.push_back(palabra);
        puntos.push_back(punto);
    }
    lados.assign(2 * nodos, vector<int>(0));
    numero_comas.assign(2 * nodos, false);
    for (int i = 1; i < texto_ingresado.size(); i++) {
        int a = palabras[texto_ingresado[i]];
        int b = palabras[texto_ingresado[i - 1]];
        if (puntos[i - 1])
            continue;
        lados[2 * b + 1].push_back(2 * a);
        lados[2 * a].push_back(2 * b + 1);
    }
    for (int i = 0; i < comas_completadas.size(); i++)
        colas(2 * comas_completadas[i] + 1);
    for (int i = 0; i < texto_ingresado.size(); i++) {
        cout << texto_ingresado[i];
        int indice2 = palabras[texto_ingresado[i]];
        if (puntos[i])
            cout << ".";
        else if (numero_comas[2 * indice2 + 1])
            cout << ",";
        if (i + 1 < texto_ingresado.size())
            cout << " ";
    }
}