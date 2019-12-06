/// <summary>
/// simple game loop for SFML[2.5.1]
/// 
/// @author Jay McDonald
/// @date December 2019
/// 
/// Estimated time 16 hrs
/// Actual time
///				When :	Duration(min)
/// session 1: 4 hrs
/// session 2: 2 hrs
/// session 3: 6 hrs
/// session 4: 3 hrs
/// session 5: 5 hrs
/// session 6: 3 hrs
/// </summary>

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 


#include "Game.h"

/// <summary>
/// main enrtry point
/// </summary>
/// <returns>success or failure</returns>
int main()
{
	srand(time(nullptr));
	Game game;
	game.run();

	return 1; // success
}