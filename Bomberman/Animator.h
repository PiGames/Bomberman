#pragma once
#include <SFML\System\Time.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <string>
#include <map>

#include "TextureAtlas.h"

class Animator
{
public:
	Animator();
	~Animator();

	/// Sets sprite to update
	/// <param name="sprite">reference to animation sprite</param>
	void SetSprite(sf::Sprite& sprite);


	/// Creates new animation state
	/// <param name="name">name of created animation state</param>
	/// <param name="atlas">reference to atlas</param>
	/// <param name="begin">beginning index of state's animation in atlas</param>
	/// <param name="end">ending index of state's animation in atlas</param>
	/// <returns>true OK</returns>
	/// <returns>false cannot add animation</returns>
	bool AddAnimationState(std::string name, const TextureAtlas& atlas, const size_t& begin, const size_t& end);
	
	
	/// Change active state of animation
	/// <param name="name">name of animation state</param>
	/// <returns>true OK</returns>
	/// <returns>false state doesn't exist</returns>
	bool ChangeActiveState(const std::string& name);


	/// Get Current Playing anim state
	std::string GetActiveState() const;

	
	/// Set animation speed, defuault: 1.0f
	/// <param name="speed">anim speed, from .0f</param>
	void SetAnimationSpeed(const float& speed);


	/// Set base time needed to change frame
	/// <param name="delay">time in seconds</param>
	void SetDelayBetweenFrames(const float& delay);


	/// Sets animation looping
	/// <param name="loop">looping animation</param>
	void SetLoop(bool loop);
	

	/// Updates animation state
	/// <param name="dt">delta time</param>
	void Animate(const float& dt);

private:
	struct AnimationStateInfo
	{
		TextureAtlas* atlas;
		size_t beg;
		size_t end;
	};

	std::map<std::string, AnimationStateInfo> m_states;
	std::map<std::string, AnimationStateInfo>::iterator it;

	sf::Sprite m_sprite;
	std::string m_currentState;
	TextureAtlas m_atlas;

	float m_animationSpeed;
	float m_delay;
	float m_frames;
	float m_elapsedTime;

	int m_currentFrame;
	int m_lastFrame;

	bool m_loop;
	bool m_animIsPlaying;
};

