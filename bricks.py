// Animator::Animator()
{
	m_activeStateName = "";
	m_activeStateInfo = nullptr;

	m_animationSpeed = 1.0f;
	m_delay = 0.5f;
	m_elapsedTime = 0.0f;
Bomb::Bomb(bool setColor)
	:m_state(State::waitingForExplosion),
	m_isMoving(false)
{
	m_detonationClock.restart();
	m_rays.resize(4);

	if (!m_soundBuffer.loadFromFile("data/expl.wav"))
	{
		std::cerr << "[!] Cannot load resource: 'data/expl.wav'" << std::endl;
		std::cin.get();
		std::exit(1);
	}

	m_explosionSound.setBuffer(m_soundBuffer);

	m_currentFrame = 0;
	m_lastFrame = 0;

	m_loop = false;
	m_animIsPlaying = false;

	m_timeToChangeFrame = m_delay / m_animationSpeed;
}
