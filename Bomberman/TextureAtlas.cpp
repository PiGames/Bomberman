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
		tutaj musz wczyta� tekstur� z pliku do jakiej� prywantj tekstury,
		zwracasz true je�eli wszystko posz�o ok,
		false je�eli co� jest nie tak
		np.
		return m_texture.LoadFromFile(path);
	*/
	return false;
}


bool TextureAtlas::TrimByGrid(const size_t & cellSizeX, const size_t & cellSizeY)
{
	// TODO dzielenie tekstury na cz�ci
	/*
		Raczej "dzielenie", tak naprawd� wci�� powiniene� mie� w tej klasie tylko 1 obiekt tekstury
		a ta metoda powinna raczej czy szeroko�� i wysoko�� wcze�niej wczytanej tekstury 
		jest podzielna przez podane w argumentach szeroko�� i wysoko�� (powinna te� ustawia� pola
		odpawiadaj�ce za rozmiar kom�rek, ilo�� poszczeg�lnych tekstur, ...
		true jezeli da sie podzielic
		false je�eli nie
	*/

	return false;
}


size_t TextureAtlas::GetCount() const
{
	// TODO ilosc tekstur w atlasie
	/*
		o ile wyliczy�e� wcze�niej w TrimByGrid, to tutaj po prostu zwracasz t� warto��
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
		Ustawiasz spriteowi odpowidni fragment tektury sugeruj�c si� indeksem
		co� w stylu sprite.setTextureRect(...)
		jedyny "problem" to przeliczenie jednowymiarowego indeksu na dwuwymiarowy obszar
		(co� w stylu przeliczania indeksu tablicy jednowymiarowej na dwuwymiarow�)
		potrzebujesz tutaj szeroko�ci, wysoko�ci kom�rki i samego indeksu podanego jako parametr
	*/
}
