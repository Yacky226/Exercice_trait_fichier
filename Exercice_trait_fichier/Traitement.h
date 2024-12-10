#pragma once
#include <vector>
#include<string>
#include<map>
#include<iostream>
class Traitement
{
private:
	std::vector<std::string>ch{};
	// Variables pour les statistiques
	std::map<std::string, int> statsMots; // Comptage des mots
	int totalMots = 0;
public:
	void charger(std::string F);
	void Trier();
	void afficher();
	void renverser();
	void remove_word(const std::string &word);
	void replace_word(const std::string &word,const  std::string &wordR);
	int count_word(const std::string &word);
	void write_file(const std::string &file_name);
	void analyserTexte(const std::string& nomFichier);

};

