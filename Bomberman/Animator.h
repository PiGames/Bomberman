#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <map>
#include <iostream>

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
	bool AddAnimationState(std::string name, TextureAtlas& atlas, size_t begin, size_t end, bool autoPlay=false);


	/// Change active state of animation
	/// <param name="name">name of animation state</param>
	/// <returns>true OK</returns>
	/// <returns>false state doesn't exist</returns>
	bool ChangeActiveState(const std::string& name);


	/// Get Current Playing anim state
	std::string GetActiveState() const;


	/// Set animation speed, default: 1.0f
	/// <param name="speed">anim speed, from .0f</param>
	void SetAnimationSpeed(float speed);


	/// Set base time needed to change frame
	/// <param name="delay">time in seconds</param>
	void SetDelayBetweenFrames(float delay);


	/// Sets animation looping
	/// <param name="loop">looping animation</param>
	void SetLoop(bool loop);


	/// Updates animation state
	/// <param name="dt">delta time</param>
	void Animate(float);


	/// Check anim playing state
	/// <returns>TRUE is playing</returns>
	bool IsPlaying();


	/// Resume animation
	void Play();


	/// Pause animation
	void Pause();


	/// Stop animation and set current frame to 0
	void Stop();

private:
	struct AnimationStateInfo
	{
		TextureAtlas* atlas;
		size_t beg; // first frame (inclusive)
		size_t end; // last frame (inclusive)
	};

	std::map<std::string, AnimationStateInfo> m_states;
	std::map<std::string, AnimationStateInfo>::iterator m_statesIterator;

	std::string m_activeStateName;
	AnimationStateInfo* m_activeStateInfo;

	float m_animationSpeed;
	float m_delay;
	float m_elapsedTime;
	float m_timeToChangeFrame;

	size_t m_currentFrame;
	size_t m_lastFrame;

	bool m_loop;
	bool m_animIsPlaying;

	sf::Sprite* m_sprite;
};

