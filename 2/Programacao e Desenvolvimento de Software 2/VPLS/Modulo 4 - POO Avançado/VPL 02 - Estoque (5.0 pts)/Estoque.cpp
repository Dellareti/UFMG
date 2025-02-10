#include <string>

#include "Estoque.hpp"

#include <iostream>
#include <algorithm>

void Estoque::add_mercadoria(const std::string& mercadoria, unsigned int qtd)
{
	if (estoque_.find(mercadoria) == estoque_.end())
	{
		estoque_[mercadoria] = qtd;
	}
	else
	{
		estoque_[mercadoria] += qtd;
	}
}

void Estoque::sub_mercadoria(const std::string& mercadoria, unsigned int qtd)
{
	if (estoque_.find(mercadoria) == estoque_.end())
	{
		std::cout << mercadoria << " inexistente" << std::endl;
	}
	else if (estoque_[mercadoria] < qtd)
	{
		std::cout << mercadoria << " insuficiente" << std::endl;
	}
	else
	{
		estoque_[mercadoria] -= qtd;
	}
}

unsigned int Estoque::get_qtd(const std::string& mercadoria) const
{
	if (estoque_.find(mercadoria) == estoque_.end())
	{
		return 0;
	}
	return estoque_.at(mercadoria);
}

void Estoque::imprime_estoque() const
{
	for (auto& produto : estoque_)
	{
		std::cout << produto.first << ", " << produto.second << std::endl;
	}
}

Estoque& Estoque::operator +=(const Estoque& rhs)
{
	for (auto &prod : rhs.estoque_)
	{
		add_mercadoria(prod.first, prod.second);
	}
	return *this;
}

Estoque& Estoque::operator -=(const Estoque& rhs)
{
	for (auto& produto : estoque_)
	{
		sub_mercadoria(produto.first, rhs.get_qtd(produto.first));
	}
	return *this;
}

bool operator <(Estoque& lhs, Estoque& rhs)
{
	auto menor = lhs.estoque_.size() < rhs.estoque_.size() ? &lhs : &rhs;
	return std::all_of(menor->estoque_.begin(), menor->estoque_.end(), [rhs, lhs](const std::pair<std::string, unsigned int>& p)
	{
		return lhs.get_qtd(p.first) < rhs.get_qtd(p.first) && lhs.get_qtd(p.first) != 0;
	});
}

bool operator >(Estoque& lhs, Estoque& rhs)
{
	auto menor = lhs.estoque_.size() < rhs.estoque_.size() ? &lhs : &rhs;
	return std::all_of(menor->estoque_.begin(), menor->estoque_.end(), [rhs, lhs](const std::pair<std::string, unsigned int>& p)
	{
		return lhs.get_qtd(p.first) > rhs.get_qtd(p.first) && lhs.get_qtd(p.first) != 0;
	});
}
