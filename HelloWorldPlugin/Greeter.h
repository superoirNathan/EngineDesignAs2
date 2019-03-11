#pragma once
#include "LibSettings.h"
class LIB_API Greeter
{
public:
	float Random(float min, float max);
	
	// Emitter Control
	bool Sort(int id);
	void AddEmitter();
	void DeleteEmitter(int id);
	int EmitterSize();
	void SetEmitterPos(int id, float x, float y, float z);
	void InitializeParticles(int id, int numbOfParticles);
	void UpdateEmitter(int id, float time);

	// Particle INFO
	unsigned int GetNumbOfParticles(int id);
	float* GetParticlePos(int id);
	float* GetParticleLife(int id);
	void DeleteParticlePosXYZ();
	void DeleteParticleLife();


	// Particle Settings
	void EmitterPlaying(int id, bool b);
	void BoxEmissionOn(int id, bool b);
	void BoxEmissionVol(int id, float x, float y, float z);
	void VelocityMinRange(int id, float x1, float y1, float z1);
	void VelocityMaxRange(int id, float x2, float y2, float z2);
	void LifeMinRange(int id, float x1);
	void LifeMaxRange(int id, float x2);
	void SpawnMinRange(int id, float x1);
	void SpawnMaxRange(int id, float x2);

	void DeleteMaxParticle();
	void CreateMaxParticle();
};