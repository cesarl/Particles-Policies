#ifndef					__EMESSAGES_HH__
# define				__EMESSAGES_HH__

typedef enum
  {
    MSG_ACTIVE,		// on/off update()
    MSG_VISIBLE,	// on/off draw()
    MSG_EXITAPP,	// exit app
    NEW_GAME,		// new game
    SCORE		// used for sending score from game scene to gameover scene
  }					e_message;

#endif					// __EMESSAGES_HH__
