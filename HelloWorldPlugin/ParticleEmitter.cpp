//Nathan Alphonse 100523109
//100555192 Janarthan Ravikumar

#include <iostream> // for std::cout
//#include <cstring>
#include "AnimationMath.h"
#include "ParticleEmitter.h"
#include <algorithm>

ParticleEmitter::ParticleEmitter()
	: m_pParticles(nullptr),
	m_pNumParticles(0),
	m_lastAlive(nullptr)
//	playing(true),
//	interpolateColour(false)
{
    playing = true;
    interpolateColour = false;

    //Physics properties
    velocity0 = vec3<float>(-0.05f, -5.0f, -0.05f);
    velocity1 = vec3<float>(0.05f, 5.0f, 0.05f);
    emitterPosition = vec3<float>(0.f, 0.f, 0.f);
    boxWH = vec3<float>(50.0f);
    boxOn = false;
    //Steer properties                         
    taretgOn = false;
    fleeOn = false;
    magnetOn = false;
    repelOn = false;
    gravityOn = false;
    pathOn = false;

    targetPos = vec3<float>(0.0f);
    fleePos = vec3<float>(0.0f);
    magnetPos = vec3<float>(0.0f);
    repelPos = vec3<float>(0.0f);
    gravity = vec3<float>(0.0f, 1.0f, 0.0f);
    pathEnd = vec3<float>(0.0f);

    targetStrength = 0.0f;
    fleeStrength = 0.0f;
    magnetStrength = 0.0f;
    magnetRadius = 0.0f;
    repelStrength = 0.0f;
    repelRadius = 0.0f;

    // Range Properties
    colour0 = vec4<float>(1.0f, 0.0f, 0.0f, 1.0f);
    colour1 = vec4<float>(0.0f, 0.0f, 1.0f, 1.0f);
    lifeRange = vec2<float>(3.0f, 3.0f);
//    sizeRange = vec2<float>(1.0f, 1.0f);
    spawnRange = vec2<float>(50.0f, 50.0f);
    massRange = vec2<float>(0.5f, 0.75f);

  //  emitterName = "emitter";

    //other
    durationOn = true;
    durationRepeat = false;
    durationOnX_OffY = vec2<float>(0.0f, 0.0f);
    catmullT0 = vec3<float>(0);
    catmullT1 = vec3<float>(0);
    pathPointStrength = 0.0f;
    step = 7;
    showEmitter = true;
  //  circleSquare = true;

    keyframeController.doesSpeedControl = true;

    keyframeController.addKey(catmullT0);
    keyframeController.addKey(emitterPosition);
    keyframeController.addKey(pathEnd);
    keyframeController.addKey(catmullT1);

    keyframeController.calculateLookupTable(4);

  //  initialize(300); //change this to change trail amount
}

ParticleEmitter::~ParticleEmitter()
{
//	freeMemory();
}

void ParticleEmitter::initialize(unsigned int numParticles)
{
	freeMemory(); // destroy any existing particles

	if (numParticles > 0)
	{
		m_pParticles = new Particle[numParticles];
		memset(m_pParticles, 0, sizeof(Particle) * numParticles);
		m_pNumParticles = numParticles;
	}
//        emitterName = "emitter";
}
void ParticleEmitter::initializeOther(Particle* m_ptr, unsigned int numParticles)
{
	m_pParticles = m_ptr; // instead of creating it, we use from one existing array
	memset(m_pParticles, 0, sizeof(Particle) * numParticles);
	m_pNumParticles = numParticles;
}
void ParticleEmitter::moveM_ptr(Particle * m_ptr)
{
	Particle* oldM_ptr = m_pParticles;
	m_pParticles = m_ptr;

	// loop through each particle and replace
	Particle* particle = m_pParticles;
	for (unsigned int i = 0; i < m_pNumParticles; ++i, ++particle)
	{
		*particle = *(oldM_ptr + i);
	}
}
void ParticleEmitter::freeMemory()
{
	if (m_pParticles) // if not a null pointer
	{
		delete[] m_pParticles;
		m_pParticles = nullptr;
		m_pNumParticles = 0;
	}
}

