

#include<audiere.h>

audiere::AudioDevicePtr device(audiere::OpenDevice());

audiere::OutputStreamPtr exp1(audiere::OpenSound(device, "sounds//explosion1.wav", false));

audiere::OutputStreamPtr exp2(audiere::OpenSound(device, "sounds//explosion2.wav", false));

audiere::OutputStreamPtr shoot(audiere::OpenSound(device, "sounds//shoot.wav", false));

audiere::OutputStreamPtr selectm(audiere::OpenSound(device, "sounds//select.wav", false));

audiere::OutputStreamPtr menu(audiere::OpenSound(device, "music//menu.mp3", false));

audiere::OutputStreamPtr mapm(audiere::OpenSound(device, "music//map.mp3", false));


void InitSound()
{
	shoot->setVolume(0.2f);
	exp2->setVolume(0.5f);
	exp1->setVolume(0.3f);

	selectm->setVolume(0.5f);

	menu->setRepeat(true);
	mapm->setRepeat(true);
}