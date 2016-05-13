#include "TextureAtlas.h"



TextureAtlas::TextureAtlas()
{
}


TextureAtlas::~TextureAtlas()
{
}


bool TextureAtlas::LoadFromFile(const std::string & path)
{
	// TODO wczytywanie tekstury z pliku
	/*
		tutaj musz wczytaæ teksturê z pliku do jakiejœ prywantj tekstury,
		zwracasz true je¿eli wszystko posz³o ok,
		false je¿eli coœ jest nie tak
		np.
		return m_texture.LoadFromFile(path);
	*/
	return false;
}


bool TextureAtlas::TrimByGrid(const size_t & cellSizeX, const size_t & cellSizeY)
{
	// TODO dzielenie tekstury na czêœci
	/*
		Raczej "dzielenie", tak naprawdê wci¹¿ powinieneœ mieæ w tej klasie tylko 1 obiekt tekstury
		a ta metoda powinna raczej czy szerokoœæ i wysokoœæ wczeœniej wczytanej tekstury 
		jest podzielna przez podane w argumentach szerokoœæ i wysokoœæ (powinna te¿ ustawiaæ pola
		odpawiadaj¹ce za rozmiar komórek, iloœæ poszczególnych tekstur, ...
		true jezeli da sie podzielic
		false je¿eli nie
	*/

	return false;
}


size_t TextureAtlas::GetCount() const
{
	// TODO ilosc tekstur w atlasie
	/*
		o ile wyliczy³eœ wczeœniej w TrimByGrid, to tutaj po prostu zwracasz t¹ wartoœæ
	*/
	return size_t();
}


size_t TextureAtlas::GetCellSizeX() const
{
	// TODO szerokosc pojedynczej tekstury
	/*
		zwracasz szerokosc pojedynczej tekstur, inaczej param cellSizeX z TrimByGrid
	*/
	return size_t();
}


size_t TextureAtlas::GetCellSizeY() const
{
	// TODO wysokosc pojedynczej tekstury
	/*
		analogiczna sytuacja do tej z GetCellSizeX()
	*/
	return size_t();
}


void TextureAtlas::SetSpriteTextureByIndex(sf::Sprite & sprite, size_t index)
{
	// TODO ustawianie sprite'owi tekstury
	/*
		Ustawiasz spriteowi odpowidni fragment tektury sugeruj¹c siê indeksem
		coœ w stylu sprite.setTextureRect(...)
		jedyny "problem" to przeliczenie jednowymiarowego indeksu na dwuwymiarowy obszar
		(coœ w stylu przeliczania indeksu tablicy jednowymiarowej na dwuwymiarow¹)
		potrzebujesz tutaj szerokoœci, wysokoœci komórki i samego indeksu podanego jako parametr
	*/
}
