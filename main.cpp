#include "main.h"

#pragma region "Bibliothèques"//{

#if __has_include("bibliotheque_cours.hpp")
#include "bibliotheque_cours.hpp"
#define BIBLIOTHEQUE_COURS_INCLUS
using bibliotheque_cours::cdbg;
#else
auto& cdbg = clog;
#endif

#if __has_include("verification_allocation.hpp")
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"
#endif

void initialiserBibliothequeCours([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	#ifdef BIBLIOTHEQUE_COURS_INCLUS
	bibliotheque_cours::activerCouleursAnsi();
	#endif
}

using namespace std;
using namespace std::literals;
using namespace iter;
using namespace gsl;

#pragma endregion//}


/* ITÉRATEURS */
/* ITÉRATEUR LISTE HISTORIQUE */
template <typename T>
IterateurConcretListeHistorique<T>::IterateurConcretListeHistorique(const_iterator iterateur):
	iterateur_(iterateur)
{}

template <typename T>
string IterateurConcretListeHistorique<T>::nomElementParcouru() const
{
	return iterateur_->getNom();
}

template <typename T>
int IterateurConcretListeHistorique<T>::prioriteElementParcouru() const
{
	return iterateur_->getPriorite();
}

template <typename T>
bool IterateurConcretListeHistorique<T>::finIterateur() const
{
	return false;
}

template <typename T>
void IterateurConcretListeHistorique<T>::prochainElement() const
{

}

template <typename T>
void IterateurConcretListeHistorique<T>::reinitialiser() const
{

}

/* ITÉRATEUR LISTE COURANTE */
template <typename T>
IterateurConcretListeCourante<T>::IterateurConcretListeCourante(const_iterator iterateur) :
	iterateur_(iterateur)
{}

template <typename T>
string IterateurConcretListeCourante<T>::nomElementParcouru() const
{
	return iterateur_->getNom();
}

template <typename T>
int IterateurConcretListeCourante<T>::prioriteElementParcouru() const
{
	return iterateur_->getPriorite();
}

template <typename T>
bool IterateurConcretListeCourante<T>::finIterateur() const
{
	return false;
}

template <typename T>
void IterateurConcretListeCourante<T>::prochainElement() const
{

}

template <typename T>
void IterateurConcretListeCourante<T>::reinitialiser() const
{

}


/* LISTE D'OBJECTIFS */
/* LISTE D'OBJECTIFS COURANTS */
template <typename T>
ListeObjectifsCourants<T>::ListeObjectifsCourants(vector<T> objectifsInitiaux)
{
	//? Nous parcourons les objectifs initiaux et les ajoutons à notre liste d'objectifs
	for (T& objectif : objectifsInitiaux)
		objectifs_.push_back(objectif);
}

template <typename T>
size_t ListeObjectifsCourants<T>::nElements() const
{
	//? Retourne la taille du vecteur des objectifs
	return objectifs_.size();
}

template <typename T>
void ListeObjectifsCourants<T>::ajouterObjectif(T objectif)
{
	//? On ajoute l'objectif en paramètres aux objectifs
	objectifs_.push_back(move(objectif));
}

template <typename T>
void ListeObjectifsCourants<T>::supprimerObjectif(const T& objectif)
{
	//? Nous parcourons la liste d'objectifs et effaçons l'objectif qui correspond à celui transmis en paramètres
	for (size_t i : range(objectifs_.size()))
		if (objectifs_[i] == objectif)
			objectifs_.erase(objectifs_.begin() + i);
}

template <typename T>
T& ListeObjectifsCourants<T>::operator[](const int index) const
{
	return objectifs_[index];
}


/* LISTE D'OBJECTIFS PASSÉS */
template <typename T>
ListeObjectifsPasses<T>::ListeObjectifsPasses(std::vector<T> objectifsInitiaux)
{
	//? Nous parcourons les objectifs initiaux et les ajoutons à notre liste d'objectifs
	for (T& objectif : objectifsInitiaux)
		objectifs_.push_back(objectif);
}

template <typename T>
size_t ListeObjectifsPasses<T>::nElements() const
{
	//? Retourne la taille du vecteur des objectifs
	return objectifs_.size();
}

template <typename T>
void ListeObjectifsPasses<T>::ajouterObjectif(T objectif)
{
	//? On ajoute l'objectif en paramètres aux objectifs
	objectifs_.push_back(objectif);
}

template <typename T>
void ListeObjectifsPasses<T>::supprimerObjectif(const T& objectif)
{
	//? Nous parcourons la liste d'objectifs et effaçons l'objectif qui correspond à celui transmis en paramètres
	for (size_t i : range(objectifs_.size()))
		if (*objectifs_[i] == objectif) { //? Déréférencement du unique_ptr pour avoir l'objectif brut
			objectifs_[i].reset(); //? Nous relâchons la mémoire avant de détruire la case du vector
			objectifs_.erase(objectifs_.begin() + i); //? Nous enlevons la case associée au pointeur intelligent (maintenant à nullptr)
		}
}

template <typename T>
T& ListeObjectifsPasses<T>::operator[](const int index) const 
{
	return objectifs_[index];
}

/* OBJECTIF */
Objectif::Objectif(string nom, int priorite) :
	nom_(nom), priorite_(priorite)
{}

string Objectif::getNom() const
{
	return nom_;
}

int Objectif::getPriorite() const
{
	return priorite_;
}

bool Objectif::operator==(const Objectif& autre)
{
	//? Si le nom ET la priorité sont les mêmes, nous retournons true
	return(nom_ == autre.nom_ && priorite_ == autre.priorite_);
}

int main(int argc, char* argv[])
{
	initialiserBibliothequeCours(argc, argv);
	
	/* PARTIE PREMIÈRE --- TESTONS LES MÉTHODES ET L'IMPLÉMENTATION DES LISTES D'OBJECTIFS */

	//? 1. Créons une liste d'objectifs courants qui possède l'objectif de développer la dynamique et la justesse des notes
	
	//? 1.1 Nous créons d'abord un vector qui contiendra l'objectif initial en vue de la création de la liste des objectifs courants
	vector<Objectif> listeObjectifsInitiaux = {
		{ "justesse", prioriteObjectifJustesse }
	};

	//? 1.2.1. Création de la liste des objectifs courants à partir de l'objectif initial
	ListeObjectifsCourants listeObjectifsCourants{ listeObjectifsInitiaux };

	//? 1.2.2. Vérifions que la création a bien été effectuée en comptant le nombre d'objectifs présents --> devrait afficher 1
	cout << "1.2.2. -> Vérification de la création de la liste d'objectifs courants:\nNombre d'objectif(s) initial(aux): " << listeObjectifsCourants.nElements() << endl;

	//? 1.3.1. Nous ajoutons à présent le second objectif à la liste d'objectifs courants, soit la dynamique
	Objectif dynamique{ "dynamique", prioriteObjectifDynamique };
	listeObjectifsCourants.ajouterObjectif(dynamique);

	//? 1.3.2. Vérifions que l'ajout a bien été effectué en comptant le nombre d'objectifs présents --> devrait afficher 2
	cout << "\n1.3.2. -> Vérification de l'ajout d'un objectif dans la liste d'objectifs courants:\nNombre d'objectifs: " << listeObjectifsCourants.nElements() << endl;
	

	//? 2. Créons une liste d'objectifs passés, soit le rythme, la hauteur des notes et les accentuations

	//? 2.1 Nous créons d'abord un vector qui contiendra les objectifs passés (déjà dans la base de données),
	//?		en vue de la création de la liste des objectifs passés
	vector<Objectif> listeObjectifsHistorique = {
		{ "rythme",				prioriteObjectifRythme			},
		{ "hauteur des notes",	prioriteObjectifHauteurNotes	},
		{ "accentuations",		prioriteObjectifAccentuations	}
	};

	//? 2.2. Création de la liste des objectifs passés à partir des objectifs passés
	ListeObjectifsPasses listeObjectifsPasses{ listeObjectifsHistorique };


	//? 3. Estimons que l'élève, à la suite de multiples séances, ait terminé de travailler sur l'objectif de la dynamique
	//? 3.1.1. Créons une copie de l'objectif à enlever pour itérer correctement (nous aurions pu itérer selon l'index ou seulement le nom/la
	//?		   priorité de l'objectif à rechercher. Nous avons simplement choisi de faire une recherche par copie.
	Objectif objectifTermine{ "dynamique", prioriteObjectifDynamique };

	//? 3.1.2. Retirons l'objectif de la liste d'objectifs courants (normalement, cette étape est opérée à partir d'un contrôleur d'objectifs)
	listeObjectifsCourants.supprimerObjectif(objectifTermine);

	//? 3.1.3. Ajoutons l'objectifs à la liste d'objectifs passés	(normalement, cette étape est opérée à partir d'un contrôleur d'objectifs)
	listeObjectifsPasses.ajouterObjectif(objectifTermine);

	//? 3.2. Vérifions si la délétion et l'ajout ont bien été effecutés --> devrait afficher 1 comme objectif courant et 4 comme objectifs passés
	cout << "\n3.2. -> Objectifs courants suite à la délétion d'un objectif:\nNombre d'objectif: " << listeObjectifsCourants.nElements() << endl;
	cout << "\n3.2. -> Objectifs passés suite à l'ajout d'un objectif:\nNombre d'objectifs: " << listeObjectifsPasses.nElements() << endl;


	/* PARTIE SECONDE --- TESTONS LES MÉTHODES ET L'IMPLÉMENTATION DES ITÉRATEURS */
	auto iterateur = listeObjectifsPasses.creerIterateur();
	cout << iterateur->getNom() << endl;
}
