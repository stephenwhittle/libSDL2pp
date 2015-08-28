/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
  Copyright (C) 2015 Dmitry Marakasov <amdmi3@amdmi3.ru>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDLMixer.hh>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Chunk.hh>

using namespace SDL2pp;

int main() try {
	SDL sdl(SDL_INIT_AUDIO);
	SDLMixer mixerlib(MIX_INIT_OGG);
	Mixer mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);

	Chunk chunk(TESTDATA_DIR "/test.ogg");

	int chan;

	mixer.ChannelFinished([](int channel){
			std::cerr << "Channel " << channel << " finished playback" << std::endl;
		});

	// Fade in
	chan = mixer.FadeInChannel(-1, chunk, 0, 1000);
	std::cerr << "Fading sound in on channel " << chan << "\n";

	SDL_Delay(2000);

	// Mix 3 sounds
	chan = mixer.PlayChannel(-1, chunk);
	std::cerr << "Playing sound on channel " << chan << "\n";

	SDL_Delay(250);

	chan = mixer.PlayChannel(-1, chunk);
	std::cerr << "Playing sound on channel " << chan << "\n";

	SDL_Delay(250);

	chan = mixer.PlayChannel(-1, chunk);
	std::cerr << "Playing sound on channel " << chan << "\n";

	SDL_Delay(2000);

	// Fade out
	chan = mixer.PlayChannel(-1, chunk);
	std::cerr << "Fading out sound on channel " << chan << "\n";
	mixer.FadeOutChannel(chan, 2000);

	SDL_Delay(2000);

	// Make sure no chunks are being played before destroying Chunk
	mixer.HaltChannel();

	return 0;
} catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << std::endl;
	return 1;
}
