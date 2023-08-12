#include "cbase.h"
#include "soundscape.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

CON_COMMAND(soundscape_test, "A command intended for soundscape tests.\nEntering it on the current map kills all existing env_soundscapes and creates a new env_soundscape that plays the soundscape you entered.")
{
	int argCount = args.ArgC();
	if (argCount > 1)
	{
		//Kill all existing env_soundscape on the map
		for (CBaseEntity *pEntity = gEntList.FirstEnt(); pEntity != NULL; pEntity = gEntList.NextEnt(pEntity))
		{
			// Check if the entity is an instance of the "env_soundscape" class
			if (FClassnameIs(pEntity, "env_soundscape"))
			{				
				// Send the "Kill" input for the found env_soundscape
				pEntity->AcceptInput("Kill", NULL, NULL, variant_t(), 0);
			}
		}

		//Restart soundscape_manifest.txt
		//Restart all sounds
		engine->ClientCommand(UTIL_GetCommandClient()->edict(), "soundscape_flush");
		engine->ClientCommand(UTIL_GetCommandClient()->edict(), "snd_restart");

		//Get the name of the soundscape being tested and the player entity
		const char *nameSoundscape = args.Arg(1);
		CBasePlayer *pPlayer = UTIL_GetLocalPlayer();

		//Create new env_soundscape
		CEnvSoundscape *pSoundscape = static_cast<CEnvSoundscape*>(CreateEntityByName("env_soundscape"));
		pSoundscape->SetAbsOrigin(pPlayer->GetAbsOrigin());
		pSoundscape->KeyValue("soundscape", nameSoundscape);
		pSoundscape->KeyValue("radius", "-1");
		pSoundscape->Spawn();

		Msg("Soundscape name: %s\n", nameSoundscape, argCount);
	}
	else
	{
		Warning("Not enough arguments to execute\nExample: soundscape_test d1_trainstation.city");
	}
}