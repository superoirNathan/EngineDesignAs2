#include "Greeter.h"
#include "StackObj.h"
#include "ParticleEmitter.h"

#define MAX_Particles 1000
unsigned int particlesAllocated = 0;
// 1 min particles max

float* particlePosXYZ = nullptr; // match pos to object in unity
float* particleLife = nullptr; // match alpha value of canvas renderer with unity obj 
Particle* totalParticles = nullptr; // allocate all possible particle space
std::vector<ParticleEmitter> emitters;






float Greeter::Random(float min, float max)
{	
	int i = (rand() % (int)max - min);
	return 	((float)((int)rand() % 101)) / 100.0f;//linearRand(0, 1);// Fix this
}
bool Greeter::Sort(int id) {
	if (id >= 0 && id <= emitters.size())
		emitters[id].sortParticlesByHeight();
	else
		return true; // if true, out of bounds
	return false;
}

void Greeter::AddEmitter()
{
	ParticleEmitter* temp = new ParticleEmitter();
	emitters.push_back(*temp);
}
void Greeter::DeleteEmitter(int id)
{
//	emitters[id].freeMemory();

	particlesAllocated -= emitters[id].getNumParticles();

	// if more then 1 emitter or not last emitter
	if (emitters.size() > 1 && id < emitters.size()-1) {
		Particle* oldPtr = emitters[id].GetMPtr();
		emitters.erase(emitters.begin() + id); // delete old area
		emitters[id].moveM_ptr(oldPtr); // take the next id and move it there
		// if still more then 1 emitter and not last emitter
		if (emitters.size() > 1 && id < emitters.size() - 1) {
			// Grab next emitters and replace it in the old spce // NOTE: should skip for loop if out of bounds or no other emitters
			for (int i = id + 1; i < emitters.size(); i++) {
				Particle* oldMovedPtr = emitters[i - 1].GetMPtr() + emitters[i - 1].getNumParticles(); // just to be safe, get previous head and move to end
				emitters[i].moveM_ptr(oldMovedPtr);
			}
		}

	}
	else {
		emitters.erase(emitters.begin() + id); // delete old area
	}
}

int Greeter::EmitterSize()
{
	return emitters.size();
}

void Greeter::SetEmitterPos(int id, float x, float y, float z)
{
	emitters[id].emitterPosition = vec3<float>(x, y, z);
}

void Greeter::InitializeParticles(int id, int numbOfParticles)
{
//	emitters[id].initialize(numbOfParticles);

	if (MAX_Particles > (particlesAllocated + numbOfParticles)) {
		emitters[id].initializeOther(totalParticles + particlesAllocated, numbOfParticles);
		particlesAllocated += numbOfParticles;
	}
	else {
	}
}

void Greeter::UpdateEmitter(int id, float time)
{
	emitters[id].update(time);
}

unsigned int Greeter::GetNumbOfParticles(int id)
{
	return emitters[id].getNumParticles();
}
float * Greeter::GetParticlePos(int id)
{
	if (particlePosXYZ != nullptr) {
		delete[] particlePosXYZ;
		particlePosXYZ = nullptr;
	}
	particlePosXYZ = new float[emitters[id].getNumParticles() * 3];

	vec3<float> tempPos;
	int d = 0;
	for (unsigned int i = 0; i < emitters[id].getNumParticles(); i++) 
	{
		tempPos = emitters[id].getParticlePosition(i);
		particlePosXYZ[d] = tempPos.x;
		d++;
		particlePosXYZ[d] = tempPos.y;
		d++;
		particlePosXYZ[d] = tempPos.z;
		d++;
	}
	return particlePosXYZ;
}
float * Greeter::GetParticleLife(int id)
{
	if (particleLife!= nullptr) 
	{
		delete[] particleLife;
		particleLife = nullptr;
	}
	particleLife = new float[emitters[id].getNumParticles()];
	int d = 0;
	for (unsigned int i = 0; i < emitters[id].getNumParticles(); i++) {
		particleLife[i] = emitters[id].getParticleLife(i);
	}
	return particleLife;
}
void Greeter::DeleteParticlePosXYZ()
{
	if (particlePosXYZ != nullptr)
	{
		delete[] particlePosXYZ;
		particlePosXYZ = nullptr;
	}
}

void Greeter::DeleteParticleLife() // deletes array of last sent particle life
{
	if (particleLife != nullptr) 
	{
		delete[] particleLife;
		particleLife = nullptr;
	}

}

void Greeter::EmitterPlaying(int id, bool b)
{
	emitters[id].playing = b;
}

void Greeter::BoxEmissionOn(int id, bool b)
{
	emitters[id].boxOn = b;
}

void Greeter::BoxEmissionVol(int id, float x, float y, float z)
{
	emitters[id].boxWH = vec3<float>(x, y, z);
}

void Greeter::VelocityMinRange(int id, float x1, float y1, float z1)
{
	emitters[id].velocity0 = vec3<float>(x1, y1, z1);
}

void Greeter::VelocityMaxRange(int id, float x2, float y2, float z2)
{
	emitters[id].velocity1 = vec3<float>(x2, y2, z2);
}

void Greeter::LifeMinRange(int id, float x1)
{
	emitters[id].lifeRange.x = x1;
}

void Greeter::LifeMaxRange(int id, float x2)
{
	emitters[id].lifeRange.y = x2;
}

void Greeter::SpawnMinRange(int id, float x1)
{
	emitters[id].spawnRange.x = x1;
}

void Greeter::SpawnMaxRange(int id, float x2)
{
	emitters[id].spawnRange.y = x2;
}

void Greeter::DeleteMaxParticle()
{
	if (totalParticles != nullptr)
		delete[] totalParticles;
	totalParticles = nullptr;

	if (emitters.size() > 0) {
			emitters.clear();
	}
	particlesAllocated = 0;
}

void Greeter::CreateMaxParticle()
{
	if (totalParticles != nullptr)
		delete[] totalParticles;
	else
		totalParticles = new Particle[MAX_Particles];
	particlesAllocated = 0;
}
