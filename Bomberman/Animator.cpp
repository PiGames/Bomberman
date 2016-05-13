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
		sprite któremu nale¿y aktualizowaæ wyœwietlan¹ teksturê
	*/
}

bool Animator::AddAnimationState(std::string name, const TextureAtlas & atlas, const size_t & begin, const size_t & end)
{
	// TODO tworzenie nowego stanu animacji
	/*
		Dodanie nowego stanu animacji, np "bieg", "stanie" itd
		Jako parametr otrzymuje referencjê na atlas tekstur z zakresem indeksów dla danej animacji 
		(jeden atlas mo¿e mieæ np animacje dla wszystkich stanów gracza, inny dla bomby, etc)
		indeksy s¹ ³¹cznie, tzn end to wci¹¿ indeks nale¿¹cy do danej animacji stanu

		polecam u¿yæ mapê i strukturê opisuj¹c¹ stan animacji AnimationStateInfo
	*/
	return false;
}


bool Animator::ChangeActiveState(const std::string & name)
{
	// TODO zmiana aktywnego stanu
	/*
		np z biegania na podan¹ przez argument
		false, je¿eli stan z argumentu nie istnieje
	*/
	return false;
}


std::string Animator::GetActiveState() const
{
	// TODO aktywny stan
	/*
		po prostu zwracasz aktywnie odtwarzan¹ animacjê
	*/
	return std::string();
}


void Animator::SetAnimationSpeed(const float & speed)
{
	// TODO prêdkoœæ animacji
	/*
		zmienia prêdkoœæ odtwarzania animacji, tzn 1.0 to domyœlna wartoœæ 
		i przy np speed = 1 i delay = 10 kolejne klatki animacji odtwarza co 10 sekund
		przy speed = 0.5f i delay = 10 kolejne klatki animacji zmieniaj¹ siê co 15 sekund
		speed = 1.5f i delay = 10 zmiana klatki nastêpuje co 5sekund

		mniejsza wartoœæ to wiêksze spowolnienie animacji, wiêksze to przeyspieszenie
	*/
}


void Animator::SetDelayBetweenFrames(const float & delay)
{
	// TODO czas pomiêdzy klatkami
	/*
		bazowy czas pomiêdzy klatkami animacji w sekundach
	*/
}


void Animator::SetLoop(bool loop)
{
	// TODO zapêtlenie animacji
	/*
		czy animacja ma siê zapêtlaæ, tzn je¿eli true
		to po narysowaniu ostatniej klatki animacji
		animacja powinna zacz¹æ siê od pocz¹tku,

		je¿eli false to powinna siê zatrzymaæ
	*/

}


void Animator::Animate(const float & dt)
{
	// TODO Animate
	/*
		Aktualizacja obecnie wyœwietlanej klatki animacji
		UWAGA! nie potrzebujesz Clocka do sprawdzenia, czy powinieneœ zmieniæ
		obecnie wyœwietlan¹ klatkê, wystarczy ci zliczanie dt
	*/
}
