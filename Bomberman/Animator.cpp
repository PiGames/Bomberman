#include "Animator.h"



Animator::Animator()
{
}


Animator::~Animator()
{
}


void Animator::SetSprite(sf::Sprite & sprite)
{
	sprite = m_sprite;
}

bool Animator::AddAnimationState(std::string name, const TextureAtlas & atlas, const size_t & begin, const size_t & end)
{
	it = m_states.find(name);
	if ((!name.empty()) && !(it!=m_states.end()))
	{
		m_states.insert(std::pair <std::string, AnimationStateInfo>(name, AnimationStateInfo()));
		TextureAtlas m_atlas = atlas;
		m_states[name].atlas = &m_atlas;
		m_states[name].beg = begin;
		m_states[name].end = end;

		return true;
	}
	return false;
}


bool Animator::ChangeActiveState(const std::string & name)
{
	it = m_states.find(name);
	if (it != m_states.end())
	{
		m_currentstate = name;
		return true;
	}
	else
		return false;
}


std::string Animator::GetActiveState() const
{
	return m_currentstate;
}


void Animator::SetAnimationSpeed(const float & speed)
{
	m_animationspeed = speed;
	m_delay = 10.f;
	m_frames = speed * m_delay;
}


void Animator::SetDelayBetweenFrames(const float & delay)
{
	m_delay = delay;
}


void Animator::SetLoop(bool loop)
{
	m_loop = loop;
}


void Animator::Animate(const float & dt)
{
	int m_currentFrame = m_states[m_currentstate].beg; //first frame
	int end = m_states[m_currentstate].end; //last frame

	if (!m_animIsPlaying)
		return;

	m_elapsedTime += dt;

	float m_speed = 1 / m_animationspeed;

	if (m_elapsedTime > m_delay* m_speed)
	{
		m_atlas.SetSpriteTextureByIndex(m_sprite, m_currentFrame);
		m_elapsedTime = 0.f;

		m_currentFrame++;
		if (m_currentFrame == end)
		{
			if (m_loop)
				m_currentFrame = m_states[m_currentstate].beg;
			else
				m_animIsPlaying = false;
		}
	}
}