void ParticleEmitter::update(float dt)
{
    // if any force is active, calulate forces
    if ((taretgOn) || (fleeOn) || (magnetOn) || (repelOn) || (gravityOn) || (pathOn)) {
        applyForcesToParticleSystem();
    }

    if (pathOn) {
        // All keyframe and tvalue management replaced with a single line of code!
        keyframeController.calculateLookupTable(step);
        interpolatedPosition = keyframeController.update(dt);

        keyframeController.setKey(0, catmullT0);
        keyframeController.setKey(1, emitterPosition);
        keyframeController.setKey(2, pathEnd);
        keyframeController.setKey(3, catmullT1);

//        pointHandles[0].position = emitterPosition;
//        pointHandles[1].position = pathEnd;
    }


    TotalT += dt;

	if (m_pParticles && playing) // make sure memory is initialized and system is playing
	{
		// loop through each particle
		Particle* particle = m_pParticles;
		for (unsigned int i = 0; i < m_pNumParticles; ++i, ++particle)
		{
            if (durationOn) {
				float randomTvalRate = ((float)((int)rand() % 101))/ 100.0f;//linearRand(0, 1);// Fix this
                float tempRate = Math::lerp(spawnRange.x, spawnRange.y, randomTvalRate);


                if (particle->life <= 0 && (TotalT >= (1 / tempRate))) // if particle has no life remaining
                {
                    vec3<float> tempEmitter = vec3<float>(0.f);

                    if (boxOn == true) {
						randomTvalRate = ((float)((int)rand() % 101)) / 100.0f;//linearRand(0.f, 1.f);
                        tempEmitter.x = Math::lerp(0.f - boxWH.x, boxWH.x, randomTvalRate);
						randomTvalRate = ((float)((int)rand() % 101)) / 100.0f;// linearRand(0.f, 1.f);
                        tempEmitter.y = Math::lerp(0.f - boxWH.y, boxWH.y, randomTvalRate);
						randomTvalRate = ((float)((int)rand() % 101)) / 100.0f;// linearRand(0.f, 1.f);
                        tempEmitter.z = Math::lerp(0.f - boxWH.z, boxWH.z, randomTvalRate);

                        //              std::cout << randomTvalRate <<":: "<< tempEmitter.x << " , " << tempEmitter.y << std::endl;
                    }

                    TotalT = 0;
                    // Respawn particle
                    // Note: we are not freeing memory, we are "Recycling" the particles
					float randomTval = ((float)((int)rand() % 101)) / 100.0f;// linearRand(0.0f, 1.0f);
                    if (gravityOn) {
                        particle->acceleration = vec3<float>(-9.8) * gravity;
                    }
                    else {
                        particle->acceleration = vec3<float>(0.0f);
                    }

                    particle->colour = Math::lerp(colour0, colour1, randomTval);
                    particle->life = Math::lerp(lifeRange.x, lifeRange.y, randomTval);
                    particle->mass = Math::lerp(massRange.x, massRange.y, randomTval);
                    particle->position = emitterPosition + tempEmitter;
                   // particle->size = Math::lerp(sizeRange.x, sizeRange.y, randomTval);
                    particle->velocity = Math::lerp(velocity0, velocity1, randomTval);

                }
				if(particle->life > 0 && lastAliveID <= i)// if particle is alive
				{
					m_lastAlive = particle; // set the last particle to this
					lastAliveID = i;
				}

            }// if duration end

                // Update physics
			if (particle->life > 0) // skip uneccesairy physics
			{
				// Update acceleration
				particle->acceleration = particle->force / particle->mass;
				particle->velocity = particle->velocity + (particle->acceleration * dt);
				//                particle->position = vec3<float>(parent->transform * vec4<float>(0, 0, 0, 1.0f)) + particle->velocity * dt;
				particle->position = particle->position + particle->velocity * dt;

				// We've applied the force, let's remove it so it does not get applied next frame
				particle->force = vec3<float>(0.0f);

				// Decrease particle life
				particle->life -= dt;

				// Update visual properties
//				if (interpolateColour)
//				{
//					// calculate t value
//					float tVal = Math::invLerp(particle->life, lifeRange.x, lifeRange.y);
//					particle->colour = Math::lerp(colour0, colour1, tVal);
//				}
				if (particle->life <= 0) { // if particle has no life remaining swap it with last alive
				
					if (particle != m_pParticles) {
						Particle temp;
						*(particle) = *(m_lastAlive);
						*m_lastAlive = temp;
						m_lastAlive--;
						lastAliveID--;
						// decrement loop so new swaped particle doesn't get missed
						i--;
						particle--;
					}
				}
			}// if particle->life > 0 end

		}// forloop end

	}// if playing end
}

bool ParticleEmitter::checkAllPartDead() {
    Particle* particle = m_pParticles;
    bool tempCheck = false;
	int lastDead = 0;
    for (unsigned int i = 0; i < m_pNumParticles; ++i, ++particle)
    {
        if (particle->life <= 0) { // if particle has no life

            tempCheck = true;
			lastDead = i;
        }
		else { // if something was dead before an alive particle
			if (tempCheck) { //swap the dead particles with the last alive particle
				Particle temp = *(m_pParticles+ lastDead);
				*(m_pParticles + lastDead) = *(m_lastAlive);
				*m_lastAlive = temp;
				m_lastAlive--;
				tempCheck = false;
			}
		}
    }
    return tempCheck;
}

void ParticleEmitter::draw()
{
}

