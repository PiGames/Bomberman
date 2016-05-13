#include "Animator.h"



Animator::Animator()
{
}


Animator::~Animator()
{
}


void Animator::SetSprite(sf::Sprite & sprite)
{
	// TODO ustawianie sprite'a
	/*
		sprite kt�remu nale�y aktualizowa� wy�wietlan� tekstur�
	*/
}

bool Animator::AddAnimationState(std::string name, const TextureAtlas & atlas, const size_t & begin, const size_t & end)
{
	// TODO tworzenie nowego stanu animacji
	/*
		Dodanie nowego stanu animacji, np "bieg", "stanie" itd
		Jako parametr otrzymuje referencj� na atlas tekstur z zakresem indeks�w dla danej animacji 
		(jeden atlas mo�e mie� np animacje dla wszystkich stan�w gracza, inny dla bomby, etc)
		indeksy s� ��cznie, tzn end to wci�� indeks nale��cy do danej animacji stanu

		polecam u�y� map� i struktur� opisuj�c� stan animacji AnimationStateInfo
	*/
	return false;
}


bool Animator::ChangeActiveState(const std::string & name)
{
	// TODO zmiana aktywnego stanu
	/*
		np z biegania na podan� przez argument
		false, je�eli stan z argumentu nie istnieje
	*/
	return false;
}


std::string Animator::GetActiveState() const
{
	// TODO aktywny stan
	/*
		po prostu zwracasz aktywnie odtwarzan� animacj�
	*/
	return std::string();
}


void Animator::SetAnimationSpeed(const float & speed)
{
	// TODO pr�dko�� animacji
	/*
		zmienia pr�dko�� odtwarzania animacji, tzn 1.0 to domy�lna warto�� 
		i przy np speed = 1 i delay = 10 kolejne klatki animacji odtwarza co 10 sekund
		przy speed = 0.5f i delay = 10 kolejne klatki animacji zmieniaj� si� co 15 sekund
		speed = 1.5f i delay = 10 zmiana klatki nast�puje co 5sekund

		mniejsza warto�� to wi�ksze spowolnienie animacji, wi�ksze to przeyspieszenie
	*/
}


void Animator::SetDelayBetweenFrames(const float & delay)
{
	// TODO czas pomi�dzy klatkami
	/*
		bazowy czas pomi�dzy klatkami animacji w sekundach
	*/
}


void Animator::SetLoop(bool loop)
{
	// TODO zap�tlenie animacji
	/*
		czy animacja ma si� zap�tla�, tzn je�eli true
		to po narysowaniu ostatniej klatki animacji
		animacja powinna zacz�� si� od pocz�tku,

		je�eli false to powinna si� zatrzyma�
	*/

}


void Animator::Animate(const float & dt)
{
	// TODO Animate
	/*
		Aktualizacja obecnie wy�wietlanej klatki animacji
		UWAGA! nie potrzebujesz Clocka do sprawdzenia, czy powiniene� zmieni�
		obecnie wy�wietlan� klatk�, wystarczy ci zliczanie dt
	*/
}
