#include "Animator.h"



Animator::Animator()
{
	m_activeStateName = "";
	m_activeStateInfo = nullptr;

	m_animationSpeed = 1.0f;
	m_delay = 0.5f;
	m_elapsedTime = 0.0f;

	m_currentFrame = 0;
	m_lastFrame = 0;

	m_loop = false;
	m_animIsPlaying = false;

	m_timeToChangeFrame = m_delay / m_animationSpeed;
}


Animator::~Animator()
{
}


void Animator::SetSprite(sf::Sprite & sprite)
{
	m_sprite = &sprite;
}


bool Animator::AddAnimationState(std::string name, TextureAtlas & atlas, size_t begin, size_t end, bool autoPlay)
{
	m_statesIterator = m_states.find(name);
	if (m_statesIterator == m_states.end())
	{
		m_states.insert
		(
			std::pair <std::string,
			AnimationStateInfo>(name, AnimationStateInfo() =
			{
				&atlas, begin, end
			})
		);

		if (autoPlay)
			ChangeActiveState(name);

		return true;
	}
	return false;
}


bool Animator::ChangeActiveState(const std::string & name)
{
	if (m_sprite == nullptr)
	{
		return false;
	}

	m_statesIterator = m_states.find(name);
	if (m_statesIterator == m_states.end())
		return false;

	m_activeStateName = m_statesIterator->first;
	m_activeStateInfo = &m_statesIterator->second;

	m_currentFrame = m_activeStateInfo->beg;
	m_lastFrame = m_activeStateInfo->end;

	m_activeStateInfo->atlas->SetSpriteTextureByIndex(*m_sprite, m_activeStateInfo->beg);
	m_animIsPlaying = true;

	return true;
}


std::string Animator::GetActiveState() const
{
	return m_activeStateName;
}


void Animator::SetAnimationSpeed(float speed)
{
	m_animationSpeed = speed;

	if (m_animationSpeed < 0.0001f)
		m_animationSpeed = 0.0001f;

	m_timeToChangeFrame = m_delay / m_animationSpeed;
}


void Animator::SetDelayBetweenFrames(float delay)
{
	m_delay = delay;
	if (m_delay < 0.0f)
		m_delay = 0.0f;

	m_timeToChangeFrame = m_delay / m_animationSpeed;
}


void Animator::SetLoop(bool loop)
{
	m_loop = loop;
}


void Animator::Animate(float dt)
{
	if (!m_animIsPlaying)
		return;

	m_elapsedTime += dt;

	if (m_elapsedTime > m_timeToChangeFrame)
	{
		m_currentFrame++;
		if (m_currentFrame > m_lastFrame)
		{
			if (m_loop)
				m_currentFrame = m_activeStateInfo->beg;
			else
			{
				m_currentFrame = m_activeStateInfo->end;
				m_animIsPlaying = false;
			}
		}

		m_activeStateInfo->atlas->SetSpriteTextureByIndex(*m_sprite, m_currentFrame);
		m_elapsedTime = 0.f;
	}
}


bool Animator::IsPlaying()
{
	return m_animIsPlaying;
}


void Animator::Play()
{
	m_animIsPlaying = true;
}


void Animator::Pause()
{
	m_animIsPlaying = false;
}


void Animator::Stop()
{
	ChangeActiveState(m_activeStateName);
	Pause();
}