void ParticleEmitter::applyForcesToParticleSystem()
{
    // TODO: implement seeking
    // Loop through each particle in the emitter and apply a seeking for to them

    vec3<float> seekVec, fleeVec, magVec, repelVec, pathVec;
    vec3<float> seekDirection, fleeDirection, magnetDirection, repelDirection, pathDirection;
    vec3<float> seekForce, fleeForce, magnetForce, repelForce, gravityForce, pathForce;


    for (int i = 0; i <= getNumParticles() - 1; i++) {
        if (getParticleLife(i) > 0) {

            //target is on
            if (taretgOn == true) {
                seekVec = targetPos - getParticlePosition(i);
                seekDirection = normalize(seekVec);
                seekForce = seekDirection *(targetStrength);
            }
            // flee is on
            if (fleeOn == true) {
                fleeVec = fleePos - getParticlePosition(i);
                fleeDirection = normalize(0.0f-fleeVec);
                fleeForce = fleeDirection *(fleeStrength);
            }
            // Magnet is on
            if (magnetOn == true) {
                magVec = magnetPos - getParticlePosition(i);
                magnetDirection = normalize(magVec);
                if (length(magVec) <= magnetRadius)
                    setParticleVelocity(i, magnetDirection* (absol(getParticleVelocity(i))));
                else
                    magnetForce = (magnetDirection)*((magnetStrength) / (length(magVec) / 100.0f));
            }
            // Repel is on
            if (repelOn == true) {
                repelVec = repelPos - getParticlePosition(i);
                repelDirection = normalize(0.0f-repelVec);
                if (length(repelVec) <= repelRadius)
                    setParticleVelocity(i, repelDirection*(absol(getParticleVelocity(i))));
                else
                    repelForce = repelDirection *(repelStrength) / length(0.0f-repelVec / 100.0f);
            }
            if (gravityOn == true) {
                gravityForce = gravity;
            }
            if (pathOn) {
                // Seek point between steps
                vec3<float> p0, p1, p2, p3;
                p0 = catmullT0;
                p1 = emitterPosition;
                p2 = pathEnd;
                p3 = catmullT1;
                //itereate a seek function at all points on spline
                for (float j = 0.0f; j < 1.0f;)
                {
                    //                      vec3<float> catPoint0 = Math::catmull(p0, p1, p2, p3, i);
                    vec3<float> catPoint = Math::catmull(p0, p1, p2, p3, j += (1 / step));
                    pathVec = catPoint - getParticlePosition(i);
                    pathDirection = normalize(pathVec);


                    pathForce += pathDirection * pathPointStrength;
                }
                setParticleVelocity(i, pathDirection* (absol(getParticleVelocity(i))));
            }

            //Total Force
            vec3<float> totalForce = seekForce + fleeForce + magnetForce + repelForce + gravityForce + pathForce;
			totalForce = 2.0f * totalForce;
            applyForceToParticle(i, totalForce);
        }
    }
}




void ParticleEmitter::applyForceToParticle(unsigned int idx, vec3<float> force)
{
	if (idx >= m_pNumParticles)
	{
		std::cout << "ParticleEmitter::applyForceToParticle ERROR: idx " << idx << "out of range!" << std::endl;
		return;
	}

	m_pParticles[idx].force = force;
}


bool sortByHeight(Particle lhs, Particle rhs) {
//	if (std::isnan(lhs.position.y))
		//        *lhs = glm::vec3(-10000.0f);


//	if (lhs.life < 0)
//		return true;
	return lhs.life > rhs.life;

//	return lhs.position.y < rhs.position.y;
//	return false;
}

void ParticleEmitter::sortParticlesByHeight()
{
	Particle* particle = m_pParticles;
	Particle* particleEnd = particle + m_pNumParticles;
	std::sort(particle, particleEnd, sortByHeight);
}

vec3<float> ParticleEmitter::getParticlePosition(unsigned int idx)
{
	if (idx >= m_pNumParticles)
	{
		std::cout << "ParticleEmitter::getParticlePosition ERROR: idx " << idx << "out of range!" << std::endl;
		return vec3<float>();
	}

	return m_pParticles[idx].position;
}

vec3<float> ParticleEmitter::getParticleVelocity(unsigned int idx)
{
    if (idx >= m_pNumParticles)
    {
        std::cout << "ParticleEmitter::getParticlePosition ERROR: idx " << idx << "out of range!" << std::endl;
        return vec3<float>();
    }

    return m_pParticles[idx].position;
}
vec4<float> ParticleEmitter::getParticleColor(unsigned int idx)
{
    if (idx >= m_pNumParticles)
    {
        std::cout << "ParticleEmitter::getParticlePosition ERROR: idx " << idx << "out of range!" << std::endl;
        return vec4<float>();
    }

    return m_pParticles[idx].colour;
}
void ParticleEmitter::setParticleVelocity(unsigned int idx, vec3<float> newVeloctiy)
{
    if (idx >= m_pNumParticles)
    {
        std::cout << "ParticleEmitter::getParticlePosition ERROR: idx " << idx << "out of range!" << std::endl;
    }

    m_pParticles[idx].velocity = newVeloctiy;
}
void ParticleEmitter::setParticleAcceleration(unsigned int idx, vec3<float> addedAcceleration)
{
    if (idx >= m_pNumParticles)
    {
        std::cout << "ParticleEmitter::getParticlePosition ERROR: idx " << idx << "out of range!" << std::endl;
    }

    m_pParticles[idx].acceleration = addedAcceleration;

}
float ParticleEmitter::getParticleLife(unsigned int idx)
{
    if (idx >= m_pNumParticles)
    {
        std::cout << "ParticleEmitter::getParticlePosition ERROR: idx " << idx << "out of range!" << std::endl;
        return float();
    }
    return m_pParticles[idx].life;
}


