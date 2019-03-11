#pragma once
#include "LibSettings.h"

#ifdef __cplusplus
extern "C"
{
#endif

	LIB_API float Random(float min, float max);

	// Emitter Control
	LIB_API bool Sort(int id);
	LIB_API void AddEmitter();
	LIB_API void DeleteEmitter(int id);
	LIB_API int EmitterSize();
	LIB_API void SetEmitterPos(int id, float x, float y, float z);
	LIB_API void InitializeParticles(int id, int numbOfParticles);
	LIB_API void UpdateEmitter(int id, float time);

	// Particle INFO
	LIB_API unsigned int GetNumbOfParticles(int id);
	LIB_API float* GetParticlePos(int id); // array size is numb of Particles * 3
	LIB_API float* GetParticleLife(int id); // array size is numb of Particles
	LIB_API void DeleteParticlePosXYZ();
	LIB_API void DeleteParticleLife();

	// Particle Settings
	LIB_API void EmitterPlaying(int id, bool b);
	LIB_API void VelocityMinRange(int id, float x1, float y1, float z1);
	LIB_API void VelocityMaxRange(int id, float x2, float y2, float z2);
	LIB_API void LifeMinRange(int id, float x1);
	LIB_API void LifeMaxRange(int id, float x2);
	LIB_API void SpawnMinRange(int id, float x1);
	LIB_API void SpawnMaxRange(int id, float x2);
	LIB_API void BoxEmissionOn(int id, bool b);
	LIB_API void BoxEmissionVol(int id, float x, float y, float z);
	LIB_API void DeleteMaxParticle();
	LIB_API void CreateMaxParticle();
#ifdef __cplusplus
}
#endif