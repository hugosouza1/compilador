#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

#include "../lexico/tokenHandler.hpp"
#include "gramatica.hpp"

int analisadorSintatico(vector<tabelaToken>& tabela);