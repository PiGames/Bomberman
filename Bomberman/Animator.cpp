#include "Animator.h"
​
​
​
Animator::Animator()
{
}
​
​
Animator::~Animator()
{
}
​
​
void Animator::SetSprite(sf::Sprite & sprite)
{
	sprite = m_sprite;
}
​
bool Animator::AddAnimationState(std::string name, const TextureAtlas & atlas, const size_t & begin, const size_t & end)
{ // TODO powinieneś dodać stan do mapy, a nie tworzyć tylko 1
	if (!name.empty())
	{
		m_states.insert[name];
		TextureAtlas m_atlas = atlas;
		m_states[name]->atlas = &m_atlas;
		m_states[name]->beg = begin;
		m_states[name]->end = end;
​
		return true;
	}
	return false;
}
​
​
bool Animator::ChangeActiveState(const std::string & name)
{
	auto search = m_states.find(name); // TODO antypattern!
	if (search != m_states.end())
	{
		m_currentstate = name;
		return true;
	}
	else
		return false;
}
​
​
std::string Animator::GetActiveState() const
{
	return m_currentstate;
}
​
​
void Animator::SetAnimationSpeed(const float & speed)
{
	m_delay = 10.f;
	m_frames = speed * m_delay;
}
​
​
void Animator::SetDelayBetweenFrames(const float & delay)
{
	m_delay = delay;
}
​
​
void Animator::SetLoop(bool loop)
{
	m_loop = loop;
}
​
​
void Animator::Animate(const float & dt)
{ // TODO kamilos fixup needed
	/*if (dt >= m_delay)
	{
​
		size_t begin = m_states[m_currentstate]->beg;
		size_t end = m_states[m_currentstate]->end;
		if (m_loop)
		{
			while (0)
			{
				for (int i = begin; i < end; i++)
				{
					m_sprite.setTexture(m_atlas.SetSpriteTextureByIndex);
				}
			}
		}
		else if(!m_loop)
		{
			for (int i = begin; i < end; i++)
			{
				m_sprite.setTexture(m_atlas.SetSpriteTextureByIndex);
			}
		}
	}*/
}
