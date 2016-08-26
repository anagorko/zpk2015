// Christos Savvopoulos <savvopoulos@gmail.com>
// Elias Sprengel <blockbattle@webagent.eu>

#include <cstdlib>

#include "bot-starter.h"
#include "bot-parser.h"

using namespace std;

/**
 * Main File, starts the whole process.
**/

int main() {
  BotStarter botStarter;
  BotParser parser(botStarter);
  parser.Run();
}
