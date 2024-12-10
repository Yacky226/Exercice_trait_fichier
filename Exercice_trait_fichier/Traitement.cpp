#include "Traitement.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cctype>
#include <iomanip>


using namespace std;

void Traitement::charger(std::string nomfile)
{
    ifstream f(nomfile);
    if (!f) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << nomfile << endl;
        return;
    }
    string line;
    while (getline(f, line)) 
    {
        // Nettoyer la ligne ,supprimer ponctuation et diviser en mots
        line.erase(remove_if(line.begin(), line.end(), [](char c) {
            return ispunct(static_cast<unsigned char>(c));
            }), line.end());

        stringstream chaine(line);
        string mot;
        while (chaine >> mot) 
        {
            ch.push_back(mot);
        }
    }
    f.close();
}

void Traitement::Trier() {
    sort(ch.begin(), ch.end());
}

void Traitement::afficher() 
{
    for (const auto& x : ch) 
    {
        cout << x << endl;
    }
}

void Traitement::renverser()
{
    reverse(ch.begin(), ch.end());
}

void Traitement::remove_word(const string& word) 
{
    ch.erase(remove(ch.begin(), ch.end(), word), ch.end());
}

void Traitement::replace_word(const string& word, const string& wordR) 
{
    for (auto& token : ch)
    {
        if (token == word) {
            token = wordR;
        }
    }
}

int Traitement::count_word(const string& word)
{
    int count = 0;

    // Créer une copie locale de "word" et convertir en minuscule
    string word_lower = word;
    transform(word_lower.begin(), word_lower.end(), word_lower.begin(), ::tolower);

    // Parcourir chaque mot du vecteur
    for (auto w : ch)
    {
        // Créer une copie  de chaque mot de ch et le convertir en minuscule
        transform(w.begin(), w.end(), w.begin(), ::tolower);
        if (w == word_lower)
            count++;
    }

    return count;
}


void Traitement::write_file(const string& file_name)
{
    ofstream F(file_name);
    if (!F) {
        cerr << "Erreur d'ouverture du fichier : " << file_name << endl;
        return;
    }
    for (const auto& word : ch) {
        F << word << '\n';
    }
    F.close();
}

void Traitement::analyserTexte(const std::string& nomFichier) 
{
  
        // Ouvrir le fichier
        std::ifstream fichier(nomFichier);
        if (!fichier) {
            cerr << "Erreur : Impossible d'ouvrir le fichier " << nomFichier << std::endl;
            return;
        }

        string ligne;
        while (getline(fichier, ligne)) 
{
            // Nettoyer la ligne (supprimer ponctuation et diviser en mots)
            ligne.erase(remove_if(ligne.begin(), ligne.end(), [](char c) {
                return ispunct(static_cast<unsigned char>(c));
                }), ligne.end());

            stringstream chaine(ligne);
            string mot;
            while (chaine >> mot)
            {
                ch.push_back(mot);
                // Convertir le mot en minuscules
                std::transform(mot.begin(), mot.end(), mot.begin(), ::tolower);

                // Comptabiliser le mot
                ++statsMots[mot];
                ++totalMots;
            }
        }
        fichier.close();

        // Afficher les statistiques globales
        cout << "Analyse du texte : " << nomFichier << std::endl;
        cout << "---------------------------------" << std::endl;
        cout << "Nombre total de mots : " << totalMots << std::endl;
        cout << "Nombre de mots uniques : " << statsMots.size() << std::endl;
        
        // Trier les mots par fréquence
        vector<pair<string, int>> mots(statsMots.begin(), statsMots.end());

        sort(mots.begin(), mots.end(), [](const auto& a, const auto& b) {
            return a.second >b.second; // Ordre décroissant de fréquence
            });

        // Afficher les mots les plus fréquents
        cout << "\nLes mots les plus frequents :\n";
        for (size_t i = 0; i < min(size_t(10), mots.size()); ++i) 
        {
               cout << mots[i].first << " : " << mots[i].second
                << " (" << std::setprecision(3)
                << (mots[i].second * 100.0 / totalMots) << "%)" << std::endl;
        }
    }
