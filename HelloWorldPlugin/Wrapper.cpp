#include "Greeter.h"
#include "Wrapper.h"

Greeter greeter;


float Random(float min, float max)
{
	return greeter.Random(min, max);
}

 bool Sort(int id)
{
	return greeter.Sort(id);
}

 void AddEmitter()
{
	return  greeter.AddEmitter();
}

 void DeleteEmitter(int id)
{
	return  greeter.DeleteEmitter(id);
}

 int EmitterSize()
{
	return  greeter.EmitterSize();
}

 void SetEmitterPos(int id, float x, float y, float z)
{
	 return  greeter.SetEmitterPos(id, x, y, z);
}

 void InitializeParticles(int id, int numbOfParticles)
{
	 return  greeter.InitializeParticles(id, numbOfParticles);
}

 void UpdateEmitter(int id, float time)
{
	 return  greeter.UpdateEmitter(id, time);
}

 unsigned int GetNumbOfParticles(int id)
{
	 return  greeter.GetNumbOfParticles(id);
}

 float * GetParticlePos(int id)
{
	 return greeter.GetParticlePos(id);
}

 float * GetParticleLife(int id)
{
	 return greeter.GetParticleLife(id);
}

 void DeleteParticlePosXYZ() {
	 greeter.DeleteParticlePosXYZ();
 }

  void DeleteParticleLife()
 {
	  return  greeter.DeleteParticleLife();
 }

  void EmitterPlaying(int id, bool b)
 {
	  return  greeter.EmitterPlaying(id, b);
 }

  void VelocityMinRange(int id, float x1, float y1, float z1)
 {
	  return  greeter.VelocityMinRange(id, x1, y1, z1);
 }

  void VelocityMaxRange(int id, float x2, float y2, float z2)
 {
	  return  greeter.VelocityMaxRange(id, x2, y2, z2);
 }

  void LifeMinRange(int id, float x1)
 {
	  return  greeter.LifeMinRange(id, x1);
 }

  void LifeMaxRange(int id, float x2)
 {
	  return  greeter.LifeMaxRange(id, x2);
 }

  void SpawnMinRange(int id, float x1)
 {
	  return  greeter.SpawnMinRange(id, x1);
 }

  void SpawnMaxRange(int id, float x2)
 {
	  return  greeter.SpawnMaxRange(id, x2);
 }

  void BoxEmissionOn(int id, bool b)
 {
	  return  greeter.BoxEmissionOn(id, b);
 }

  void BoxEmissionVol(int id, float x, float y, float z)
 {
	  return  greeter.BoxEmissionVol(id, x, y, z);
 }
  // Delete This for no memory management
  void DeleteMaxParticle() {
	  greeter.DeleteMaxParticle();
  }
  void CreateMaxParticle() {
	  greeter.CreateMaxParticle();
  }
