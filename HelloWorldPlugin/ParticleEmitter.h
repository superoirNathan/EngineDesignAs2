//Nathan Alphonse 100523109
//100555192 Janarthan Ravikumar

#pragma once

#include "KeyframeController.h"
#include "vec.h"
// Params for each particle
// Note: this is a bare minimum particle structure
// Add any properties you want to control here
struct Particle
{
    // Physics properties
    // Position is where the particle currently is
    // Velocity is the rate of change of position
    // Acceleration is the rate of change of velocity
    // p' = p + v*dt
    // current position is the previous position plus the change in position multiplied by the amount of time passed since we last calculated position
    // v' = v + a*dt
    vec3<float> position;
    vec3<float> velocity;
    vec3<float> acceleration;
    vec3<float> force;
    float mass;

    // Visual Properties
    float size;
    vec4<float> colour;
    // Other properties... 
    // ie. sprite sheet

	float life = -1.0f; // start dead
};

// Emitter is responsible for emitting (creating, dispatching) particles
class ParticleEmitter
{
public:
private:
    unsigned int m_pNumParticles;
    float TotalT;
    Particle* m_pParticles;
	Particle* m_lastAlive;
	unsigned int lastAliveID;
public:
    ParticleEmitter();
    ~ParticleEmitter();


    void initialize(unsigned int numParticles);							// Greeter Needed
	void initializeOther(Particle* m_ptr, unsigned int numParticles);
	void moveM_ptr(Particle* m_ptr);
	Particle* GetMPtr() { return m_pParticles; };
    void freeMemory();

    void update(float dt);												// Greeter Needed
    void draw(); // useless

    void applyForceToParticle(unsigned int idx, vec3<float> force);
	void sortParticlesByHeight();										// Greeter Needed

    //setters and getters for particles
    unsigned int getNumParticles() { return m_pNumParticles; }			// Greeter Needed
    vec3<float> getParticlePosition(unsigned int idx);					// Greeter Needed
    vec3<float> getParticleVelocity(unsigned int idx);
    vec4<float> getParticleColor(unsigned int idx);
    void setParticleVelocity(unsigned int idx, vec3<float> newVelocity);
    void setParticleAcceleration(unsigned int idx, vec3<float> newVelocity);
    float getParticleLife(unsigned int idx);							// Greeter Needed
    void applyForcesToParticleSystem();
    ///// Playback properties
    bool playing;														// Greeter Needed
    //// Update flags
    bool interpolateColour;

    ///// Initial properties for newly spawned particles

    vec3<float> emitterPosition;										// Greeter Needed
    // Box emmiter
    vec3<float> boxWH;													// Greeter Needed
    bool boxOn;															// Greeter Needed
    // Steering Target
    vec3<float> targetPos; // Greeter Needed
    vec3<float> fleePos; // Greeter Needed
    float targetStrength; // Greeter Needed
    float fleeStrength; // Greeter Needed
    bool taretgOn; // Greeter Needed
    bool fleeOn; // Greeter Needed
    // Emitter Gravity
    vec3<float> gravity; // Greeter Needed
    bool gravityOn; // Greeter Needed
    // Emitter Magnet and Repel
    vec3<float> magnetPos; // Greeter Needed
    vec3<float> repelPos;  // Greeter Needed
    float magnetRadius; // Greeter Needed
    float repelRadius; // Greeter Needed
    float magnetStrength; // Greeter Needed
    float repelStrength; // Greeter Needed
    bool magnetOn; // Greeter Needed
    bool repelOn; // Greeter Needed
    // Emitter Path
    bool pathOn; // Greeter Needed
    vec3<float> pathEnd; // Greeter Needed
    // Emitter Duration of Effect
    bool durationRepeat; 
    bool durationOn;
    vec2<float> durationOnX_OffY;
    // Emitter Strings
  //  std::string emitterName;
    // Storing ranges for each property so each particle has some randomness
    vec3<float> velocity0;												// Greeter Needed
    vec3<float> velocity1;												// Greeter Needed
    // these properties are single floats, so we can pack the min and max into a vec2<float>, just data!
    vec2<float> lifeRange;												// Greeter Needed
//    vec2<float> sizeRange; 
    vec2<float> massRange; // Greeter Needed
    vec2<float> spawnRange;												// Greeter Needed
    vec4<float> colour0; 
    vec4<float> colour1;
    // Keyframes
    KeyframeController<vec3<float>> keyframeController; // holds and updates our keyframe animation
    vec3<float> catmullT0; // Greeter Needed
    vec3<float> catmullT1; // Greeter Needed
    float pathPointStrength; // Greeter Needed
    float step;
    bool showEmitter;
    //reset value
    float elapsedTime;
    vec3<float> interpolatedPosition;
    // other
    //bool circleSquare;
    // ... what would be a better way of doing this?
    // Make a keyframe controller for each property! this gives you max control!!
    // See the KeyframeController class
    // (this is what full out particle editors do, ie popcorn fx)
    //not in READER or Writer
    // Check to see if all part dead.
    bool checkAllPartDead();
};