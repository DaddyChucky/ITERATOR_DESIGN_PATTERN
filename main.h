#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <gsl/span>
#include <cppitertools/range.hpp>
#include <cppitertools/enumerate.hpp>

/* CONSTANTES */
constexpr int prioriteObjectifDynamique		= 0;
constexpr int prioriteObjectifJustesse		= 1;
constexpr int prioriteObjectifRythme		= 2;
constexpr int prioriteObjectifHauteurNotes	= 3;
constexpr int prioriteObjectifAccentuations = 4;

/* ITÉRATEURS */
/* ITÉRATEUR ABSTRAIT */
template <typename T>
class IterateurAbstrait
{
public:
	virtual std::string			nomElementParcouru()		const = 0;
	virtual int					prioriteElementParcouru()	const = 0;
	virtual bool				finIterateur()				const = 0;
	virtual void				prochainElement()			const = 0;
	virtual void				reinitialiser()				const = 0;
	~IterateurAbstrait()										  = default;
};


/* ITÉRATEUR LISTE HISTORIQUE */
template <typename T>
class IterateurConcretListeHistorique : public IterateurAbstrait<T>
{
	typedef const std::vector<T>::const_iterator const_iterator;
	const const_iterator iterateur_;

public:
	IterateurConcretListeHistorique(const_iterator);
	std::string	nomElementParcouru()		const override;
	int			prioriteElementParcouru()	const override;
	bool		finIterateur()				const override;
	void		prochainElement()			const override;
	void		reinitialiser()				const override;
};

/* ITÉRATEUR LISTE COURANTE */
template <typename T>
class IterateurConcretListeCourante : public IterateurAbstrait<T>
{
	typedef const std::vector<T>::const_iterator const_iterator;
	const const_iterator iterateur_;

public:
	IterateurConcretListeCourante(const_iterator);
	std::string	nomElementParcouru()		const override;
	int			prioriteElementParcouru()	const override;
	bool		finIterateur()				const override;
	void		prochainElement()			const override;
	void		reinitialiser()				const override;
};


/* LISTE D'OBJECTIFS */
/* LISTE D'OBJECTIFS ABSTRAITE */
template <typename T>
class ListeObjectifsAbstraite
{
public: 
	typedef const std::vector<T>::const_iterator const_iterator;
	virtual const_iterator creerIterateur() const = 0;
	~ListeObjectifsAbstraite()							 = default;
};

/* LISTE D'OBJECTIFS COURANTS */
template <typename T>
class ListeObjectifsCourants : public ListeObjectifsAbstraite<T>
{
	std::vector<T> objectifs_;

public:
	ListeObjectifsCourants(std::vector<T>);
	typedef const std::vector<T>::const_iterator const_iterator;
	const_iterator	creerIterateur()		const override {
		return objectifs_.begin();
	}
	size_t								nElements()				const;
	void								ajouterObjectif(T);
	void								supprimerObjectif(const T&);
	T& operator[](const int) const;
};

/* LISTE D'OBJECTIFS PASSÉS */
template <typename T>
class ListeObjectifsPasses : public ListeObjectifsAbstraite<T>
{
	typedef const std::vector<T>::const_iterator const_iterator;

	std::vector<T> objectifs_;

public:
	ListeObjectifsPasses(std::vector<T>);
	const_iterator	creerIterateur()	const override {
		return objectifs_.begin();
	}
	size_t												nElements()			const;
	void												ajouterObjectif(T);
	void												supprimerObjectif(const T&);
	T& operator[](const int) const;
};


/* OBJECTIF */
class Objectif
{
	std::string nom_;
	int priorite_;

public:
	Objectif(std::string, int);
	bool operator==(const Objectif&);
	std::string		getNom()		const;
	int				getPriorite()	const;
};
